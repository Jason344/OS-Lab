# 模拟进程调度执行
> 要求和假设

* 假设进程的状态分为**执行**和**就绪**两种
* 每个进程以其PCB为代表
* 以**链表**的方式组织，分为三个队列`freeQueue` `readyQueue` `runningQueue`
* 进程的调度采用**随机**的方式

> 操作流程

1. 输入进程数量以及每个进程需要的运行的时间,在`freeQueue`中生成节点
2. 从`freeQueue`中取出节点，插入`readyQueue`来创建进程
3. 随机地从`readyQueue`选择一个节点，插入`runningQueue`的队尾来进入运行状态
4. 若`runningQueue`中有2个节点，则将第一个节点的剩余运行时间减2，若结果大于0，将其插入`readyQueue`队尾，若结果小于等于0，将其插入`freeQueue`队尾
5. 打印信息示例
6. 重复3~6直至`readyQueue`为空


>思路描述

1. 定义一个`PCB`的结构体，包含各种程序运行的信息
2. 定义一个`Queue`的结构体来管理各种队列，包含成员`phead` `ptail` `num`
3. 为PCB编写各种操作函数，包括`run` `printPCB` `createPCB`
4. 为`Queue`编写各种操作函数，包括`append` `isEmpty` `isSingle` `popFirst` `popRandom` `printQueue` `iniQueue`
5. 编写`printInfo`来打印信息示例
6. 按照操作流程的步骤调用已写好的函数完成程序


>问题说明

1. 声明的结构体使用时忘加struct
2. 混淆了==与=
3. 指针的使用，本来不想向`isEmpty` `isSingle` `printQueue`传入指针的，因为这些函数没必要修改queue的内容，就没必要给他们指针；但这样想在  `popFirst`中调用这些函数就不太方便，因为`popFirst`中只有指针。还是都传指针进去好了，虽然可能导致可能的修改危险。
4. rand函数的使用
```
srand(time(NULL));
int r = rand();
```
 这是我网上看到的随机数生成代码，直接可以生成随机数，但当我把他封装在函数里的时候，每次调用都会生成同样的数字。因此我就把每次生成的结果保留，作为下一次的种子，随机性比原来更好，但总感觉还是有待完善
 ```
 static int pre = 0;

 if(pre==0)
	 srand(time(NULL));
 else srand(pre);
 pre = rand();
 ```

>体会



> 查阅资料

1. 下载了kernel 4.7.5,并找出task_structd的定义
```
struct task_struct {
	u64 curr_chain_key;
	int lockdep_depth;
	unsigned int lockdep_recursion;
	struct held_lock held_locks[MAX_LOCK_DEPTH];
	gfp_t lockdep_reclaim_gfp;
	int pid;
	char comm[17];
};
```
2.

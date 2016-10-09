#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#define free 0
#define ready 1
#define running 2
#define ts 2 /* time slice */
#define false 0
#define true 1
#define enough 1
#define lack 0
struct PCB {
    int pid;
    int pstate;
    char pname[20];
    int ptime;
    struct PCB *pnext;
};
struct Queue{
	struct PCB* phead;
	struct PCB* ptail;
	int num;
};
typedef int bool;
int run(struct PCB*);
void printPCB(struct PCB*);
struct PCB* createPCB(int);
void changeState(struct PCB*,int);
void changeId(struct PCB*,int);
void append(struct Queue*,struct PCB*);
void printQueue(struct Queue*);
void iniQueue(struct Queue*);
bool isEmpty(struct Queue*);
bool isSingle(struct Queue*);
struct PCB* popFirst(struct Queue*);
struct PCB* popRandom(struct Queue*);
int getRandomNum();
void createProcess(struct Queue*,struct Queue*,int time);
void printInfo(struct Queue*,struct Queue*,struct Queue*);
bool isTimeEnough(struct Queue*);
void schedule(struct Queue*,struct Queue*,struct Queue*);
int cnt = 0;
int main(){
	struct Queue freeQueue,readyQueue,runningQueue;
	struct PCB* p;
	int i,n,required;
	
	iniQueue(&freeQueue);
	iniQueue(&readyQueue);
	iniQueue(&runningQueue);

	createProcess(&freeQueue,&readyQueue,10);
	createProcess(&freeQueue,&readyQueue,20);
	createProcess(&freeQueue,&readyQueue,20);
	createProcess(&freeQueue,&readyQueue,11);
	createProcess(&freeQueue,&readyQueue,21);
	createProcess(&freeQueue,&readyQueue,43);
	createProcess(&freeQueue,&readyQueue,14);
	createProcess(&freeQueue,&readyQueue,26);

/*
	printf("How many process do you want to create?");
	scanf("%d",&n);
	for(i=0;i<n;i++){
		printf("Required time for process %d:",i);
		scanf("%d",&required);
		createProcess(&freeQueue,&readyQueue,required);
	}
*/ 
	while(!isEmpty(&runningQueue)||!isEmpty(&readyQueue)){
		printf("*******************\n");
		schedule(&freeQueue,&readyQueue,&runningQueue);
/* 
		printf("\n\nfree:");
		printQueue(&freeQueue);
		printf("\nready:");
		printQueue(&readyQueue);
		printf("\nrunning:");
		printQueue(&runningQueue);
		printf("\n\n");
*/
		printf("*******************\n");
	}
}

//create PCB with given time,and append to freeQueue
struct PCB* createPCB(int time){
	struct PCB* newPCB = (struct PCB*)malloc(sizeof(struct PCB));
	
	newPCB->pid = cnt++;
	newPCB->pstate = ready;
	strcpy(newPCB->pname,"Unknow");
	newPCB->ptime = time;
	newPCB->pnext = NULL;
	printPCB(newPCB);
	return newPCB;
}
//run pcb and decline time
int run(struct PCB* pcb){
	pcb->ptime -=2;
	return pcb->ptime;
}
//print PCB
void printPCB(struct PCB* pcb){
	if(pcb!=NULL)
		printf("id:%d\tstate:%d\tname:%s\ttime:%d\n",pcb->pid,pcb->pstate,pcb->pname,pcb->ptime);
}
//change the state of PCB
void changeState(struct PCB* pcb,int state){
	pcb->pstate = state;
}
void changeId(struct PCB* pcb ,int id){
	pcb->pid = id;
}

//append something to the queue
void append(struct Queue* queue,struct PCB* pcb){
	if(pcb != NULL){
		if(queue->phead==NULL){
			queue->phead = pcb;
			queue->ptail = pcb;
			pcb->pnext = NULL;
			queue->num++;
		}else{
			pcb->pnext = NULL;
			queue->ptail->pnext = pcb;
			queue->ptail = pcb;
			queue->num++;
		}
	}
}
//print queue from front to the end
//输出格式有待优化 
void printQueue(struct Queue* queue){
	struct PCB* p = queue->phead;

	if(isEmpty(queue)){
		printf("It's empty");
	}else{
		while(p != NULL){
			printf("P%d\t",p->pid);
			p = p->pnext;
		}
	}
}
//init Queue with some default value
void iniQueue(struct Queue* queue){
	queue->phead = NULL;
	queue->ptail = NULL;
	queue->num = 0;
}

//figure out whether the queue is empty
bool isEmpty(struct Queue* queue){
	if(queue->num==0)
		return true;
	else return false;
}

//figure out whether the queue only have one element
bool isSingle(struct Queue* queue){
	if(queue->num==1)
		return true;
	else return false;
}
//pop the first element of the queue
struct PCB* popFirst(struct Queue* queue){
	struct PCB* result = NULL;
	if(isEmpty(queue)){
		return result;
	}else if(isSingle(queue)){
		result = queue->phead;
		queue->num--;
		queue->phead = queue->ptail = NULL;
		return result;
	}else{
		result = queue->phead; 
		queue->phead = result->pnext;
		queue->num--;
		return result;
	}
}
//pop  element of the queue randomly
struct PCB* popRandom(struct Queue* queue){
	int n = queue->num;
	int r = (getRandomNum())%(n>0?n:1);
	int i = 0;
	struct PCB* result = NULL;
	struct PCB* p = NULL;
	if(isEmpty(queue)){
		return result;
	}else if(r == 0){
		return popFirst(queue);
	}else{
		queue->num--;
		p = queue->phead;
		for(i=1;i<r;i++){
			p = p->pnext;
		}
		result = p->pnext;
		p->pnext = result->pnext;
		if(p->pnext==NULL)
			queue->ptail = p;
		return result;
	}
}
//get a integer randomly
int getRandomNum(){
	static int pre = 0;
	
	if(pre==0)
		srand(time(NULL));
	else srand(pre);
	pre = rand();
   	return pre;
}
//create process 
void createProcess(struct Queue* freeQueue,struct Queue* readyQueue,int time){
	struct PCB* pcb= NULL;
	if(isEmpty(freeQueue)){
		append(readyQueue,createPCB(time));
	}else{
		pcb = popFirst(freeQueue);
		changeState(pcb,ready);
		changeId(pcb,cnt++);
		append(readyQueue,pcb);
	}
}
//figure out whether the time is enough
bool isTimeEnough(struct Queue* runnningQueue){
	struct PCB* ran = runnningQueue->phead;
	
	if(ran!=NULL){
		if(ran->ptime-2>0){
			return lack;
		}else return enough;
	}else return -1;
}
//print infomation when runningQueue have two element
void printInfo(struct Queue* freeQueue,struct Queue* readyQueue,struct Queue* runningQueue){
	struct PCB* ran = runnningQueue->phead;
	struct PCB* run = runnningQueue->ptail;
	bool time = isTimeEnough(runningQueue);
	if(isSingle(runningQueue)){
		if(ran->pstate == ready){
			printf("Sched: P%d(Ready -> Running)\n",run->pid);
		}
		else {
			printf("run again\n");
			printf("Sched: P%d(Running -> Running)\n",run->pid);
		}
	}else if(time == enough){
		printf("Sched: P%d(Running -> Free), P%d(Ready -> Running)\n",ran->pid,run->pid);
	}else{
		printf("Sched: P%d(Running -> Ready), P%d(Ready -> Running)\n",ran->pid,run->pid);
		
	}
	printf("Running: P%d\n",run->pid);
	printf("Ready: ");
	printQueue(readyQueue);
	if(time == lack){
		printf("\tp%d\n",ran->pid);
	}
	printf("\n");
		
}
//change the running process
void schedule(struct Queue* freeQueue,struct Queue* readyQueue,struct Queue* runningQueue){
	struct PCB* toRun = popRandom(readyQueue); 
	struct PCB* ran = NULL;
	bool time = isTimeEnough(runningQueue);
	

	if(isEmpty(readyQueue)&&isEmpty(runningQueue)){
		printf("nothing to run");
	}else if(isEmpty(readyQueue)&&isSingle(runningQueue)){
		append(runningQueue,toRun);
		printInfo(freeQueue,readyQueue,runningQueue);
		ran = popFirst(runningQueue);
		run(ran);
		changeState(ran,running);
		if(time == enough){
			append(freeQueue,ran);
		}else{
			append(runningQueue,ran); 
		}
	}else {		
		append(runningQueue,toRun);
		printInfo(freeQueue,readyQueue,runningQueue);
		if(!isSingle(runningQueue)){
			ran = popFirst(runningQueue);
			run(ran);
			if(time == enough){
				changeState(ran,free);
				append(freeQueue,ran);
			}else{
				changeState(ran,ready);
				append(readyQueue,ran);
			}
		}
	}
}

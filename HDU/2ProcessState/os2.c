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
void createPCB(struct Queue*,int);
void append(struct Queue*,struct PCB*);
void printQueue(struct Queue*);
void iniQueue(struct Queue*);
bool isEmpty(struct Queue*);
bool isSingle(struct Queue*);
struct PCB* popFirst(struct Queue*);
struct PCB* popRandom(struct Queue*);
int getRandomNum();
int main(){
	struct Queue freeQueue,readyQueue,runningQueue;
	struct PCB* p;
	int i;
	
	iniQueue(&freeQueue);
	iniQueue(&readyQueue);
	iniQueue(&runningQueue);
	createPCB(&freeQueue,3);
	createPCB(&freeQueue,2);
	createPCB(&freeQueue,5);
	createPCB(&freeQueue,1);
	createPCB(&freeQueue,2);
	createPCB(&freeQueue,3);
	createPCB(&freeQueue,4);
	createPCB(&freeQueue,12);
	createPCB(&freeQueue,11);
	createPCB(&freeQueue,9);
	createPCB(&freeQueue,8);
	for(i=0;i<15;i++){
		if((p=popRandom(&freeQueue))!=NULL){
			printf("P%d\n",p->pid);
		}else{
			printf("empty!\n");
		}	
	}
	
	
}

//create PCB with given time,and append to freeQueue
//后期要修改直接中freeQueue中取 
void createPCB(struct Queue* queue,int time){
	static int cnt = 0;
	struct PCB* newPCB = (struct PCB*)malloc(sizeof(struct PCB));
	newPCB->pid = cnt++;
	newPCB->pstate = free;
	strcpy(newPCB->pname,"Unknow");
	newPCB->ptime = time;
	newPCB->pnext = NULL;
	printPCB(newPCB);
	append(queue,newPCB);
}
//run pcb and decline time
int run(struct PCB* pcb){
	pcb->ptime -=2;
	return pcb->ptime;
}
//print PCB
void printPCB(struct PCB* pcb){
	printf("id:%d\tstate:%d\tname:%s\ttime:%d\n",pcb->pid,pcb->pstate,pcb->pname,pcb->ptime);
}


//append something to the queue
void append(struct Queue* queue,struct PCB* pcb){
	if(queue->phead==NULL){
		queue->phead = pcb;
		queue->ptail = pcb;
		pcb->pnext = NULL;
	}else{
		pcb->pnext = NULL;
		queue->ptail->pnext = pcb;
		queue->ptail = pcb;
	}
	queue->num++;
}
//print queue from front to the end
//输出格式有待优化 
void printQueue(struct Queue* queue){
	struct PCB* p = queue->phead;

	if(isEmpty(queue)){
		printf("It's empty\n");
	}else{
		while(p != NULL){
			printf("P%d\t",p->pid);
			p = p->pnext;
		}
		printf("\n");	
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
	int cnt = 0,i = 0;
	struct PCB* result = NULL;
	struct PCB* p = NULL;
	if(isEmpty(queue)){
		return result;
	}else if(r == 0){
		return popFirst(queue);
	}else{
		queue->num--;
		p = queue->phead;
		for(i=1;i<cnt;i++){
			p = p->pnext;
		}
		result = p->pnext;
		p->pnext = result->pnext;
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

#include<stdio.h>
#include<string.h>
#define free 0
#define ready 1
#define running 2
#define ts 2 /* time slice */

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
int run(struct PCB*);
void printPCB(struct PCB*);
void createPCB(struct Queue*,int);

void append(struct Queue*,struct PCB*);
void printQueue(struct Queue*);
void iniQueue(struct Queue*);
int main(){
	struct Queue freeQueue,readyQueue,runningQueue;

	iniQueue(&freeQueue);
	iniQueue(&readyQueue);
	iniQueue(&runningQueue);
	createPCB(&freeQueue,3);
	createPCB(&freeQueue,2);
//	printQueue(&freeQueue);
}


//create PCB with given time,and append to freeQueue
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
	printQueue(queue);
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
void printQueue(struct Queue* queue){
	struct PCB* p = queue->phead;

	while(p != NULL){
		printf("P%d\t",p->pid);
		p = p->pnext;
	}
	printf("\n");
}
//init Queue with some default value
void iniQueue(struct Queue* queue){
	queue->phead = NULL;
	queue->ptail = NULL;
	queue->num = 0;
}


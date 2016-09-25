#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define ROAD "D:\\SourceCode\\os\\os1\\data.txt"
struct Student{
    char sno[20];
    char sname[20];
    int sage;
    char sclass[20];
    struct Student* next;
};
struct StudentList{
    struct Student* phead ;
    struct Student* ptail ;
}sList;
void insert(struct Student* student);
struct Student* find(char* sno);
void update(struct Student* student);
void erase(char* sno);
struct Student* createStudent(char* sno,char* sname,int sage,char* sclass);
void printStudent(struct Student* student);
int init();
void printList();

int main(){
	struct Student* p = NULL;
    char sno[20],sname[20],sclass[20];
    int sage;
    init();
    //Test find
    /*
    while(scanf("%s",sno)!=EOF){

	p = find(sno);
	printStudent(p);

    }*/
    //Test update
    /*
    printf("Please Enter some information about student:\n");
    printf("(sno sname sage sclass)");
    scanf("%s %s %d %s",sno,sname,&sage,sclass);
    p = createStudent(sno,sname,sage,sclass);
	update(p);
	p = find(sno);
	printStudent(p);
	*/
	//Test delete
	/*
    p = find("14051309");
    printStudent(p);
    erase("14051309");
    p = find("14051309");
    printStudent(p);
    */
    //Test printList
    //printList();
}


void insert(struct Student* student){

	if(sList.phead == NULL){
		sList.phead = student;
		sList.ptail = student;
	}else{
		sList.ptail->next = student;
		sList.ptail = student;
		sList.ptail->next = NULL;
	}
}
struct Student* find(char* sno){
	/*
	if(sList.phead == NULL)
	   return NULL;
    struct Student* ahead = sList.phead->next;
    struct Student* behind = sList.phead;

    if(strcmp(sno,behind->sno)==0){
    	return behind;
    }
    while(ahead!=NULL && strcmp(sno,ahead->sno)!=0){
        behind = ahead;
        ahead = ahead->next;
    }
    if(ahead!=NULL && strcmp(sno,ahead->sno)==0){
        return ahead;
    }
    return NULL;*/
    struct Student* p = sList.phead;
    while(p!=NULL){
    	if(strcmp(sno,p->sno)==0){
	    	return p;
	    }
    }
    return NULL;
}
void update(struct Student* student){
    struct Student* target = find(student->sno);
    strcpy(target->sname , student->sname);
    target->sage = student->sage;
    strcpy(target->sclass , student->sclass);
}
void erase(char* sno){
    struct Student* p = sList.phead;
    struct Student* temp = find(sno);
    if(temp == sList.phead){
    	sList.phead = sList.phead->next;
    	free(temp);
    	return ;
    }
    while(p->next!=temp){
    	p = p->next;
    }
    p->next = p->next->next;
    free(temp);
    return ;
}
struct Student* createStudent(char* sno,char* sname,int sage,char* sclass){
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    strcpy(newStudent->sno,sno);
    strcpy(newStudent->sname,sname);
    newStudent->sage = sage;
    strcpy(newStudent->sclass , sclass);
    newStudent->next = NULL;
    return newStudent;
}
void printStudent(struct Student* student){
	if(student!= NULL)
    	printf("sno:%s\tsname:%s\tsage:%d\t\tsclass%s\n",student->sno,student->sname,student->sage,student->sclass);
	else
		printf("NULL\n");
}
int init(){
	FILE *fp;
    char sno[20],sname[20],sclass[20];
    int sage;
    sList.phead = sList.phead =  NULL;
    struct Student* p = NULL;
	fp =fopen(ROAD,"r");
	if(fp==NULL)
	{
		puts("Can't find the file");
		return -1;
	}
	while(!feof(fp))
	{
	     fscanf(fp,"%s %s %d %s",sno,sname,&sage,sclass);
         p = createStudent(sno,sname,sage,sclass);
         insert(p);
	}
	fclose(fp);
	return 1;
}

void printList(){
	struct Student* p = sList.phead;

	while(p!=NULL){
		printStudent(p);
		p = p->next;
	}
	return ;
}

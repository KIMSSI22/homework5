#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4  // 큐의 크기

typedef char element;  //element는 char
typedef struct {  //QueueType 구조체
	element queue[MAX_QUEUE_SIZE];  //큐 배열
	int front, rear;
}QueueType;

//함수 선언
QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();


int main(void)
{
    printf("김민서 2022040010\n");
	QueueType *cQ = createQueue();  //큐 생성
	element data;

	char command;

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

        //command 값에 따른 케이스
		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ,&data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue()  //큐 생성 
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));  //QueueType 구조체 크기만큼 동적 메모리를 할당
	cQ->front = 0;  //큐의 front 초기화
	cQ->rear = 0;  //큐의 rear 초기화
	return cQ;
}

int freeQueue(QueueType *cQ)  //동적 할당된 큐를 해제 
{
    if(cQ == NULL) return 1;
    free(cQ);
    return 1;
}

element getElement()  //큐에 삽입할 데이터 입력
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


int isEmpty(QueueType *cQ)  //큐 비어있는지 확인
{
	if (cQ->front == cQ->rear){  //값이 같으면 비었다는 뜻
		printf("Circular Queue is empty!");
		return 1;
	}
	else return 0;
}

int isFull(QueueType *cQ)  //큐 채워진지 확인
{
	if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) {  //rear에 1더하고 크기만큼 나눈게 front와 같으면 찼다는 뜻
		printf(" Circular Queue is full!");
		return 1;
	}
	else return 0;
}

void enQueue(QueueType *cQ, element item)  //큐에 데이터 삽입
{
	if(isFull(cQ)) return;
	else {
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;
		cQ->queue[cQ->rear] = item;
	}
}

void deQueue(QueueType *cQ, element *item)  //큐에 데이터 제거
{
	if(isEmpty(cQ)) return;
	else {
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE;
		*item = cQ->queue[cQ->front];
		return;
	}
}


void printQ(QueueType *cQ)  //큐 출력
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;  //처음과
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;  //마지막 찾아줌

	printf("Circular Queue : [");

	i = first;
	while(i != last){  //last가 될때까지 배열에 있는 큐 출력
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)  //디버그 출력
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	//printQ(cQ);
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}
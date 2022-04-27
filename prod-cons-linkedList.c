#include <stdio.h>
#include <pthread.h>
#include "/home/dwseo/Course/SP/hw7/linkedlist.h"
#include <stdlib.h>
#include <unistd.h>

void *producer(void*);
void *consumer(void*);
#define MAX_BUF 100
//shared variables


void ListInit(struct LinkedList* plist){

   plist->numOfItems = 0;
   plist->head = NULL;
   plist->tail = NULL;
}

int isEmpty(struct LinkedList* plist){

	if(plist->numOfItems == 0){
		return TRUE;
	} else {
		return FALSE;
	}
}

int isFull(struct LinkedList* plist){

	if(plist->numOfItems == MAX_ITEM){
		return TRUE;
	} else {
		return FALSE;
	}
}


void insertItem(struct LinkedList* plist, int data) {
   struct Node * newNode = (struct Node*)malloc(sizeof(struct Node));
      newNode->data = data;
      newNode->next = NULL;

   if ( plist->head == NULL ) {
      plist->head = newNode;
      plist->tail = newNode;
   } else {
      plist->tail->next = newNode;
      plist->tail = newNode;
   }

   (plist->numOfItems)++;
}

int getItem(struct LinkedList* plist){

	struct Node* tmpNode;
	int ret;
	
	ret = plist->head->data;

	tmpNode = plist->head;
	plist->head = plist->head->next;

	free(tmpNode);
	(plist->numOfItems)--;

	return ret;
}

void freeAllNode(struct LinkedList* plist) {

	struct Node* tmpNode;
	tmpNode = plist->head;

	while(tmpNode != NULL){
		plist->head = plist->head->next;
		free(tmpNode);
		tmpNode = plist->head;

		(plist->numOfItems)--;
	}
}



//int buffer[MAX_BUF];
int count = 0;
int in = -1, out = -1;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buffer_has_space = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_has_data = PTHREAD_COND_INITIALIZER;

struct LinkedList buffer; //define buffer size 100


int main(void)
{ 	

	ListInit(&buffer); //define buffer size 100buffer);
	
	int i; 
	pthread_t threads[2];
	pthread_create (&threads[0], NULL, producer, NULL);
	pthread_create (&threads[1], NULL, consumer, NULL);
	for (i=0; i< 2; i++) 
		pthread_join(threads[i], NULL);
	freeAllNode(&buffer);
	return 0;
}	

void *producer (void *v)
{
	int i;
	for (i =0; i < 1000; i++) {
		pthread_mutex_lock(&mutex);
		if (isFull(&buffer) == 1) // buffer full ! 
			pthread_cond_wait(&buffer_has_space, &mutex); //wait
		in++;
		insertItem(&buffer, i); // insert integer data at the tail
		printf("producer: insert data %d to buffer (%d)\n",i, in);
		pthread_cond_signal(&buffer_has_data); 
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
} 

void *consumer (void *v)
{
	int i, data;
	for (i =0; i < 1000; i++) {
		pthread_mutex_lock(&mutex); //lock
		if (isEmpty(&buffer) == 1) // buffer empty !
			pthread_cond_wait(&buffer_has_data, &mutex);//wait
		data = getItem(&buffer);//get the data at the head
		out++;
		printf("consumer : get data %d from buffer (%d)\n",data,out);
		pthread_cond_signal(&buffer_has_space);
		pthread_mutex_unlock(&mutex); //unlock
		//printf("data = %d\n",data);
		sleep(1);
	}
}

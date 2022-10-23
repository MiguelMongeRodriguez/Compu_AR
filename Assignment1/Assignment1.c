#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef enum { FALSE, TRUE } bool;

struct param{
	int reps;
	char str[50];
};

void *funcionC(void *arg);
	pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

int ct = 0;

int main() {
	pthread_t tid1, tid2;
	int rc1, rc2;
	char temp;
	bool end = TRUE;
	
	struct param *param1, *param2;
	param1 = malloc(sizeof(struct param) * 1);
	param2 = malloc(sizeof(struct param) * 1);
	
	/* ---------------- Input del usuario main thread ---------------------- */
	
	while (end){
		printf("Input a number : ");
		scanf("%d", &param1->reps);  scanf("%c",&temp);
		param2->reps = param1->reps;
		printf("Input first line : ");
		scanf("%[^\t\n]s",&param1->str); scanf("%c",&temp);
		//printf("str1: %s\n", param1->str);
		printf("Input second line : ");
		scanf("%[^\t\n]s",&param2->str); scanf("%c",&temp);
		//printf("str2: %s\n", param2->str);
		//printf("str1len: %d str2len: %d\n", strlen(param1->str),strlen(param2->str) ); // Longitud de los strings
		
		/* ---------------- Creamos los dos hilos ---------------------- */
		if( (rc1=pthread_create( &tid1, NULL, &funcionC, (void *) param1)) ) {
		printf("Error creating thread1 1: %d\n", rc1);
		}
		if( (rc2=pthread_create( &tid2, NULL, &funcionC, (void *) param2)) ) {
		printf("Error creating thread2 2: %d\n", rc2);
		}
		/* Wait until thread terminate */
		pthread_join(tid1, NULL);
		pthread_join(tid2, NULL);
		ct = 0;
	}
	exit(0);
}
void *funcionC(void *arg){
	pthread_mutex_lock(&mutex1);
	struct param * p;
	p = ( struct param *) arg ;
	ct++;
	for (int i = 1; i <= p->reps; i++ ){
		printf("thread_%d (%d) %d %s\n",ct, gettid(), i, p->str);
	}
	pthread_mutex_unlock(&mutex1);
} 

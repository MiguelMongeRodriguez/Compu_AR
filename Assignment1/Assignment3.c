#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef enum { FALSE, TRUE } bool;

#define MAX 20  

struct param{
	int vector[MAX];
	int num;
	int sum;
};

void *funcionC(void *arg);
	pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

int ct = 0;

int main() {
	pthread_t tid1, tid2, tid3, tid4;
	int rc1, rc2, rc3, rc4;
	char temp;
	bool end = TRUE;
	
	struct param *param1;
	param1 = malloc(sizeof(struct param) * 1);
	
	/* ---------------- Input del usuario main thread ---------------------- */
	
	while (end){
		printf("Input vector numbers:\n");
		for (int i = 0; i < MAX; i++ ){
			printf("(%d) ", i);scanf("%d", &param1->vector[i]);  scanf("%c",&temp);
		}
		printf("\nInput number to search:\n");scanf("%d", &param1->num);  scanf("%c",&temp);
		
		/* ---------------- Creamos los dos hilos ---------------------- */
		if( (rc1=pthread_create( &tid1, NULL, &funcionC, (void *) param1)) ) {
		printf("Error creating thread1 1: %d\n", rc1);
		}
		if( (rc2=pthread_create( &tid2, NULL, &funcionC, (void *) param1)) ) {
		printf("Error creating thread2 2: %d\n", rc2);
		}
		if( (rc3=pthread_create( &tid3, NULL, &funcionC, (void *) param1)) ) {
		printf("Error creating thread3 3: %d\n", rc3);
		}
		if( (rc4=pthread_create( &tid4, NULL, &funcionC, (void *) param1)) ) {
		printf("Error creating thread4 4: %d\n", rc4);
		}
		/* Wait until thread terminate */
		pthread_join(tid1, NULL);
		pthread_join(tid2, NULL);
		pthread_join(tid3, NULL);
		pthread_join(tid4, NULL);
		ct = 0;
		
		printf("\nOcurrences of number '%d' in vector: %d\n",param1->num, param1->sum);
	}
	exit(0);
}
void *funcionC(void *arg){
	pthread_mutex_lock(&mutex1);
	struct param * p;
	p = ( struct param *) arg ;
	int cont = 0, qua = (MAX/4), ini = (ct)*qua; // Para dividir un vector en 4, buscamos los cuartiles. ini: donde empieza el segmento del vector para cada thread;
	ct++;
	
	printf("thread_%d (%d) finished. Vector:",ct, gettid());
	
	for (int i = ini; i < ini+qua; i++ ){
		printf("%d ", p->vector[i]);
		if (p->vector[i] == p->num){
			cont++;
		}
	}
	printf("\n");
	
	p->sum += cont;
	
	pthread_mutex_unlock(&mutex1);
} 

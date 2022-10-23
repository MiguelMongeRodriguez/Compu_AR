#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef enum { FALSE, TRUE } bool;

struct vector{
	int matrix1[3];
	int matrix2[3];
	int sum[3];
};

void *funcionC(void *arg);
	pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

int ct = 0;

int main() {
	pthread_t tid1, tid2, tid3;
	int rc1, rc2, rc3;
	char temp;
	bool end = TRUE;
	
	struct vector *vector1, *vector2, *vector3;
	vector1 = malloc(sizeof(struct vector) * 1);
	vector2 = malloc(sizeof(struct vector) * 1);
	vector3 = malloc(sizeof(struct vector) * 1);
	
	/* ---------------- Input del usuario main thread ---------------------- */
	
	while (end){
		printf("Input first matrix numbers (i,j):\n");
		printf("(0,0) ");scanf("%d", &vector1->matrix1[0]);  scanf("%c",&temp);
		printf("(1,0) ");scanf("%d", &vector1->matrix1[1]);  scanf("%c",&temp);
		printf("(2,0) ");scanf("%d", &vector1->matrix1[2]);  scanf("%c",&temp);
		
		printf("(0,1) ");scanf("%d", &vector2->matrix1[0]);  scanf("%c",&temp);
		printf("(1,1) ");scanf("%d", &vector2->matrix1[1]);  scanf("%c",&temp);
		printf("(2,1) ");scanf("%d", &vector2->matrix1[2]);  scanf("%c",&temp);
		
		printf("(0,2) ");scanf("%d", &vector3->matrix1[0]);  scanf("%c",&temp);
		printf("(1,2) ");scanf("%d", &vector3->matrix1[1]);  scanf("%c",&temp);
		printf("(2,2) ");scanf("%d", &vector3->matrix1[2]);  scanf("%c",&temp);
		printf("------------------\n%d\t%d\t%d\t\n%d\t%d\t%d\t\n%d\t%d\t%d\t\n------------------\n",
		vector1->matrix1[0], vector2->matrix1[0], vector3->matrix1[0],
		vector1->matrix1[1], vector2->matrix1[1], vector3->matrix1[1],
		vector1->matrix1[2], vector2->matrix1[2], vector3->matrix1[2]);
		
		printf("Input second matrix numbers (i,j):\n");
		printf("(0,0) ");scanf("%d", &vector1->matrix2[0]);  scanf("%c",&temp);
		printf("(1,0) ");scanf("%d", &vector1->matrix2[1]);  scanf("%c",&temp);
		printf("(2,0) ");scanf("%d", &vector1->matrix2[2]);  scanf("%c",&temp);
		
		printf("(0,1) ");scanf("%d", &vector2->matrix2[0]);  scanf("%c",&temp);
		printf("(1,1) ");scanf("%d", &vector2->matrix2[1]);  scanf("%c",&temp);
		printf("(2,1) ");scanf("%d", &vector2->matrix2[2]);  scanf("%c",&temp);
		
		printf("(0,2) ");scanf("%d", &vector3->matrix2[0]);  scanf("%c",&temp);
		printf("(1,2) ");scanf("%d", &vector3->matrix2[1]);  scanf("%c",&temp);
		printf("(2,2) ");scanf("%d", &vector3->matrix2[2]);  scanf("%c",&temp);
		printf("------------------\n%d\t%d\t%d\t\n%d\t%d\t%d\t\n%d\t%d\t%d\t\n------------------\n",
		vector1->matrix2[0], vector2->matrix2[0], vector3->matrix2[0],
		vector1->matrix2[1], vector2->matrix2[1], vector3->matrix2[1],
		vector1->matrix2[2], vector2->matrix2[2], vector3->matrix2[2]);
		
		/* ---------------- Creamos los dos hilos ---------------------- */
		if( (rc1=pthread_create( &tid1, NULL, &funcionC, (void *) vector1)) ) {
		printf("Error creating thread1 1: %d\n", rc1);
		}
		if( (rc2=pthread_create( &tid2, NULL, &funcionC, (void *) vector2)) ) {
		printf("Error creating thread2 2: %d\n", rc2);
		}
		if( (rc3=pthread_create( &tid3, NULL, &funcionC, (void *) vector3)) ) {
		printf("Error creating thread3 3: %d\n", rc3);
		}
		/* Wait until thread terminate */
		pthread_join(tid1, NULL);
		pthread_join(tid2, NULL);
		pthread_join(tid3, NULL);
		ct = 0;
		
		printf("------------------\n%d\t%d\t%d\t\n%d\t%d\t%d\t\n%d\t%d\t%d\t\n------------------\n",
		vector1->sum[0], vector2->sum[0], vector3->sum[0],
		vector1->sum[1], vector2->sum[1], vector3->sum[1],
		vector1->sum[2], vector2->sum[2], vector3->sum[2]);
	}
	exit(0);
}
void *funcionC(void *arg){
	pthread_mutex_lock(&mutex1);
	struct vector * v;
	v = ( struct vector *) arg ;
	ct++;
	printf("thread_%d (%d) finished\n",ct, gettid());
	
	
	v->sum[0] = v->matrix1[0] + v->matrix2[0];
	v->sum[1] = v->matrix1[1] + v->matrix2[1];
	v->sum[2] = v->matrix1[2] + v->matrix2[2];
	
	pthread_mutex_unlock(&mutex1);
} 

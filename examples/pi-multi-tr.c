// Параллельное вычисление числа Пи
// Pi=4 − 4/3 + 4/5 − 4/7 + … + ( (-1)^(n+1)*4)/(2*n-1)

#include <stdio.h>
#include <math.h> 
#include <stdlib.h>
#include <pthread.h>

double sumPi( int startN, int count ) {
    double s = 0;
    int n;
    
    for( n = startN; n<startN+count; n++ ) {
        s += pow( -1, n + 1 ) * 4 / ( 2*n -1 );
    }
    
    return s;
}

typedef struct {
    int epp;
    int len;
} tdata;

double pi = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void * start_thread1 ( void *data ) {    
    tdata *t = (tdata*)data;
    //tdata tt = *t;
    //printf("tdata 2: %d, %d\n", tt.epp, tt.len);

    double s = sumPi( t->epp, t->len );
    printf("Child with params %d, %d result: %f\n", t->epp, t->len, s);

    pthread_mutex_lock (&mutex);

    pi += s;

    pthread_mutex_unlock (&mutex);
}

int main(int argc, char **argv) {   
    if ( argc != 3 ) {
        printf("You should enter number of sum elements and number of processes\n");
        return 1;
    }
    
    int K = strtol(argv[1], NULL, 10);
    int N = strtol(argv[2], NULL, 10);   
    int i;
            
    int elementsPerProcess = K/N;
    pthread_t tids[N];
    
    tdata t[N];
    for( i=0; i<N; i++ ) {
        t[i].epp = (i * elementsPerProcess) + 1;
        t[i].len = elementsPerProcess;

        printf("tdata: %d, %d\n", t[i].epp, t[i].len);

        pthread_create( &tids[i], NULL, start_thread1, (void *) &t[i] );        
    } 
    
    for( i=0; i<N; i++ ) {
        pthread_join( tids[i], NULL );
    }

    printf("\nTotal pi: %f\n", pi);
}
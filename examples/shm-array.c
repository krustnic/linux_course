#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <stdlib.h>

int M = 100;
int N = 4;

int* getArray( int initialValue ) {
    int *m = malloc( M*sizeof(int) );
    
    int i, j;
    
    for( i=0; i<M; i++ ) {        
        m[i] = initialValue;        
    }
    
    return m;
}

int main() {
    int *m1 = getArray( 1 );
    int *m2 = getArray( 2 );
    int i, pid;
    
    int *RESULT;
    int sm;
    sm = shmget( IPC_PRIVATE, M*sizeof(int), 0666 | IPC_CREAT | IPC_EXCL );
    RESULT = (int*)shmat(sm, NULL, 0);
    
    for( i=0; i<N; i++ ) {
        pid = fork();
        
        if (pid == 0) {
            int j;
            int l;
            
            if ( i == N - 1 ) {
                l = M/N + M % N;
            }
            else {
                l = M/N;
            }
            
            printf("l=%d\n", l);
            
            for( j = i*l; j < i*l + l; j++  ) {
                RESULT[j] = m1[j] * m2[j];         
            }
            
            return 0;
        }        
    }
    
    for( i=0; i<N; i++ ) {
        wait( NULL );
    }
    
    for( i=0; i<M; i++ ) {
        printf("%d,", RESULT[i]);
    }
    
    shmctl(sm, IPC_RMID, NULL);
    
    printf("\n");
}
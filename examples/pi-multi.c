// Параллельное вычисление числа Пи
// Pi=4 − 4/3 + 4/5 − 4/7 + … + ( (-1)^(n+1)*4)/(2*n-1)

#include <stdio.h>
#include <math.h> 
#include <stdlib.h>

double sumPi( int startN, int count ) {
    double s = 0;
    int n;
    
    for( n = startN; n<startN+count; n++ ) {
        s += pow( -1, n + 1 ) * 4 / ( 2*n -1 );
    }
    
    return s;
}

int main(int argc, char **argv) {   
    if ( argc != 3 ) {
        printf("You should enter number of sum elements and number of processes\n");
        return 1;
    }
    
    int K = strtol(argv[1], NULL, 10);
    int N = strtol(argv[2], NULL, 10);   
    int i;
    int fd[2];
    
    if ( pipe( fd ) < 0 ) {
        printf("Pipe error\n");
        return 1;
    }
        
    int elementsPerProcess = K/N;
    int pid;
    
    for( i=0; i<N; i++ ) {
        pid = fork();
        
        if ( !pid ) {
            close( fd[0] );
            
            double s = sumPi( (i * elementsPerProcess) + 1, elementsPerProcess );
            printf("Child with params %d, %d result: %f\n", (i * elementsPerProcess) + 1, elementsPerProcess, s);
            
            write( fd[1], &s, sizeof( double ) );
            return 0;
        }
    } 
    
    int status;
    double pi = 0;
    double partialResult;
    
    for( i=0; i<N; i++ ) {
        wait(&status);
            
        read( fd[0], &partialResult, sizeof(double) );
        printf("Partial: %f\n", partialResult);
        pi += partialResult;
    }
    
    printf("\nTotal pi: %f\n", pi);
}
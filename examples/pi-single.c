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
    
    printf("Start calculating with params: K=%d, N=%d\n", K, N);
    double pi = sumPi( 1, K );
    printf("Pi: %f\n", pi);     
}
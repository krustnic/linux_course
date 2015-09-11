#include <stdio.h>
#include <math.h> 
#include <stdlib.h>

int fd1[2], fd2[2];

void child( int m, int out ) {
    while( 1 ) {
        int waittime = m; // rand() % 5;
        
        int pid = getpid();
        int r = write( out, &pid, sizeof(int) );
        sleep( waittime );
    }
}

int main(int argc, char **argv) {          
    
    pipe( fd1 );
    pipe( fd2 );
    
    int pid = fork();    
    if ( pid == 0 ) {
        close( fd1[0] );
        child( 2, fd1[1] );            
        return 0;
    }
    
    close( fd1[1] );
    
    pid = fork();
    
    if ( pid == 0 ) {
        close( fd2[0] );
        child( 1, fd2[1] );            
        return 0;
    }
    
    close( fd2[1] );
    
    printf("Parent ready\n");
    while( 1 ) {        
        read( fd1[0], &pid, sizeof(int) );
        printf("hello form: 1\n");
        read( fd2[0], &pid, sizeof(int) );
        printf("hello form: 2\n");
    }
}
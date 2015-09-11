#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

FILE *fd;

void atclose() {
    printf("Close fd\n");
    fclose( fd );
}

int main (int argc, char *argv[]) {
    int pid, s;    
    
    char str[100];
    
    atexit( &atclose );
    
    fd = fopen( "./_exit.c", "r" );
    fgets( str, 10, fd );    
    printf("Read: %s\n", str);
       
    pid = fork();
        
    if ( pid > 0 ) {
        // Parent
        printf("Parent\n");
        wait( &s );
        printf("End child\n");
        
        fgets( str, 10, fd );    
        printf("Read: %s\n", str);
        
        printf("End parent\n");
        
        exit(0);
    }
    else {
        printf("Child\n");
        
        fgets( str, 10, fd );    
        printf("Read child: %s\n", str);
        
        exit(0);
    }
    
    return 0;
}
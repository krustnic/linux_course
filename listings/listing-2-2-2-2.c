// Родительский процесс завершается раньше дочернего

#include <unistd.h>
#include <stdio.h>

int main(void) {
    pid_t pid;
    
    pid = fork();
    
    if ( pid == 0 ) {
        // child
        printf("Child process PPID on start = %d\n", getppid() );
        sleep(4);
        printf("Child process PPID after parent finished = %d\n", getppid() );
    }
    else {
        sleep(2);
        printf("Parent finished\n");
        
        return 0;
    }
    
    return 0;
}
// Пример работы с функцией fork
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int global = 0;

int main(void) {
    pid_t pid;
    int status;
    
    pid = fork();
    
    if ( pid < 0 ) {
        perror("Ошибка fork()\n");
        exit(1);
    }
    else if ( pid == 0 ) {
        // Дочерний процесс
        sleep(2);        
    }
    else {
        // Родительский процесс
        printf("Global var is modified\n");
        global += 1;
        wait( &status );
    }
    
    printf("Global from process with pid = %d: %d\n", getpid(), global);
}
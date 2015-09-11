// Дочерний процесс завершается до того как родитель об этом узнает. Процесс-зомби.

#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main ()
{
    pid_t pid;

    pid = fork();
    if ( pid > 0 ) {
        // Parent
        sleep (10);
    }
    else {
        // Child
        exit (0);
    }
    
    return 0;
}
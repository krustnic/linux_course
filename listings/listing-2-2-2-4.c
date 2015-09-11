// Программа для определения причин завершения дочернего процесса

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (void) {
    int status;
    pid_t pid;
    if ( !fork () ) {
        //return 1;
        abort();
    }

    pid = wait (&status);
    
    if (pid == -1) {
        printf("wait");
        return 1;
    }
    
    printf ("pid=%d\n", pid);
    
    if (WIFEXITED (status))
        printf( "Нормальное завершение, статус=%d\n", WEXITSTATUS (status) );
    
    if (WIFSIGNALED (status))
        printf ("Убит сигналом=%d%s\n", WTERMSIG (status), WCOREDUMP (status) ? " (dumped core)" : "");
    
    if (WIFSTOPPED (status))
        printf ("Остановлен сигналом=%d\n", WSTOPSIG (status));
    
    if (WIFCONTINUED (status))
        printf ("Продолжен\n");
    
    return 0;
}
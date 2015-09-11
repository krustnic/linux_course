// Простой командный интерпретатор
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pid;
    char in[10];
    int status;
    
    while ( 1 ) {
        printf("Enter command: ");
        scanf("%s", &in);
        
        if ( strcmp( in, "exit" ) == 0 ) {
            printf("Exit\n");
            return 0;
        }
        
        pid = fork();
        if ( pid == 0 ) {
            int r = execlp( in, in, NULL );
            
            if ( r == -1 ) {
                printf("Error while try to run command: %s\n", in);
                return 1;
            }
        }
        else {
            wait( &status );
        }
    }
    
}
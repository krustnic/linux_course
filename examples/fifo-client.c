// FIFO-client калькулятор

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct {
    int a;
    int b;
    int op;
    int pid;
} task;

int main() {
    char fifoServer[] = "/tmp/calc.fifo";

    printf("Opening fifo for writing ...\n");
    int fd = open( fifoServer, O_WRONLY );    

    if ( fd == -1 ) {
        printf("Error opening the fifo file!\n");
        return 0;
    }
    
    printf("Fifo opened ...\n");

    task t;
    t.a = 1;
    t.b = 2;
    t.op = 1;
    t.pid = getpid();

    write( fd, &t, sizeof( task ) );
    printf("Message was sent\n");

    return 0;
}

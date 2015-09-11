// FIFO Client-Server простой калькулятор
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
    int op;
    int pid;
} task;

char *fifoServerPath = "/tmp/calc.fifo";

void onExit( int sigNum ) {
    printf("Catch signal!\n");

    if ( sigNum == SIGINT ) {
        unlink( fifoServerPath );
        exit(0);
    }
}

int main() {
    if ( signal( SIGINT, &onExit ) == SIG_ERR ) {
        printf("SIGINT error: %d", errno);
        return 1;
    }

    int r = mkfifo( fifoServerPath, 0666 );
    if ( r == -1 && errno != EEXIST ) {
        printf("Error creating fifo\n");
        return 1;
    }

    task t;

    r = 0;
    int fd = 0;

    while( 1 ) {

        if ( r == 0 ) {
            if ( fd ) close(fd);

            printf("Waiting for first client\n");
            fd = open( fifoServerPath, O_RDONLY );
            printf("First client detected!\n");
        }
        else {
            printf("Got new task: %d, %d, %d from %d\n", t.a, t.b, t.op, t.pid);
            
            // Connect to personal fifo and calculation
        }

        printf("Waiting for new task...\n");
        r = read( fd, &t, sizeof(t) );

    }
}

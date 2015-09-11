// Реализация fgets
//

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

char *my_fgets( int fd ) {
    int r;
    char c;
    char buffer[1024];
    int idx = 0;

    do {
        r = read( fd, &c, sizeof(char) );

        if ( r != 0 ) {
            buffer[idx] = c;
        }
        else {
            buffer[idx] = '\n';
        }

        idx += 1;
    } while( c != '\n' && r != 0 );

    buffer[idx] = '\0';
    char *line = malloc( sizeof(char)*(idx + 1) );
    strncpy( line, buffer, idx + 1 );

    return line;
}

int main() {
    int fd = open( "/etc/passwd", O_RDONLY );
    int i = 0;
    char *line;

    for( i=0; i<10; i++ ) {
        line = my_fgets( fd );
        printf("Line %d: %s", i, line);

        free(line);
    }

    close(fd);
}

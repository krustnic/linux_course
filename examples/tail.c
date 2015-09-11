// tail. Вывод последней строчки. 

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>                                                                                                                                                                                                           
#include <fcntl.h>   

int main(int argc, char **argv) {
    
    int fd = open( argv[1], O_RDONLY );
    
    lseek( fd, 0, SEEK_END );
    
    int countOfLines = 0;
    int r;
    char c;
    char buffer[1024];
    while( countOfLines != 10 ) {
        int idx = 0;

        while( c != '\n' ) {
            lseek( fd, -2, SEEK_CUR );
            
            r = read( fd, &c, sizeof(char) );  
            
            printf("Char: %c, %d\n", c, r);               
            buffer[ idx ] = c;
            idx += 1;
        }
        
        printf("idx %d\n", idx);
        int i;
        for( i=idx; i>0; i-- ) {
            printf("%d=%c", idx, buffer[idx]);
        }        
        printf("\n");

        countOfLines += 1;
        break;
    }
}
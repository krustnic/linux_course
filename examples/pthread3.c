#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <sys/types.h>                                                                                                                                                                                   
#include <sys/stat.h>                                                                                                                                                                                    
#include <fcntl.h> 

long s = 0;

void * start_thread () {        
    while( 1 ) {        
        s += 1;        
        pthread_testcancel();
    }       
}

int main (void)
{
    
    pthread_t thing1;
        
    pthread_create (&thing1, NULL, start_thread, NULL);   
    pthread_setcanceltype( PTHREAD_CANCEL_DEFERRED, NULL );
    
    int d;
    scanf("%d", &d);
    
    int r = pthread_cancel( thing1 );
    printf("pthread_cancel: %d\n", r);
    
    r = pthread_join (thing1, NULL);
    printf("Join r: %d\n", r);
    
    printf("Results: %d\n", s);

}
        
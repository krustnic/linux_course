#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>

void * start_thread1 (void *message)
{
    printf ("%s\n", (const char *) message);
    sleep(3);
    return message;
}

void * start_thread2 (void *message)
{
    sleep(3);
    printf ("%s\n", (const char *) message);
    
    return message;
}

int main (void)
{
    pthread_t thing1, thing2;
    const char *message1 = "Thing 1";
    const char *message2 = "Thing 2";
    
    /* Создаются два потока, каждый со своим сообщением */
    pthread_create (&thing1, NULL, start_thread1, (void *) message1);
    pthread_create (&thing2, NULL, start_thread2, (void *) message2);
    
    int r = pthread_detach (thing2);    
    printf("Detach r: %d\n", r);
    
    r = pthread_join (thing1, NULL);
    printf("Join r: %d\n", r);
    
    r = pthread_join (thing2, NULL);    
    printf("Join r: %d\n", r);
    
    if ( r == EDEADLK ) {
        printf("Join r: EDEADLK\n", r);
    }
    
    if ( r == EINVAL ) {
        printf("Join r: EINVAL\n", r);
    }
    
    if ( r == ESRCH ) {
        printf("Join r: ESRCH\n", r);
    }
    
    
    return 0;
}
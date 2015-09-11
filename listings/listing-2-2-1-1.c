// Вывод характеристик процесса: PID, PPID, UID, GID

#include <unistd.h>
#include <stdio.h>

int main(void) {
    pid_t pid, ppid;
    uid_t uid;
    gid_t gid;
    char any_key;
    
    pid  = getpid();
    ppid = getppid();
    uid  = getuid();
    gid  = getgid();
    
    printf( "PID:  %d\n", pid );
    printf( "PPID: %d\n", ppid );
    printf( "UID:  %d\n", uid );
    printf( "GID:  %d\n", gid );
    
    printf( "\nPRESS ANY KEY TO EXIT\n");
    scanf("%c", &any_key);
    
    return 0;
}
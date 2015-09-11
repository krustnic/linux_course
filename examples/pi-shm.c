#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>

int main(void) {
    int sd, semd, pid1,pid2;
    double *A;
    struct sembuf mybuf; // структура для выполнения операций над семафорами
    
    sd   = shmget(IPC_PRIVATE, sizeof(double), 0666 | IPC_CREAT | IPC_EXCL ); 
    semd = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);

    A = (double*)shmat(sd,NULL,0);
    
    *A = 4.0;
    
    mybuf.sem_num = 0; // задаем начальное значение семафора равное 1
    mybuf.sem_op = 1;
    mybuf.sem_flg = 0;
    
    semop(semd,&mybuf,1);
    
    if ( pid1=fork() ==0 ) { 
        int i;
        
        struct sembuf mybuf;
        
        for(i=2; i<1000000;i=i+2){
            
            mybuf.sem_num = 0;
            mybuf.sem_op = -1;
            mybuf.sem_flg = 0;            
            semop(semd,&mybuf,1);
            
            *A=*A+((double)4/(2*i-1)*(-1));
            
            mybuf.sem_num = 0;
            mybuf.sem_op = 1;
            mybuf.sem_flg = 0;
            semop(semd,&mybuf,1);
        }
    }
    else {
        if ( pid2=fork() ==0 ) {
            int j;
            
            struct sembuf mybuf;
            
            for(j=3; j<1000000; j=j+2){
                
                mybuf.sem_num = 0;
                mybuf.sem_op = -1;
                mybuf.sem_flg = 0;
                
                semop(semd,&mybuf,1);
                
                *A=*A+((double)4/(2*j-1)*(1));
                
                mybuf.sem_num = 0;
                mybuf.sem_op = 1;
                mybuf.sem_flg = 0;
                semop(semd,&mybuf,1);
            }
        }
        else {
            int z;
            wait(NULL); // ожидаем завершения вычислений 
            wait(NULL);
            
            printf("PI=%lf\n",*A); // выводим результат
            
            shmctl(sd, IPC_RMID, NULL); // освобождаем ресурсы системы из-под разделяемой памяти
            semctl(semd, 0, IPC_RMID, NULL); // освобождаем ресурсы системы из-под семафоров
        }
    }
    return 0;
}
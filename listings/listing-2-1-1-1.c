// Использование обработчиков выхода

#include <stdio.h>
#include <stdlib.h>

void my_exit1(void);
void my_exit2(void);

int main(void) {
    if (atexit(my_exit2) != 0) {
        printf("невозможно зарегистрировать my_exit2\n");
        exit(1);
    }
    
    if (atexit(my_exit1) != 0) {
        printf("невозможно зарегистрировать my_exit1\n");
        exit(1);
    }
    
    if (atexit(my_exit1) != 0) {
        printf("невозможно зарегистрировать my_exit1\n");
        exit(1);
    }        
    
    printf("функция main завершила работу\n");
    
    return 0;
}

void my_exit1(void) {
    printf("первый обработчик выхода\n");
}

void my_exit2(void) {
    printf("второй обработчик выхода\n");
}
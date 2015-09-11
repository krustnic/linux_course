#include <stdio.h>

int sum(int a, int b) {
    return a + b;
}

int main() {
    int i;
    int s;
    
    s = 0;
    
    for( i=0; i<5; i++ ) {
        s = sum(s, i);
    }
    
    printf("s = %d\n", s);
    
    return 0;
}
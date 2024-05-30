#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    char buf[25];
    int n;
    
    while ((n = read(1, buf, sizeof(buf))) > 0) {
        write(1, buf, n);
    }
    
    exit(0);
}
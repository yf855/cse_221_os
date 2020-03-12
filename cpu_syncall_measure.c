#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    int loops = 10;
    int i =0;
    for (;i<loops;i++){
        system("./cpu_syncall");
    }

    return 0;
}

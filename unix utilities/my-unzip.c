#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("my-unzip: file1 [file2 ...]\n");
        exit(1);
    } else {
        FILE *file = fopen(argv[1], "rb");
        char buffer[100];
        int buffer1;
        while(fread(&buffer1, 4,1, file)){
            fread(&buffer, 1, 1, file);
            for(int i=0; i < buffer1; i++) {
                printf("%s", buffer);
            }  
        }
    }
    
    return 0;
}
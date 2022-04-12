#include <stdio.h>
#include <stdlib.h>
#define MAX 1000000

void cat_function (char *filename) { /*Cat_function will print the file data to stdout*/
    FILE *file;
    char line[MAX];
    file = fopen(filename, "r");
    if(file==NULL) {
        perror("my-cat: cannot open file\n");
        exit(1);
    } else {
        while(fgets(line, MAX, file)) {
            printf("%s", line);
        }
    }
    fclose(file); 
}

int main(int argc, char *argv[]) {
    if(argc == 1) {
        exit(0);
    } else {
        for(int i = 1; i < argc; i++) {
        printf("\n-------------------------------file: %d--------------------------------\n", i);
        cat_function(argv[i]);
        }
        printf("\n");
    }   
    
    return 0;
}
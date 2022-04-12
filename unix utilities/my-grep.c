#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void search_function(char *searchterm, char *filename) {
    char *line = NULL;
    size_t lenght = 0;
    FILE *file = fopen(filename, "r");
    if(file==NULL) {
        perror("my-grep: cannot open file ");
        exit(1);
    } else {
        while(getline(&line, &lenght, file) != -1) {
            if(strstr(line, searchterm)){
                line[strcspn(line, "\n")] = '\0';
                printf("%s", line);
            }
        }
        printf("\n");
        fclose(file);
        free(line);
    }
}

void searchingfrominput(char *searchterm) {
    char *line = NULL;
    size_t lenght = 0;
    while(getline(&line, &lenght, stdin) != -1) {
        if(strstr(line, searchterm)){
            printf("%s", line);
        }
    }
    printf("\n");
    free(line);
    
}
int main(int argc, char *argv[]) {
    if(argc == 1) {
        printf("my-grep: searchterm [file ...]\n");
        exit(1);
    } else if(argc == 2) {
        printf("No file specified\nreading from stdin\nctrl+d to end:\n");
        searchingfrominput(argv[1]);
    } else {
        for(int i=2; i < argc; i++) {
            search_function(argv[1], argv[i]);
        }
    }
    
    return 0;
}
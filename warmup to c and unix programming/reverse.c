#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list {
    char *line;
    struct list *pnext;
    struct list *pprev;
}LIST;

LIST *addData(LIST *pstart, char readline[]) {
    LIST *pnew, *ptr;
    if ((pnew = (LIST*)malloc(sizeof(LIST))) == NULL) { /*ERROR HANDLING*/
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    
    if ((pnew->line = (char*)malloc(sizeof(*readline))) == NULL) { /*ERROR HANDLING*/
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }

    strcpy(pnew->line, readline);

    if (pstart == NULL) { /*Special case for the first one*/
        pstart = pnew;
    } else { /*This is for the case when there is already something in the list*/
        ptr = pstart;
        while(ptr->pnext != NULL){
            ptr = ptr->pnext;
        }
        ptr->pnext = pnew;
        pnew->pprev = ptr;
    }
    return pnew;
}

LIST *read(char filename[], LIST* pstart) {
    char *line = NULL;
    size_t lenght = 0;
    FILE *file;
    if((file = fopen(filename, "r"))==NULL) { /*ERROR HANDLING*/
        fprintf(stderr, "error: cannot open file '%s'\n", filename);
        exit(1);
    } 
    while(getline(&line, &lenght, file) != -1) { /*Reading the file line by line*/
        line[strcspn(line, "\n")] = '\0'; /*Removing the trailing newline*/
        pstart = addData(pstart, line);
        }
    free(line);
    fclose(file);
    return pstart;
}

void printing(LIST* pstart) { /*Function to print to the stdout*/
    LIST *ptr = pstart;
    while(ptr != NULL) {
        if(ptr->pprev == NULL) { /*Traversin linked list backwards from the end to the start to print the right output*/
            printf("%s", ptr->line);
        } else {
            printf("%s\n", ptr->line);
        }
        ptr = ptr->pprev; 
    }
    printf("\n");
}

void fileprint(LIST* pstart, char filename[]) { /*Function to print to a specific file*/
    LIST *ptr = pstart;
    FILE *file;
    if((file = fopen(filename, "w"))==NULL) { /*ERROR HANDLING*/
        fprintf(stderr, "error: cannot open file '%s'\n", filename);
        exit(1);
    }
    while(ptr != NULL) {
        if(ptr->pprev == NULL) { /*Traversin linked list backwards from the end to the start to print the right output*/
            fprintf(file, "%s", ptr->line);
        } else {
            fprintf(file, "%s\n", ptr->line);
        }
        ptr = ptr->pprev; 
    }
    fclose(file);
}


LIST *readfromstdin(LIST* pstart) {
    char *line = NULL;
    size_t lenght = 0;
    
    while(getline(&line, &lenght, stdin) != -1) { /*Reading the lines from the stdin*/
        line[strcspn(line, "\n")] = '\0'; /*Removing the trailing newline*/
        pstart = addData(pstart, line);
        }
    free(line);
    return pstart;
}

int main(int argc, char *argv[]) {
    LIST* pstart = NULL;
    if(argc == 2) {
        pstart = read(argv[1], pstart);
        printing(pstart);
    }
    else if(argc == 3) {
        if(strcmp(argv[1], argv[2]) == 0) { 
            fprintf(stderr, "Input and output file must differ\n");
            exit(1);
        }
        else {
            pstart = read(argv[1], pstart);
            fileprint(pstart, argv[2]);
        }
    } 
    else if(argc > 3){
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }
    else if(argc == 1) {
        pstart = readfromstdin(pstart);
        printing(pstart);
    }
    free(pstart);
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void zip(char *filename) {
    char c;
    char prevc;
    char *line = NULL;
    int count = 0;
    int overallcount = 0;
    FILE *file = fopen(filename, "r");
    if(file==NULL) { /*ERROR HANDLING*/
        perror("my-zip: cannot open file");
        exit(1);
    } else {
        while((c=fgetc(file))!=EOF) { /*Reading the file until END OF FILE*/
                if (overallcount == 0) {
                    overallcount += 1;
                    prevc = c;
                    count = 1;
                } else if(prevc == c){
                    count += 1;
                } 
                else if (prevc != c) { 
                    fwrite(&count, sizeof(count), 1, stdout); /*Writes the number*/
                    fwrite(&prevc, sizeof(prevc), 1, stdout); /*Writes the character*/
                    count = 1;
                    prevc = c;
                } 
        }
    fwrite(&count, sizeof(count), 1, stdout); /*Writes the number*/
    fwrite(&prevc, sizeof(prevc), 1, stdout); /*Writes the character*/
    }   
    fclose(file);
    free(line);
}

int main(int argc, char *argv[]) {
    int newlinehelper = 1;
    if(argc == 1) { /*No input file*/
        printf("my-zip: file1 [file2 ...]\n");
        exit(1);
    } else if (argc == 2) { /*One input file*/
        zip(argv[1]);
    } else if (argc > 2) { /*More than one inputfile*/
        for(int i = 1; i < argc ; i++) {
            zip(argv[i]);
            fwrite(&newlinehelper, sizeof(int), 1, stdout); /*Writes the number*/
            fwrite("\n", sizeof(char), 1, stdout); /*When there are multiple files the zip program will put a newline between the file contents*/
        }
    }
    return 0;
}
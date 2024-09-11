#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h> // Add the stdlib.h header for malloc
#include "imageConversion.h"

int main() {
    // char filename[] = "Chessboard";
    char * dir = "Text Images";
    struct dirent * dp;

    DIR * dfd = opendir(dir);

    if(dfd == NULL) {
        printf("Error opening directory\n");
        return 1;
    }

    while((dp = readdir(dfd)) != NULL) {


        if(strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
            continue;
        }

        char filename[256];
        int * dimensions = (int *)malloc(2 * sizeof(int));

        strcpy(filename, dp->d_name);

        printf("%s", filename);
        filename[strlen(filename) - 4] = '\0';
        printf("Processing file: %s\n", filename);
        if (!ConvertToBin(filename, dimensions)) {
            return 1;
        }

        if(!CheckBin(filename, dimensions, false)) {
            return 1;
        }
    }

    return 0;


}
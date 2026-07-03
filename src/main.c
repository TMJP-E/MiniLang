#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"

#define FILE_SIZE 1024

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Debe ingresar archivos para evaluar.\n");
        return -1;
    }

    for (size_t i = 1; i < argc; i++)
    {
        FILE *fileptr = fopen(argv[i], "r");
        char buffer[FILE_SIZE] = {0};
        char file[FILE_SIZE * 4] = {0};

        while (fgets(buffer, sizeof(buffer), fileptr) != NULL)
        {
            strcat(file, buffer);
        }

        input = file;
        pos = 0;

        parse();
    }
}
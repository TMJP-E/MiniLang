#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"

#define FILE_SIZE 4096

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
        char *buffer = NULL;
        size_t len;
        size_t bytes_read = getdelim(&buffer, &len, '\0', fileptr);

        if (bytes_read != -1)
        {
            input = buffer;
            pos = 0;

            parse();
        }
    }
}
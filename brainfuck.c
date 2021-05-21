#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Please specify a file as an argument.\n");
        exit(-1);
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp)
    {
        printf("Could not open file: \'%s\'\n", argv[1]);
        exit(-1);
    }

    int n = 0;
    while (fgetc(fp) != EOF) 
    {
        n++;
    }
    fseek(fp, 0, SEEK_SET);

    char *source = (char *)calloc((n + 1), sizeof(char));
    if (source == NULL)
    {
        printf("Could not allocate memory.\n");
        exit(-1);
    }
    char *sp = source;
    char c;
    while ((c = fgetc(fp)) != EOF)
    {
        *sp = c;
        sp++;
    }
    fclose(fp);

    char *arr;
    size_t capacity = 30000;
    arr = (char *)calloc(capacity, sizeof(char));
    if (arr == NULL)
    {
        printf("Could not allocate memory.\n");
        exit(-1);
    }

    int i = 0;
    size_t pos = 0;
    while (source[i] != '\0')
    {
        switch (source[i])
        {
        case '>':
            arr++;
            pos++;
            break;
        case '<':
            arr--;
            pos--;
            break;
        case '+':
            (*arr)++;
            break;
        case '-':
            (*arr)--;
            break;
        case '.':
            putchar(*arr);
            break;
        case ',':
            *arr = getchar();
            break;
        case '[':
            if (*arr == 0)
            {
                while (source[i] != ']')
                {
                    i++;
                }
            }
            break;
        case ']':
            if (*arr != 0)
            {
                while (source[i] != '[')
                {
                    i--;
                }
            }
            break;
        default:
            break;
        }
        i++;

        if (pos == capacity - 1)
        {
            char *tmp = realloc(arr, capacity + 256);
            if (tmp == NULL)
            {
                free(arr);
                printf("Could not allocate memory.\n");
                exit(-1);
            }
            arr = tmp;
        }
    }

    free(source);
    free(arr);

    return 0;
}
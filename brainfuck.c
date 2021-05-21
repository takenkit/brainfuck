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

    size_t srclen = 0;
    while (fgetc(fp) != EOF) 
    {
        srclen++;
    }
    fseek(fp, 0, SEEK_SET);

    char *src = (char *)calloc((srclen + 1), sizeof(char));
    if (src == NULL)
    {
        printf("Could not allocate memory.\n");
        exit(-1);
    }
    char *sp = src;
    char c;
    while ((c = fgetc(fp)) != EOF)
    {
        *sp = c;
        sp++;
    }
    fclose(fp);

    size_t len = 30000;
    char *arr = (char *)calloc(len, sizeof(char));
    if (arr == NULL)
    {
        printf("Could not allocate memory.\n");
        exit(-1);
    }
    char *ptr = arr;// trying not to raise a segmentation fault when the array is deallocated memory. 

    size_t srcpos = 0;
    size_t ptrpos = 0;
    while (srcpos < srclen)
    {
        switch (src[srcpos])
        {
        case '>':
            ptr++;
            ptrpos++;
            break;
        case '<':
            ptr--;
            ptrpos--;
            break;
        case '+':
            (*ptr)++;
            break;
        case '-':
            (*ptr)--;
            break;
        case '.':
            putchar(*ptr);
            break;
        case ',':
            *ptr = getchar();
            break;
        case '[':
            if (*ptr == 0)
            {
                while (src[srcpos] != ']')
                {
                    srcpos++;
                }
            }
            break;
        case ']':
            if (*ptr != 0)
            {
                while (src[srcpos] != '[')
                {
                    srcpos--;
                }
            }
            break;
        default:
            break;
        }

        if (ptrpos == len - 1)
        {
            char *tmp = realloc(ptr, len + 256);
            if (tmp == NULL)
            {
                free(ptr);
                printf("Could not reallocate memory any more.\n");
                exit(-1);
            }
            ptr = tmp;
            len += 256;
        }

        srcpos++;
    }

    free(src);
    free(arr);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#define ARRAY_SIZE 30000


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Please specify a file as an argument.");
        exit(-1);
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp)
    {
        printf("Could not open file \'%s\'", argv[1]);
        exit(-1);
    }

    int n = 0;
    while (fgetc(fp) != EOF) 
    {
        n++;
    }
    fseek(fp, 0, SEEK_SET);

    char *s = (char *)calloc((n + 1), sizeof(char));
    char *sp = s;
    char c;
    while ((c = fgetc(fp)) != EOF)
    {
        *sp = c;
        sp++;
    }
    fclose(fp);

    char *ptr;
    ptr = (char *)calloc(ARRAY_SIZE, sizeof(char));
    if (ptr == NULL)
    {
        printf("Could not allocate memory");
        exit(-1);
    }

    int i = 0;
    while (s[i] != '\0')
    {
        switch (s[i])
        {
        case '>':
            ptr++;
            break;
        case '<':
            ptr--;
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
                while (s[i] != ']')
                {
                    i++;
                }
            }
            break;
        case ']':
            if (*ptr != 0)
            {
                while (s[i] != '[')
                {
                    i--;
                }
            }
            break;
        default:
            break;
        }
        i++;
    }

    free(s);
    free(ptr);

    return 0;
}
#define GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 30000

typedef struct source
{
    char chars;
    int len;
} source;

source src;

// 
void editorAppendRow(char *s, size_t len)
{
    s = realloc(s, sizeof(char) * len);
    E.row[at].size = len;
    E.row[at].chars = malloc(len + 1);
    memcpy(E., s, len);
    E.row[at].chars[len] = '\0';
}

void editorOpen(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        printf("could not open %s", argv[1]);
        exit(-1);
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t linelen;
    while ((linelen = getline(&line, &len, fp)) != -1)
    {
        editorAppendRow(line, linelen);
    }
    free(line);
    fclose(fp);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        
    }
    if (argc >= 2)
    {

    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp)
    {
        printf("could not open %s", argv[1]);
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
    *sp = '\0';

    fclose(fp);

    char *ptr;
    ptr = (char *)calloc(ARRAY_SIZE, sizeof(char));
    if (ptr == NULL)
    {
        printf("could not allocate memory");
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
            //putchar(*ptr);
            printf("%d ", *ptr);
            break;
        case ',':
            *ptr = getchar();
            break;
        case '{':
            if (*ptr == 0)
            {
                while (s[i] != '}')
                {
                    i++;
                }
            }
            break;
        case '}':
            if (*ptr != 0)
            {
                while (s[i] != '{')
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

    printf("\n");

    return 0;
}
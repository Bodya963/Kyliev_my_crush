#include "floy.h"

struct floy
{
    char * name;
    char * buff;
    size_t size;
    FILE * fd;
};

struct floy * floy_create_stdin()
{
    struct floy * floy1 = (struct floy *)calloc( 1, sizeof(struct floy));

    floy1->name = "stdin";
    floy1->size = MAXBUFF;
    floy1->fd = stdin;
    floy1->buff = (char *)calloc( MAXBUFF, sizeof(char));

    return floy1;
}

struct floy * floy_create( char * str)
{
    struct floy * floy1 = (struct floy *)calloc(1, sizeof( struct floy));

    floy1->name = str;
    floy1->size = MAXBUFF;
    floy1->fd = fopen( str, "r");
    floy1->buff = (char *)calloc( MAXBUFF, 1);

    if( floy1->fd == NULL)
    {
        printf(" In floy_create(): cant open file %s", str);
    }

    return floy1;
}

int floy_readln( struct floy * floy1)
{
    if ( (getline( &(floy1->buff), &(floy1->size), floy1->fd)) == -1)
    {
        return EOF;
    }

    int check_n = 0;

    for( int i = floy1->size-1; i > -1; i--) // проверяю есть символ новой строки, если нет, то добавляю
    {
        if( floy1->buff[i] == '\n')
        {
            check_n = 1;
            break;
        }
    }

    if( check_n == 0)
    {
        floy1->buff[floy1->size-1] = '\n'; // сигфолта не будет, у меня там есть лишний байт см строчку 30
    }

    //printf( " readln = %s\n", floy1->buff);

    return 0;
}

char floy_get_first( struct floy * floy1)
{
    return floy1->buff[0];
}

void floy_delete( struct floy * floy1)
{
    if( strcmp( floy1->name, "stdin") != 0)
    {
        fclose( floy1->fd);
    }

    free( floy1->buff);
    free( floy1);
}


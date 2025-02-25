#include "library.h"

struct library 
{
    char ** words;
    int * counts;
    int size;
};

struct library * library_create( void)
{
    struct library * library1 = (struct library *)calloc( 1, sizeof( struct library));

    library1->size = MAXWORDS;
    library1->words = (char **)calloc( library1->size,  sizeof(char *));
    library1->counts = (int *)calloc( library1->size, sizeof(int));

    return library1;
}

void library_push( struct library * library1, char * word)
{
    if( library1->words[library1->size-1] != NULL)
    {
        library1->size = library1->size + STEPWORDS;
        library1->words = (char **)realloc(library1->words, (sizeof(char *) * library1->size));
        library1->counts = (int *)realloc(library1->counts, (sizeof(int) * library1->size));

        for ( int i = 0; i < STEPWORDS; i++)
        {
            library1->words[ library1->size-STEPWORDS + i] = 0;
            library1->counts[ library1->size-STEPWORDS + i] = 0;
        }
    }

    for ( int i = 0; i < library1->size; i++)
    {
        if(library1->words[i] == NULL)
        {
            library1->words[i] = (char *)calloc( sizeof(word), 1);

            strcpy( library1->words[i], word);

            library1->counts[i] = 1;
            break;
        }

        if( strcmp( word, library1->words[i]) == 0)
        {
            library1->counts[i] = library1->counts[i] + 1;
            break;
        }

    }

    // for( int i = 0; i < library1->size; i++)
    // {
    //     printf("lib: [%d] = %s %d\n", i, library1->words[i], library1->counts[i]);
    //     if( library1->words[i] == NULL)
    //     {
    //         break;
    //     }
    // }

}

void library_print( struct library * library1)
{
    for ( int i  = 0; i < library1->size; i++)
    {
        if( library1->counts[i] == 0)
        {
            break;
        }

        printf( "%s : %d\n", library1->words[i], library1->counts[i]);
    }
}

void library_delete( struct library * library1)
{
    all_free( library1->words);

    free( library1->counts);

    free( library1);
}
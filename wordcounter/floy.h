#pragma once

#include "header.h"

#define MAXBUFF 255

struct floy;

struct floy * floy_create_stdin( void); // принимает данные из stdin
struct floy* floy_create( char *);
int floy_readln( struct floy *);
char floy_get_first( struct floy *); // Получается первый символ буффера
void floy_delete( struct floy * );
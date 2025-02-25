#pragma once

#include "header.h"

#define MAXWORDS 150
#define STEPWORDS 20

struct library;

struct library * library_create( void);

void library_push( struct library * , char *);

void library_print( struct library *);

void library_delete( struct library *);
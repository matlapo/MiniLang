#include "tree.h"

#define HashSize 317

typedef enum type
{
    intk,
    floatk,
    stringk,
    boolk,
    none
} type;

typedef struct SymbolTable {
    char *var;
    type t;
    struct SymbolTable *next;
} SymbolTable;

//void printSymbolTable(SymbolTable *table);
void putSymbol(char *name, type typ);
type getSymbol(char *name);

int buildTable(DECLS *d);
int lookUp(EXP *e);
void printTable();

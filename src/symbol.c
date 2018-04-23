#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "symbol.h"

extern PROG *program;

struct SymbolTable *head = NULL; //should probably be defined in main
struct SymbolTable *current = NULL;
char* undeclaredName = NULL; //will be set if an undeclared variable is used

void putSymbol(char *name, type typ) {
    SymbolTable *new = (SymbolTable *)malloc(sizeof(SymbolTable));
    char *copy = strdup(name);
    new->var = copy;
    new->t = typ;
    new->next = NULL;
    if (head == NULL) {
        head = new;
        current = new;
        return;
    }
    //walk to end of list, do not change head
    current = head;
    while (current->next != NULL) 
    {
        current = current->next;
    }
    current->next = new;
    current = new;
}

//returns -1 if it can't find it, otherwise the associated enum case
type getSymbol(char *name) {
    current = head;
    while (current != NULL) {
        if (strcmp(current->var, name) == 0) {
            return current->t;
        }
    current = current->next;
    }
    return none;
}

int lookUp(EXP *e) {
    EXP *left;
    EXP *right;
    if (e == NULL)
        return 0;
    switch (e->kind) {
        case idK:
            if (getSymbol(e->val.idE) == none) {
                undeclaredName = e->val.idE;
                return -1;
            }
            else 
                return 0;
            break;
        case intconstK: return 0; break;
        case floatconstK: return 0; break;
        case stringconstK: return 0; break;
        case boolconstK: return 0; break;
        case timesK:
            left = e->val.timesE.left;
            right = e->val.timesE.right;
            break;
        case minusK:
            left = e->val.minusE.left;
            right = e->val.minusE.right;
            break;
        case divK:
            left = e->val.divE.left;
            right = e->val.divE.right;
            break;
        case plusK:
            left = e->val.plusE.left;
            right = e->val.plusE.right;
            break;
        case orK:
            left = e->val.orE.left;
            right = e->val.orE.right;
            break;
        case andK:
            left = e->val.andE.left;
            right = e->val.andE.right;
            break;
        case negateK:
            left = e->val.negateE.child;
            right = NULL;
            break;
        case bangK:
            left = e->val.bangE.child;
            right = NULL;
            break;
        case equalsK:
            left = e->val.equalsE.left;
            right = e->val.equalsE.right;
            break;
        case neqK:
            left = e->val.neqE.left;
            right = e->val.neqE.right;
            break;
        case parenthesisK:
            left = e->val.parenthesisE.child;
            right = NULL;
            break;
    }
        
    if (lookUp(left) == -1 || lookUp(right) ==  -1)
        return -1;
    else 
        return 0;
}

int buildTable(DECLS *d) {
    EXP *expr;
    char *name;
    type t;
    if (d == NULL)
        return 0;
    switch (d->val.dec.decl->kind) {
        case assignInt:
            name = d->val.dec.decl->val.assignI.name;
            t = intk;
            expr = d->val.dec.decl->val.assignI.exp;
            break;
        case assignFloat:
            name = d->val.dec.decl->val.assignF.name;
            t = floatk;
            expr = d->val.dec.decl->val.assignF.exp;
            break;
        case assignString:
            name = d->val.dec.decl->val.assignS.name;
            t = stringk;
            expr = d->val.dec.decl->val.assignS.exp;
            break;
        case assignBool:
            name = d->val.dec.decl->val.assignB.name;
            t = boolk;
            expr = d->val.dec.decl->val.assignB.exp;
            break;
    }
    //perform lookup before adding new name to the table
    if (lookUp(expr) == -1) {
        fprintf(stderr, "Error: (line %d) identifier \"%s\" not declared\n", d->val.dec.decl->lineno, undeclaredName);
        return -1;
    }
    if (getSymbol(name) != none) {
        fprintf(stderr, "Error: (line %d) identifier \"%s\" already declared\n", d->val.dec.decl->lineno, name);
        return -1;
    }
    putSymbol(name, t);    
    return buildTable(d->val.dec.decls);
}

void printTable() {
    struct SymbolTable *temp = head;
    while (temp != NULL) {
        printf ("%s: ", temp->var);
        switch (temp->t) {
            case intk:
                printf("int\n");
                break;
            case floatk:
                printf("float\n");
                break;
            case stringk:
                printf("string\n");
                break;
            case boolk:
                printf("bool\n");
                break;
            case none:
                printf("unknown\n");
                break;
        }
        temp = temp->next;
    }
}

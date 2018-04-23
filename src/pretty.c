#include <stdio.h>
#include <stdlib.h>
#include "pretty.h"

int current_indent = 0;
 
void prettyEXP(EXP *e)
{ 
    char *value = (char *)malloc(sizeof(char)*6);
    switch (e->kind) {
    case idK:
         printf("%s",e->val.idE);
         break;
    case intconstK:
         printf("%i",e->val.intconstE);
         break;
    case floatconstK:
         printf("%f", e->val.floatconstE);
         break;
    case stringconstK:
         printf("%s", e->val.stringconstE);
         break;
    case boolconstK:
         if (e->val.boolconstE == 0)
            value = "FALSE";
         else 
            value = "TRUE";
         printf("%s", value);
         break;
    case timesK:
         printf("(");
         prettyEXP(e->val.timesE.left);
         printf(" * ");
         prettyEXP(e->val.timesE.right);
         printf(")");
         break;
    case divK:
         printf("(");
         prettyEXP(e->val.divE.left);
         printf(" / ");
         prettyEXP(e->val.divE.right);
         printf(")");
         break;
    case plusK:
         printf("(");
         prettyEXP(e->val.plusE.left);
         printf(" + ");
         prettyEXP(e->val.plusE.right);
         printf(")");
         break;
    case minusK:
         printf("(");
         prettyEXP(e->val.minusE.left);
         printf(" - ");
         prettyEXP(e->val.minusE.right);
         printf(")");
         break;
    case orK:
         printf("(");
         prettyEXP(e->val.orE.left);
         printf("||");
         prettyEXP(e->val.orE.right);
         printf(")");
         break;
    case andK:
         printf("(");
         prettyEXP(e->val.andE.left);
         printf("&&");
         prettyEXP(e->val.andE.right);
         printf(")");
         break;
    case negateK:
         printf("-(");
         prettyEXP(e->val.negateE.child);
         printf(")");
         break;
    case bangK:
         printf("!(");
         prettyEXP(e->val.bangE.child);
         printf(")");
         break;
    case equalsK:
         printf("(");
         prettyEXP(e->val.equalsE.left);
         printf(" == ");
         prettyEXP(e->val.equalsE.right);
         printf(")");
         break;
    case neqK:
         printf("(");
         prettyEXP(e->val.equalsE.left);
         printf(" != ");
         prettyEXP(e->val.equalsE.right);
         printf(")");
         break;
    case parenthesisK:
         prettyEXP(e->val.parenthesisE.child);
         break;
  }
}

void prettyDECL(DECL *d)
{ 
    switch (d->kind) {
        case assignInt:
            printf("var ");
            printf("%s", d->val.assignI.name);
            printf(": int = ");
            prettyEXP(d->val.assignI.exp);
            break;
        case assignFloat:
            printf("var ");
            printf("%s", d->val.assignF.name);
            printf(": float = ");
            prettyEXP(d->val.assignF.exp);
            break;
        case assignString:
            printf("var ");
            printf("%s", d->val.assignS.name);
            printf(": string = ");
            prettyEXP(d->val.assignS.exp);
            break;
        case assignBool:
            printf("var ");
            printf("%s", d->val.assignB.name);
            printf(": boolean = ");
            prettyEXP(d->val.assignB.exp);
            break;
  }
}

void prettySTM(STM *s)
{ 
    int i = 0;
    for (i = 0; i < current_indent; i++) printf("\t");
    switch (s->kind) {
    case assignK:
        printf("%s", s->val.assignS.id);
        printf(" = ");
        prettyEXP(s->val.assignS.exp);
        printf(";\n");
        break;
    case whileK:
        printf("while ");
        prettyEXP(s->val.whileS.exp);
        printf(" {\n");
        current_indent++;
        prettySTMS(s->val.whileS.body);
        current_indent = current_indent - 1;
        for (i = 0; i < current_indent; i++) printf("\t");
        printf("}\n");
        break;
    case ifK:
        printf("if ");
        prettyEXP(s->val.ifS.exp);
        printf(" {\n");
        current_indent++;
        prettySTMS(s->val.ifS.body);
        current_indent = current_indent - 1;
        for (i = 0; i < current_indent; i++) printf("\t");
        if (s->val.ifS.elses != NULL) {
            printf("} else {\n");
            current_indent++;
            prettySTMS(s->val.ifS.elses);
            current_indent = current_indent - 1;
            for (i = 0; i < current_indent; i++) printf("\t");
            printf("}\n");
        } else 
            printf("}\n");
        break;
    case printK:
        printf("print ");
        prettyEXP(s->val.printS.exp);
        printf(";\n");
        break;
    case readK:
        printf("read ");
        printf("%s;\n", s->val.readS.name);
        break;
 }
}

void prettyDECLS(DECLS *ds) 
{ 
    if (ds != NULL) {
        if (ds->val.dec.decl != NULL) { 
            prettyDECL(ds->val.dec.decl);
            printf(";\n");
        }
        if (ds->val.dec.decls != NULL)
            prettyDECLS(ds->val.dec.decls);
    }
}

void prettySTMS(STMS *ss)
{
    if (ss != NULL) {
        if (ss->val.st.stm != NULL) 
            prettySTM(ss->val.st.stm);
        if (ss->val.st.stms != NULL) 
            prettySTMS(ss->val.st.stms);
    }
}

void prettyPROG(PROG *p) 
{
    current_indent = 0;
    if (p != NULL) {
        if (p->val.prog.decls != NULL) {
            prettyDECLS(p->val.prog.decls);
            printf("\n");
        }
        if (p->val.prog.stmts != NULL)
            prettySTMS(p->val.prog.stmts);
    }
}

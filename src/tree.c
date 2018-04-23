#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

extern PROG *program;

PROG *makePROG(DECLS *decls, STMS *stmts) {
    PROG *p = malloc(sizeof(PROG));
    p->val.prog.decls = decls;
    p->val.prog.stmts = stmts;
    program = p; //attach the extern var to the tree
    return p;
}

DECLS *makeDECLS(DECL *decl, DECLS *decls) {
    DECLS *ds = malloc(sizeof(DECLS));
    ds->val.dec.decl = decl;
    ds->val.dec.decls = decls;
    return ds;
}

STMS *makeSTMS(STM *stm, STMS *stms) {
    STMS *ss = malloc(sizeof(STMS));
    ss->val.st.stm = stm;
    ss->val.st.stms = stms;
    return ss;
}

STM *makeSTMassign(char *id, EXP *value, int lineno) {
    STM *s = malloc(sizeof(STM));
    s->lineno = lineno;
    s->kind = assignK;
    s->val.assignS.id = id;
    s->val.assignS.exp = value;
    return s;
}

STM *makeSTMif(EXP *expr, STMS *stmts, STMS *elses, int lineno) {
    STM *s = malloc(sizeof(STM));
    s->lineno = lineno;
    s->kind = ifK;
    s->val.ifS.exp = expr;
    s->val.ifS.body = stmts;
    s->val.ifS.elses = elses;
    return s;
}

STM *makeSTMwhile(EXP *expr, STMS *stmts, int lineno) {
    STM *s = malloc(sizeof(STM));
    s->lineno = lineno;
    s->kind = whileK;
    s->val.whileS.exp = expr;
    s->val.whileS.body = stmts;
    return s;
}

STM *makeSTMprint(EXP *expr, int lineno) {
    STM *s = malloc(sizeof(STM));
    s->lineno = lineno;
    s->kind = printK;
    s->val.printS.exp = expr;
    return s;
}

STM *makeSTMread(char *id, int lineno) {
    STM *s = malloc(sizeof(STM));
    s->lineno = lineno;
    s->kind = readK;
    s->val.readS.name = id;
    return s;
}

DECL *makeDECLint(char *id, EXP *value, int lineno) {
    DECL *d = malloc(sizeof(DECL));
    d->lineno = lineno;
    d->kind = assignInt;
    d->val.assignI.name = id;
    d->val.assignI.exp = value;
    return d;
}


DECL *makeDECLfloat(char *id, EXP *value, int lineno) {
    DECL *d = malloc(sizeof(DECL));
    d->lineno = lineno;
    d->kind = assignFloat;
    d->val.assignF.name = id;
    d->val.assignF.exp = value;
    return d;
}

DECL *makeDECLstring(char *id, EXP *value, int lineno) {
    DECL *d = malloc(sizeof(DECL));
    d->lineno = lineno;
    d->kind = assignString;
    d->val.assignS.name = id;
    d->val.assignS.exp = value;
    return d;
}

DECL *makeDECLbool(char *id, EXP *value, int lineno) {
    DECL *d = malloc(sizeof(DECL));
    d->lineno = lineno;
    d->kind = assignBool;
    d->val.assignB.name = id;
    d->val.assignB.exp = value;
    return d;
}

EXP *makeEXPid(char *id, int lineno) {
	EXP *e = malloc(sizeof(EXP));
	e->lineno = lineno;
	e->kind = idK;
	e->val.idE = id;
	return e;
}

EXP *makeEXPint(int intconst, int lineno) {
	EXP *e = malloc(sizeof(EXP));
	e->lineno = lineno;
	e->kind = intconstK;
	e->val.intconstE = intconst;
	return e;
}

EXP *makeEXPfloat(float floatconst, int lineno) {
	EXP *e = malloc(sizeof(EXP));
	e->lineno = lineno;
	e->kind = floatconstK;
	e->val.floatconstE = floatconst;
	return e;
}

EXP *makeEXPstring(char *str, int lineno) {
	EXP *e = malloc(sizeof(EXP));
	e->lineno = lineno;
	e->kind = stringconstK;
	e->val.stringconstE = str;
	return e;
}

EXP *makeEXPbool(int boolconst, int lineno) {
	EXP *e = malloc(sizeof(EXP));
	e->lineno = lineno;
	e->kind = boolconstK;
	e->val.boolconstE = boolconst;
	return e;
}

EXP *makeEXPtimes(EXP *left, EXP *right, int lineno) {
	EXP *e = malloc(sizeof(EXP));
	e->lineno = lineno;
	e->kind = timesK;
	e->val.timesE.left = left;
	e->val.timesE.right = right;
	return e;
}

EXP *makeEXPdiv(EXP *left, EXP *right, int lineno) {
	EXP *e = malloc(sizeof(EXP));
	e->lineno = lineno;
	e->kind = divK;
	e->val.divE.left = left;
	e->val.divE.right = right;
	return e; 
}

EXP *makeEXPplus(EXP *left, EXP *right, int lineno) {
	EXP *e = malloc(sizeof(EXP));
	e->lineno = lineno;
	e->kind = plusK;
	e->val.plusE.left = left;
	e->val.plusE.right = right;
	return e;
}

EXP *makeEXPminus(EXP *left, EXP *right, int lineno) {
	EXP *e = malloc(sizeof(EXP));
	e->lineno = lineno;
	e->kind = minusK;
	e->val.minusE.left = left;
	e->val.minusE.right = right;
	return e;
}

EXP *makeEXPequals(EXP *left, EXP *right, int lineno) {
	EXP *e = malloc(sizeof(EXP));
	e->lineno = lineno;
	e->kind = equalsK;
	e->val.equalsE.left = left;
	e->val.equalsE.right = right;
	return e;
}

EXP *makeEXPneq(EXP *left, EXP *right, int lineno) {
	EXP *e = malloc(sizeof(EXP));
	e->lineno = lineno;
	e->kind = neqK;
	e->val.neqE.left = left;
	e->val.neqE.right = right;
	return e;
}

EXP *makeEXPor(EXP *left, EXP *right, int lineno) {
	EXP *e = malloc(sizeof(EXP));
	e->lineno = lineno;
	e->kind = orK;
	e->val.orE.left = left;
	e->val.orE.right = right;
	return e;
}

EXP *makeEXPand(EXP *left, EXP *right, int lineno) {
	EXP *e = malloc(sizeof(EXP));
	e->lineno = lineno;
	e->kind = andK;
	e->val.andE.left = left;
	e->val.andE.right = right;
	return e;
}

EXP *makeEXPbang(EXP *expr, int lineno) {
	EXP *e = malloc(sizeof(EXP));
	e->lineno = lineno;
	e->kind = bangK;
	e->val.bangE.child = expr;
	return e;
}

EXP *makeEXPnegate(EXP *expr, int lineno) {
	EXP *e = malloc(sizeof(EXP));
	e->lineno = lineno;
	e->kind = negateK;
	e->val.negateE.child = expr;
	return e;
}

EXP *makeEXPparenthesis(EXP *expr, int lineno) {
	EXP *e = malloc(sizeof(EXP));
	e->lineno = lineno;
	e->kind = parenthesisK;
	e->val.parenthesisE.child = expr;
	return e;
}








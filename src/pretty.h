#ifndef PRETTY_H
#define PRETTY_H

#include "tree.h"

void prettyEXP(EXP *e);
void prettySTM(STM *s);
void prettyDECL(DECL *d);
void prettySTMS(STMS *s);
void prettyDECLS(DECLS *d);
void prettyPROG(PROG *p);

#endif /* !PRETTY_H */

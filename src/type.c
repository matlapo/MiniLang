#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "type.h"

extern PROG *program;

char* typeToString(type t) {
    switch (t) {
        case intk:
            return "int";
        case floatk:
            return "float";
        case stringk:
            return "string";
        case boolk:
            return "boolean";
        case none:
            return "unexpected_type";
    }
}

char* expectingType(type t) {
    switch (t) {
        case intk:
            return "'int'";
        case floatk:
            return "'int', 'float'";
        case stringk:
            return "'string'";
        case boolk:
            return "'bool'";
        case none:
            return "unexpected_type";
    }
}

//all the type rules are defined in this one function
type typeCheckEXP(EXP *e) {
    type left;
    type right;
    type typ;
    if (e == NULL)
        return none; //this might cause problems...
    switch (e->kind) {
        case idK:
            typ = getSymbol(e->val.idE);
            if (typ == none)
                printf("Error: (line %d) identifier \"%s\" not declared\n", e->lineno, e->val.idE);
            return getSymbol(e->val.idE);
        case intconstK:
            return intk;
        case floatconstK:
            return floatk;
        case stringconstK:
            return stringk;
        case boolconstK:
            return boolk;
        case timesK:
            left = typeCheckEXP(e->val.timesE.left);
            right = typeCheckEXP(e->val.timesE.right);
            if (right == none || left == none) return none;
            switch (left) {
                case intk:
                    if (right == intk)
                        return intk;
                    else if (right == floatk)
                        return floatk;
                    else if (right == stringk)
                        return stringk;
                    else if (right == boolk) 
                        printf("Error: (line %d) incompatible operands to '*' operation [int * boolean]\n", e->lineno);
                    return none;
                case floatk:
                    if (right == floatk)
                        return floatk;
                    else if (right == intk)
                        return floatk;
                    printf("Error: (line %d) incompatible operands to '*' operation [%s * %s]\n", e->lineno, typeToString(left), typeToString(right));
                    return none;
                case stringk:
                    if (right == intk)
                        return stringk;
                    printf("Error: (line %d) incompatible operands to '*' operation [%s * %s]\n", e->lineno, typeToString(left), typeToString(right));
                    return none;
                case boolk:
                    printf("Error: (line %d) incompatible operands to '*' operation [%s * %s]\n", e->lineno, typeToString(left), typeToString(right));
                    return none;
                default:
                    return none;
            }
        case divK:
            left = typeCheckEXP(e->val.divE.left);
            right = typeCheckEXP(e->val.divE.right);
            if (right == none || left == none) return none;
            switch (left) {
                case intk:
                    if (right == intk)
                        return intk;
                    else if (right == floatk)
                        return floatk;
                    printf("Error: (line %d) incompatible operands to '/' operation [%s / %s]\n", e->lineno, typeToString(left), typeToString(right));
                    return none;
                case floatk:
                    if (right == floatk)
                        return floatk;
                    else if (right == intk)
                        return floatk;
                    printf("Error: (line %d) incompatible operands to '/' operation [%s / %s]\n", e->lineno, typeToString(left), typeToString(right));
                    return none;
                case stringk:
                    printf("Error: (line %d) incompatible operands to '/' operation [%s / %s]\n", e->lineno, typeToString(left), typeToString(right));
                    return none;
                default:
                    return none;
            }
        case plusK:
            left = typeCheckEXP(e->val.plusE.left);
            right = typeCheckEXP(e->val.plusE.right);
            if (right == none || left == none) return none;
            switch (left) {
                case intk:
                    if (right == intk) 
                        return intk;
                    else if (right == floatk)
                        return floatk;
                    printf("Error: (line %d) incompatible operands to '+' operation [%s + %s]\n", e->lineno, typeToString(left), typeToString(right));
                    return none;
                case floatk:
                    if (right == floatk)
                        return floatk;
                    else if (right == intk)
                        return floatk;
                    printf("Error: (line %d) incompatible operands to '+' operation [%s + %s]\n", e->lineno, typeToString(left), typeToString(right));
                    return none;
                case stringk:
                    if (right == stringk)
                        return stringk;
                    printf("Error: (line %d) incompatible operands to '+' operation [%s + %s]\n", e->lineno, typeToString(left), typeToString(right));
                    return none;
                case boolk:
                    printf("Error: (line %d) incompatible operands to '+' operation [%s + %s]\n", e->lineno, typeToString(left), typeToString(right));
                    return none;
                default:
                    return none;
            }
        case minusK:
            left = typeCheckEXP(e->val.minusE.left);
            right = typeCheckEXP(e->val.minusE.right);
            if (right == none || left == none) return none;
            switch (left) {
                case intk:
                    if (right == intk)
                        return intk;
                    else if (right == floatk)
                        return floatk;
                    printf("Error: (line %d) incompatible operands to '-' operation [%s - %s]\n", e->lineno, typeToString(left), typeToString(right));
                    return none;
                case floatk:
                    if (right == floatk)
                        return floatk;
                    else if (right == intk)
                        return floatk;
                    printf("Error: (line %d) incompatible operands to '-' operation [%s - %s]\n", e->lineno, typeToString(left), typeToString(right));
                    return none;
                case stringk:
                    printf("Error: (line %d) incompatible operands to '-' operation [%s - %s]\n", e->lineno, typeToString(left), typeToString(right));
                    return none;
                case boolk:
                    printf("Error: (line %d) incompatible operands to '-' operation [%s - %s]\n", e->lineno, typeToString(left), typeToString(right));
                    return none;
                default:
                    return none;
            }
        case orK:
            left = typeCheckEXP(e->val.orE.left);
            right = typeCheckEXP(e->val.orE.right);
            if (right == none || left == none) return none;
            switch (left) {
                case boolk:
                    if (right == boolk || right == intk)
                        return boolk;
                    printf("Error: (line %d) incompatible operands to '||' operation [%s || %s]\n", e->lineno, typeToString(left), typeToString(right));
                    return none;
                case intk:
                    if (right == boolk || right == intk)
                        return boolk;
                    printf("Error: (line %d) incompatible operands to '||' operation [%s || %s]\n", e->lineno, typeToString(left), typeToString(right));
                    return none;
                case stringk:
                    printf("Error: (line %d) incompatible operands to '||' operation [%s || %s]\n", e->lineno, typeToString(left), typeToString(right));
                    return none;
                case floatk:
                    printf("Error: (line %d) incompatible operands to '||' operation [%s || %s]\n", e->lineno, typeToString(left), typeToString(right));
                    return none;
                default:
                    return none;
            }
        case andK:
            left = typeCheckEXP(e->val.andE.left);
            right = typeCheckEXP(e->val.andE.right);
            if (right == none || left == none) return none;
            switch (left) {
                case boolk:
                    if (right == boolk || right == intk)
                        return boolk;
                    printf("Error: (line %d) incompatible operands to '&&' operation [%s && %s]\n", e->lineno, typeToString(left), typeToString(right));
                    return none;
                case intk:
                    if (right == boolk || right == intk)
                        return boolk;
                    printf("Error: (line %d) incompatible operands to '&&' operation [%s && %s]\n", e->lineno, typeToString(left), typeToString(right));
                    return none;
                case floatk:
                    printf("Error: (line %d) incompatible operands to '&&' operation [%s && %s]\n", e->lineno, typeToString(left), typeToString(right));
                    return none;
                case stringk:
                    printf("Error: (line %d) incompatible operands to '&&' operation [%s && %s]\n", e->lineno, typeToString(left), typeToString(right));
                    return none;
                default:
                    return none;
            }
        case bangK:
            left = typeCheckEXP(e->val.bangE.child);
            if (left == none) return none;
            if (left == boolk) 
                return boolk;
            printf("Error: (line %d) incompatible operand to '!' operation [%s]\n", e->lineno, typeToString(left));
            return none;
        case negateK:
            left = typeCheckEXP(e->val.negateE.child);
            if (left == none) return none;
            if (left == intk)
                return intk;
            else if (left == floatk)
                return floatk;
            printf("Error: (line %d) incompatible operand to '-' operation [%s]\n", e->lineno, typeToString(left));
            return none;
        case equalsK:
            left = typeCheckEXP(e->val.equalsE.left);
            right = typeCheckEXP(e->val.equalsE.right);
            if (right == none || left == none) return none;
            switch (left) {
                case intk:
                    typ = intk;
                    break;
                case floatk:
                    typ = floatk;
                    break;
                case stringk:
                    typ = stringk;
                    break;
                case boolk:
                    typ = boolk;
                    break;
                case none:
                    return none;
            }
            if (right == typ) {
                return boolk;
            }
            printf("Error: (line %d) incompatible operands to '==' operation [%s == %s]\n", e->lineno, typeToString(left), typeToString(right));
            return none;
        case neqK:
            left = typeCheckEXP(e->val.neqE.left);
            right = typeCheckEXP(e->val.neqE.right);
            if (right == none || left == none) return none;
            switch (left) {
                case intk:
                    typ = intk;
                    break;
                case floatk:
                    typ = floatk;
                    break;
                case stringk:
                    typ = stringk;
                    break;
                case boolk:
                    typ = boolk;
                    break;
                case none:
                    return none;
            }
            if (right == typ)
                return boolk;
            printf("Error: (line %d) incompatible operands to '!=' operation [%s != %s]\n", e->lineno, typeToString(left), typeToString(right));
            return none;
        case parenthesisK:
            return typeCheckEXP(e->val.parenthesisE.child);
    }
}

int typeCheckDECLS(DECLS *d) {
    EXP *expr;
    char *name;
    if (d == NULL)
        return 0;
    switch (d->val.dec.decl->kind) {
        case assignInt:
            name = d->val.dec.decl->val.assignI.name;
            expr = d->val.dec.decl->val.assignI.exp;
            break;
        case assignFloat:
            name = d->val.dec.decl->val.assignF.name;
            expr = d->val.dec.decl->val.assignF.exp;
            break;
        case assignString:
            name = d->val.dec.decl->val.assignS.name;
            expr = d->val.dec.decl->val.assignS.exp;
            break;
        case assignBool:
            name = d->val.dec.decl->val.assignB.name;
            expr = d->val.dec.decl->val.assignB.exp;
            break;
    }
    type n = getSymbol(name);
    type e = typeCheckEXP(expr);
    if (n == none || e == none) return -1;
    if (n != e) {
        if (n == floatk && e == intk) //we accept this
            return typeCheckDECLS(d->val.dec.decls);
        printf("Error: (line %d) incompatible assignment [%s = %s] expected %s\n", d->val.dec.decl->lineno, typeToString(n), typeToString(e), expectingType(n));
        return -1;
    }
    return typeCheckDECLS(d->val.dec.decls);
}

int typeCheckSTMS(STMS *s) {
    if (s == NULL) 
        return 0;
    type n;
    type e;
    switch (s->val.st.stm->kind) {
        case assignK:
            n = getSymbol(s->val.st.stm->val.assignS.id);
            e = typeCheckEXP(s->val.st.stm->val.assignS.exp);
            if (n == none) {
                printf("Error: (line %d) identifier \"%s\" not declared\n", s->val.st.stm->lineno, s->val.st.stm->val.assignS.id);
            }
            if (n == none || e == none) return -1;
            if (n != e) {
                if (n == floatk && e == intk)
                    break;
                printf("Error: (line %d) incompatible assignment [%s = %s] expected %s\n", s->val.st.stm->lineno, typeToString(n), typeToString(e), expectingType(n));
                return -1;
            }
            break;
        case whileK:
            e = typeCheckEXP(s->val.st.stm->val.whileS.exp);
            if (e == none) return -1;
            if (e == floatk || e == stringk) {
                printf("Error: (line %d) while loop condition expected type 'boolean' or 'int', received '%s'\n", s->val.st.stm->lineno, typeToString(e));
                return -1;
            }
            if (typeCheckSTMS(s->val.st.stm->val.whileS.body) != 0) {
                return -1;
            }
            break;
        case ifK:
            e = typeCheckEXP(s->val.st.stm->val.ifS.exp);
            if (e == none) return -1;
            if (e == floatk || e == stringk) {
                printf("Error: (line %d) if condition expected type 'boolean' or 'int', received '%s'\n", s->val.st.stm->lineno, typeToString(e));
                return -1;
            }
            if (typeCheckSTMS(s->val.st.stm->val.ifS.body) != 0 || typeCheckSTMS(s->val.st.stm->val.ifS.elses) != 0) {
                return -1;
            }
            break;
        case printK:
            if (typeCheckEXP(s->val.st.stm->val.printS.exp) == none) 
                return -1;
            break;
        case readK:
            if (getSymbol(s->val.st.stm->val.readS.name) == none) {
                printf("Error: (line %d) identifier \"%s\" not declared\n", s->val.st.stm->lineno, s->val.st.stm->val.readS.name);
                return -1;
            }
            break;
    }

    return typeCheckSTMS(s->val.st.stms);

}

int typeCheckPROG(PROG *p) {
    if (typeCheckDECLS(p->val.prog.decls) == -1) {
        return -1;
    }
    if (typeCheckSTMS(p->val.prog.stmts) == -1) {
        return -1;
    }
    return 0;
}
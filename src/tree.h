#ifndef TREE_H
#define TREE_H


typedef struct EXP {
	int lineno;
	enum 
    {
        idK,
        intconstK,
        floatconstK, 
        stringconstK,
        boolconstK,
        timesK,
        divK,
        plusK,
        minusK,
        orK,
        andK,
        negateK,
        bangK,
        equalsK,
        neqK,
        parenthesisK
    } kind;
	union {
		char *idE;
		int intconstE;
        float floatconstE;
        char *stringconstE;
        int boolconstE;
		struct {struct EXP *left; struct EXP *right;} timesE;
		struct {struct EXP *left; struct EXP *right;} divE;
		struct {struct EXP *left; struct EXP *right;} plusE;
		struct {struct EXP *left; struct EXP *right;} minusE;
        struct {struct EXP *left; struct EXP *right;} orE;
        struct {struct EXP *left; struct EXP *right;} andE;
        struct {struct EXP *child;} negateE;
        struct {struct EXP *child;} bangE;
        struct {struct EXP *left; struct EXP *right;} equalsE;
        struct {struct EXP *left; struct EXP *right;} neqE;
        struct {struct EXP *child;} parenthesisE;
	} val;
} EXP;

typedef struct DECL {
    int lineno;
    enum 
    {
        assignInt,
        assignFloat,
        assignString,
        assignBool
    } kind;
    union {
		struct {char *name; struct EXP *exp;} assignI;
		struct {char *name; struct EXP *exp;} assignF;
		struct {char *name; struct EXP *exp;} assignS;
		struct {char *name; struct EXP *exp;} assignB;
    } val;
} DECL;

typedef struct DECLS { //no need for lineno right?
    union {
        struct {struct DECL *decl; struct DECLS *decls;} dec;
    } val;
} DECLS;

typedef struct STM {
    int lineno;
    enum 
    {
        assignK,
        whileK,
        printK,
        readK,
        ifK
    } kind;
    union {
		struct {char *id; struct EXP *exp;} assignS;
		struct {struct EXP *exp; struct STMS *body; struct STMS *elses;} ifS;
		struct {struct EXP *exp; struct STMS *body;} whileS;
		struct {struct EXP *exp;} printS;
		struct {char *name;} readS;
    } val;
} STM;

typedef struct STMS {
    union {
        struct {struct STM *stm; struct STMS *stms;} st;
    } val;
} STMS;

 
typedef struct PROG {
    union {
        struct {struct DECLS *decls; struct STMS *stmts;} prog;
    } val;
} PROG;

PROG *makePROG(DECLS *decls, STMS *stmts);

DECLS *makeDECLS(DECL *decl, DECLS *decls);
STMS *makeSTMS(STM *stm, STMS *stms);

DECL *makeDECLint(char *id, EXP *value, int lineno);
DECL *makeDECLfloat(char *id, EXP *value, int lineno);
DECL *makeDECLstring(char *id, EXP *value, int lineno);
DECL *makeDECLbool(char *id, EXP *value, int lineno);

STM *makeSTMassign(char *id, EXP *value, int lineno);
STM *makeSTMif(EXP *expr, STMS *stmts, STMS *elses, int lineno);
STM *makeSTMwhile(EXP *expr, STMS *stmst, int lineno);
STM *makeSTMprint(EXP *expr, int lineno);
STM *makeSTMread(char *id, int lineno);
 
EXP *makeEXPid(char *id, int lineno);
EXP *makeEXPfloat(float val, int lineno);
EXP *makeEXPstring(char *val, int lineno);
EXP *makeEXPbool(int val, int lineno);
EXP *makeEXPint(int intconst, int lineno);
EXP *makeEXPtimes(EXP *left, EXP *right, int lineno);
EXP *makeEXPdiv(EXP *left, EXP *right, int lineno);
EXP *makeEXPplus(EXP *left, EXP *right, int lineno);
EXP *makeEXPminus(EXP *left, EXP *right, int lineno);
EXP *makeEXPor(EXP *left, EXP *right, int lineno);
EXP *makeEXPand(EXP *left, EXP *right, int lineno);
EXP *makeEXPnegate(EXP *child, int lineno);
EXP *makeEXPbang(EXP *child, int lineno);
EXP *makeEXPequals(EXP *left, EXP *right, int lineno);
EXP *makeEXPneq(EXP *left, EXP *right, int lineno);
EXP *makeEXPparenthesis(EXP *expr, int lineno);


#endif /* !TREE_H */

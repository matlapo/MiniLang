#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "codegen.h"

int currentIdent = 0;

//if the string is a constant use its length for malloc, otherwise use 10 (arbitrary)
int getStringLength(EXP *e) {
    switch (e->kind) {
        case stringconstK:
            return strlen(e->val.stringconstE);
        default:
            return 10;
    }
}

//this function is taken from https://stackoverflow.com/questions/22599556/return-string-of-characters-repeated-x-times
static const char repeatFunction[] = "char* v__repeat(const char *s, int x) {\n"
    "\tif(s) {\n"
        "\t\tint i, count = 0;\n"
        "\t\twhile(s[count] != \'\\0\'){\n"
        "\t\t\t++count;\n"
        "\t\t}\n"
        "\t\tchar *newArray = malloc(count * x + 1);\n"
        "\t\tif(newArray) {\n"
            "\t\t\tchar *na = newArray;\n"
            "\t\t\tfor(i = 0; i < x; ++i) {\n"
                "\t\t\t\tconst char *p=s;\n"
                "\t\t\t\twhile(*p)\n"
                    "\t\t\t\t\t*na++ = *p++;\n"
            "\t\t\t}\n"
            "\t\t\t*na = \'\\0\';\n"
        "\t\t}\n"
        "\t\t\treturn newArray;\n"
    "\t\t} else {\n"
        "\t\t\treturn NULL;\n"
    "\t}\n"
"}\n";

static const char concatFunction[] = "char* v__strcat(char *dest, char *src)\n"
"{\n"
    "\tchar *dest2 = malloc(sizeof(char)*(strlen(dest) + strlen(src) + 30));\n"
    "\tstrcpy(dest2, dest);\n"
    "\tsize_t i,j;\n"
    "\tfor (i = 0; dest2[i] != \'\\0\'; i++)\n"
        "\t\t;\n"
    "\tfor (j = 0; src[j] != \'\\0\'; j++)\n"
        "\t\tdest2[i+j] = src[j];\n"
    "\tdest2[i+j] = \'\\0\';\n"
    "\treturn dest2;\n"
"}\n";

void codegenEXP(EXP *e)
{ 
    switch (e->kind) {
    case idK:
         printf("__%s",e->val.idE);
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
            printf("%s", "false");
         else 
            printf("%s", "true");
         break;
    case timesK:
         if (typeCheckEXP(e->val.timesE.left) == stringk && typeCheckEXP(e->val.timesE.right) == intk) {
             printf("v__repeat(");
             codegenEXP(e->val.timesE.left);
             printf(", ");
             codegenEXP(e->val.timesE.right);
             printf(")");
         } else if (typeCheckEXP(e->val.timesE.left) == intk && typeCheckEXP(e->val.timesE.right) == stringk) {
             printf("v__repeat(");
             codegenEXP(e->val.timesE.right);
             printf(", ");
             codegenEXP(e->val.timesE.left);
             printf(")");
         } else {
            printf("(");
            codegenEXP(e->val.timesE.left);
            printf(" * ");
            codegenEXP(e->val.timesE.right);
            printf(")");
         }
         break;
    case divK:
         printf("(");
         codegenEXP(e->val.divE.left);
         printf(" / ");
         codegenEXP(e->val.divE.right);
         printf(")");
         break;
    case plusK:
         if (typeCheckEXP(e->val.plusE.left) == stringk) {
             printf("v__strcat(");
             codegenEXP(e->val.plusE.left);
             printf(", ");
             codegenEXP(e->val.plusE.right);
             printf(")");
             break;
         }
         printf("(");
         codegenEXP(e->val.plusE.left);
         printf(" + ");
         codegenEXP(e->val.plusE.right);
         printf(")");
         break;
    case minusK:
         printf("(");
         codegenEXP(e->val.minusE.left);
         printf(" - ");
         codegenEXP(e->val.minusE.right);
         printf(")");
         break;
    case orK:
         printf("(");
         codegenEXP(e->val.orE.left);
         printf("||");
         codegenEXP(e->val.orE.right);
         printf(")");
         break;
    case andK:
         printf("(");
         codegenEXP(e->val.andE.left);
         printf("&&");
         codegenEXP(e->val.andE.right);
         printf(")");
         break;
    case negateK:
         printf("-(");
         codegenEXP(e->val.negateE.child);
         printf(")");
         break;
    case bangK:
         printf("!(");
         codegenEXP(e->val.bangE.child);
         printf(")");
         break;
    case equalsK:
        printf("(");
         codegenEXP(e->val.equalsE.left);
         printf(" == ");
         codegenEXP(e->val.equalsE.right);
         printf(")");
         break;
    case neqK:
         printf("(");
         codegenEXP(e->val.equalsE.left);
         printf(" != ");
         codegenEXP(e->val.equalsE.right);
         printf(")");
         break;
    case parenthesisK:
         codegenEXP(e->val.parenthesisE.child);
         break;
  }
}

void codegenDECL(DECL *d)
{ 
    printf("\t");
    switch (d->kind) {
        case assignInt:
            printf("int ");
            printf("__%s", d->val.assignI.name);
            printf(" = ");
            codegenEXP(d->val.assignI.exp);
            break;
        case assignFloat:
            printf("float ");
            printf("__%s", d->val.assignF.name);
            printf(" = ");
            codegenEXP(d->val.assignF.exp);
            break;
        case assignString:
            printf("char* ");
            printf("__%s", d->val.assignS.name);
            printf(" = malloc(sizeof(char)*%d);\n", 10*getStringLength(d->val.assignS.exp));
            printf("\tstrcpy(__%s, ", d->val.assignS.name);
            codegenEXP(d->val.assignS.exp);
            printf(");\n");
            break;
        case assignBool:
            printf("bool ");
            printf("__%s", d->val.assignB.name);
            printf(" = ");
            codegenEXP(d->val.assignB.exp);
            break;
  }
}

void codegenSTM(STM *s)
{ 
    int i = 0;
    char* str = "%";
    for (i = 0; i < currentIdent; i++) printf("\t");
    switch (s->kind) {
    case assignK:
        printf("__%s", s->val.assignS.id);
        printf(" = ");
        codegenEXP(s->val.assignS.exp);
        printf(";\n");
        break;
    case whileK:
        printf("while (");
        codegenEXP(s->val.whileS.exp);
        printf(") {\n");
        currentIdent++;
        codegenSTMS(s->val.whileS.body);
        currentIdent = currentIdent - 1;
        for (i = 0; i < currentIdent; i++) printf("\t");
        printf("}\n");
        break;
    case ifK:
        printf("if (");
        codegenEXP(s->val.ifS.exp);
        printf(") {\n");
        currentIdent++;
        codegenSTMS(s->val.ifS.body);
        currentIdent = currentIdent - 1;
        for (i = 0; i < currentIdent; i++) printf("\t");
        printf("}\n");
        if (s->val.ifS.elses != NULL) {
            for (i = 0; i < currentIdent; i++) printf("\t");
            printf("else {\n");
            currentIdent++;
            codegenSTMS(s->val.ifS.elses);
            currentIdent = currentIdent - 1;
            for (i = 0; i < currentIdent; i++) printf("\t");
            printf("}\n");
        }
        break;
    case printK:
        printf("printf(\"");
        switch (typeCheckEXP(s->val.printS.exp)) {
            case intk:
                printf("%sd", str);
                break;
            case floatk:
                printf("%sf", str);
                break;
            case stringk:
                printf("%ss", str);
                break;
            case boolk:
                printf("%sd", str);
                break;
            case none:
                printf("%ss", str); //shouldn't happen, if it does use string format
                break;
        }
        printf("\\n\", ");
        codegenEXP(s->val.printS.exp);
        printf(");\n");
        break;
    case readK:
        printf("scanf(\"");
        switch (getSymbol(s->val.readS.name)) {
            case intk:
                printf("%sd", str);
                break;
            case floatk:
                printf("%sf", str);
                break;
            case stringk:
                printf("%ss", str);
                break;
            case boolk:
                printf("%sd", str);
                break;
            case none:
                printf("%ss", str); //shouldn't happen, if it does use string format
                break;
        }
        printf("\", &__%s);\n", s->val.readS.name);
        break;
 }
}

void codegenDECLS(DECLS *ds) //doesnt cover empty programs
{ 
    if (ds != NULL) {
        if (ds->val.dec.decl != NULL) { //useless
            codegenDECL(ds->val.dec.decl);
            printf(";\n");
        }
        if (ds->val.dec.decls != NULL)
            codegenDECLS(ds->val.dec.decls);
    }
}

void codegenSTMS(STMS *ss)
{
    if (ss != NULL) {
        if (ss->val.st.stm != NULL) 
            codegenSTM(ss->val.st.stm);
        if (ss->val.st.stms != NULL) 
            codegenSTMS(ss->val.st.stms);
    }
}

void codegenPROG(PROG *p, char* filename) 
{
    currentIdent = 1;
    close(1);
    open(strcat(filename, ".c"), O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (p != NULL) {
        printf("#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n#include <stdbool.h>\n\n");
        printf("%s\n", repeatFunction);
        printf("%s\n", concatFunction);
        printf("\nint main() {\n");
        if (p->val.prog.decls != NULL)
            codegenDECLS(p->val.prog.decls);
        printf("\n");
        if (p->val.prog.stmts != NULL)
            codegenSTMS(p->val.prog.stmts);
        printf("\n\treturn 0;\n}\n");
    }
}

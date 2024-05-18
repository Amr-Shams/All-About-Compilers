#include "helpers.h"

nodeType *operation(int oper, int nops, ...) {
    va_list ap;
    nodeType *p;
    int i;
    if ((p = (nodeType* )malloc(sizeof(nodeType) + (nops - 1)*sizeof(nodeType*))) == NULL)
        yyerror("out of memory");
    p->type = Operator_Node;
    p->oper.oper = oper;
    p->oper.nops = nops;
    va_start(ap, nops);
    for (i = 0; i < nops; i++)
        p->oper.op[i] = va_arg(ap, nodeType*);
    va_end(ap);
    return p;
}
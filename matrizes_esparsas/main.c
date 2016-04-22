#include "matrix.h"

int main(){
        Matrix *m, *n, *r;

        matrix_create(&m);
        matrix_create(&n);

        matrix_print(m);
        matrix_print(n);

        matrix_add(m,n,&r);

        matrix_destroy(m);
        matrix_destroy(n);

        return 0;
}

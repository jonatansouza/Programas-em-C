#include "matrix.h"

int main(){
        Matrix *m, *n;
        Matrix *r;

        matrix_create(&m);
        matrix_create(&n);

        matrix_print(m);
        matrix_print(n);

        //matrix_add(m,n,&r);
        //matrix_multiply(m, n, &r);
        matrix_transpose(n, &r);
        matrix_print(r);

        matrix_destroy(m);
        matrix_destroy(n);
        matrix_destroy(r);

        return 0;
}

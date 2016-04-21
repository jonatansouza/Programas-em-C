#include <stdio.h>

void input_values(){

        float numbers[1000];
        int size = 0, i;
        for(i=0; i<100; i++) {
                scanf("%f", &numbers[size]);
                if(numbers[size] == 0)
                        break;
                size++;
        }
        for(i=0; i<size; i++) {
                printf("%f\n", numbers[i]);
        }
}

int main(int argc, char const *argv[]) {
        input_values();
        return 0;
}

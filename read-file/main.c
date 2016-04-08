#include <stdio.h>

int main(int argc, char *argv[]){
	
	 char str[100];
     scanf("%[^EOF]", str);
     printf("CONTEUDO DO ARQUIVO:\n%s\n", str);  
     return 0; 
}

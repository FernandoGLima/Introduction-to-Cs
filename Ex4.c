#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, aux, rev=0;

    printf("Digite o numero:\n");
    scanf("%d", &n);

    aux=n;

    while(aux!=0){
        rev=rev*10+aux%10;
        aux=aux/10;
    }
    if(rev==n){
        printf("O numero %d eh palindromo", n);
    }
    else
        printf("O numero nao eh palindromo");

return 0;
}

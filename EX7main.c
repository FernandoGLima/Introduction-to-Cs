#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int main()
{
    int n, A[MAX][MAX], i, j, flag=1, l=1, soma=0, padrao;

    printf("Digite o numero que sera a dimensao da matriz quadrada: \n");
    scanf("%d",&n);

    for(i=0; i<n; i++){
        printf("Digite os numeros da linha %d \n", l);

            for(j=0; j<n; j++){
               scanf("%d", &A[i][j]);
            }
        l++;
    }

    for(i=0; i<n; i++){
         for(j=0; j<n; j++){
              soma=soma+A[i][j];
         }

         if(i==0){
            padrao=soma;
         }
        else if(padrao!=soma){
            flag=0;
        }
    soma=0;
    }

    if(flag==1){
         for(i=0; i<n; i++){
              for(j=0; j<n; j++){
                  soma=soma+A[j][i];
              }

              if(padrao!=soma){
                  flag=0;
              }
         soma=0;
        }
     }

    if(flag==1){
        for(i=0; i<n; i++){
            soma=soma+A[i][i];
        }

        if(padrao!=soma){
                flag=0;
        }
    }
soma=0;

    if(flag==1){
        for(i=0; i<n; i++){
             soma=soma+A[i][n-i-1];
        }

        if(padrao!=soma){
            flag=0;
        }
    }


    if(flag==0){
        printf("A matriz nao eh um quadrado magico\n");
    }
    else{
        printf("A matriz eh um quadrado magico!!\n");
    }

    return 0;
}

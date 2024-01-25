#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int main()
{
    int m, n, i, cont, seq[MAX], s2[MAX], v1, aux;

    printf("Digite a quantidade de numeros da primeira e da segunda sequencia; \n");
    scanf("%d %d", &m, &n);

    printf("Digite os numeros da primeira sequencia (Sem numero repetido): \n");

    for(i=0; i<m; i++){
        scanf("%d", &seq[i]);

           for(v1=0; v1<i; v1++){
              if(seq[v1]==seq[i]){
                printf("Voce digitou um numero repetido, digite outro numero novamente: \n");
                i--;
              }
           }
    }

    printf("Digite os numeros da segunda sequencia: \n");

    for(cont=0; cont<n; cont++){
        scanf("%d", &s2[cont]);

           for(v1=0; v1<cont; v1++){
              if(s2[v1]==s2[cont]){
                printf("Voce digitou um numero repetido, digite outro numero: \n");
                cont--;
              }
           }
    }


    for(cont=0; cont<n; cont++){
            seq[i]=s2[cont];

            for(v1=0; v1<i; v1++){
                  if(seq[v1]==seq[i]){
                      i--;
                  }
            }
        i++;
     }

     for(cont=0; cont<i; cont++){
        for(v1=0; v1<i-1; v1++){
            if(seq[v1]>seq[v1+1]){
               aux=seq[v1];
               seq[v1]=seq[v1+1];
               seq[v1+1]=aux;
            }
        }
     }

     printf("A sequencia ordenada: \n");

     for(cont=0; cont<i; cont++)
        printf("%d\n", seq[cont]);


    return 0;
}

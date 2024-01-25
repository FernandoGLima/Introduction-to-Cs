#include <stdio.h>
#include <stdlib.h>
#define max 256

int *load_image_from_file(char *filenam, int *w, int *h){
     FILE *arq;

     int line[max], *I, i, m;

     arq=fopen(filenam, "r");
    if(arq==NULL){
        printf("Nao abriu o arquivo, por favor verifique novamente o nome do arquivo\n");
    }

    fscanf(arq, "%[^\n]\n", line);
    fscanf(arq, "%d %d", &*w, &*h);
    fscanf(arq, "%d", &m);

    I= malloc(sizeof(int)*(*w)*(*h));
    if(I==NULL){
        printf("Deu erro a alocacao\n");
    }

    for(i=0; i<*h*(*w); i++){
        fscanf(arq, "%d ", &I[i]);
    }

    fclose(arq);
    return I;
}


void save_image_to_file(char *fil, int *I, int w, int h){

     FILE *arq;

     int i, j;

     arq=fopen(fil, "w");
     if(arq==NULL){
        printf("Nao abriu o arquivo\n");
     }

    fprintf(arq, "P2\n");
    fprintf(arq, "%d %d\n", w, h);
    fprintf(arq, "255\n");

    for(i=0; i<h; i++){
        for(j=0; j<w; j++){
            fprintf(arq, "%d ", I[i*w+j]);
        }
        fprintf(arq, "\n");
    }
}


int *binarize(int *I, int w, int h, int t){
     int *R, i;

     R=malloc(sizeof(int)*h*w);
     if(R==NULL){
        printf("A alocacao deu erro");
     }

     for(i=0; i<w*h; i++){
        if(I[i]>=t){
            R[i]=255;
        }
        else{
            R[i]=0;
        }
     }

     return R;
}


int *invert_image(int *I, int w, int h){
    int i, *R;

    R=malloc(sizeof(int)*h*w);
    if(R==NULL){
        printf("Alocacao deu erro");
    }

     for(i=0; i<h*w; i++){
        R[i]=255-I[i];
    }

    return R;
}


/* Dicionario: I= vetor entrada, R= vetor copia para alarga o filtro, h=altura da matriz, w= largura, tipo= tipo do filtro,
    d= (numero impar) que sera o tamanho da mini matriz dxd que servira nas funções de minimo, maximo, etc,
    (d-1)/2= tamanho de linha/coluna que foi aumentada na matriz copia, w+(d-1)= largura nova. h+(d-1)= altura nova
    i e j = cordenadas da matriz
    i<h+(d-1)/2= altura que vai ate a matriz antiga*/

int *filter_image(int *I, int w, int h, int d, int tipo){
    int i, j, *Rc, cont=0, *Rdevolve;


    Rc= malloc(sizeof(int)*(h+d-1)*(w+d-1));
    if(Rc==NULL){
        printf("A alocacao deu erro");
    }
    Rdevolve= malloc(sizeof(int)*h*w);
    if(Rdevolve==NULL){
        printf("A alocacao deu erro");
    }

    /*Preencher o centro da matriz filtro*/
    for(i=(d-1)/2; i<h+((d-1)/2); i++){
        for(j=(d-1)/2; j<w+((d-1)/2); j++){
            Rc[i*(w+d-1)+j]=I[cont];
            cont++;
        }
    }

    cont=0;
    /*Preencher linhas adicionais superiores*/
    for(i=0; i<(d-1)/2; i++){
        for(j=(d-1)/2; j<w+((d-1)/2); j++){
            Rc[i*(w+d-1)+j]=I[cont];
            cont++;
        }
        cont=0;
    }

    /*Preencher linhas adicionais inferiores*/
    for(i=h+((d-1)/2); i<h+(d-1); i++){
        for(j=(d-1)/2; j<w+((d-1)/2); j++){
            Rc[i*(w+d-1)+j]=I[(h*w)-w+cont];
            cont++;
        }
        cont=0;
    }

    /*Preencher linhas adicionais a esquerda*/
    for(j=0; j<(d-1)/2; j++){
        for(i=(d-1)/2; i<h+((d-1)/2); i++){
            Rc[i*(w+d-1)+j]=I[cont];
            cont+=w;
        }
        cont=0;
    }

    cont=w-1;
    /*Preencher linhas adicionais a direita*/
    for(j=w+(d-1)/2; j<w+(d-1); j++){
        for(i=(d-1)/2; i<h+((d-1)/2); i++){
            Rc[i*(w+d-1)+j]=I[cont];
            cont+=w;
        }
        cont=w-1;
    }

    cont=0;
    /*Preencher o canto superior esquerdo*/
    for(i=0; i<(d-1)/2; i++){
        for(j=0; j<(d-1)/2; j++){
            Rc[i*(w+d-1)+j]=I[cont];
        }
    }

    cont=w-1;
    /*Preencher canto superior direito*/
    for(i=0; i<(d-1)/2; i++){
        for(j=w+(d-1)/2; j<w+d-1; j++){
            Rc[i*(w+d-1)+j]=I[cont];
        }
    }

    cont=(h*w)-w;
    /*Preencher canto inferior esquerdo*/
    for(i=h+(d-1)/2; i<h+d-1; i++){
        for(j=0; j<(d-1)/2; j++){
            Rc[i*(w+d-1)+j]=I[cont];
        }
    }

    cont=(h*w)-1;
    /*Preencher canto inferior direito*/
    for(i=h+(d-1)/2; i<h+d-1; i++){
        for(j=w+(d-1)/2; j<w+d-1; j++){
            Rc[i*(w+d-1)+j]=I[cont];
        }
    }
    cont=0;
    if(tipo==1){
        for(i=(d-1)/2; i<h+(d-1)/2; i++){
            for(j=(d-1)/2; j<w+(d-1)/2; j++){
                Rdevolve[cont]=minimo(Rc, h, w, d, i, j);
                cont++;
            }
        }
    }
    else if(tipo==2){ cont=0;
            for(i=(d-1)/2; i<h+(d-1)/2; i++){
                for(j=(d-1)/2; j<w+(d-1)/2; j++){
                    Rdevolve[cont]= mediana(Rc, h, w, d, i, j);
                    cont++;
                }
            }
    }
    else{ cont=0;
            for(i=(d-1)/2; i<h+(d-1)/2; i++){
                for(j=(d-1)/2; j<w+(d-1)/2; j++){
                    Rdevolve[cont]= maximo(Rc, h, w, d, i, j);
                    cont++;
                }
            }
    }

    free(Rc); Rc=NULL;

    return Rdevolve;
}


int minimo(int *V, int h, int w, int d, int i, int j){
    int cont1, cont2, menorelement;

    menorelement=V[i*(w+d-1)+j];

    for(cont1=i-(d-1)/2; cont1<i+1+(d-1)/2; cont1++){
        for(cont2=j-(d-1)/2; cont2<j+1+(d-1)/2; cont2++){
            if(V[cont1*(w+d-1)+cont2]<menorelement){
                menorelement=V[cont1*(w+d-1)+cont2];
            }
        }
    }

    return menorelement;
}


int maximo(int *V, int h, int w, int d, int i, int j){
    int cont1, cont2, maiorelement;

    maiorelement=V[i*(w+d-1)+j];

    for(cont1=i-(d-1)/2; cont1<i+1+(d-1)/2; cont1++){
        for(cont2=j-(d-1)/2; cont2<j+1+(d-1)/2; cont2++){
            if(V[cont1*(w+d-1)+cont2]>maiorelement){
                maiorelement=V[cont1*(w+d-1)+cont2];
            }
        }
    }
    return maiorelement;
}


int mediana(int *V, int h, int w, int d, int i, int j){
    int cont1, cont2, *Ord, cont3=0, aux, devolve;

    Ord= malloc(sizeof(int)*d*d);
    if(Ord==NULL){
        printf("Alocacao deu erro!\n");
    }

    for(cont1=i-(d-1)/2; cont1<i+1+(d-1)/2; cont1++){
        for(cont2=j-(d-1)/2; cont2<j+1+(d-1)/2; cont2++){
            Ord[cont3]=V[cont1*(w+d-1)+cont2];
            cont3++;
        }
    }

    for(cont1=0; cont1<cont3-1; cont1++){
        for(cont2=cont1+1; cont2<cont3; cont2++){
            if(Ord[cont1]>Ord[cont2]){
                aux=Ord[cont1];
                Ord[cont1]=Ord[cont2];
                Ord[cont2]=aux;
            }
        }
    }

    devolve=Ord[((d*d)-1)/2];
    free(Ord); Ord=NULL;

     return devolve;
}


int *label_components(int *I, int w, int h, int *ncc){
     int i, j, *R;

     R= malloc(sizeof(int)*h*w);
     if(R==NULL){
        printf("A alocacao deu erro\n");
     }

     for(i=0; i<h*w; i++){
        R[i]=I[i];
     }

     for(i=0; i<h; i++){
        for(j=0; j<w; j++){
            if(R[i*w+j]==255){
                R[i*w+j]= *ncc;
                retorna(R, w, h, i, j, *ncc);
                *ncc=*ncc+1;
            }
        }
     }
     *ncc=*ncc-1;
     if(*ncc<=127){
        for(i=0; i<h*w; i++){
            R[i]=R[i]*(255/(*ncc));
        }
     }

     return R;
}

void retorna(int *R, int w, int h, int i, int j, int ncc){
    int cont1, cont2;

    for(cont1=i-1; cont1<i+2; cont1++){
        for(cont2=j-1; cont2<j+2; cont2++){
            if(cont1>=0 && cont2>=0 && cont1<h && cont2<w){
                    if(R[cont1*w+cont2]==255){
                        R[cont1*w+cont2]= ncc;
                        retorna(R, w, h, cont1, cont2, ncc);
                    }
            }
        }
    }
}

int main()
{
    char fil[max], filenam[max], opcao[1];
    int *I, *R=NULL, w, h, t, d, tipo, ncc=1, i, j;

    printf("-------------------------------------\n");
    printf("Escolha uma opcao:\n");
    printf("Q - Quit\n");
    printf("L - Ler um arquivo\n");
    printf("S - Salvar imagem em arquivo\n");
    printf("M - Manter entrada anterior\n\n");
    printf("B - Binarizar a imagem\n");
    printf("C - Contorno da imagem\n");
    printf("I - Inverter a imagem\n");
    printf("F - Filtrar a imagem\n");
    printf("R - Rotular os componentes conexos\n");
    printf("-------------------------------------\n");
    scanf("%s", &opcao);

    while(opcao[0]!='Q' && opcao[0]!='L'){
        printf("Escolha uma opcao valida!: Q - Quit ou L - Ler uma imagem de um arquivo para inciar as operacoes\n");
        scanf("%s", &opcao);
    }

    if(opcao[0]=='L'){
        printf("\nDigite o nome do arquivo de entrada:\n");
        scanf("%s", &filenam);
        printf("\n");

        I= load_image_from_file(filenam, &w, &h);

        while(opcao[0]!='Q'){
            printf("-------------------------------------\n");
            printf("Escolha uma opcao:\n");
            printf("Q - Quit\n");
            printf("L - Ler um arquivo\n");
            printf("S - Salvar imagem em arquivo\n");
            printf("M - Manter entrada anterior\n\n");
            printf("B - Binarizar a imagem\n");
            printf("C - Contorno da imagem\n");
            printf("I - Inverter a imagem\n");
            printf("F - Filtrar a imagem\n");
            printf("R - Rotular os componentes conexos\n");
            printf("-------------------------------------\n");
            scanf("%s", &opcao);


            if(opcao[0]=='L'){
                free(I); I=NULL;
                free(R); R=NULL;

                printf("\nDigite o nome do arquivo de entrada:\n");
                scanf("%s", &filenam);
                printf("\n");

                I= load_image_from_file(filenam, &w, &h);
            }


            else if(opcao[0]=='M'){
                free(R); R=NULL;

                printf("**A imagem de entrada foi mantida!\n\n");
            }


            else if(opcao[0]=='B'){

                if(R==NULL){
                    printf("Digite o limiar:\n");
                    scanf("%d", &t);

                    R= binarize(I, w, h, t);

                    printf("**Imagem foi binarizada!\n\n");
                }

                else{
                    free(I), I=NULL;
                    I=R;

                    printf("Digite o limiar:\n");
                    scanf("%d", &t);

                    R= binarize(I, w, h, t);

                    printf("**Imagem foi binarizada!\n\n");
                }
            }


            else if(opcao[0]=='I'){
                if(R==NULL){
                    R= invert_image(I, w, h);

                    printf("**A imagem foi invertida!\n\n");
                }

                else{
                    free(I); I=NULL;
                    I=R;

                    R= invert_image(I, w, h);

                    printf("**A imagem foi invertida!\n\n");
                }
            }


            else if(opcao[0]=='F'){
                if(R==NULL){
                    printf("Digite o tamanho do filtro:\n");
                    scanf("%d", &d);
                         while(d%2==0){
                            printf("O tamanho deve ser um numero impar, por favor digite novamente!:\n");
                            scanf("%d", &d);
                         }
                    printf("Digite o tipo do filtro: 1-Minimo, 2-Mediana, 3-Maximo\n");
                    scanf("%d", &tipo);
                         while(tipo!=1 && tipo!=2 && tipo!=3){
                            printf("Digite um valor valido para o tipo: 1,2 e 3\n");
                            scanf("%d", &tipo);
                         }

                    R= filter_image(I, w, h, d, tipo);

                    printf("**Imagem foi filtrada!\n\n");
                }

                else{
                    free(I); I=NULL;
                    I=R;

                    printf("Digite o tamanho do filtro:\n");
                    scanf("%d", &d);
                         while(d%2==0){
                            printf("O tamanho deve ser um numero impar, por favor digite novamente!:\n");
                            scanf("%d", &d);
                         }
                    printf("Digite o tipo do filtro: 1-Minimo, 2-Mediana, 3-Maximo\n");
                    scanf("%d", &tipo);
                         while(tipo!=1 && tipo!=2 && tipo!=3){
                            printf("Digite um valor valido para o tipo: 1,2 ou 3\n");
                            scanf("%d", &tipo);
                         }

                    R= filter_image(I, w, h, d, tipo);

                    printf("**Imagem foi filtrada!\n\n");

                }
            }


            else if(opcao[0]=='R'){
                if(R==NULL){
                    R= label_components(I, w, h, &ncc);

                    printf("**Imagem foi rotulada!\n");
                    printf("Numeros de componentes conexos: %d\n\n", ncc);
                }

                else{
                    free(I); I=NULL;
                    I=R;

                    R= label_components(I, w, h, &ncc);

                    printf("**Imagem foi rotulada!\n");
                    printf("Numeros de componentes conexos: %d\n\n", ncc);
                }
            }


            else if(opcao[0]=='S'){
                printf("Digite o nome do arquivo de saida:\n");
                scanf("%s", &fil);

                if(R!=NULL){
                    save_image_to_file(fil, R, w, h);

                    printf("**Imagem gravada no arquivo: %s\n\n", fil);
                }
                else{
                    save_image_to_file(fil, I, w, h);

                    printf("**Imagem gravada no arquivo: %s\n\n", fil);
                }
            }


            else if(opcao[0]=='C'){
                if(R==NULL){
                    d=3; tipo=1;

                    R= filter_image(I, w, h, d, tipo);

                    for(i=0; i<h; i++){
                        for(j=0; j<w; j++){
                           R[i*w+j]=I[i*w+j]-R[i*w+j];
                        }
                    }

                    printf("**Contorno foi calculado!\n\n");
                }

                else{
                    free(I); I=NULL;
                    I=R;

                    d=3; tipo=1;

                    R= filter_image(I, w, h, d, tipo);

                    for(i=0; i<h; i++){
                        for(j=0; j<w; j++){
                           R[i*w+j]=I[i*w+j]-R[i*w+j];
                        }
                    }

                    printf("**Contorno foi calculado!\n\n");
                }
            }


            else if(opcao[0]!='Q'){
                printf("Voce digitou uma letra invalida, digite novamente:\n\n");
            }
        }
    }

    return 0;
}

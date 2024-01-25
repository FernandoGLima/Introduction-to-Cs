#include <stdio.h>
#include <stdlib.h>
#define PI 3.14159
#define RADIO_AP 200
#define RADIO_ZA 2000
#define DELTA_ALARME 60
#define EPS_COS 0.000001
#define EPS 0.01


double raiz(double x, double epsilon){
      double anterior, posterior, condic=1;

      anterior=x;
      if(x==0){
        return 0;
      }
      else{
        while(condic>epsilon){
             posterior=(anterior+x/anterior)/2;
             condic=anterior-posterior;
             if(condic<0){
                 condic*=-1;
             }
             anterior=posterior;
        }
       return posterior;
    }
}


int fato(int n){
    int f=1;

    while(n!=0){
        f=f*n;
        n--;
    }
    return f;
}
double cosseno(double theta, double epsilon){
       double x, pot=1, cos=1, potencia=1;
       int n=2, i, w=1, div, cont=2;

       x=(theta*PI)/180;

       while(pot>epsilon){
            div=fato(n);
            pot= (potencia*x*x)/div;
             if(cont%2==0){
                pot*=-1;
            }
            cos+=pot;
            n+=2;
            cont++;
                for(i=0; i<w; i++){
                    potencia=potencia*x*x;
                }
            if(pot<0){
                pot*=-1;
            }
       }
    return cos;
}


double disbase(double cos, double h){
       double dis;

       dis=cos*h;

    return dis;
}


int localiza(double xi, double yi, double div, double xj, double yj, double djv, double xk, double yk, double dkv, double *xv, double *yv){
    double pij, qij, pik, qik, pjk, qjk;
    int eqij, eqik, eqjk;
    int devolve;

    eqij=iguais(xi, xj);
    eqik=iguais(xi, xk);
    eqjk=iguais(xj, xk);

    if(eqij==0 && eqik==0){
        pij=((xi*xi)-(xj*xj)+(yi*yi)-(yj*yj)-(div*div)+(djv*djv))/(2*(xi-xj));
        qij=(yj-yi)/(xi-xj);

        pik=((xi*xi)-(xk*xk)+(yi*yi)-(yk*yk)-(div*div)+(dkv*dkv))/(2*(xi-xk));
        qik=(yk-yi)/(xi-xk);

        *yv=(pij-pik)/(qik-qij);
        *xv=pij+(qij*(*yv));
        devolve=1;
        return devolve;
    }
    else if(eqij==0 && eqjk==0){
        pij=((xi*xi)-(xj*xj)+(yi*yi)-(yj*yj)-(div*div)+(djv*djv))/(2*(xi-xj));
        qij=(yj-yi)/(xi-xj);

        pjk=((xj*xj)-(xk*xk)+(yj*yj)-(yk*yk)-(djv*djv)+(dkv*dkv))/(2*(xj-xk));
        qjk=(yk-yj)/(xj-xk);

        *yv=(pij-pjk)/(qjk-qij);
        *xv=pij+(qij*(*yv));
        devolve=1;
        return devolve;
    }
    else if(eqjk==0 && eqik==0){
        pjk=((xj*xj)-(xk*xk)+(yj*yj)-(yk*yk)-(djv*djv)+(dkv*dkv))/(2*(xj-xk));
        qjk=(yk-yj)/(xj-xk);

        pik=((xi*xi)-(xk*xk)+(yi*yi)-(yk*yk)-(div*div)+(dkv*dkv))/(2*(xi-xk));
        qik=(yk-yi)/(xi-xk);

        *yv=(pjk-pik)/(qik-qjk);
        *xv=pjk+(qjk*(*yv));
        devolve=1;
        return devolve;
    }
    else
        devolve=0;

    return devolve;
}


double velocidade(double x0, double y0, double x1, double y1, double deltaT){
       double d, dist, veloc;

       d=(x1-x0)*(x1-x0)+(y1-y0)*(y1-y0);
       dist=raiz(d, EPS);
       veloc=dist/deltaT;

    return veloc;
}

int iguais(double x, double y){
    if(x-y<EPS && y-x<EPS){
        return 1;
    }
    else
        return 0;
}

int intercepta(double x0, double y0, double x1, double y1, double *x, double *y){
    double m, px1, py1, px2, py2, delta, a, b, c, devolve, d1, d2, dv1, dv2, yv;
    int eq, eq1;

    eq=iguais(x0, x1);

    if(eq==0){
        m=(y1-y0)/(x1-x0);
        a=1+(m*m);
        b=(2*m)*(y0-(m*x0));
        c=(y0-(m*x0))*(y0-(m*x0))-(RADIO_AP*RADIO_AP);

        delta=(b*b)-4*a*c;
        eq1=iguais(delta, 0);

        if(delta>0){
             px1=(-b+raiz(delta, EPS))/(2*a);
             py1=(m*px1)-(m*x0)+y0;

             px2=(-b-raiz(delta, EPS))/(2*a);
             py2=(m*px2)-(m*x0)+y0;

             d1=(x1-px1)*(x1-px1)+(y1-py1)*(y1-py1);
             d1=raiz(d1, EPS);
             d2=(x1-px2)*(x1-px2)+(y1-py2)*(y1-py2);
             d2=raiz(d2, EPS);

             dv1=(x0-px1)*(x0-px1)+(y0-py1)*(y0-py1);
             dv1=raiz(dv1, EPS);
             dv2=(x0-px2)*(x0-px2)+(y0-py2)*(y0-py2);
             dv2=raiz(dv2, EPS);

                if(d1<d2 && dv1<dv2){
                  *x=px1;
                  *y=py1;

                  devolve=1;
                  return devolve;
                }
                else if(d2<d1 && dv2<dv1){
                  *x=px2;
                  *y=py2;

                  devolve=1;
                  return devolve;
                }
                else{
                  devolve=0;
                  return devolve;
                }
        }
        else if(eq1==1){
            *x=-b/(2*a);
            *y=(m*(*x))-(m*x0)+y0;

            dv1=(x0-(*x))*(x0-(*x))+(y0-(*y))*(y0-(*y));
            dv1=raiz(dv1, EPS);
            dv2=(x1-x0)*(x1-x0)+(y1-y0)*(y1-y0);
            dv2=raiz(dv2, EPS);

            if(dv1<dv2){
                devolve=0;
                return devolve;
            }
            else{
            devolve=1;
            return devolve;
            }
        }
        else{
            devolve=0;
            return devolve;
        }
    }
    else if(-200<=x1 && x1<=200){
      if((y1>0 && y1<y0) || (y1<0 && y1>y0)){
         *x=x1;
         yv=(RADIO_AP*RADIO_AP)-((*x)*(*x));
         *y=raiz(yv, EPS);
           if(y1<0 && y1>y0){
               (*y)=(*y)*-1;
           }

         devolve=1;
         return devolve;
      }
      else{
         devolve=0;
         return devolve;
      }
    }
    else{
        devolve=0;
        return devolve;
    }
}


double distanciacarro(double x0, double y0, double x1, double y1){
       double d, dist, dorig;

       d=(x1-x0)*(x1-x0)+(y1-y0)*(y1-y0);
       dist=raiz(d, EPS);

    return dist;
}

double distanciaorigem(double x0, double y0, double x1, double y1, double *daorigantes){
       double dorig, dorigantes;

        dorigantes=(x0-0)*(x0-0)+(y0-0)*(y0-0);
        *daorigantes=raiz(dorigantes, EPS);

        dorig=(x1-0)*(x1-0)+(y1-0)*(y1-0);
        dorig=raiz(dorig, EPS);

  return dorig;
}


int main()
{
    FILE *arq;

    char filename[256];
    printf("Digite o nome do arquivo:\n");
    scanf("%s", filename);
    arq=fopen(filename, "r");

    int idv, idi, idj, idk, casos;
    double x0, y0, x1, y1, xi, yi, hi, graui, cosi, di, xj, yj, hj, grauj, cosj, dj, xk, yk, hk, grauk, cosk, dk, recebeLocaliza;
    double xv, yv, deltaT, distpercorri, veloc, distorig, distorigantes, x, y, recebeIntercepta, dx1, dx0, tempocruz;

    fscanf(arq, "%d", &casos);

    if(casos>0){
        printf("Numeros de casos a serem analisados: %d\n\n\n", casos);

        while(casos!=0){
            fscanf(arq, "%d", &idv);
            printf("IDENTIFICACAO: Veiculo %d\n\n", idv);

            fscanf(arq, "%d %lf %lf %lf %lf", &idi, &xi, &yi, &hi, &graui);
            fscanf(arq, "%d %lf %lf %lf %lf", &idj, &xj, &yj, &hj, &grauj);
            fscanf(arq, "%d %lf %lf %lf %lf", &idk, &xk, &yk, &hk, &grauk);

            cosi=cosseno(graui, EPS_COS);
            cosj=cosseno(grauj, EPS_COS);
            cosk=cosseno(grauk, EPS_COS);

            di=disbase(cosi, hi);
            dj=disbase(cosj, hj);
            dk=disbase(cosk, hk);

            printf("Antenas na posicao previa\n");
            printf("id |     posicao     |  H (m)  | theta(graus) | distancia (m)\n");
            printf("%d | ( %.2lf, %.2lf) |  %.2lf  |   %.2lf   |  %.2lf\n", idi, xi, yi, hi, graui, di);
            printf("%d | ( %.2lf, %.2lf) |  %.2lf  |   %.2lf   |  %.2lf\n", idj, xj, yj, hj, grauj, dj);
            printf("%d | ( %.2lf, %.2lf) |  %.2lf  |   %.2lf   |  %.2lf\n\n", idk, xk, yk, hk, grauk, dk);

            recebeLocaliza=localiza(xi, yi, di, xj, yj, dj, xk, yk, dk, &xv, &yv);

            if(recebeLocaliza==0){
                printf("Nao foi possivel calcular a localizacao inicial do veiculo %d\n\n", idv);
                printf("Nao foi possivel determinar a situacao do veiculo %d\n\n\n\n", idv);
                fscanf(arq, "%lf", &deltaT);
                fscanf(arq, "%d %lf %lf %lf %lf", &idi, &xi, &yi, &hi, &graui);
                fscanf(arq, "%d %lf %lf %lf %lf", &idj, &xj, &yj, &hj, &grauj);
                fscanf(arq, "%d %lf %lf %lf %lf", &idk, &xk, &yk, &hk, &grauk);
            }
            else{
                x0=xv;
                y0=yv;

                printf("Localizacao previa: ( %.2lf,  %.2lf)\n\n", x0, y0);

                fscanf(arq, "%lf", &deltaT);
                printf("Intervalo de Tempo: %.2lf segundos\n\n", deltaT);

                fscanf(arq, "%d %lf %lf %lf %lf", &idi, &xi, &yi, &hi, &graui);
                fscanf(arq, "%d %lf %lf %lf %lf", &idj, &xj, &yj, &hj, &grauj);
                fscanf(arq, "%d %lf %lf %lf %lf", &idk, &xk, &yk, &hk, &grauk);

                cosi=cosseno(graui, EPS_COS);
                cosj=cosseno(grauj, EPS_COS);
                cosk=cosseno(grauk, EPS_COS);

                di=disbase(cosi, hi);
                dj=disbase(cosj, hj);
                dk=disbase(cosk, hk);

                printf("Antenas na posicao atual\n");
                printf("id |     posicao     |  H (m)  | theta(graus) | distancia (m)\n");
                printf("%d | ( %.2lf, %.2lf) |  %.2lf  |   %.2lf  |  %.2lf\n", idi, xi, yi, hi, graui, di);
                printf("%d | ( %.2lf, %.2lf) |  %.2lf  |   %.2lf  |  %.2lf\n", idj, xj, yj, hj, grauj, dj);
                printf("%d | ( %.2lf, %.2lf) |  %.2lf  |   %.2lf  |  %.2lf\n\n", idk, xk, yk, hk, grauk, dk);

                recebeLocaliza=localiza(xi, yi, di, xj, yj, dj, xk, yk, dk, &xv, &yv);

                if(recebeLocaliza==0){
                    printf("Nao foi possivel calcular a posicao atual do veiculo %d\n\n", idv);
                    printf("Nao foi possivel determinar a situacao do veiculo %d\n\n\n\n", idv);
                }
                else{
                   x1=xv;
                   y1=yv;

                   printf("Localizacao atual: ( %.2lf,  %.2lf)\n\n", x1, y1);

                   distpercorri=distanciacarro(x0, y0, x1, y1);
                   printf("Distancia percorrida: %.2lf m\n", distpercorri);
                   veloc=velocidade(x0, y0, x1, y1, deltaT);
                   printf("Velocidade: %.2lf m/s\n\n", veloc);


                   distorig=distanciaorigem(x0, y0, x1, y1, &distorigantes);
                   printf("Distancia da origem: %.2lf\n", distorig);


                   if(distorig>RADIO_ZA && veloc==0){
                         printf("Veiculo estacionado FORA da zona de alerta\n\n\n\n");
                   }
                   else if(distorig>RADIO_ZA){
                      printf("Veiculo em movimento FORA da zona de alerta\n\n\n\n");
                   }
                   else if(distorig<=RADIO_AP && veloc==0){
                      printf("Veiculo estacionado na AP\n\n");
                      printf("************************************\n");
                      printf("  ALARME, ALARME, ALARME, ALARME !!\n");
                      printf("       Veiculo esta na AP !\n");
                      printf("************************************\n\n\n\n");
                   }
                   else if(distorig<=RADIO_AP){
                      printf("Veiculo em movimento na AP\n\n");
                      printf("************************************\n");
                      printf("  ALARME, ALARME, ALARME, ALARME !!\n");
                      printf("       Veiculo esta na AP !\n");
                      printf("************************************\n\n\n\n");
                   }
                   else if(distorigantes<RADIO_AP && distorig>RADIO_AP){
                      printf("Veiculo em movimento na ZONA DE ALERTA\n\n");
                      printf("Trajetoria NAO INTERCEPTARA A AP\n\n\n\n");
                   }
                   else{
                      recebeIntercepta=intercepta(x0, y0, x1, y1, &x, &y);

                      if(recebeIntercepta==0 && veloc!=0){
                        printf("Veiculo em movimento na ZONA DE ALERTA\n\n");
                        printf("Trajetoria NAO INTERCEPTARA A AP\n\n\n\n");
                      }
                      else if(recebeIntercepta==0){
                        printf("Veiculo estacionado na ZONA DE ALERTA\n\n\n\n");
                      }
                      else{
                         dx1=(x1-x)*(x1-x)+(y1-y)*(y1-y);
                         dx1=raiz(dx1, EPS);
                         dx0=(x0-x)*(x0-x)+(y0-y)*(y0-y);
                         dx0=raiz(dx0, EPS);

                         if(dx1>dx0){
                             printf("Veiculo em movimento na ZONA DE ALERTA\n\n");
                             printf("Trajetoria NAO INTERCEPTARA A AP\n\n\n\n");
                         }
                         else{
                             printf("Veiculo em movimento na ZONA DE ALERTA\n\n");
                             printf("Trajetoria INTERCEPTARA A AP\n");
                             printf("Distancia atual a AP e' de %.2lf metros\n", dx1);

                             tempocruz=dx1/veloc;
                             printf("Interseccao ocorrera em %.2lf segundos\n", tempocruz);
                             printf("na coordenada (  %.2lf,  %.2lf)\n\n\n", x, y);

                             if(tempocruz<=DELTA_ALARME){
                                printf("************************************\n");
                                printf("  ALARME, ALARME, ALARME, ALARME !!\n");
                                printf("       Invasao Iminente !\n");
                                printf("************************************\n\n\n\n");
                             }
                         }
                      }
                   }
                }
            }
     casos--;
        }
    }
    else{
        printf("Voce digitou um numero invalido para o total de casos!\n");
    }

    fclose(arq);

    return 0;
}

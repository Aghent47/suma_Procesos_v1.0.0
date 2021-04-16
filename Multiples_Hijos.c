#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/*
	Neider Hernández M.
	Estudiante Ingenieria de Sistemas
	Universidad del Magdalena
	2021 - 1
	Sistema Operativo usado -> Linux Mint
*/

/*
  Exercise

The father will have two children where each child will process 
half a vector of integers divided by the parent and also each
child will write in a new file (out.txt) their respective sum 
where then the parent reads the said file and makes the Total sum.

NOTE: This exercise is solved in a easy way.
*/

/*  Declaración de Funciones a usar   */
int crear_hijos(int num[],int,int,int);
int SumaHijo1(int num[],int,int,int);
int SumaHijo2(int num[],int,int,int);
void imprimir(int);

//Función para calcular la suma de Hijo 1
int SumaHijo1(int num[],int n,int ind1,int ind2){
        int suma1 = 0;
         for (int i=0; i < ind2; i++){
           printf("[%d] ",num[i]);
           suma1 = suma1 + num[i] ;
        }     
    return(suma1);
}
//Función para calcular la suma de Hijo 2
int SumaHijo2(int num[],int n,int ind1,int ind2){
        int suma2 = 0;
         for (ind2; ind2 < n-1; ind2++){
           printf("[%d] ",num[ind2]);
           suma2 = suma2 + num[ind2] ;
        }
     
    return(suma2);
}

//Función para crear y operar hijos
int crear_hijos(int num[],int n,int ind1,int ind2){
    
    pid_t pidHijo;
    int suma1 = 0, suma2 = 0;
    int NUM_CHILD = 2, status;
    bool aux = true; 
    
    for (int i = 0; i < NUM_CHILD; i++){
        pidHijo = fork();

      if(pidHijo > 0 ){
          if(aux){
              printf("\nPADRE: PID = %d \n", getpid());
              aux = false;
          }
        pidHijo =  wait(&status);
        
      }else
        if(pidHijo == 0 & i == 0){
            
            suma1 = SumaHijo1(num,n,ind1,ind2);
        printf("HIJO: PID = %d, Valor Cal = %d \n",getpid(),suma1);
         FILE *out = fopen("out.txt", "wt");
             fprintf (out,"%d",suma1);
             fclose(out);
            return(0);

        }else if ( i == 1){
           
            suma2 = SumaHijo2(num,n,ind1,ind2);
         printf("HIJO: PID = %d, Valor Cal = %d \n",getpid(),suma2);
             FILE *out = fopen("out.txt", "a+");
             fprintf (out,"\n%d",suma2);
             fclose(out);
          
            return (i);
        }
        
        //error
    }
    return (-2);
}
//Función para leer y sumar el total de archivo out.txt
int leerTotal(){
 FILE *myfile;
    int sumap1=0,sumap2=0,total=0; myfile = fopen("out.txt","r");
    if(!myfile) perror("Error padre archivo resultados");
        fscanf(myfile,"%d", &sumap1);
        fscanf(myfile,"%d", &sumap2);
    total = sumap1 + sumap2; 
    return total;
 }
/*MAIN*/
int main (void){
    int *num,n=0;
    int dato,dato2 = 0, suma = 0;
    int indiceP1=0, indiceP2,TOTAL=0;

    FILE *archivo = fopen( "input.txt","a+" );
        if (archivo == NULL) {
            printf( "ERROR\n" );
            return 0;
        }
    while (!feof(archivo)) {
        fscanf( archivo, "%d", &dato );
            num[n] = dato;
            n++;
    }
    indiceP2 = (n-1)/2;
    
    if(crear_hijos(num,n,indiceP1,indiceP2)>0){
        TOTAL = leerTotal();
         imprimir(TOTAL);
    }
        
    fclose(archivo);
    
    
}
void imprimir(int SUMA){
    printf("Suma = %d\n",SUMA);
}
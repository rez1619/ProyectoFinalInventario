#include <stdio.h>
#include <conio.h>
#include <fstream>
#include <String.h>
#include <stdlib.h>
using namespace std;

int op;
const char archivo1[30] = "productos.txt";
const char archivo2[30] = "movimientos.txt";
char *returnStr;

struct NodeProd{
	int pclave;
	char pnombre[21];
	char pfamilia[21];
	char pmedida[21];
	int ppu;
	int peini;
	int peact;
	int psmin;
	int psmax;
	NodeProd *next;
	NodeProd *prev;
};

NodeProd *pprimero, *pactual, *pultimo, *pnuevo, *panterior, *psiguiente, *ptemporal;

struct NodeMov{
	int mclave;
	char mfecha[11];
	int mcantidad;
	char mmainmov;
	char msubmov;
	NodeMov *next;
	NodeMov *prev;
};

NodeMov *mprimero, *mactual, *multimo, *mnuevo, *manterior, *msiguiente, *mtemporal;

struct NodeProdSort{
	int pclave;
	char pnombre[21];
	char pfamilia[21];
	char pmedida[21];
	int ppu;
	int peini;
	int peact;
	int psmin;
	int psmax;
	NodeProdSort *next;
	NodeProdSort *prev;
};

NodeProdSort *ppprimero, *ppactual, *ppultimo, *ppnuevo, *ppanterior, *ppsiguiente, *pptemporal;

struct NodeMovSort{
	int mclave;
	char mfecha[11];
	int mcantidad;
	char mmainmov;
	char msubmov;
	NodeMovSort *next;
	NodeMovSort *prev;
};

NodeMovSort *mmprimero, *mmactual, *mmultimo, *mmnuevo, *mmanterior, *mmsiguiente, *mmtemporal;

char *pedir_cadena(int limite1, int limite2, char const *stonks) {
	int limiteReal1= limite1+1;
	int limiteReal2= limite2+1;
	char *x;
	x = new char[limite2+2];
	do {
		printf("%s entre %d y %d : ", stonks, limite1, limite2); fgets(x, limiteReal2+2, stdin); fflush(stdin);
		if ((strlen(x)<limiteReal1) || (strlen(x)>limiteReal2)) {
			printf("Error, cadena fuera del rango. Intente de nuevo.\n");
			getche();
		}
	} while ((strlen(x)<limiteReal1) || (strlen(x)>limiteReal2));
	if (x[strlen(x)-1] == '\n'){
		x[strlen(x)-1]='\0';
	}
	returnStr = (char *)malloc((limite2+2) * sizeof(char));
	strcpy(returnStr, x);
	delete x;
	return returnStr;
}

char *pedir_cadena_sinespacios(int limite1, int limite2, char const *stonks) {
	int limiteReal1= limite1+1;
	int limiteReal2= limite2+1;
	char *x;
	x = new char[limite2+2];
	do {
		printf("%s entre %d y %d : ", stonks, limite1, limite2); fgets(x, limiteReal2+2, stdin); fflush(stdin);
		if ((strlen(x)<limiteReal1) || (strlen(x)>limiteReal2)) {
			printf("Error, cadena fuera del rango. Intente de nuevo.\n");
			getche();
		}
	} while ((strlen(x)<limiteReal1) || (strlen(x)>limiteReal2));
	for (int i = 0; i<strlen(x); i++){
		if (x[i]==' '){
			x[i]='_';
		}
	}
	if (x[strlen(x)-1] == '\n'){
		x[strlen(x)-1]='\0';
	}
	returnStr = (char *)malloc((limite2+2) * sizeof(char));
	strcpy(returnStr, x);
	delete x;
	return returnStr;
}

int pedir_entero(int limite1, int limite2, char const *stonks) {
	int x;
	do {
		printf("%s entre %d y %d : ", stonks, limite1, limite2); scanf("%d", &x); fflush(stdin);
		if ((x<limite1) || (x>limite2)) {
			printf("Error, numero fuera del rango. Intente de nuevo.\n");
			getche();
		}
	} while ((x<limite1) || (x>limite2));
	return x;
}

void menuReportes(){
	char x[2];
	do{
		printf("\n=================\n");
		printf("==MENU REPORTES==\n");
		printf("=================\n");
		printf("a) General de productos ordenados por clave\n");
		printf("b) General de productos ordenados por nombre\n");
		printf("c) Productos por familia\n");
		printf("d) Productos a Ordenar ordenado por existencia\n");
		printf("e) Productos a Ofertar ordenado por existencia\n");
		printf("f) Listado de movimientos de un producto ordenado por fecha\n");
		printf("x) Terminar\n\n");
		strcpy(x, pedir_cadena(1, 1, "Indica la opcion"));
		free(returnStr);
		if (strcmp(x, "a") == 0){

		}else if (strcmp(x, "b") == 0){

		}else if (strcmp(x, "c") == 0){
			
		}else if (strcmp(x, "d") == 0){
			
		}else if (strcmp(x, "e") == 0){
			
		}else if (strcmp(x, "f") == 0){
			
		}else if (strcmp(x, "x") == 0){
			printf("Gracias por usar el programa...\n");
			getche();
		}else{
			printf("Opcion Incorrecta...\n");
			getche();
		}
	}while(strcmp(x, "x") != 0);
}

main(){
	ofstream arch;
	arch.open(archivo1, ios::app);
	arch.close();
	arch.open(archivo2, ios::app);
	arch.close();
	menuReportes();
}
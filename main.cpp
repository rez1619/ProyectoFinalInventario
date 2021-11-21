#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <conio.h>
#include <ctime>
#include <String.h>

using namespace std;
char *returnStr;

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


//Productos
int pclave;
char pnombre[21];
char pfamilia[21];
char pmedida[21];
int ppu;
int peini;
int peact;
int psmin;
int psmax;

//Movimientos
int mclave;
char mfecha[11];
int mcantidad;
char mmainmov;
char msubmov;


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

//Espacio de inserta_productos ----------------------->
void inserta_productos(int clave, char nombre[21], char familia[21], char medida[21], int pu, int eini, int eact, int smin, int smax){
}
//Espacio del tulas <-----------------------


//Espacio de inserta_movimientos <----------------
void inserta_movimientos(int clave, char fecha[11], int cantidad, char mainmov, char submov){
    mnuevo = new NodeMov;
    mnuevo->mclave=clave;
    strcpy(mnuevo->mfecha,fecha);
    mnuevo->mcantidad=cantidad;
    mnuevo->mmainmov=mainmov;
    mnuevo->msubmov=submov;
    mnuevo->next = NULL;
    if(mprimero == NULL){
        mnuevo->prev = NULL;
        mprimero = mnuevo;
    }else{
        multimo->next = mnuevo;
        mnuevo->prev = multimo;
    }
    multimo = mnuevo;
}
//Espacio del Monas Chinas ---------------->

void cargar_productos(std::string filename){
    std::ifstream file;
    file.open(filename,std::ios::in);
    while(!file.eof()){
        file>>pclave>>pnombre>>pfamilia>>pmedida>>ppu>>peini>>peact>>psmin>>psmax;
        if(!file.eof()) inserta_productos(pclave,pnombre,pfamilia,pmedida,ppu,peini,peact,psmin,psmax);
    }
    file.close();
}

void cargar_movimientos(std::string filename){
    std::ifstream file;
    file.open(filename,std::ios::in);
    while(!file.eof()){
        file>>mclave>>mfecha>>mcantidad>>mmainmov>>msubmov;
        if(!file.eof()) inserta_movimientos(mclave, mfecha, mcantidad, mmainmov, msubmov);
    }
    file.close();
}

void guardar_productos(std::string filename){
    if(pprimero == NULL){
        std::ofstream file;
        file.open(filename,std::ios::out);
        file.close();
        return;
    }
    std::ofstream file;
    file.open(filename,std::ios::out);
    pactual = pprimero;
    while(pactual != NULL){
        file<<pclave<<" "<<pnombre<<" "<<pfamilia<<" "<<pmedida<<" "<<ppu<<" "<<peini<<" "<<peact<<" "<<psmin<<" "<<psmax<<std::endl;
        pactual = pactual->next;
    }

    file.close();
}

void guardar_movimientos(std::string filename){
    if(mprimero == NULL){
        std::ofstream file;
        file.open(filename,std::ios::out);
        file.close();
        return;
    }
    std::ofstream file;
    file.open(filename,std::ios::out);
    mactual = mprimero;
    while(mactual != NULL){
        file<<mclave<<" "<<mfecha<<" "<<mcantidad<<" "<<mmainmov<<" "<<msubmov<<std::endl;
        mactual = mactual->next;
    }

    file.close();
}

//Espacio del tulas ----------------------->
void inserta__productos(int pclave, char pnombre[21], char pfamilia[21], char pmedida[21], int ppu, int peini, int peact, int psmin, int psmax){
}
//Espacio del tulas <-----------------------


//Espacio del Monas Chinas <----------------
void entradas_compras(){
    system("cls");
    int clave = pedir_entero(1,99999,"Indique la clave del producto");

    bool existe;
    pactual = pprimero;
    while(pactual != NULL){
        if(pactual->pclave == clave){
            existe = true;
            break;
        }
        pactual = pactual->next;
    }
    if(!existe){
        std::cout<<std::endl<<"ERROR. Clave de producto inexistente...";getch();
        return;
    }

    int cantidad = pedir_entero(1,999999,"Indique la cantidad de unidades compradas");  
    time_t now = time(0);
    tm *ltm = localtime(&now);
    std::string fecha =  std::to_string(ltm->tm_mday) + "/" + std::to_string(1 + ltm->tm_mon) + "/" +std::to_string(1900 + ltm->tm_year);
    char mainmov = 'E';
    char submov = 'C';
    
    pactual->peact = pactual->peact + cantidad;
    guardar_productos("productos.txt");

    inserta_movimientos(clave,(char *) fecha.c_str(),cantidad,mainmov,submov);
    guardar_movimientos("movimientos.txt");

    std::cout<<"El movimiento fue registrado correctamente...";getch();
}

void menu_entradas_salidas(){
    char op;
    
    do{
        system("cls");
        std::cout<<"|=======================================|"<<std::endl;
        std::cout<<"|         MENU ENTRADAS/SALIDAS         |"<<std::endl;
        std::cout<<"|=======================================|"<<std::endl;
        std::cout<<"|a) Entradas por compras                |"<<std::endl;
        std::cout<<"|b) Entradas por devolucion de clientes |"<<std::endl;
        std::cout<<"|c) Salidas por ventas                  |"<<std::endl;
        std::cout<<"|c) Salidas por devolucion a proveedores|"<<std::endl;
        std::cout<<"|c) Salidas por mermas                  |"<<std::endl;
        std::cout<<"|x) Terminar                            |"<<std::endl;
        std::cout<<"|=======================================|"<<std::endl;
        std::cout<<"Indique la opcion deseada: ";
        op = getche();
        switch (op){
        case 'a': entradas_compras(); break;
        case 'b': break;
        case 'c': break;
        case 'x': break;
        default:
            system("cls");
            std::cout<<"Opcion no valida..."; getch(); 
            break;
        }
    }while(op != 'x');
}

//Espacio del Monas Chinas ---------------->


//Espacio del Hlib ------------------------>
    //Aca escribe el Hlib

//Espacio del Hlib <------------------------


void menu_principal(){
    char op;
    
    do{
        system("cls");
        std::cout<<"|===================================|"<<std::endl;
        std::cout<<"|           MENU PRINCIPAL          |"<<std::endl;
        std::cout<<"|===================================|"<<std::endl;
        std::cout<<"|a) Archivo de Productos            |"<<std::endl;
        std::cout<<"|b) Entradas/Salidas de Producto    |"<<std::endl;
        std::cout<<"|c) Reportes                        |"<<std::endl;
        std::cout<<"|x) Terminar                        |"<<std::endl;
        std::cout<<"|===================================|"<<std::endl;
        std::cout<<"Indique la opción deseada: ";
        op = getche();
        switch (op){
        case 'a': break;
        case 'b': menu_entradas_salidas();break;
        case 'c': break;
        case 'x': break;
        default:
            system("cls");
            std::cout<<"Opcion no valida..."; getch(); 
            break;
        }
    }while(op != 'x');
}

int main(int argc, char const *argv[]){
    std::ofstream file;
    file.open("productos.txt",std::ios::app);
    file.close();
    file.open("movimientos.txt",std::ios::app);
    file.close();
    cargar_productos("productos.txt");
    cargar_movimientos("movimientos.txt");
    menu_principal();
    guardar_productos("productos.txt");
    guardar_movimientos("movimientos.txt");
    return 0;
}
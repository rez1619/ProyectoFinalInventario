#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <conio.h>
#include <ctime>
#include <String.h>
#include <cctype>

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
void inserta_productos(int clv, char nmb[21], char fam[21], char med[21], int uni, int ini, int act, int smn, int smx){
    pnuevo=new NodeProd;
    pnuevo->pclave=clv;
    strcpy(pnuevo->pnombre,nmb);
    strcpy(pnuevo->pfamilia,fam);
    strcpy(pnuevo->pmedida,med);
    pnuevo->ppu=uni;
    pnuevo->peini=ini;
    pnuevo->peact=act;
    pnuevo->psmin=smn;
    pnuevo->psmax=smx;
    pnuevo->next=NULL;
    pnuevo->prev=NULL;
    if(pprimero==NULL){
        pprimero=pnuevo;
        pultimo=pnuevo;
    }
    else{
        pultimo->next=pnuevo;
        pnuevo->prev=pultimo;
        pultimo=pnuevo;
    }
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
    file.open("productos.txt",std::ios::in);
    while(!file.eof()){
        file>>pclave>>pnombre>>pfamilia>>pmedida>>ppu>>peini>>peact>>psmin>>psmax;
        if(!file.eof()) inserta_productos(pclave,pnombre,pfamilia,pmedida,ppu,peini,peact,psmin,psmax);
    }
    file.close();
}

void cargar_movimientos(std::string filename){
    std::ifstream file;
    file.open("movimientos.txt",std::ios::in);
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
    file.open("productos.txt",std::ios::out);
    pactual = pprimero;
    while(pactual != NULL){
        file<<pactual->pclave<<" "<<pactual->pnombre<<" "<<pactual->pfamilia<<" "<<pactual->pmedida<<" "<<pactual->ppu<<" "<<pactual->peini<<" "<<pactual->peact<<" "<<pactual->psmin<<" "<<pactual->psmax<<std::endl;
        pactual = pactual->next;
    }

    file.close();
}

void guardar_movimientos(std::string filename){
    if(mprimero == NULL){
        std::ofstream file;
        file.open("movimientos.txt",std::ios::out);
        file.close();
        return;
    }
    std::ofstream file;
    file.open("movimientos.txt",std::ios::out);
    mactual = mprimero;
    while(mactual != NULL){
        file<<mactual->mclave<<" "<<mactual->mfecha<<" "<<mactual->mcantidad<<" "<<mactual->mmainmov<<" "<<mactual->msubmov<<std::endl;
        mactual = mactual->next;
    }

    file.close();
}

//Espacio del tulas ----------------------->

bool busca_clave(int clv_bus){
    pactual=pprimero;
    panterior=NULL;
    while (pactual!=NULL){
        if (pactual->pclave==clv_bus){
            return true;
        }
        panterior=pactual;
        pactual=pactual->next;
    }
    return false;
}

void altas_productos(){
    system("cls");
    std::cout<<"|===================================|"<<std::endl;
    std::cout<<"|        ALTAS DE PRODUCTOS         |"<<std::endl;
    std::cout<<"|===================================|"<<std::endl;
    do{
        pclave=pedir_entero(1,99999,      "Indica la clave            del producto");
        if (busca_clave(pclave)){
            printf("Error, la clave se repite en el archivo, use una diferente\n");
        }
        else{
            strcpy(pnombre,pedir_cadena_sinespacios (1,20,"Indica el nombre           del producto"));
            strcpy(pfamilia,pedir_cadena_sinespacios(1,20,"Indica la familia          del producto"));
            strcpy(pmedida,pedir_cadena_sinespacios (1,20,"Indica la unidad de medida del producto"));
            ppu=pedir_entero(1,999999,        "Indica el precio unitario  del producto");
            peini=pedir_entero(1,999999,      "Indica la cantidad inicial del producto");
            peact=peini;
            psmin=pedir_entero(1,999999,      "Indica el stock minimo     del producto");
            psmax=pedir_entero(1,999999,      "Indica el stock maximo     del producto");
        }
    }while(busca_clave(pclave));
    inserta_productos(pclave,pnombre,pfamilia,pmedida,ppu,peini,peact,psmin,psmax);
    guardar_productos("productos.txt");
}

void bajas_productos(){
    system("cls");
    std::cout<<"|===================================|"<<std::endl;
    std::cout<<"|        BAJAS DE PRODUCTOS         |"<<std::endl;
    std::cout<<"|===================================|"<<std::endl;
    NodeProd *aux;
    aux=new NodeProd;
    pactual==pprimero;
    if(pprimero==NULL){
        printf("Error, la lista est%c vac%ca\n",160,161);
        getche();
        return;
    }
    pclave=pedir_entero(1,99999,"Indica la clave del producto a eliminar");
    if(!busca_clave(pclave)){
        printf("La clave del producto no existe en el archivo\n");
        getche();
    }
    else{
        if (pprimero==pultimo){
            delete(pactual);
            pprimero=NULL;
            pultimo=NULL;
        }
        else{
            if(pactual==pprimero){
                aux=pprimero->next;
                aux->prev=NULL;
                delete(pactual);
                pprimero=aux;
            }
            else{
                if(pactual==pultimo){
                    aux=pactual->prev;
                    aux->next=NULL;
                    delete(pactual);
                    pultimo=aux;
                }
                else{
                    aux=pactual->prev;
                    aux->next=pactual->next;
                    aux=pactual->next;
                    aux->prev=pactual->prev;
                    delete(pactual);
                }
            }
        }
    }
    guardar_productos("productos.txt");
}

void consulta_productos(){
    system("cls");
    std::cout<<"|===================================|"<<std::endl;
    std::cout<<"|        CONSULTA DE PRODUCTOS      |"<<std::endl;
    std::cout<<"|===================================|"<<std::endl;
    pclave=pedir_entero(1,99999,"Indica la clave del producto a buscar");
    if(busca_clave(pclave)){
    	printf("========================================\n");
        printf("Nombre           :  %s\n",pactual->pnombre);
        printf("Familia          :  %s\n",pactual->pfamilia);
        printf("Unidad de medida :  %s\n",pactual->pmedida);
        printf("Precio unitario  : $%6d\n",pactual->ppu);
        printf("Cantidad inicial :  %6d\n",pactual->peini);
        printf("Cantidad actual  :  %6d\n",pactual->peact);
        printf("Stock minimo     :  %6d\n",pactual->psmin);
        printf("Stock maximo     :  %6d\n",pactual->psmax);
        printf("========================================\n");
        getche();
    }
    else{
        printf("Error, la clave no existe en el archivo de productos\n");
        getche();
    }
}

void consulta_familia(){
    system("cls");
    std::cout<<"|===================================|"<<std::endl;
    std::cout<<"|        CONSULTA POR FAMILIA       |"<<std::endl;
    std::cout<<"|===================================|"<<std::endl;
    strcpy(pfamilia,pedir_cadena_sinespacios(1,20,"Indica la familia de productos a filtrar"));
    pactual=pprimero;
    while(pactual!=NULL){
        if(strcmp(pfamilia,pactual->pfamilia)==0){
            break;
        }
        pactual=pactual->next;
    }
    if(pactual == NULL){
        std::cout<<std::endl<<"ERROR. Familia de producto inexistente...";getch();
        return;
    }
    printf("Clave                Nombre               Familia              U.Medida    Preciounitario   E.inicial   E.actual   StockMin   StockMax\n");
    printf("--------------------------------------------------------------------------------------------------------------------------------------\n");
    //      12345  123456789/123456789/  123456789/123456789/  123456789/123456789/          $ 123456      123456     123456     123456     123456
    pactual=pprimero;
    while(pactual!=NULL){
        if(strcmp(pfamilia,pactual->pfamilia)==0){
            printf("%5d  %20s  %20s  %20s          $ %6d      %6d     %6d     %6d     %6d\n",
            pactual->pclave,pactual->pnombre,pactual->pfamilia,pactual->pmedida,pactual->ppu,pactual->peini,pactual->peact,pactual->psmin,pactual->psmax);
        }
        pactual=pactual->next;
    }
    getche();
}

void menu_productos(){
    char op;
    
    do{
        system("cls");
        std::cout<<"|===================================|"<<std::endl;
        std::cout<<"|           MENU PRODUCTOS          |"<<std::endl;
        std::cout<<"|===================================|"<<std::endl;
        std::cout<<"|a) Altas de productos nuevos       |"<<std::endl;
        std::cout<<"|b) Bajas de productos obsoletos    |"<<std::endl;
        std::cout<<"|c) Consulta productos por clave    |"<<std::endl;
        std::cout<<"|d) Consulta productos por familia  |"<<std::endl;
        std::cout<<"|x) Terminar                        |"<<std::endl;
        std::cout<<"|===================================|"<<std::endl;
        std::cout<<"Indique la opcion deseada: ";
        op=getche();
        op=tolower(op);
        switch (op){
        case 'a': altas_productos(); break;
        case 'b': bajas_productos(); break;
        case 'c': consulta_productos(); break;
        case 'd': consulta_familia(); break;
        case 'x': break;
        default:
            system("cls");
            std::cout<<"Opcion no valida..."; getch(); 
            break;
        }
    }while(op != 'x');
}
//Espacio del tulas <-----------------------


//Espacio del Monas Chinas <----------------
void movimientos(char tipo, char subtipo){
    system("cls");
    std::string mensaje;
    switch (subtipo){
    case 'C': 
        std::cout<<"|=======================================|"<<std::endl;
        std::cout<<"|         ENTRADAS POR COMPRAS          |"<<std::endl;
        std::cout<<"|=======================================|"<<std::endl;
        mensaje = "Indique la cantidad de unidades compradas";
        break;
    case 'D': 
        std::cout<<"|=======================================|"<<std::endl;
        std::cout<<"|        ENTRADAS POR DEVOLUCION        |"<<std::endl;
        std::cout<<"|=======================================|"<<std::endl;
        mensaje = "Indique la cantidad de unidades devueltas";
        break;
    case 'V': 
        std::cout<<"|=======================================|"<<std::endl;
        std::cout<<"|          SALIDAS POR VENTAS           |"<<std::endl;
        std::cout<<"|=======================================|"<<std::endl;
        mensaje = "Indique la cantidad de unidades vendidas";
        break;
    case 'P': 
        std::cout<<"|=======================================|"<<std::endl;
        std::cout<<"|        SALIDAS POR DEVOLUCION         |"<<std::endl;
        std::cout<<"|=======================================|"<<std::endl;
        mensaje = "Indique la cantidad de unidades devueltas";
        break;
    case 'M': 
        std::cout<<"|=======================================|"<<std::endl;
        std::cout<<"|          SALIDAS POR MERMAS           |"<<std::endl;
        std::cout<<"|=======================================|"<<std::endl;
        mensaje = "Indique la cantidad de unidades perdidas por merma";
        break;
    default : break;
    }

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

    int cantidad = pedir_entero(1,999999,mensaje.c_str());  
    time_t now = time(0);
    tm *ltm = localtime(&now);
    std::string fecha =  std::to_string(ltm->tm_mday) + "/" + std::to_string(1 + ltm->tm_mon) + "/" +std::to_string(1900 + ltm->tm_year);

    switch (tipo){
    case 'E': pactual->peact = pactual->peact + cantidad; break;
    case 'S': pactual->peact = pactual->peact - cantidad;break;
    default : break;
    }
    
    guardar_productos("productos.txt");

    inserta_movimientos(clave,(char *) fecha.c_str(),cantidad,tipo,subtipo);
    guardar_movimientos("movimientos.txt");

    std::cout<<std::endl<<"El movimiento fue registrado correctamente...";getch();
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
        std::cout<<"|d) Salidas por devolucion a proveedores|"<<std::endl;
        std::cout<<"|e) Salidas por mermas                  |"<<std::endl;
        std::cout<<"|x) Terminar                            |"<<std::endl;
        std::cout<<"|=======================================|"<<std::endl;
        std::cout<<"Indique la opcion deseada: ";
        op = getche();
        op = tolower(op);
        switch (op){
        case 'a': movimientos('E','C'); break;
        case 'b': movimientos('E','D'); break;
        case 'c': movimientos('S','V'); break;
        case 'd': movimientos('S','P'); break;
        case 'e': movimientos('S','M'); break;
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
        std::cout<<"Indique la opcion deseada: ";
        op = getche();
        op = tolower(op);
        switch (op){
        case 'a': menu_productos(); break;
        case 'b': menu_entradas_salidas(); break;
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

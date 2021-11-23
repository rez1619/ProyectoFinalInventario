#include <stdio.h>
#include <conio.h>
#include <fstream>
#include <String.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>
#include <string>
using namespace std;

int op;
const char archivo1[30] = "productos.txt";
const char archivo2[30] = "movimientos.txt";
char *returnStr;

struct NodeProdSort{
	int spclave;
	char spnombre[21];
	char spfamilia[21];
	char spmedida[21];
	int sppu;
	int speini;
	int speact;
	int spsmin;
	int spsmax;
	NodeProdSort *next;
	NodeProdSort *prev;
};

NodeProdSort *spprimero, *spactual, *spultimo, *spnuevo, *spanterior, *spsiguiente, *sptemporal;

struct NodeMovSort{
	int smclave;
	char smfecha[11];
	int smcantidad;
	char smmainmov;
	char smsubmov;
	NodeMovSort *next;
	NodeMovSort *prev;
};

NodeMovSort *smprimero, *smactual, *smultimo, *smnuevo, *smanterior, *smsiguiente, *smtemporal;

void inserta_productos_sort(int clv, char nmb[21], char fam[21], char med[21], int uni, int ini, int act, int smn, int smx, int pos){
    spnuevo=new NodeProdSort;
    spnuevo->spclave=clv;
    strcpy(spnuevo->spnombre,nmb);
    strcpy(spnuevo->spfamilia,fam);
    strcpy(spnuevo->spmedida,med);
    spnuevo->sppu=uni;
    spnuevo->speini=ini;
    spnuevo->speact=act;
    spnuevo->spsmin=smn;
    spnuevo->spsmax=smx;
    spnuevo->next=NULL;
    spnuevo->prev=NULL;
    if(spprimero==NULL){
        spprimero=spnuevo;
        spultimo=spnuevo;
    }
    else{
		spanterior = NULL;
		sptemporal = spprimero;
		int count = 1;
		while(sptemporal!=NULL){
			if(count == pos){
				break;
			}
			spanterior = sptemporal;
			sptemporal = sptemporal->next;
			count++;
		}
		if(spanterior == NULL){
			sptemporal->prev=spnuevo;
			spnuevo->next=sptemporal;
			spnuevo->prev=spanterior;
			spprimero=spnuevo;
		}
		else if(sptemporal == NULL){
			spnuevo->next=sptemporal;
			spanterior->next=spnuevo;
			spnuevo->prev=spanterior;
			spultimo=spnuevo;
		}else{
			sptemporal->prev=spnuevo;
			spnuevo->next=sptemporal;
			spanterior->next=spnuevo;
			spnuevo->prev=spanterior;
		}
    }
}

void inserta_movimientos_sort(int clave, char fecha[11], int cantidad, char mainmov, char submov, int pos){
    smnuevo=new NodeMovSort;
    smnuevo->smclave=clave;
    strcpy(smnuevo->smfecha,fecha);
    smnuevo->smcantidad=cantidad;
    smnuevo->smmainmov=mainmov;
    smnuevo->smsubmov=submov;
    smnuevo->next = NULL;
    if(smprimero==NULL){
        smprimero=smnuevo;
        smultimo=smnuevo;
    }
    else{
		smanterior = NULL;
		smtemporal = smprimero;
		int count = 1;
		while(smtemporal!=NULL){
			if(count == pos){
				break;
			}
			smanterior = smtemporal;
			smtemporal = smtemporal->next;
			count++;
		}
		if(smanterior == NULL){
			smtemporal->prev=smnuevo;
			smnuevo->next=smtemporal;
			smnuevo->prev=smanterior;
			smprimero=smnuevo;
		}
		else if(smtemporal == NULL){
			smnuevo->next=smtemporal;
			smanterior->next=smnuevo;
			smnuevo->prev=smanterior;
			smultimo=smnuevo;
		}else{
			smtemporal->prev=smnuevo;
			smnuevo->next=smtemporal;
			smanterior->next=smnuevo;
			smnuevo->prev=smanterior;
		}
    }
}

void muestraProd(){
	if (spprimero==NULL){
		printf("Error! No hay nodos para mostrar. Esto puede significar que no hay registros, o no hay registros para el filtro especificado.\n");
		getche();
		return;
	}else{
		spactual = spprimero;
		printf("===============================================================================================================\n");
		printf("CLAVE                NOMBRE               FAMILIA               UNI/MED    PR/U   EXINI   EXACT   STMIN   STMAX\n");
		printf("===============================================================================================================\n");
		do{
			printf("%5d  %20s  %20s  %20s  %6d  %6d  %6d  %6d  %6d\n", spactual->spclave, spactual->spnombre, spactual->spfamilia, spactual->spmedida, spactual->sppu, spactual->speini, spactual->speact, spactual->spsmin, spactual->spsmax);
			spactual=spactual->next;
		}while(spactual!=NULL);
		printf("===============================================================================================================\n");
		printf("Presione Enter para continuar...");
		getche();
	}
}

void muestraMovi(){
	if (smprimero==NULL){
		printf("Error! No hay nodos para mostrar. Esto puede significar que no hay registros, o no hay registros para el filtro especificado.\n");
		getche();
		return;
	}else{
		smactual = smprimero;
		printf("====================================================\n");
		printf("CLAVE  FECHA       CANTIDAD   TIPO_MOV  SUB_TIPO_MOV\n");
		printf("====================================================\n");
		do{
			printf("%5d  %10s    %6d      %c            %c\n", smactual->smclave, smactual->smfecha, smactual->smcantidad, smactual->smmainmov, smactual->smsubmov);
			smactual=smactual->next;
		}while(smactual!=NULL);
		printf("====================================================\n");
		printf("Presione Enter para continuar...");
		getche();
	}
}

void sortClave(){
	pactual = pprimero;
	spprimero = NULL;
	spactual = NULL;
	spultimo = NULL;
	spnuevo = NULL;
	spanterior = NULL;
	spsiguiente = NULL;
	sptemporal = NULL;
	do{
		if (spprimero==NULL){
			inserta_productos_sort(pactual->pclave, pactual->pnombre, pactual->pfamilia, pactual->pmedida, pactual->ppu, pactual->peini, pactual->peact, pactual->psmin, pactual->psmax, 1);
		}else{
			int pos = 1;
			int check = 0;
			spactual = spprimero;
			do{
				if (pactual->pclave < spactual->spclave){
					inserta_productos_sort(pactual->pclave, pactual->pnombre, pactual->pfamilia, pactual->pmedida, pactual->ppu, pactual->peini, pactual->peact, pactual->psmin, pactual->psmax, pos);
					check = 1;
					break;
				}
				pos++;
				spactual = spactual->next;
			}while(spactual!=NULL);
			if (check == 0){
				inserta_productos_sort(pactual->pclave, pactual->pnombre, pactual->pfamilia, pactual->pmedida, pactual->ppu, pactual->peini, pactual->peact, pactual->psmin, pactual->psmax, pos);
			}
		}
		pactual=pactual->next;
	}while(pactual!=NULL);
}

void sortNombre(){
	pactual = pprimero;
	spprimero = NULL;
	spactual = NULL;
	spultimo = NULL;
	spnuevo = NULL;
	spanterior = NULL;
	spsiguiente = NULL;
	sptemporal = NULL;
	do{
		if (spprimero==NULL){
			inserta_productos_sort(pactual->pclave, pactual->pnombre, pactual->pfamilia, pactual->pmedida, pactual->ppu, pactual->peini, pactual->peact, pactual->psmin, pactual->psmax, 1);
		}else{
			int pos = 1;
			int check = 0;
			int n = 0;
			string nombrep;
			string nombres;
			spactual = spprimero;
			do{
				int n = 0;
				nombrep = pactual -> pnombre;
				nombres = spactual -> spnombre;
				int i = 0;
				while( nombrep[i] ) {
					nombrep[i] = tolower(nombrep[i]);
					i++;
				}
				i = 0;
				while( nombres[i] ) {
					nombres[i] = tolower(nombres[i]);
					i++;
				}
				while(true){
					if(nombrep.substr(0, n) == nombres.substr(0, n)){
						n++;
						continue;
					}else{
						break;
					}
				}
				if (nombrep.substr(0, n) < nombres.substr(0, n)){
					inserta_productos_sort(pactual->pclave, pactual->pnombre, pactual->pfamilia, pactual->pmedida, pactual->ppu, pactual->peini, pactual->peact, pactual->psmin, pactual->psmax, pos);
					check = 1;
					break;
				}
				pos++;
				spactual = spactual->next;
			}while(spactual!=NULL);
			if (check == 0){
				inserta_productos_sort(pactual->pclave, pactual->pnombre, pactual->pfamilia, pactual->pmedida, pactual->ppu, pactual->peini, pactual->peact, pactual->psmin, pactual->psmax, pos);
			}
		}
		pactual=pactual->next;
	}while(pactual!=NULL);
}

void sortExistenciaOr(){
	pactual = pprimero;
	spprimero = NULL;
	spactual = NULL;
	spultimo = NULL;
	spnuevo = NULL;
	spanterior = NULL;
	spsiguiente = NULL;
	sptemporal = NULL;
	do{
		if (pactual->peact < pactual->psmin){
			if (spprimero==NULL){
				inserta_productos_sort(pactual->pclave, pactual->pnombre, pactual->pfamilia, pactual->pmedida, pactual->ppu, pactual->peini, pactual->peact, pactual->psmin, pactual->psmax, 1);
			}else{
				int pos = 1;
				int check = 0;
				spactual = spprimero;
				do{
					if (pactual->peact < spactual->speact){
						inserta_productos_sort(pactual->pclave, pactual->pnombre, pactual->pfamilia, pactual->pmedida, pactual->ppu, pactual->peini, pactual->peact, pactual->psmin, pactual->psmax, pos);
						check = 1;
						break;
					}
					pos++;
					spactual = spactual->next;
				}while(spactual!=NULL);
				if (check == 0){
					inserta_productos_sort(pactual->pclave, pactual->pnombre, pactual->pfamilia, pactual->pmedida, pactual->ppu, pactual->peini, pactual->peact, pactual->psmin, pactual->psmax, pos);
				}
			}
			pactual=pactual->next;
		}else{
			pactual=pactual->next;
		}
	}while(pactual!=NULL);
}

void sortExistenciaOf(){
	pactual = pprimero;
	spprimero = NULL;
	spactual = NULL;
	spultimo = NULL;
	spnuevo = NULL;
	spanterior = NULL;
	spsiguiente = NULL;
	sptemporal = NULL;
	do{
		if (pactual->peact > pactual->psmax){
			if (spprimero==NULL){
				inserta_productos_sort(pactual->pclave, pactual->pnombre, pactual->pfamilia, pactual->pmedida, pactual->ppu, pactual->peini, pactual->peact, pactual->psmin, pactual->psmax, 1);
			}else{
				int pos = 1;
				int check = 0;
				spactual = spprimero;
				do{
					if (pactual->peact < spactual->speact){
						inserta_productos_sort(pactual->pclave, pactual->pnombre, pactual->pfamilia, pactual->pmedida, pactual->ppu, pactual->peini, pactual->peact, pactual->psmin, pactual->psmax, pos);
						check = 1;
						break;
					}
					pos++;
					spactual = spactual->next;
				}while(spactual!=NULL);
				if (check == 0){
					inserta_productos_sort(pactual->pclave, pactual->pnombre, pactual->pfamilia, pactual->pmedida, pactual->ppu, pactual->peini, pactual->peact, pactual->psmin, pactual->psmax, pos);
				}
			}
			pactual=pactual->next;
		}else{
			pactual=pactual->next;
		}
	}while(pactual!=NULL);
}

void sortFecha(){
	mactual = mprimero;
	smprimero = NULL;
	smactual = NULL;
	smultimo = NULL;
	smnuevo = NULL;
	smanterior = NULL;
	smsiguiente = NULL;
	smtemporal = NULL;
	/*int smclave;
	char smfecha[11];
	int smcantidad;
	char smmainmov;
	char smsubmov;*/
	do{
		if (smprimero==NULL){
			inserta_movimientos_sort(mactual->mclave, mactual->mfecha, mactual->mcantidad, mactual->mmainmov, mactual->msubmov, 1);
		}else{
			int pos = 1;
			int check = 0;
			smactual = smprimero;
			string fechan;
			string fechas;
			string dian;
			string dias;
			string mesn;
			string mess;
			string yean;
			string yeas;
			do{
				fechan = mactual -> mfecha;
				fechas = smactual -> smfecha;
				dian = fechan.substr(0, 2);
				dias = fechas.substr(0, 2);
				mesn = fechan.substr(3, 2);
				mess = fechas.substr(3, 2);
				yean = fechan.substr(6, 4);
				yeas = fechas.substr(6, 4);
				if (std::stoi(yean) < std::stoi(yeas)){
					inserta_movimientos_sort(mactual->mclave, mactual->mfecha, mactual->mcantidad, mactual->mmainmov, mactual->msubmov, pos);
					check = 1;
					break;
				}else if (std::stoi(yean) == std::stoi(yeas) && std::stoi(mesn) < std::stoi(mess)){
					inserta_movimientos_sort(mactual->mclave, mactual->mfecha, mactual->mcantidad, mactual->mmainmov, mactual->msubmov, pos);
					check = 1;
					break;
				}else if (std::stoi(mesn) == std::stoi(mess) && std::stoi(dian) <= std::stoi(dias)){
					inserta_movimientos_sort(mactual->mclave, mactual->mfecha, mactual->mcantidad, mactual->mmainmov, mactual->msubmov, pos);
					check = 1;
					break;
				}
				pos++;
				smactual = smactual->next;
			}while(smactual!=NULL);
			if (check == 0){
				inserta_movimientos_sort(mactual->mclave, mactual->mfecha, mactual->mcantidad, mactual->mmainmov, mactual->msubmov, pos);
			}
		}
		mactual=mactual->next;
	}while(mactual!=NULL);
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
			sortClave();
			muestraProd();
		}else if (strcmp(x, "b") == 0){
			sortNombre();
			muestraProd();
		}else if (strcmp(x, "c") == 0){
			//consulta_familia()
		}else if (strcmp(x, "d") == 0){
			sortExistenciaOr();
			muestraProd();
		}else if (strcmp(x, "e") == 0){
			sortExistenciaOf();
			muestraProd();
		}else if (strcmp(x, "f") == 0){
			pclave=pedir_entero(1,99999,"Indica la clave del producto a buscar");
    		if(!busca_clave(pclave)){
				printf("\nError, la clave no existe en productos.\n");
				getche();
			}else{
			sortFecha();
			muestraMovi();
			}
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
	std::ofstream file;
    file.open("productos.txt",std::ios::app);
    file.close();
    file.open("movimientos.txt",std::ios::app);
    file.close();
    cargar_productos("productos.txt");
    cargar_movimientos("movimientos.txt");
	menuReportes();
}
#ifndef CLUBES_H_INCLUDED
#define CLUBES_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <windows.h>


#define ARG_ARCH_CLUB_A 1
#define ARG_ARCH_CLUB_B 2
#define ARG_ARCH_CLUB_FUS 3

#define TAM_MAX_LINEA 30

#define TODO_OK 0
#define ERROR_ARCH 1
#define ERROR_MEM 2
#define ERROR_LINEA 3

typedef struct
{
	char codSocio[12];
	char apyn[51];
	int antiguedad;
}
SocioA;


typedef struct
{
	int nroSocio;
	char apyn[51];
	int antiguedad;
}
SocioB;


typedef int (*Cmp)(const void*, const void*);


void generarArchivoSociosClubA(char* nombreArchBin);
void mostrarArchSociosA(char*nombreArchBin);
void generarArchivoSociosClubBTxtDesord(char* nombreArchTxt);
void mostrarArchSociosBTxt(char*nombreArchTxt);

int fusionarArchivos_ALU(const char* nombreSociosClubA, const char* nombreSociosClubBTxt, const char* nombreSociosFus);
int sociosBTxtABin_ALU(const char* nombreSociosBTxt, const char* nombreSociosBBin);
int txtVarABin_ALU(char* linea,SocioB* socioBAcual);
SocioB* crearVectorSociosB_ALU(const char* nombreSociosBBin, int* ce);
int fusionarArchivoYVector_ALU(const char* nombreSociosClubA, SocioB* sociosBVec, int ce, const char* nombreSociosFus);

void crearSocioFu_ALU(SocioA* sFu,SocioA* sA, SocioB* sB,int op);

void ordenarVector_ALU(void* vec, int ce, int tamElem, Cmp cmp);
void* buscarMenor_ALU(void*ini,void*fin,size_t tamElem,Cmp cmp);
void intercambiar_ALU(void* x,void*y,size_t tamElem);
int compararNroSocio_ALU(const void*, const void*);
int compararCodSocio_ALU(const void*x,const void* y);

#endif // CLUBES_H_INCLUDED

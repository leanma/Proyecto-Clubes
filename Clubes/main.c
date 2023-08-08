#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include "Clubes.h"

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "spanish");
	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);


	printf("Lista de socios CLUB A\n");
	generarArchivoSociosClubA(argv[ARG_ARCH_CLUB_A]);
	mostrarArchSociosA(argv[ARG_ARCH_CLUB_A]);

    printf("\nLista de socios CLUB B\n");
    generarArchivoSociosClubBTxtDesord(argv[ARG_ARCH_CLUB_B]);
    mostrarArchSociosBTxt(argv[ARG_ARCH_CLUB_B]);


    int estaOk=fusionarArchivos_ALU(argv[ARG_ARCH_CLUB_A], argv[ARG_ARCH_CLUB_B], argv[ARG_ARCH_CLUB_FUS]);

    if(estaOk!=TODO_OK)
        return estaOk;

    printf("\nLista de socios CLUB FUSIONADOS\n");
    mostrarArchSociosA(argv[ARG_ARCH_CLUB_FUS]);

    return TODO_OK;
}



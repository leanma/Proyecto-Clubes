#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include "Clubes.h"



void generarArchivoSociosClubA(char* nombreArchBin)
{
    SocioA vecSocio[]={
                        {"16001129","Wilkerson Berk",1},
                        {"16200214","Clark Scott",2},
                        {"16230902","Boyd Chaney",3},
                        {"16231024","Guerra Oliver",4},
                        {"16540430","Brennan Lee",5},
                        {"16621004","Mcclain Ronan",6},
                        {"16660110","Dale Isaac",7},
                        {"16780215","Sosa Zeph",8},
                        {"16860403","Gibbs Clinton",9},
                        {"16870210","Cole Coby",1},
                        {"16900207","Gallegos Nash",2},
                        {"16940212","Hunter Rajah",3},
                        };
    int ce=12;

    ordenarVector_ALU(vecSocio,ce,sizeof(SocioA),compararCodSocio_ALU);

    FILE*archBin=fopen(nombreArchBin,"wb");
    if(!archBin)
        exit(ERROR_ARCH);


    for(SocioA*i=vecSocio;i<vecSocio+ce;i++)
    {
        fwrite(i,sizeof(SocioA),1,archBin);
    }

    fclose(archBin);
}


void mostrarArchSociosA(char*nombreArchBin)
{
    FILE*archBin=fopen(nombreArchBin,"rb");
    if(!archBin)
        exit(ERROR_ARCH);

    SocioA socioActual;
    fread(&socioActual,sizeof(SocioA),1,archBin);
    while(!feof(archBin))
    {
        printf("%-13s|%-15s|%d\n",socioActual.codSocio,socioActual.apyn,socioActual.antiguedad);
        fread(&socioActual,sizeof(SocioA),1,archBin);
    }

    fclose(archBin);
}

void generarArchivoSociosClubBTxtDesord(char* nombreArchTxt)
{
    SocioB vecSocio[]={
                        {16001129,"Wilkerson Berk",10},
                        {16200214,"Clark Scott",20},
                        {16230902,"Boyd Chaney",1},
                        {16860403,"Gibbs Clinton",9},
                        {16870210,"Cole Coby",4},
                        {16900207,"Gallegos Nash",1},
                        {99999999,"Jake Domm",90},
                        };
    int ce=7;

    FILE*archTxt=fopen(nombreArchTxt,"wt");
    if(!archTxt)
        exit(ERROR_ARCH);


    for(SocioB*i=vecSocio;i<vecSocio+ce;i++)
    {
        fprintf(archTxt,"%d|%s|%d\n",i->nroSocio,i->apyn,i->antiguedad);
    }

    fclose(archTxt);
}


void mostrarArchSociosBTxt(char*nombreArchTxt)
{
    FILE*archTxt=fopen(nombreArchTxt,"rt");
    if(!archTxt)
        exit(ERROR_ARCH);

    char linea[TAM_MAX_LINEA];
    fgets(linea,TAM_MAX_LINEA,archTxt);

    while(!feof(archTxt))
    {
        printf("%s",linea);
        fgets(linea,TAM_MAX_LINEA,archTxt);
    }

    fclose(archTxt);
}



int fusionarArchivos_ALU(const char* nombreSociosClubA, const char* nombreSociosClubBTxt, const char* nombreSociosFus)
{
    int estaOk=sociosBTxtABin_ALU(nombreSociosClubBTxt,"Socios_CLub_B.dat");
    if(estaOk!=TODO_OK)
        return estaOk;

    int ce=0;
    SocioB* vecSB=crearVectorSociosB_ALU("Socios_CLub_B.dat",&ce);
    if(!vecSB)
        return ERROR_ARCH;

    ordenarVector_ALU(vecSB,ce,sizeof(SocioB),compararNroSocio_ALU);


    estaOk=fusionarArchivoYVector_ALU(nombreSociosClubA,vecSB,ce,nombreSociosFus);
    if(estaOk!=TODO_OK)
        return estaOk;

    free (vecSB);
    return TODO_OK;
}

int sociosBTxtABin_ALU(const char* nombreSociosBTxt, const char* nombreSociosBBin)
{
    FILE* archTxt=fopen(nombreSociosBTxt,"rt");
    if(!archTxt)
    {
        printf("ERROR EN LA APERTURA DE ARCHIVO\n");
        return ERROR_ARCH;
    }

    FILE* archBin=fopen(nombreSociosBBin,"wb");
    if(!archBin)
    {
        printf("ERROR EN LA APERTURA DE ARCHIVO\n");
        fclose(archTxt);
        return ERROR_ARCH;
    }

    char linea[TAM_MAX_LINEA];
    SocioB socioBAcual;

    fgets(linea,TAM_MAX_LINEA,archTxt);

    while(!feof(archTxt))
    {
        txtVarABin_ALU(linea,&socioBAcual);
        fwrite(&socioBAcual,sizeof(SocioB),1,archBin);
        fgets(linea,TAM_MAX_LINEA,archTxt);
    }

    fclose(archBin);
    fclose(archTxt);
    return TODO_OK;

}


int txtVarABin_ALU(char* linea,SocioB*socioBAcual)
{
    char*act=strchr(linea,'\n');
    if(!act)
    {
        printf("ERROR DE LINEA EN EL TXT\n");
        return ERROR_LINEA;
    }

    *act='\0';
    act=strrchr(linea,'|');
    sscanf(act+1,"%d",&socioBAcual->antiguedad);

    *act='\0';
    act=strrchr(linea,'|');
    strcpy(socioBAcual->apyn,act+1);

    *act='\0';
    sscanf(linea,"%d",&socioBAcual->nroSocio);

    return TODO_OK;
}




SocioB* crearVectorSociosB_ALU(const char* nombreSociosBBin, int* ce)
{
    FILE* archBin=fopen(nombreSociosBBin,"rb");
    if(!archBin)
    {
        printf("ERROR EN LA APERTURA DE ARCHIVO\n");
        return NULL;
    }

    fseek(archBin,0,SEEK_END);
    long tamArch=ftell(archBin);
    *ce=(int)tamArch/(int)sizeof(SocioB);

    SocioB* vec=malloc(*ce*sizeof(SocioB));
    if(!vec)
    {
        fclose(archBin);
        return NULL;
    }
    rewind(archBin);

    SocioB* vec_ptr=vec;
    SocioB SocioBActual;

    fread(&SocioBActual,sizeof(SocioB),1,archBin);
    while(!feof(archBin))
    {
        *vec_ptr=SocioBActual;
        vec_ptr++;
        fread(&SocioBActual,sizeof(SocioB),1,archBin);
    }

    fclose(archBin);
    return vec;
}

void ordenarVector_ALU(void* vec, int ce, int tamElem, Cmp cmp)
{
    void*m;
    void*ult=(char*)vec+(ce-1)*tamElem;

    for(char*i=(char*)vec;i<(char*)ult;i+=tamElem)
    {
        m=buscarMenor_ALU(i,ult,tamElem,cmp);
        if(i!=m)
            intercambiar_ALU(i,m,tamElem);
    }
}

void* buscarMenor_ALU(void*ini,void*fin,size_t tamElem,Cmp cmp)
{
    void*m=ini;
    for(char*j=(char*)ini+tamElem;j<=(char*)fin;j+=tamElem)
    {
        if(cmp(j,m)<0)
            m=j;
    }

    return m;
}

int compararNroSocio_ALU(const void*x,const void* y)
{
    SocioB socio1=*(SocioB*)x;
    SocioB socio2=*(SocioB*)y;

    if(socio1.nroSocio>socio2.nroSocio)
        return 1;
    if(socio1.nroSocio<socio2.nroSocio)
        return -1;
    return 0;
}

void intercambiar_ALU(void* x,void*y,size_t tamElem)
{
    void* xTemp=malloc(tamElem);
    memcpy(xTemp,x,tamElem);
    memcpy(x,y,tamElem);
    memcpy(y,xTemp,tamElem);
    free(xTemp);
}

int compararCodSocio_ALU(const void*x,const void* y)
{
    SocioA socio1=*(SocioA*)x;
    SocioA socio2=*(SocioA*)y;

    if(atoi(socio1.codSocio)>atoi(socio2.codSocio))
        return 1;
    if(atoi(socio1.codSocio)<atoi(socio2.codSocio))
        return -1;
    return 0;
}


int fusionarArchivoYVector_ALU(const char* nombreSociosClubA, SocioB* sociosBVec, int ce, const char* nombreSociosFus)
{
    FILE* archSA=fopen(nombreSociosClubA,"rb");
    if(!archSA)
    {
        printf("ERROR EN LA APERTURA DE ARCHIVO\n");
        return ERROR_ARCH;
    }

    FILE* archFu=fopen(nombreSociosFus,"wb");
    if(!archFu)
    {
        printf("ERROR EN LA APERTURA DE ARCHIVO\n");
        fclose(archSA);
        return ERROR_ARCH;
    }

    SocioB*actualSB=sociosBVec;
    SocioA actualSA;
    SocioA actualSFu;

    fread(&actualSA,sizeof(SocioA),1,archSA);

    while(!feof(archSA) && actualSB<sociosBVec+ce)
    {
        int comp=atoi(actualSA.codSocio)-actualSB->nroSocio;
        if(comp==0)
        {
            sprintf(actualSFu.codSocio,"%d-AB",actualSB->nroSocio);
            strcpy(actualSFu.apyn,actualSA.apyn);
            if(actualSA.antiguedad>actualSB->antiguedad)
                actualSFu.antiguedad=actualSA.antiguedad;
            else
            {
                actualSFu.antiguedad=actualSB->antiguedad;
            }
            actualSB++;
            fread(&actualSA,sizeof(SocioA),1,archSA);
        }
        if(comp<0)
        {
            strcpy(actualSFu.codSocio,actualSA.codSocio);
            strcat(actualSFu.codSocio,"-A");
            strcpy(actualSFu.apyn,actualSA.apyn);
            actualSFu.antiguedad=actualSA.antiguedad;
            fread(&actualSA,sizeof(SocioA),1,archSA);
        }
        if(comp>0)
        {
            sprintf(actualSFu.codSocio,"%d-B",actualSB->nroSocio);
            strcpy(actualSFu.apyn,actualSB->apyn);
            actualSFu.antiguedad=actualSB->antiguedad;
            actualSB++;
        }
        fwrite(&actualSFu,sizeof(SocioA),1,archFu);
    }

    while(!feof(archSA))
    {
        strcpy(actualSFu.codSocio,actualSA.codSocio);
        strcat(actualSFu.codSocio,"-A");
        strcpy(actualSFu.apyn,actualSA.apyn);
        actualSFu.antiguedad=actualSA.antiguedad;
        fwrite(&actualSFu,sizeof(SocioA),1,archFu);
        fread(&actualSA,sizeof(SocioA),1,archSA);
    }
    while(actualSB<sociosBVec+ce)
    {
        sprintf(actualSFu.codSocio,"%d-B",actualSB->nroSocio);
        strcpy(actualSFu.apyn,actualSB->apyn);
        actualSFu.antiguedad=actualSB->antiguedad;
        fwrite(&actualSFu,sizeof(SocioA),1,archFu);
        actualSB++;
    }


    fclose(archFu);
    fclose(archSA);
    return TODO_OK;
}




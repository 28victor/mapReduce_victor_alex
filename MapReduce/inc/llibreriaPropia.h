#ifndef __LLIBRERIA_PROPIA_H__
#define __LLIBRERIA_PROPIA_H__
// incloure les llibreries que es necessiten
#include <stdbool.h>

#define FICADENA '\0'
#define MAXCADENA 100
#define SALTLINIA '\n'
void acabament(void);
int demanaNumeroEntreDosValors(int, int);
int generarNumeroEntreDosValors(int, int);
int demanaNumeroAPartirUnValor(int);
bool esTraspas(int);
char demanarCaracter();
int demanaNumero(void);
void intercanviVariables(int *, int *);
bool cerca(int[], int, int);
bool cercaSentilla(int[], int);
int posicio(int[], int, int);
void seleccioMin(int[], int);
void mostraContingut(int[], int);
void bombollaMin(int[], int);
bool esLletra(char);
bool esVocal(char);
int calculLongitud(char[], int);
void pintaCadena(char[], int);
void entrarCadena(char[], int);
void generarFitxer(char[]);
void escriureFitxerBasicFinal(char[]);
void llegirFitxerSencer(char[]);
bool existeixFitxer(char[]);
bool fitxerBuit(char[]);
void eliminaSaltLinia(char[]);
bool escullFitx(char[]);
void continua();

#endif
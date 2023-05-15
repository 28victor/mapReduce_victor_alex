#ifndef D8E5564E_A998_46E6_9A70_0B73488F1AF3
#define D8E5564E_A998_46E6_9A70_0B73488F1AF3
//incloure les llibreries que es necessiten
#include <stdbool.h>

#define RUTANOVA './fitxers/resum.txt'
    
   enum OPCIOMENU
   {
        COMPTEPARAULES=1,
        COMPTELLETRES,
        SORTIR
   };

void pintaMenu();
void compteparaules();
void borrarCarSeparadores(char [], int );
void duplicarFitxer (char [], char []);
bool nomRepetit(char [], char []);

#endif /* D8E5564E_A998_46E6_9A70_0B73488F1AF3 */

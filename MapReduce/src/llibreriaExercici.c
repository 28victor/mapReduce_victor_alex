#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "rlutil.h"
#include "llibreriaPropia.h"
#include "llibreriaExercici.h"

// Imprimir menú
void pintaMenu()
{
    char opcions[SORTIR][MAXCADENA] = {"Compte paraules", "Compte caràcers", "Sortir"};

    for (int i = 0; i < SORTIR; i++)
    {
        printf("\n%d:-%s", i + 1, opcions[i]);
    }
}

void compteparaules()
{

    // Borrem el "Resultat.txt" anterior per no tenir problemes.
    remove("./fitxers/Resultat.txt");
    remove("./fitxers/noms.txt");
    remove("./fitxers/dup.txt");

    // Definim les rutas dels fitxers.
    char rutaFitxP[MAXCADENA] = "./fitxers/";
    char rutaDupliP[MAXCADENA] = "./fitxers/dup.txt";
    char rutaNomsP[MAXCADENA] = "./fitxers/noms.txt";

    // Definim fitxers del que usarem de referencia i el que usarem per guardar els noms.
    FILE *fAnalitzarP;
    FILE *fNomsP;

    // En cas que ja hagues un fitxer "noms.txt" el sobreescribim per que estigui buit.
    fNomsP = fopen(rutaNomsP, "wt");
    fclose(fNomsP);

    // Cadena que guardara la paraula auxiliar cada volta que s'executi el codi.
    char nomP[MAXCADENA];

    // Natajem pantalla
    cls();

    // Entrem a la funció "escullFitx()" la qual ens demanarà un fitxer. Si el fitxer existeix la funció retorna 1.
    if (escullFitx(rutaFitxP))
    {
        // Executem el procediment "duplicarFitxer()", el qual creara una copia
        // exacta del fitxer que anteriorment habiem escollit.

        // -- Aquest pas no es totalment obligatori, ja que es poden obrir 2 instanciés
        // -- simultaniament en el mateix fitxer i amb cursors a diferentes posicions.
        // -- Pero d'aquesta manera es molt més fàcil d'entendre i debuggar.

        duplicarFitxer(rutaFitxP, rutaDupliP);

        // Obrim el fitxer amb el que haurem de treballar.
        fAnalitzarP = fopen(rutaFitxP, "rt");

        // Amb el <feof()> podrém entrar en un bucle que es repetira fins que el cursor arribi al final del fitxer.
        while (feof(fAnalitzarP) == 0)
        {

            // Guardem la primera paraula a una cadena (nomP).
            // -- El problema que podem trobar es en el cas que hi hagi un separador. Ja que també el guarda com part de la cadena.
            fscanf(fAnalitzarP, "%s", nomP);

            // Per evitar guardar un caràcter separador, entrem al procediment "borrarCarSeparadores()". La qual si a la cadena que acabem de guardar
            // hi ha un caràcter separador (,|.) el substituira per '\0' (caràcter que defineix el final de la cadena).
            borrarCarSeparadores(nomP, strlen(nomP));

            // Entrem en la funció "nomRepetit()", la qual retorna un bool (0|1), si el nom ja ha sigut contat anteriorment o no.
            if (!nomRepetit(nomP, rutaNomsP))
            {
                // Si em entrat aquí s'ignifica que la paraula que anem a contar (nomP) encara no ha sigut contada abanç.

                // D'aquí res anem a contar la nova paraula, es per aixó que per evitar que es torni a contar
                // l'afagim al fitxer "noms.txt" com a una nova linía.
                // Obrim el fitxer "noms.txt" amb el mode "at", el qual colocará el cursor al final del fitxer per poder afegir més contingut.
                fNomsP = fopen(rutaNomsP, "at");
                // Afegim el nou nom y un '\n' perque la següent vegada que afegim un nom nou, sigui a una nova línia.
                fprintf(fNomsP, "%s\n", nomP);

                // Tenquem el fitxer.
                fclose(fNomsP);

                // Entrem en el procediment "contadorParaula()".
                contadorParaula(nomP, rutaDupliP);
            }
        }
        // Quan ja em analitzat i fet el MapReduce, tenquem el fitxer de text.
        fclose(fAnalitzarP);
    }

    // Borrem els fitxers extras per millor optimització i comoditat.
    remove("./fitxers/noms.txt");
    remove("./fitxers/dup.txt");

    // Executem una animació per l'usuari.
    cls();
    anim();
    cls();

    // Executem un procediment que llegira el fitxer "Resultat.txt" complet.
    llegirFitxerSencer("Resultat");
    printf("\n");

    // Demanem a l'usuari que premi una tecla per continuar.
    // continua();
    // cls();
}

// El procediment "contadorParaula()" crea el fitxer "Resultat.txt" on guardarem el MapReduce finalitzat.
void contadorParaula(char titol[], char rutaDup[])
{
    FILE *fAuxP;
    FILE *fDuplicatP;

    // Obrim el fitxer duplicat per poder recorrel i contar quants cops apareix.
    fDuplicatP = fopen(rutaDup, "rt");

    // Creem el contador iniciat a 0.
    int cont = 0;

    // El nomAux será la cadena on guardarem la paraula que estem consultant en el fitxer duplicat.
    char nomAux[MAXCADENA];

    // Al igual que abanç, mentres que el cursor del fitxer duplicat no hagi arribat al final,
    // es comparan la paraula que busquem amb cada paraula que conté el fitxer duplicat i si son iguals, es suma 1 al contador.
    while (feof(fDuplicatP) == 0)
    {
        // Guardem la següent paraula del fitxer a la cadena nomAux
        fscanf(fDuplicatP, "%s", nomAux);

        // En cas que contingui un caràcter seprador, s'elimina.
        borrarCarSeparadores(nomAux, strlen(nomAux));

        // Si finalment aquestes 2 cadenes son iguals, es suma 1 al contador.
        if (strcmpi(titol, nomAux) == 0)
        {
            cont++;
        }
    }

    // Tenquem el fitxer duplicat.
    fclose(fDuplicatP);

    // Obrim el fitxer "Resultat.txt" amb mode "at" per actualitzar-lo.
    fAuxP = fopen("./fitxers/Resultat.txt", "at");
    // Afegim a la nova línia del fitxer, la nova paraula i quantes vegades apareix.
    fprintf(fAuxP, "[%s] : %d\n", titol, cont);
    // Tenquem el fitxer "Resultat.txt".
    fclose(fAuxP);
}

// Procediment que escaneja un fitxer i el duplica a un altre.
void duplicarFitxer(char ruta[], char rutaDupli[])
{
    FILE *fDup;
    FILE *fOrg;

    // Obrim els 2 fitxers, un per llegir, el altre per escriure.
    fOrg = fopen(ruta, "rt");
    fDup = fopen(rutaDupli, "wt");

    char cadCpy[MAXCADENA];

    // Fins que no arribem al final del fitxer original, es copia el contingut de la línia al fitxer duplicat.
    while (feof(fOrg) == 0)
    {
        fgets(cadCpy, MAXCADENA, fOrg);
        fprintf(fDup, "%s", cadCpy);
    }

    // Tenquem els 2 fitxers.
    fclose(fOrg);
    fclose(fDup);
}

// Procediment que rep una cadena i la seva longitud.
// Aquesta cadena pot o no tenir caràcters separadors, en cas de tenir, al detectar-lo el substituira per un '\0'.
void borrarCarSeparadores(char cad[], int len)
{
    // Bucle <for> que es repeteix tantes vegades com caràcters te la cadena.
    for (int i = 0; i <= len; i++)
    {
        // Si la posició [i] de la cadena es == a ',' o a '.' es substituira aquell caràcter per '\0'.
        if (cad[i] == ',' || cad[i] == '.')
        {
            cad[i] = FICADENA;
        }
    }
}

// Funció que rep la paraula actual i comproba comparant amb cada una de les paraules del fitxer "noms.txt" si ja ha surtit.
// -- El fitxer "noms.txt" es un fitxer que cada cop que surt una paraula nova la guarda com una nova linia per evitar contar
// -- la mateixa paraula més d'un cop.
bool nomRepetit(char nom[], char ruta[])
{
    // Variable bool de resultat.
    bool res = false;
    // Fitxer de "noms.txt".
    FILE *f;

    // Paraula que es guarda la linia de "noms.txt"
    char paraula[MAXCADENA];

    f = fopen(ruta, "rt");

    // Mentres el cursor no hagi arribat al final i el resultat siguie fals.
    while (feof(f) == 0 && res == false)
    {
        // Guardem una paraula a la cadena.
        fscanf(f, "%s", paraula);

        // Comparem la paraula actual amb la que hi ha al arxiu "noms.txt".
        // Si son iguals s'ignifica que aquesta paraula ja ha sigut contada, així que no em de tornar a procesar-la.
        if (strcmpi(paraula, nom) == 0)
        {
            res = true;
        }
    }

    // Tenquem fitxer i retornem el resultat bool.
    fclose(f);
    return res;
}

bool carRepetit(char nomC, char rutaNomsC[])
{
    bool res = false;

    FILE *f;

    char carAux;

    f = fopen(rutaNomsC, "rt");
    nomC = tolower(nomC);
    while (feof(f) == 0 && res == false)
    {
        carAux = fgetc(f);
        carAux = tolower(carAux);
        if (nomC == carAux)
        {
            res = true;
        }
    }

    fclose(f);
    return res;
}

void compteLletres()
{
    // Borrem el "Resultat.txt" anterior per no tenir problemes.
    remove("./fitxers/Resultat.txt");
    remove("./fitxers/noms.txt");
    remove("./fitxers/dup.txt");
    
    // Definim les rutas dels fitxers.
    char rutaFitxC[MAXCADENA] = "./fitxers/";
    char rutaDupliC[MAXCADENA] = "./fitxers/dup.txt";
    char rutaNomsC[MAXCADENA] = "./fitxers/noms.txt";

    // Definim fitxers del que usarem de referencia i el que usarem per guardar els noms.
    FILE *fAnalitzarC;
    FILE *fNomsC;

    // En cas que ja hagues un fitxer "noms.txt" el sobreescribim per que estigui buit.
    fNomsC = fopen(rutaNomsC, "wt");
    fclose(fNomsC);

    // Cadena que guardara la paraula auxiliar cada volta que s'executi el codi.
    char nomC;

    // Natajem pantalla
    cls();

    // Entrem a la funció "escullFitx()" la qual ens demanarà un fitxer. Si el fitxer existeix la funció retorna 1.
    if (escullFitx(rutaFitxC))
    {
        // Executem el procediment "duplicarFitxer()", el qual creara una copia
        // exacta del fitxer que anteriorment habiem escollit.

        // -- Aquest pas no es totalment obligatori, ja que es poden obrir 2 instanciés
        // -- simultaniament en el mateix fitxer i amb cursors a diferentes posicions.
        // -- Pero d'aquesta manera es molt més fàcil d'entendre i debuggar.

        duplicarFitxer(rutaFitxC, rutaDupliC);

        // Obrim el fitxer amb el que haurem de treballar.
        fAnalitzarC = fopen(rutaFitxC, "rt");

        while (feof(fAnalitzarC) == 0)
        {
            nomC = fgetc(fAnalitzarC);

            while (nomC == '\n')
            {
                nomC = fgetc(fAnalitzarC);
            }

            if (!carRepetit(nomC, rutaNomsC))
            {
                fNomsC = fopen(rutaNomsC, "at");

                fprintf(fNomsC, "%c\n", nomC);

                fclose(fNomsC);

                contadorCaracter(nomC, rutaDupliC);
            }
        }
        fclose(fAnalitzarC);
    }

    // Borrem els fitxers extras per millor optimització i comoditat.
    remove("./fitxers/noms.txt");
    remove("./fitxers/dup.txt");

    // Executem una animació per l'usuari.
    cls();
    anim();
    cls();

    // Executem un procediment que llegira el fitxer "Resultat.txt" complet.
    llegirFitxerSencer("Resultat");
    printf("\n");

    // Demanem a l'usuari que premi una tecla per continuar.
    // continua();
    // cls();
}

void contadorCaracter(char nomC, char rutaDupliC[])
{
    FILE *fAuxC;
    FILE *fDuplicatC;

    fDuplicatC = fopen(rutaDupliC, "rt");

    int cont = 0;

    char carAux;
    nomC = tolower(nomC);

    while (feof(fDuplicatC) == 0)
    {
        carAux = fgetc(fDuplicatC);
        carAux = tolower(carAux);
        // Si finalment aquestes 2 cadenes son iguals, es suma 1 al contador.
        if (carAux == nomC)
        {
            cont++;
        }
    }

    fclose(fDuplicatC);

    fAuxC = fopen("./fitxers/Resultat.txt", "at");

    fprintf(fAuxC, "[%c] : %d\n", nomC, cont);

    fclose(fAuxC);
}

//                #@%                                                                                         .*((
//                     &  #                                                                            #*,/,,@
//                       %. *                                                                       @.    &,
//                        @# ,                                                                   /. ( /.@
//                         @/  /&                                                              #.     @
//                         %. ., *                                                            %  /  /@
//                          @  #                                                            * . *   @
//                          @  #  .,*                                                      (   .  ,@
//                          ,@ @  % *,                                                    #  #  (&#(
//                           @@    % % /                                                 @ %  .%#/@
//                            @&@ & *   /.                                               #  %   #@.
//                             @@@  , / @ . %                                        @ # %   %, /@
//                              @@#@ #     (    @                                &/    . ,    @@@
//                    #.*%        %@@ % #    . ,   @         *               @&     #    ..  @@(          (&/,  *#(
//                      %%(,*       %@(/  ( ,    # ( @,,                 %@ * #          .  @@     @*,( .,.@
//                        .,   (      %@(, *  (   .%@%                      @&.&&  #  .,  @,   .*   /  @
//                          ( .(#%(%    @@@  ..  (/.    .                 ,     @#&%(# @@/   @. # * @
//                            @  ./  %  &#@@**  ./    %                  , ,%     ..% @@%  ,(    #,
//                              @   *  * ,*  *(%.     *  (              @ (*@     ./#((.     .  *
//                                /**.    /   &                                  *    .#.*   . @
//                                   .@/ */  ,,   *                             #*     /&**@
//                                 ,@#(*#@%%&    //                            /            ( &
//                             ,%                 ./                          .                 (*(
//                          &,            %        /                         .       %%%            &
//                       &/#            #*&  #      **                     (      *   %@              %/
//                    & ,%             * &@   /,                                ,&    (#@              / #*
//                 &                . %@%%@    &                               .@.    %.%@, @*               @
//           /&                   %/ ( ,## ,    %@@@.%                     (*@&@@     @ % %@@@&@    %             ((
//    /&/     %#   (&@%&  *@( #&@/@   ./   #    .@/@, @#&               (/@ @& @      *  ,#@#,.. /%(  /@ ,   @(@.         #,
//       (&(. .&*(((%/&/,     #/&  %(       &      ,@@@@@&  .         , @@@@&..      &      ./ ,*&@#@.*  % ,#. &  @&@@%.
//                 &%(.                       *          /(,@        /%.@          /%
//                                              #         */@        #%         %@%
//                                               #(/       *         &        @
//                                                   (     .#        (      %,
//                                                    @              *
//                                                                   ,     @
//                                                     @             .
//                                                     ,     #      @     ,
//                                                       &@/         @@@@ %
//                                                            /    @      ,
//                                                       ,               %
//                                                        /(    (     &%@
//                                                         @         ..(
//                                                          %#,        .
//                                                           &%(   , #*
//                                                            %@*(/% ./
//                                                             (@..%%*
//                                                              # ,#
//                                                            & &.*
//                                                             .,
//                                                               \.

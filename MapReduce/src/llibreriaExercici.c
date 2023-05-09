#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "rlutil.h"
#include "llibreriaPropia.h"
#include "llibreriaExercici.h"

void pintaMenu()
{
    char opcions[SORTIR][MAXCADENA] = {"Compte paraules", "Compte lletres", "Sortir"};

    for (int i = 0; i < SORTIR; i++)
    {
        printf("\n%d:-%s", i + 1, opcions[i]);
    }
}

void compteparaules()
{
    remove("./fitxers/Resultat.txt");
    char rutaFitxP[MAXCADENA] = "./fitxers/";
    char rutaDupliP[MAXCADENA] = "./fitxers/dup.txt";
    char rutaNomsP[MAXCADENA] = "./fitxers/noms.txt";

    FILE *fAnalitzarP;
    FILE *fNomsP;

    fNomsP = fopen(rutaNomsP, "wt");
    fclose(fNomsP);

    // char paraula[MAXCADENA];
    char nomP[MAXCADENA];

    cls();
    if (escullFitx(rutaFitxP))
    {
        duplicarFitxer(rutaFitxP, rutaDupliP);
        fAnalitzarP = fopen(rutaFitxP, "rt");

        while (feof(fAnalitzarP) == 0)
        {
            fscanf(fAnalitzarP, "%s", nomP);
            borrarCarSeparadores(nomP, strlen(nomP));

            if (!nomRepetit(nomP, rutaNomsP))
            {
                fNomsP = fopen(rutaNomsP, "at");
                fprintf(fNomsP, "%s\n", nomP);
                fclose(fNomsP);
                contadorParaula(nomP, rutaDupliP);
            }
        }
        fclose(fAnalitzarP);
    }
    remove("./fitxers/noms.txt");
    remove("./fitxers/dup.txt");


    cls();
    anim();
    cls();
    llegirFitxerSencer("Resultat");
    printf("\n");
    continua();
}

void contadorParaula(char titol[], char rutaDup[])
{
    FILE *fAuxP;
    FILE *fDuplicatP;

    fDuplicatP = fopen(rutaDup, "rt");

    int cont = 0;

    char nomAux[MAXCADENA];

    while (feof(fDuplicatP) == 0)
    {
        fscanf(fDuplicatP, "%s", nomAux);
        borrarCarSeparadores(nomAux, strlen(nomAux));

        if (strcmpi(titol, nomAux) == 0)
        {
            cont++;
        }
    }

    fclose(fDuplicatP);
    fAuxP = fopen("./fitxers/Resultat.txt", "at");
    fprintf(fAuxP, "[%s] : %d\n", titol, cont);
    fclose(fAuxP);
}

void duplicarFitxer(char ruta[], char rutaDupli[])
{
    FILE *fDup;
    FILE *fOrg;

    fOrg = fopen(ruta, "rt");
    fDup = fopen(rutaDupli, "wt");

    char cadCpy[MAXCADENA];

    while (feof(fOrg) == 0)
    {
        fgets(cadCpy, MAXCADENA, fOrg);
        fprintf(fDup, "%s", cadCpy);
    }

    fclose(fOrg);
    fclose(fDup);
}

void borrarCarSeparadores(char cad[], int len)
{
    for (int i = 0; i <= len; i++)
    {
        if (cad[i] == ',' || cad[i] == '.')
        {
            cad[i] = FICADENA;
        }
    }
}

bool nomRepetit(char nom[], char ruta[])
{
    bool res = false;
    FILE *f;
    char paraula[MAXCADENA];

    f = fopen(ruta, "rt");

    while (feof(f) == 0 && res == false)
    {
        fscanf(f, "%s", paraula);
        if (strcmpi(paraula, nom) == 0)
        {
            res = true;
        }
    }

    fclose(f);
    return res;
}

void compteLletres()
{
    cls();
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

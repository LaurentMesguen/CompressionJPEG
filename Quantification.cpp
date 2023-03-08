/*************************************************
* Titre    : quantification.c                    *
* Auteur   : LE SAUCE Julien / MESGUEN Laurent   *
* Groupe   : ISEN                                *
* Créé     : 14.02.12                            *
* Modifié  : 17.02.12                            *
**************************************************/

/** Fonction ********************************************************************************************
*                                                                                                       *
* Prototype : void quantification (Image *img, int qualite);                                            *
*                                                                                                       *
* Description : Cette fonction permet de réaliser une quantification des matrices de luminance et de    *
*               chrominance selon deux matrices de quantification données. Les matrices                 *
*               de quantification de luminance et de chrominance ont été optimisées et adoptées dans le *
*               standard JPEG.                                                                          *
*               La fonction va ainsi diviser chaque bloc de 8*8 (ou de 4*4) de l'image donnée en entrée *
*               par la matrice de quantification correspondante en tenant compte d'un facteur de        *
*               qualité donné également en entrée (facteur variant de 2 à 62 par pas de 2).             *
*               Formule de quantification :                                                             *
*               pixelQuantifie(x,y) = [ pixel(x,y) * 16 ] / [ quantification(x,y) * facteurQualite ]    *
*                                                                                                       *
* Paramètre E/S :                                                                                       *
*       - Entrée :  - Pointeur de structure de type Image contenant la matrice de taille N*M de         *
*                      luminance (tab1) et de taille N/2*M/2 de chrominance (tab2 et tab3).             *
*                   - Entier de type int représentant le facteur de qualité variant de 2 à 62 par pas   *
*                      de 2.                                                                            *
*                                                                                                       *
*       - Sortie :  - void _ On ne modifie que la structure donnée en entrée.                           *
*                                                                                                       *
********************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "quantification.h"
/*
Quant quantification (Image *img, uint32_t qualite) {
    int x,y,i,j;
    Quant table;
    // Matrice de quantification pour la luminance
    int luminance[8][8] = {
                            {16,11,10,16,24,40,51,61},
                            {12,12,14,19,26,58,60,55},
                            {14,13,16,24,40,57,69,56},
                            {14,17,22,29,51,87,80,62},
                            {18,22,37,56,68,109,103,77},
                            {24,35,55,64,81,104,113,92},
                            {49,64,78,87,103,121,120,101},
                            {72,92,95,98,112,100,103,99} };

    // Matrice de quantification pour la chrominance
    int chrominance[8][8] = {
                            {17,18,24,47,99,99,99,99},
                            {18,21,26,66,99,99,99,99},
                            {24,26,56,99,99,99,99,99},
                            {47,66,99,99,99,99,99,99},
                            {99,99,99,99,99,99,99,99},
                            {99,99,99,99,99,99,99,99},
                            {99,99,99,99,99,99,99,99},
                            {99,99,99,99,99,99,99,99} };

    /** Vérification du format du facteur de qualité **/

    /*if(!( qualite >= 1 && qualite <= 100) ){
        printf("ERREUR 'quantification' : le facteur qualite doit etre compris entre 1 et 100\n");
    }*/

    /** Modification des matrices de base en tenant compte du facteur de qualité **/
    // On balaye les tableaux et on utilise la formule du facteur de qualité
    /*if(qualite == 100){
        for (x=0; x<8; x++) {
            for (y=0; y<8; y++) {
                table.luminance[x][y] = 1;
                table.chrominance[x][y] = 1;
            }
        }
    }
    for (x=0; x<8; x++) {
        for (y=0; y<8; y++) {
            table.luminance[x][y] = (luminance[x][y] * 50) / qualite;
            table.chrominance[x][y] = (chrominance[x][y] * 50) / qualite;
        }
    }*/


    /** Application de la quantification **/
    // On balaye toute l'image par blocs de 8*8
    /*for(x=0; x< img->get_height(); x+=8) {
        for(y=0; y< img->get_width(); y+=8) {

            // Dans chaque bloc de 8*8 on balaye tous les pixels
            for(i=0; i<8; i++) {
                for(j=0; j<8; j++) {
                    // On divise chaque valeur par la valeur correspondante de la matrice de quantification
                    img->get_r_matrix()[x+i][y+j] /= table.luminance[i][j];
                    img->tab2[x+i][y+j] /= table.chrominance[i][j];
                    img->tab3[x+i][y+j] /= table.chrominance[i][j];
                }
            }
        }
    }

    printf("Quantification...\n");
    return table;
}*/

/*************************************************
* Titre    : irle.c                              *
* Auteur   : LE SAUCE Julien / MESGUEN Laurent   *
* Groupe   : ISEN                                *
* Créé     : 30.04.12                            *
* Modifié  : 30.04.12                            *
*************************************************/

/** Fonction ********************************************************************************************
*                                                                                                       *
* Prototype : ImageVector* irle (ImageRle* imgRle);                                                     *
*                                                                                                       *
* Description :     - Cette fonction a pour but de transformer une structure ImageRle en                *
*                     structure ImageVector. C'est le principe inverse de la fonction rle implémentée   *
*                     dans le fichier rle.c                                                             *
*                                                                                                       *
* Paramètre E/S :                                                                                       *
*       - Entrée :  - Pointeur de structure de type ImageRle                                            *
*                                                                                                       *
*       - Sortie :  - Pointeur de structure de type ImageVector                                         *
*                     Il y a nbBlocs vecteurs pour chaque composante (YUV)                              *
*                                                                                                       *
********************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "irle.h"

ImageVector* irle (ImageRle* imgRle) {

    int i, j, k;

    /** Allocation mémoire ****************************/

    ImageVector *imgV = new_ImageVector(imgRle->hauteur, imgRle->largeur);

    /**************************************************/

    /** Passage de ImageRle à ImageVector *************/

    Rle* temp = nullptr;

    for(i=0; i<imgRle->nbBlocs; i++){
        // Luminance
        j=0;
        temp = imgRle->luminance_l[i]->pPremier;
        while(temp != nullptr){
            // Si c'est une valeur DC
            if(temp->nbZero == V_DC){
                // On écrit simplement la valeur
                imgV->luminance[i][j] = temp->valeur;
                j++;
            }
            // Si c'est une valeur AC et qu'on tombe sur EOB (0,0)
            else if(temp->nbZero == 0 && temp->nbBit == 0){
                // On écrit tous les zéros jusqu'à la fin du vecteur
                for(k=j; k<64; k++){
                    imgV->luminance[i][j] = 0;
                    j++;
                }
            }
            // Sinon
            else{
                // On écrit tous les zéros
                for(k=0; k<temp->nbZero; k++){
                    imgV->luminance[i][j] = 0;
                    j++;
                }
                // Puis la valeur
                imgV->luminance[i][j] = temp->valeur;
                j++;
            }
            temp = temp->pSuivant;
        }

        // Chrominance1
        j=0;
        temp = imgRle->chrominance1_l[i]->pPremier;
        while(temp != nullptr){
            // Si c'est une valeur DC
            if(temp->nbZero == V_DC){
                // On écrit simplement la valeur
                imgV->chrominance1[i][j] = temp->valeur;
                j++;
            }
            // Si c'est une valeur AC et qu'on tombe sur EOB (0,0)
            else if(temp->nbZero == 0 && temp->nbBit == 0){
                // On écrit tous les zéros jusqu'à la fin du vecteur
                for(k=j; k<64; k++){
                    imgV->chrominance1[i][j] = 0;
                    j++;
                }
            }
            // Sinon
            else{
                // On écrit tous les zéros
                for(k=0; k<temp->nbZero; k++){
                    imgV->chrominance1[i][j] = 0;
                    j++;
                }
                // Puis la valeur
                imgV->chrominance1[i][j] = temp->valeur;
                j++;
            }
            temp = temp->pSuivant;
        }

        // Chrominance2
        j=0;
        temp = imgRle->chrominance2_l[i]->pPremier;
        while(temp != nullptr){
            // Si c'est une valeur DC
            if(temp->nbZero == V_DC){
                // On écrit simplement la valeur
                imgV->chrominance2[i][j] = temp->valeur;
                j++;
            }
            // Si c'est une valeur AC et qu'on tombe sur EOB (0,0)
            else if(temp->nbZero == 0 && temp->nbBit == 0){
                // On écrit tous les zéros jusqu'à la fin du vecteur
                for(k=j; k<64; k++){
                    imgV->chrominance2[i][j] = 0;
                    j++;
                }
            }
            // Sinon
            else{
                // On écrit tous les zéros
                for(k=0; k<temp->nbZero; k++){
                    imgV->chrominance2[i][j] = 0;
                    j++;
                }
                // Puis la valeur
                imgV->chrominance2[i][j] = temp->valeur;
                j++;
            }
            temp = temp->pSuivant;
        }
    }

    /**************************************************/

    /** Désallocation mémoire ************************/

    free_ImageRle(imgRle);

    /*************************************************/
    printf("IRle...\n");
    return imgV;
}

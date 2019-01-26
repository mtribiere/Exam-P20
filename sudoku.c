#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int estValideH(sudoku s,int x,int y,unsigned char n){
  int toReturn = 1;

  //Pour toutes les cases sur la ligne
  for(int j = 0;j<9;j++){
    //Si le même chiffre est detecté
    if(s[x][j] == n)
      toReturn = 0;
  }

  return toReturn;
}

int estValideV(sudoku s,int x,int y,unsigned char n){
  int toReturn = 1;

  //Pour toutes les cases sur la colonne
  for(int i = 0;i<9;i++){
    //Si le même chiffre est detecté
    if(s[i][y] == n)
      toReturn = 0;
  }

  return toReturn;
}


int estValideR(sudoku s,int x,int y,unsigned char n){
  int toReturn = 1;

  //Definir la position du haut gauche de la région
  int regionX = (x/3)*3;
  int regionY = (y/3)*3;


  //Parcourir le neufs cases de la region
  for(int i = 0;i<3;i++){
    for(int j = 0;j<3;j++){
      //Si le même chiffre est detecté
      if(s[regionX+i][regionY+j] == n){
        toReturn = 0;
      }
    }
  }

  return toReturn;
}


int estValide(sudoku s,int x,int y,unsigned char n){
  int toReturn = 0;

  //Verifier que le case soit vide
  if(s[x][y] != 0)
    toReturn = -1;

  //Si la case est vide est qu'elle respecte les 3 tests
  if(toReturn != -1 && estValideH(s,x,y,n) && estValideV(s,x,y,n) && estValideR(s,x,y,n))
    toReturn = 1;

  return toReturn;
}

int trouveMin(sudoku s,int *x,int *y,unsigned char *nb){
  int toReturn = 0;

  //Verifier si la grille est pleine
  if(grillePleine(s) == 0)
    toReturn = 1;

  //Si la grille n'est pas pleine
  if(toReturn != 1){
    int min = 10;

    //Pour toutes les cases
    for(int i = 0;i<9;i++){
      for(int j = 0;j<9;j++){

        //Si la case est vide
        if(s[i][j] == 0){
          //Si on trouve un nouveau minimal
          if(nombrePossibilite(s,i,j) < min){
            //Remplacer ses coordonées
            *x = i;
            *y = j;

            //Definir le nouveau min
            min = nombrePossibilite(s,i,j);

            //Remplacer le nb
            *nb = min;
          }
        }
      }
    }
  }

  return toReturn;
}

int grillePleine(sudoku s){
  int toReturn = 0;

  //Parcourir la grille à la recherche d'un emplacement vide
  for(int x = 0;x<9;x++){
    for(int y = 0;y<9;y++){
      //Si on trouve une case vide
      if(s[x][y] == 0)
        toReturn = 1;
    }
  }

  return toReturn;
}


int nombrePossibilite(sudoku s,int x,int y){
  int total = 0;

  //Pour tout les chiffres possibles sur cette case
  for(int i = 1;i<=9;i++){
    //Si on a un emplacement valide
    if(estValide(s,x,y,i) == 1)
      total++;
  }

  return total;
}


sudoku *chargeSudoku(char *path){
  sudoku *loaded = malloc(sizeof(sudoku));

  if(loaded != NULL){
      //Charger le fichier
      FILE *fp;
      fp = fopen(path,"r");

      //Si le fichier est bien chargé
      if(fp != NULL){
        char currentChar;
        int x = 0;
        int y = 0;
        //Parcourir le fichier
        while((currentChar = fgetc(fp)) != EOF){

          //Changement de ligne
          if(currentChar == '\n'){
            y = 0;
            x++;
          }else{//Sinon charger la valeur
            (*loaded)[x][y] = currentChar;
            y++;
          }
        }

      }else{
        free(loaded);
        loaded = NULL;
      }
  }


  return loaded;
}

int gagneSudoku(sudoku s){
  int toReturn = 0;

  //Trouver la case avec le moins de possiblitées
  int x,y;
  unsigned char nb;
  if(trouveMin(s,&x,&y,&nb) == 0){
    //Si la grille n'est pas pleine, verifier toutes les possiblitées de cette case
    for(int i = 1;i<=9;i++){

      //Si on peut le placer à cet emplacement
      if(estValide(s,x,y,i) == 1){

        //printf("%d;%d\n",x,y);
        //Mettre la valeur
        s[x][y] = i;

        //Passer à la case suivante
        if(gagneSudoku(s) == 1)
          toReturn = 1;
        else //Liberer la valeur
        s[x][y] = 0;
      }

    }
  }else{
    toReturn = 1;
  }

  return toReturn;
}

/*DEBUG*/
void afficheSudoku(sudoku s){
  for(int x = 0;x<9;x++){
    printf("|");
    for(int y = 0;y<9;y++){
      printf("%d|",s[x][y]);
    }
    printf("\n");
  }
}

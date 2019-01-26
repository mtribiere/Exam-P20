#ifndef SUDOKU
#define SUDOKU
typedef unsigned char sudoku[9][9];

int estValideH(sudoku s,int x,int y,unsigned char n);
int estValideV(sudoku s,int x,int y,unsigned char n);
int estValideR(sudoku s,int x,int y,unsigned char n);
int estValide(sudoku s,int x,int y,unsigned char n);
int trouveMin(sudoku s,int *x,int *y,unsigned char *nb);
int gagneSudoku(sudoku s);

int grillePleine(sudoku s);
int nombrePossibilite(sudoku s,int x,int y);

int gagneSudokuBonus(sudoku *s);
void afficheSudoku(sudoku s);

#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// *** AFFICHAGE DU PLATEAU *** 

void displayBoard(char board[3][3][3][3]) {
    // Affiche l'état du jeu.
    // board : état du plateau de jeu
    
    printf("┌-------┬-------┬-------┐\n");
    for (int br = 0; br < 3; br++) {
        for (int sr = 0; sr < 3; sr++) {
            for (int bc = 0; bc < 3; bc++) {
                printf("| ");
                for (int sc = 0; sc < 3; sc++) {
                    char c = board[br][bc][sr][sc];
                    printf("%c ", c ? c : '.');
                }
            }
            printf("|\n");
        }
        if (br < 2)
            printf("├-------┼-------┼-------┤\n");
        else
            printf("└-------┴-------┴-------┘\n");
    }
}



// *** VERIFICATION DU GAGNANT ***

// ** Vérification du gagnant dans un petit plateau **

char checkSmallWinner(char board[3][3][3][3], int br, int bc) {
    // Renvoie 'X' ou 'O' selon le gagnant du petit plateau considéré 
    // board : état du plateau de jeu
    // br : rangée du petit plateau considéré
    // bc : colonne du petit plateau considéré
    
    char (*b)[3] = board[br][bc];

    for (int i = 0; i < 3; i++) {
        if (b[i][0] && b[i][0] == b[i][1] && b[i][1] == b[i][2]) return b[i][0];
        if (b[0][i] && b[0][i] == b[1][i] && b[1][i] == b[2][i]) return b[0][i];
    }

    if (b[0][0] && b[0][0] == b[1][1] && b[1][1] == b[2][2]) return b[0][0];
    if (b[0][2] && b[0][2] == b[1][1] && b[1][1] == b[2][0]) return b[0][2];

    return 0;
}

// ** Vérfication : le petit plateau est-il plein ? **
int isSmallFull(char board[3][3][3][3], int br, int bc) {
    // Renvoie 1 si le petit plateau considéré est plein, sinon renvoie 0
    // board : état du plateau de jeu
    // br : rangée du petit plateau considéré
    // bc : colonne du petit plateau considéré
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[br][bc][i][j] == 0)
                return 0;
    return 1;
}

// ** Vérification du gagnant du jeu **
char checkGlobalWinner(char board[3][3][3][3]) {
    // Renvoie 'X' ou 'O' selon le gagnant du jeu 
    // board : état du plateau de jeu
    
    char big[3][3] = {0};

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            big[i][j] = checkSmallWinner(board, i, j);

    for (int i = 0; i < 3; i++) {
        if (big[i][0] && big[i][0] == big[i][1] && big[i][1] == big[i][2]) return big[i][0];
        if (big[0][i] && big[0][i] == big[1][i] && big[1][i] == big[2][i]) return big[0][i];
    }

    if (big[0][0] && big[0][0] == big[1][1] && big[1][1] == big[2][2]) return big[0][0];
    if (big[0][2] && big[0][2] == big[1][1] && big[1][1] == big[2][0]) return big[0][2];

    return 0;
}


// *** DEFINITION DES STRATEGIES ***

// ** Stratégie de l'utilisateur **
void playHuman(char board[3][3][3][3], int *br, int *bc, char player) {
    // L'utilisateur joue
    // board : état du jeu
    // br : indice de la rangée du petit plateau dans lequel il faut jouer
    // bc : indice de la colonne du petit plateau dans lequel il faut jouer
    // player : 'X' ou 'O' selon qui joue

    int inputBR, inputBC, sr, sc;
    int inputB, inputS;

    if (*br == -1)
        printf("Le joueur %c joue où il veut\n", player);
    else
        printf("Le joueur %c doit jouer dans le plateau (%d,%d)\n",
               player, *br, *bc);

    printf("Entrer: big_r big_c small_r small_c (1-3): ");
    scanf("%d %d %d %d", &inputBR, &inputBC, &sr, &sc);

    board[inputBR-1][inputBC-1][sr-1][sc-1] = player;

    if (checkSmallWinner(board, sr, sc) || isSmallFull(board, sr, sc)) {
        *br = -1;
    } else {
        *br = sr;
        *bc = sc;
    }
}


// **** MAIN ****


int main() {

    int br = -1, bc = -1;
    char player = 'X'; // joueur qui débute
    char board[3][3][3][3] = {{{{0}}}};
    int moveCount = 0;
        
    while (1) {
        displayBoard(board);
    
        if (moveCount == 81) {
            printf("Draw");
            break;
        }
    
        if (player == 'X') {
            playHuman(board, &br, &bc, player);
        }
        else {
            playHuman(board, &br, &bc, player);
        }
    
        char winner = checkGlobalWinner(board);
            
        if (winner) {
            if (winner == 'X') {
                printf("X wins");
            } else {
                printf("O wins");
            }
            break;
        }
    
        player = (player == 'X') ? 'O' : 'X';
    }
return 0;
}

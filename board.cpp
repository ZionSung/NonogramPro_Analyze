#include "board.h"

#include <cstdlib>
#include <cstring>
#include <cstdio>

Board::Board()
{
    for( int i = 0; i < Len; i++ ){
        for( int j = 0; j < Len; j++ ){
            orgBoard[i][j] = 2;
        }
    }
}

void Board::getLine( int* line, int num ){

    if( num < Len ){ // col
        for( int i = 0; i < Len; i++ ){
            line[i] = orgBoard[i][num];
        }
    }
    else{ // row
        memcpy( line, orgBoard[num-Len], Len<<2 );
    }
}

void Board::recover( int* line, int num ){
    
    if( num < Len ){ // col
        for( int i = 0; i < Len; i++ ){
            if( orgBoard[i][num] != line[i] ){
                orgBoard[i][num] = line[i];
                //newPaint = 1;
            }
        }
    }
    else{ // row
        for( int i = 0; i < Len; i++ ){
            if( orgBoard[num - Len ][i] != line[i] ){
                orgBoard[num - Len ][i] = line[i];
                //printf( " !!  %d, %d\n", num, Len );
                //newPaint = 1;
            }
        }
    }
}

void Board::printLine( int* line ){
    for( int i = 0; i < Len; i++ ){
        if( line[i] == 0 ){
                printf("0 ");
            }
            else if( line[i] == 1 ){
                printf("1 ");
            }
            else{
                printf("x ");
            }
    }
    printf("\n");
}

void Board::printBoard( Board& board ){
    
    printf("\n\n========================================\n\n");

    // print margin
    printf("    ");
    for( int m = 1; m < Len+1; m++ ){
        printf("%2d", m );
    }
    printf("\n\n");

    for( int i = 0; i < Len; i++ ){
        printf("%2d   ", i+1 );
        for( int j = 0; j < Len; j++ ){
            if( board.orgBoard[i][j] == 0 ){
                printf("0 ");
            }
            else if( board.orgBoard[i][j] == 1 ){
                printf("1 ");
            }
            else{
                printf("x ");
            }
        }
        printf("\n");
    }
    printf("\n========================================\n\n");
}

int Board::CompareBoard( Board& oldBoard, Board& newBoard ){

    int hasNew = 0;
    
    for( int i = 0; i < Len; i++ ){
        for( int j = 0; j < Len; j++ ){
            if( oldBoard.orgBoard[i][j] == 2  &&  newBoard.orgBoard[i][j] == 1 ){
                hasNew++;
                printf("[%d][%d] has new 1\n", j+1, i+1 );
            }
            else if( oldBoard.orgBoard[i][j] == 2  &&  newBoard.orgBoard[i][j] == 0 ){
                hasNew++;
                printf("[%d][%d] has new 0\n", j+1, i+1 );
            }
            else if(oldBoard.orgBoard[i][j] !=  newBoard.orgBoard[i][j]){
                hasNew++;
                printf("[%d][%d] is different => %d -> %d\n", j+1, i+1, oldBoard.orgBoard[i][j],  newBoard.orgBoard[i][j]);
            }
        }
    }
    

    if( hasNew == 0 ){
        printf("\n\nThere is NO new pixel\n");
    }
    else{
        printf(" \n\n%d pixel are different\n", hasNew );   
    }

    return hasNew;

}


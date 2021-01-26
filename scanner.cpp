/*
 question

 1. The size of buff & buff2 

*/

#include "scanner.h"

int inputData[totaNum][probMaxLen];

void readFile(){
    //int inputData[totaNum][maxClue*probLen];
    FILE *ptr = fopen( INPUT_FILE_NAME, "r");
    
    // check
    if( ptr == NULL ){
        perror("Error opening file");
        exit(-1);
    }
    
    
    for( int probNum = 0; probNum < totaNum; probNum++ ){
        
        // through the Num of Problem
        char buff[10] = {};
        fgets( buff, 100, ptr );
        //printf("%s\n", buff);

        // read each problem
        for( int i = 0; i < probLen; i++ ){

            int n = 0, count = 1;
            char c = 0;
            
            char buff2[100] = {};
            char* g = fgets( buff2, 200, ptr );
            //printf("%s\n", buff2);
            int offset = 0;
            while ( sscanf ( g , " %d%c%n" , &n , &c , &offset ) )
            {
                if(offset == 0)
                    g += 1;
                else
                    g += offset;
                
                //printf("i = %d, maxClue = %d, count = %d\n", i, maxClue, count );
                //printf("[%d][%d] = %d\n", probNum, i * maxClue + count, n );
                inputData[probNum][ i * maxClue + count ] = n;
                if ( c == 10 || c == 13 )
                {
                    inputData[probNum][i * maxClue] = count;
                    //printf("inputData[%d][%d] = %d !!\n", probNum, i * maxClue, inputData[probNum][i * maxClue]);
                    break;
                }
                count++;
            }
            //printf("edgeClue = %d\n", inputData[0][38*maxClue + 1]);
        }
    }
    
    fclose(ptr);
}

void getData( int* dest, int num ){


    memcpy( dest, inputData[num], probMaxLen<<2);


    /*
    printf("!!!!!!!!!!!!!!!!!!!!!!\n");
    for( int i = 0; i < probMaxLen; i++ ){
        printf(" %d -- \n", i );
        printf("1, %d\n", inputData[num][i]);
        
        printf("2, %d\n", dest[i]);
    }
    printf("!!!!!!!!!!!!!!!!!!!!!!\n");
    */
}
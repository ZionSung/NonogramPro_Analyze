// 10/18 0429
// new pixel for propagate;

#include "fixPaint.h"

int dp[26][14];
int d[Len/2+1];
// 25 x 25
//char S[Len+1] = {'u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u'};
// 10 x 10
char S[Len+1] = {'u','u','u','u','u','u','u','u','u','u','u'};
// 5 x 5
//char S[Len+1] = {'u','u','u','u','u','u'};
int f1[Len+1];
int f0[Len+1];
int low[Len+1];
int line[Len];
int new_pixel[probLen]{};
int hasNewPaint = 0;

Board FixPaint::lineSolving( int *data, Board b ){

    for( int num = 0; num < probLen; num++ ){
        /*
        if( num == 37 ){
            printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        }
        */
        //printf("num => %d\n", num );
        b.getLine(line, num);
        lineToS(line);
        //printLine();
        //b.printLine(line);

        int dataShift = num*maxClue;
        //printf("datashift = %d\n", dataShift );
        int j = data[dataShift];
        //printf("j = %d\n", j );
        int i = Len;
        init_dp();
        init_var( d, Len/2+1);
        init_var( f1, Len+1 );
        init_var( f0, Len+1 );
        init_var( low, Len+1 );
        //printf("i = %d\n", i );
        int f = get_f( data, num );
        //printf("f = %d\n", f );
        //printf("=====================\n");
        P(i, f, j);
        
        /*
        printf("=====================\n");
        printf("d[1] = %d\n", d[1] );
        printf("\n");
        printf("fix1 --> ");
        printInt(f1,Len+1);
        printf("fix0 --> ");
        printInt(f0,Len+1);
        printf("low --> ");
        printInt(low,Len+1);
        printf("\n");
        */
        
        insert(line, num );
        //b.printLine(line);
        b.recover(line, num);
        init_S();
    }

    while( hasNewPaint == 1 ){
        //printf("HasNewPixel!\n");
        hasNewPaint = 0;

        for( int num = 0; num < probLen; num++ ){
            
            //printf("new_pixel[%d] = %d\n",num, new_pixel[num]);
            if( new_pixel[num] == 1 ){
                //printf("New Pixel => num = %d\n", num );
                b.getLine(line, num);
                lineToS(line);
                //printLine();
                //b.printLine(line);

                int dataShift = num*maxClue;
                //printf("datashift = %d\n", dataShift );
                int j = data[dataShift];
                //printf("j = %d\n", j );
                int i = Len;
                init_dp();
                init_var( d, Len/2+1);
                init_var( f1, Len+1 );
                init_var( f0, Len+1 );
                init_var( low, Len+1 );
                //printf("i = %d\n", i );
                int f = get_f( data, num );
                //printf("f = %d\n", f );
                //printf("=====================\n");
                P(i, f, j);
        
                insert(line, num );
                //b.printLine(line);
                b.recover(line, num);
                init_S();
            }
        }
        init_var( new_pixel, probLen );        
    }


    b.printBoard(b);

    

    return b;

}

void FixPaint::lineToS( int *data ){
    // mirror
    // line 0 1 2 3 4 
    // S    5 4 3 2 1

    for( int i = 0; i < Len; i++ ){
        if( line[i] == 0 ){
            S[i+1] = '0';
        }
        else if( line[i] == 1 ){
            S[i+1] = '1';
            //printLine();
        }
    }
}

void FixPaint::printInt( int* array, int l ){
    for( int i = 1; i < l; i++ ){
        printf("%d ", array[i]);
    }
    printf("\n");
}

void FixPaint::printLine(){
    for( int i = 1; i < Len+1; i++ ){
        printf("%2d ", i );
    }
    printf("\n");
    for( int i = 1; i < Len+1; i++ ){
        printf("%2c ", S[i]);
    }
    printf("\n");
}

int FixPaint::get_f( int *data, int num ){

    int dataShift = num*maxClue;
        int j = data[dataShift];
        int totaClue = 0;
        for( int i = 0; i < j; i++ ){
            d[i+1] = data[dataShift+i+1];
            //printf("d[%d] = %d\n", i, d[i] );
            totaClue += data[dataShift+i+1]; // because the fisrt one is j
        }
        totaClue = totaClue + j - 1;
    return Len - totaClue;
}

void FixPaint::init_var( int* array, int s ){
    for( int counter = 0; counter < s; counter++ ){
        array[counter] = 0;
    }
}

void FixPaint::init_S(){
    for( int i = 0; i < Len+1; i++ ){
        S[i] = 'X';
    }
}

bool FixPaint::P( int i, int f, int j ){
    //printf("------ %d,%d\n", i, j );
    //level++;

    // dp
    if(dp[i][j] == 1){
        return true;
    }
    else if(dp[i][j] == 0){
        return false;
    }

    if( i == 0 && j == 0 ){
        dp[i][j] = 1;
        return true;
    }
    else if(j == 0){
        if(check_remaining_one(i)){
            //printf("TWO P0 true P1 false ");
            f0[i] = true; // paint1 is false paint0 is true
            //printf("%d,%d\n", i, j );
            dp[i][j] = 1;
            return true;
        }
        else{
            dp[i][j] = 0;
            return false;
        }
    }
    else if( i == 0 && j >= 1 ){ // maybe it won't happen, so we put it to the last
        //printf("ONE both false !!!!!");
        //printf("%d,%d\n", i, j );
        dp[i][j] = 0;
        return false;
    }
    bool tempP0,tempP1;
    // paint1
    if( j > 1 && check(i, j)){
        //printf("d[j] = %d, j = %d\n", d[j], j  );
        tempP1 = P( i - d[j] - 1, f, j - 1 );
    }
    else if( j == 1 && check(i, j)){
        tempP1 = P( i - d[j], f, j - 1 );
    }
    else{
        tempP1 = false;
    }

    // paint0
    if( S[i] != '1' && f > 0){
        tempP0 = P( i - 1, f - 1, j);
    }
    else{
        tempP0 = false;
    }


    if(tempP1 == true && tempP0 == false){
        //printf("Paint One (%d, %d)  ", i, j);

        //printf("FOUR P1 true P0 false ");
        f1[i] = true;
        
        low[i] = i - d[j] + 1;
        //printf("i = %d, low[i] = %d\n", i, i - d[j] +1 );
        if(j > 1){
            f0[i-d[j]] = 1; // remember paint i - d[j] to 0
        }

        // if j == 0, and paint1 is true.
        // then remaining cells may paint 0
        
        if( j == 1 ){
            //printf("hello!!! low[i] = %d\n", low[i]);
            for( int count = 0; count < low[i]; count++ ){
                f0[count] = 1;
            }
        }
        
        //printf("%d,%d\n", i, j );
        dp[i][j] = 1;

        for( int i = 1; i < Len+1; i++ ){
            if( f1[i]==true && low[i]!=0 ){
                for(int j = low[i]; j <= i; j++ ){
                    f1[j] = 1;
                }
            }
        }
        /*
        printf("fix1 --> ");
        printInt(f1,Len+1);
        printf("fix0 --> ");
        printInt(f0,Len+1);
        */
        return true;
    }
    else if(tempP1==true&&tempP0==true){
        //printf("Both Paint (%d, %d)  ", i, j);
        //printf("i = %d, low[i] = %d\n", i, i - d[j] +1 );
        
        //printf("SIX both true ");
        f1[i] = true;
        if(j > 1){
            f0[i-d[j]] = 1; // remember paint i - d[j] to 0
        }

        if( j == 1 ){
            //printf("hello!!! low[i] = %d\n", low[i]);
            for( int count = 0; count < low[i]; count++ ){
                f0[count] = 1;
            }
        }

        low[i] = i - d[j] + 1;
        f0[i] = true;
        //printf("%d,%d\n", i, j );
        dp[i][j] = 1;
        for( int i = 1; i < Len+1; i++ ){
            if( f1[i]==true && low[i]!=0 ){
                for(int j = low[i]; j <= i; j++ ){
                    f1[j] = 1;
                }
            }
        }
        /*
        printf("fix1 --> ");
        printInt(f1,Len+1);
        printf("fix0 --> ");
        printInt(f0,Len+1);
        */
        return true;
    }
    else if( tempP0 == true && tempP1 == false ){
        //printf("Paint Zero (%d, %d)  ", i, j);
        //printf("i = %d\n", i );
        //printf("FIFE P0 true P1 false ");
        f0[i] = true;
        //printf("%d,%d\n", i, j );
        dp[i][j] = 1;
        /*
        printf("fix1 --> ");
        printInt(f1,Len+1);
        printf("fix0 --> ");
        printInt(f0,Len+1);
        */
        return true;
    }
    else{
        //printf("THREE both false ");
        //printf("%d,%d\n", i, j );
        dp[i][j] = 0;
    }
    //printf("!!!!\n");  
    return false;
}

bool FixPaint::check( int i, int j ){
    for( int count = i - d[j] + 1; count <= i; count++ ){
        if( S[count] == '0'){
            return false;
        }
    }
    if(S[i-d[j]] == '1'){
    	return false;
    }
    
    return true;
}

bool FixPaint::check_remaining_one( int i ){
    for( int count = 0; count < i; count++ ){
        if( S[count] == '1'){
            return false;
        }
    }
    return true;
}

void FixPaint::init_dp(){
    for( int x = 0; x <= 25; x++ ){
        for( int y = 0; y <= 13; y++ ){
            dp[x][y] = 2;
        }
    }
}

void FixPaint::insert( int* line, int num ){

    /*
    
    printf("\nFinal ->\nfix1 --> ");
    printInt(f1,Len+1);
    printf("fix0 --> ");
    printInt(f0,Len+1);

    */
    
    

    for( int i = 1; i < Len+1; i++ ){
        //printf("new_pixel => ");
        if(f1[i] == true && f0[i] == false){
            if( line[i-1] == 1){
                //printf("It's already One\n");
            }
            else
            {
                line[i-1] = 1;
                //printf("new pixel 1 at [%d][%d]\n", i-1, num );
                // 0 1 2 3 4 
                // 5 6 7 8 9
                new_pixel[i-1] = 1;
                new_pixel[i+Len-1] = 1;
                hasNewPaint = 1;
            }
            
        }
        else if(f0[i] == true && f1[i] == false){
            if( line[i-1] == 0){
                //printf("It's already Zero\n");
            }
            else{
                line[i-1] = 0;
                //printf("new pixel 0\n");
                new_pixel[i-1] = 1;
                new_pixel[i+Len-1] = 1;
                hasNewPaint = 1;
            }
        }
    }
    /*
    printf("\nnew_pixel array => ");
    for( int i = 0; i < probLen; i++ ){
        printf("%d ", new_pixel[i]);
    }
    printf("\n");
    */
    
}
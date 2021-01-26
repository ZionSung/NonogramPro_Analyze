#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <stdlib.h>

#include "scanner.h"
#include "cdef.h"
#include "board.h"
#include "commander.h"

using namespace std;

int main(int argc , char *argv[])
{

    // read whole file
    int probData[probMaxLen] {}; // current problem data
    readFile();



    // start solving
    for( int probNum = 0; probNum < totaNum; probNum++ ){

        // get curent problem data
        /*
            j => probData[0] -> 0, 14, 28... j 
            i => probData[1] -> 1, 2, 3... 14*j + i ( 14 == maxClue )
        */

        getData( probData, probNum );
        
        // start 
        Commander command;
        command.Start( probData );

    }

    
    
    return 0;
}


#ifndef LOGICSOLVER_H
#define LOGICSOLVER_H

#include <cstdio>
#include <cstring>
#include "board.h"

class LogicSolver
{
    public:
        LogicSolver() {}
        Board RLmost( int* , Board );
        Board Sub1( int*, Board );
        Board Sub2( int*, Board );
        Board Sub3( int*, Board );
        Board Sub4( int*, Board );
        Board Sub5( int*, Board );
};

#endif 
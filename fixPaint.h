#ifndef FIXPAINT_H
#define FIXPAINT_H

#include <cstdio>
#include <cstring>
#include "board.h"

class FixPaint
{
    public:
        FixPaint(){}
        Board lineSolving( int*, Board );
        void printLine();
        int get_f( int*, int );
        void init_var( int*, int );
        void init_S();
        bool P( int, int, int );
        bool check( int, int );
        bool check_remaining_one( int );
        void init_dp();
        void insert( int*, int );
        void printInt( int*, int );
        void lineToS( int* );

};

#endif
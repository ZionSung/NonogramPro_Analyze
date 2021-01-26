#include "logicSolver.h"
#include<stdlib.h>
int shift = 0;

int finish[probLen]{};

Board LogicSolver::RLmost( int *data, Board b ){

    // run each line
    for( int num = 0; num < probLen; num++ ){

        // get line
        int line[Len];
        b.getLine(line, num);

        // main
        int dataShift = num*maxClue;
        int j = data[dataShift];

        // analyze
        /*
        printf("clue -> ");
        for( int i = 0; i < j; i++ ){
            printf("%d ", data[dataShift+i+1]);
        }
        printf("\n");
        printf("1 -> ");
        b.printLine(line);
        */
        int totaClue = 0;
        for( int i = 0; i < j; i++ ){
            totaClue += data[dataShift+i+1]; // because the fisrt one is j
        }
        totaClue = totaClue + j - 1;
        shift = Len - totaClue;
        int point = shift;
        for( int i = 0; i < j; i++ ){
            if( shift < data[dataShift+i+1] ){
                int paint = data[dataShift+i+1] - shift; // how many spaces we shall paint
                for( int p = 0; p < paint; p++ ){
                    line[p + point] = 1;
                }
            }
            point += data[dataShift+i+1];
            point++;
        }
        b.recover(line,num);
        /*
        printf("2 -> ");
        b.printLine(line);
        b.printBoard(b);
        */
    }
    //b.printBoard(b);
    return b;
}

// find "0"( has painted ) as a limit to probe new dot.
Board LogicSolver::Sub1( int *data, Board b ){
    for ( int num = 0; num < probLen; num++ ){
        printf("Num: %d\n", num );
        int line[Len];
        b.getLine( line, num );
        int dataShift = num*maxClue;
        int j = data[dataShift];

        // analyze
        
        printf("clue -> ");
        for( int i = 0; i < j; i++ ){
            printf("%d ", data[dataShift+i+1]);
        }
        printf("\n");
        printf("1 -> ");
        b.printLine(line);
        

        // ##################################
        //           Start Sub1 
        // ##################################


        // find the len of limited segment
        //              1 2 3 4 5 6 7 8 9 10
        // 2 3            0 0
        // Left  Most     0 0 x x   x x x    
        // Right Most     0 0   x x   x x x
        // Ans          0 0 0   1     1 1   
        //
        // Condition
        // 1. there is only one segment > tatol j
        // -> so we need to find the lowest j then find weather there is any segment > "it"

        // get lowest j & total_j
        int lowest_j = Len;
        for( int i = 0; i < j; i++ ){
            if( data[dataShift+i+1] < lowest_j ){
                lowest_j = data[dataShift+i+1];
            }
        }
        printf("lowest j = %d\n", lowest_j );
 

        // find segment
        int find_next_zero = 0;
        int segment_len = 0;
        int seg_count = 0; // if seg_count > 1 it can't do this rule
        int seg_head = 0;
        int seg_tail = 0;
        int used_seg = 0;
        int skip_sub1 = 0;

        for( int i = 0; i < Len; i++ ){

            // maybe we should add skip one machanism here
            if( line[i] == 0 ){

                segment_len = i - find_next_zero;
                printf("segment = %d\n", segment_len );
                if( segment_len == Len ){
                    printf("<<SKIP SUB1>> => segment == Len, it is equal to RLmost\n");
                    skip_sub1 = 1;
                    break;
                }
                else if( segment_len >= lowest_j ){
                    seg_head = find_next_zero;
                    seg_tail = i-1;
                    seg_count++;
                    used_seg = segment_len;
                    printf("seg_head = %d, seg_tail = %d\n", seg_head, seg_tail);
                }

                if( seg_count > 1 ){
                    printf("<<SKIP SUB1>> => seg_count > 1\n");
                    skip_sub1 = 1;
                    break;
                }
                find_next_zero = i+1;
            }
            else if( i == Len - 1 ){
                segment_len = i - find_next_zero + 1;
                printf("segment = %d\n", segment_len );
                if( segment_len == Len ){
                    printf("<<SKIP SUB1>> => segment == Len, it is equal to RLmost\n");
                    skip_sub1 = 1;
                    break;
                }
                else if( segment_len >= lowest_j ){
                    seg_head = find_next_zero;
                    seg_tail = i;
                    seg_count++;
                    used_seg = segment_len;
                    printf("seg_head = %d, seg_tail = %d\n", seg_head, seg_tail);
                }

                if( seg_count > 1 ){
                    printf("<<SKIP SUB1>> => seg_count > 1\n");
                    skip_sub1 = 1;
                    break;
                }
            }
        }

        // start RLmost in the segment
        if( skip_sub1 == 0 ){
            int totaClue = 0;
            for( int i = 0; i < j; i++ ){
                totaClue += data[dataShift+i+1]; // because the fisrt one is j
            }
            totaClue = totaClue + j - 1;
            shift = used_seg - totaClue;
            printf("shift = %d\n", shift );
            int point = shift;
            for( int i = 0; i < j; i++ ){
                printf("get in => \n");
                if( shift < data[dataShift+i+1] ){
                    int paint = data[dataShift+i+1] - shift; // how many spaces we shall paint
                    printf("paint = %d\n", paint );
                    for( int p = seg_head; p < seg_head+paint; p++ ){
                        line[p + point] = 1;
                        printf("### p + point = %d ###\n", p + point );
                    }
                }
            
                point += data[dataShift+i+1];
                point++;
            }
        }
        
        // ##################################
        //            End Sub1 
        // ##################################
        b.printLine(line);
        b.recover(line,num);
        b.printBoard(b);
    }
    return b;
}

Board LogicSolver::Sub2( int *data, Board b ){
    for( int num = 0; num < probLen; num++ ){
        printf("Num = %d\n", num );
        int line[Len];
        b.getLine( line, num );

        int dataShift = num*maxClue;
        int j = data[dataShift];
        int hasPainted_seg_len[j+1];
        int hasPainted_seg_place[j+1];
        int segment = 0;
        int cont = 0;

        // init array
        for( int i = 0; i < j+1; i++ ){
            hasPainted_seg_len[i] = 0;
            hasPainted_seg_place[i] = 0;
        }

        
        printf("clue -> ");
        for( int i = 0; i < j; i++ ){
            printf("%d ", data[dataShift+i+1]);
        }
        printf("\n");
        printf("1 -> ");
        b.printLine(line);
        

        // How many segment has painted
        for( int i = 0; i < Len; i++ ){ // org clue [max]
            if(line[i] == 1 && cont == 0){
                segment++;
                hasPainted_seg_len[segment]++;
                hasPainted_seg_place[segment] = i;
                
                cont = 1;
            }
            else if(line[i] != 1){
                cont = 0;
            }
            else{ // line[i] == 1 && cont == 1
                hasPainted_seg_len[segment]++;
            }
        }

        
        printf("segment = %d\n", segment);
        for( int i = 1; i <= segment; i++ ){
            printf("len = %d ", hasPainted_seg_len[i]);
            printf("place = %d\n", hasPainted_seg_place[i]);
        }
        printf("\n");
        

        int this_clue = 0;
        int remaining_blank = 0;
        int may_be_one[Len]{}; // initial may_be_one to "0"

        int may_be_one_flag = 0;

        if( segment == j ){
            for( int i = 1; i <= j; i++ ){

                this_clue = data[dataShift+i];
                printf("this_clue = %d\n", this_clue );
                
                // check whether over ( touch other clue )
                if( i != j ){
                    //if( this_clue +  )
                }


                remaining_blank = this_clue - hasPainted_seg_len[i];
                printf("remaining_blank = %d\n", remaining_blank);

                if( remaining_blank == 0 && j == 1){
                    // complement 0
                    printf("because remaining_blank == 0 && j == 1, so we complement \"0\"\n");
                    for( int i = 0; i < Len; i++ ){
                        if( line[i] == 2 ){
                            line[i] = 0;
                        }
                    }
                }
                else{
                    
                    int begin_mayOne = hasPainted_seg_place[i] - remaining_blank;
                    int end_mayOne = hasPainted_seg_place[i] + hasPainted_seg_len[i] + remaining_blank - 1;
                    int current_place = hasPainted_seg_place[i];
                    printf("begin_mayOne = %d, end_mayOne = %d\n", begin_mayOne, end_mayOne );

                    // check whether it will touch each other
                    if( i == 1 ){
                        if( ((end_mayOne >= hasPainted_seg_place[i+1]) && (hasPainted_seg_place[i+1] != 0)) || ((hasPainted_seg_place[i+1] - data[dataShift+i+1] + hasPainted_seg_len[i+1] <=  end_mayOne) && (hasPainted_seg_place[i+1] != 0)) ){
                            printf("hasPainted_seg_place[i+1] = %d\n", hasPainted_seg_place[i+1]);
                            printf("cover another clue X! (1)\n");
                            break;
                        }
                    }
                    else if( i < j ){
                        if( end_mayOne >= hasPainted_seg_place[i+1]){ // right
                            printf("cover another clue X! (2)\n");
                            break;
                        }
                        else if( begin_mayOne <= hasPainted_seg_place[i-1]){ // left
                            printf("cover another clue X! (3)\n");
                            break;
                        }
                    }
                    else{
                        if( begin_mayOne <= hasPainted_seg_place[i-1]){ // left
                            printf("cover another clue X! (4)\n");
                            break;
                        }
                    }


                    // check margin
                    if( begin_mayOne < 0 ){ // begin_mayOne < 0
                        printf("hasPainted_seg_place[i] == 0 \n");

                        for( int count = 0; count < this_clue; count++ ){
                            line[count] = 1;
                            may_be_one[count] = 1;
                        }
                        if( j == 1 ){
                            for( int i = 0; i < Len; i++ ){
                                if( line[i] != 1 ){
                                    line[i] = 0;
                                }
                            }
                        }
                        else{
                            line[this_clue] = 0;
                        }

                        b.printLine(line);
                    }
                    else if( end_mayOne + 1 > Len ){ // end_mayOne - 1 >= Len
                        printf("hasPainted_seg_place[i]+1 == Len\n");
                        for( int count = Len-1; count >= Len - this_clue; count-- ){
                            line[count] = 1;
                            may_be_one[count] = 1;
                        }
                        if( j == 1 ){
                            for( int i = 0; i < Len; i++ ){
                                if( line[i] != 1 ){
                                    line[i] = 0;
                                }
                            }
                        }
                        else{
                            line[Len-this_clue-1] = 0;
                        }
                    }
                    else{
                        printf("***************\nNormal Start\n***************\n");

                        // check margin 
                        printf("check margin => ");
                        printf("begin = %d, end = %d\n", begin_mayOne, end_mayOne );
                        b.printLine(line);

                        //int left_margin = 0;
                        int right_margin = end_mayOne+1;
                        int left_margin = begin_mayOne-1;
                        // check "0" from left to right
                        for( int i = begin_mayOne; i < Len; i++ ){
                            //begin_mayOne = i;
                            if( line[i] == 2 ){
                                int leftPaint = 0;
                                int rightPaint = 0;

                                // clue = 3
                                // 0 1 2 3 4 5 6 7 8 9  
                                // 0 0 0 x x x 1 x 0 0
                                // 
                                // right most?
                                // end_mayOne = 9
                                // but it is too much
                                // so, we need to find postition "0" and calulate
                                // right_margin = 8
                                // then left_paint = right_margin - clue = 8 - 3 = 5

                                // try RLmost 
                                //printf("Try RLmost according to this clue\n");
                                // find right margin
                                for( int j = current_place; j <= end_mayOne; j++ ){ // hasPainted_seg_place[i]
                                    if( line[j] == 0 ){
                                        right_margin = j;
                                        break;
                                    }
                                }
                                leftPaint = right_margin - this_clue;
                                // check left margin
                                for( int j = current_place; j >= begin_mayOne; j-- ){
                                    if( line[j] == 0 ){
                                        left_margin = j;
                                        break;
                                    }
                                }

                                printf("left_margin = %d, right_margin = %d\n", left_margin, right_margin );

                                
                                rightPaint = left_margin + this_clue;
                                leftPaint = right_margin - this_clue;
                                printf("leftPaint = %d, rightPaint = %d\n", leftPaint, rightPaint );

                                // Paint One!
                                for( int i = leftPaint; i <= rightPaint; i++ ){
                                    line[i] = 1;
                                } 

                                break;
                            }
                            else if( line[i] == 1 ){
                                printf("<Sub2 Implement 1 nearby 0 or margin -> Extend!>\n");
                                end_mayOne = i + this_clue - 1;
                                begin_mayOne = i;
                                // paint 1 
                                for( int i = begin_mayOne; i <= end_mayOne; i++ ){
                                    line[i] = 1;
                                }
                                // paint 0
                                if( begin_mayOne != 0 && end_mayOne != Len ){
                                    line[end_mayOne+1] = 0;
                                    line[begin_mayOne-1] = 0;
                                }
                    
                                break;
                            }
                        }
                        /*
                        printf("old begin = %d\n", begin_mayOne );
                        printf("new begin = %d\n", new_begin );

                        printf("old end = %d\n", end_mayOne );
                        printf("new end = %d\n", new_end );
                        */

                        //printf("***************\nNormal End\n***************\n");
                        may_be_one_flag = 1;
                        //printf("begin_mayOne = %d, end_mayOne = %d\n", begin_mayOne, end_mayOne );
                        for( int count = begin_mayOne; count <= end_mayOne; count++ ){
                            may_be_one[count] = 1;
                        } 
                    }
                }
            }

            if( may_be_one_flag == 1 ){
                for( int i = 0; i < Len; i++ ){
                    if( may_be_one[i] == 0 ){
                        line[i] = 0;
                    }
                }
            }

        }
        else{
            printf("No.%d has not match sub2\n", num );
        }
        printf("2 -> ");
        b.printLine(line);
        printf("#############################################\n");
        b.recover(line,num);
        b.printBoard(b);
    } // end for loop
    printf("check3\n");
    b.printBoard(b);
    printf("check4\n");
    return b;
}

Board LogicSolver::Sub3( int *data, Board b ){
    return b;
}

Board LogicSolver::Sub4( int *data, Board b ){
    return b;
}

Board LogicSolver::Sub5( int *data, Board b ){
    return b;
}


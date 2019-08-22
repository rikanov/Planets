#ifndef GLOBAL_HEADER_H
#define GLOBAL_HEADER_H

#include <iostream>      /* for test lines */
#include <sstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <unistd.h>
//#include <Windows.h>

#define log(X) std::cout<<(X)<<' '<<std::flush;
#define log2(X,Y) std::cout<<(X)<<' '<<(Y)<<std::endl;
#define log3(X,Y,Z) std::cout<<(X)<<' '<<(Y)<<' '<<(Z)<<std::endl;

static inline void CLR() { std::cout << "\033[2J\033[1;1H" << std::endl; }
static inline void Sleep(int m) {sleep(m ); }
//static inline void CLR() { system("CLS"); };
typedef unsigned char uchr;

const int MAX_NUMBER_OF_MOVES = 200;
#endif

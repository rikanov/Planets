#include "global.h"
#include "board.h"
#include "generator.h"
//#include <Windows.h>

int main()
{
  Board teszt;
  teszt.reset();
  for (int turn = 0; turn < 2; ++turn)
  {
    Generator T(turn == 0 ? teszt._collectionOfPlayer : teszt._collectionOfProgram);
    Step next;
    T.randomize();
    T.reset();
    while (T.nextRandom(next))
    {
      next.step();
      CLR();
      teszt.show();
      Sleep(1);

      next.back();
     /* CLR();
      teszt.show();
      Sleep(500);*/
    }
  }
  log("finished")
  char c; std::cin >> c;
  return 0;
}

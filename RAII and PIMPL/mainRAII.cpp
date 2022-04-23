
#include <conio.h>

#include "SBomber.h"
#include "MyTools.h"
#include "FileLogger.cpp"

using namespace std;
extern FileLogger logger;
//========================================================================================================================

int main(void){
    logger;

    SBomber game;

    do {
        game.TimeStart();

        if (_kbhit())
        {
            game.ProcessKBHit();
        }

        MyTools::ClrScr();

        game.DrawFrame();
        game.MoveObjects();
        game.CheckObjects();

        game.TimeFinish();

    } while (!game.GetExitFlag());

    

    return 0;
}

#include "basicui.h"

BasicUI::BasicUI()
    :Engine()
{

}

void BasicUI::start()
{
    for ( bool exit = false, refresh = true; !exit; ) {
        if ( refresh ) {
            CLR();
            show();
        } else {
            refresh = true;
        }
        std::cout << std::endl;
        log2 ( "player", isPlayerTurn() ? "X >" : "A >" )
        std::string nextLine;
        getline ( std::cin, nextLine );
        std::stringstream commands ( nextLine );
        char command;
        commands >> command;
        if ( ( command | 32 ) == 'h' ) {
            log2_ ( "help   \t\t\t\t", 'H' )
            log2_ ( "step <planet> <direction> \t", 'S' )
            log2_ ( "set difficulty level  <level> \t", 'L' )
            log2_ ( "start new game   \t\t", 'N' )
            log2_ ( "undo step  \t\t\t", 'U' )
            log2_ ( "redo step    \t\t\t", 'R' )
            log2_ ( "swap players  \t\t\t", 'P' )
            log2_ ( "exit   \t\t\t\t", 'X' )
            refresh = false;
        } else if ( ( command | 32 ) == 's' ) {
            int p, d;
            commands >> p;
            commands >> d;
            makeStep ( p, d );
            if ( isFinished() ) {
                log_ ( "Congrats! You won !!!" )
                char a;
                std::cin >> a;
                reset();
            }
        } else if ( ( command | 32 ) == 'l' ) {
            int l = 7;
            commands >> l;
            setBoundLevel ( l );
        } else if ( ( command | 32 ) == 'n' ) {
            reset();
        } else if ( ( command | 32 ) == 'u' ) {
            undoStep();
        } else if ( ( command | 32 ) == 'r' ) {
            redoStep();
        } else if ( ( command | 32 ) == 'p' ) {
            swapPlayers();
        } else if ( ( command | 32 ) == 'x' ) {
            exit = true;
        } else if ( ( command | 32 ) == 'g' ) {
            swapPlayers();
            Step st = getResult().getStep();
            log_ ( st.whatIs() )
            storeStep ( st );
            CLR();
            show();
            swapPlayers();
            if ( isWinnerStep ( st ) ) {
                log_ ( "AI won !!!" )
                char a;
                std::cin >> a;
                reset();
            }
        }
    }
}

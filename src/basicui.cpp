#include "basicui.h"

BasicUI::BasicUI()
    :Engine()
{

}

void BasicUI::start()
{
    for ( bool exit = false, refresh = true; !exit; )
    {
        if ( refresh )
        {
            CLR();
            show();
        }
        else
        {
            refresh = true;
        }
        std::cout << std::endl;
        log2 ( "player", isPlayerTurn() ? "X >" : "A >" )
        std::string nextLine;
        getline ( std::cin, nextLine );
        std::stringstream commands ( nextLine );
        char command;
        commands >> command;
        if ( ( command | 32 ) == 'h' )
        {
            log2_ ( "help   \t\t\t\t", 'H' )
            log2_ ( "step <planet> <direction> \t", 'S' )
            log2_ ( "set difficulty level  <level> \t", 'L' )
            log2_ ( "start new game   \t\t", 'N' )
            log2_ ( "undo step  \t\t\t", 'U' )
            log2_ ( "redo step    \t\t\t", 'R' )
            log2_ ( "swap players  \t\t\t", 'P' )
            log2_ ( "exit   \t\t\t\t", 'X' )
            log2_ ( "autoplay <level> <level> \t", 'A' )
            refresh = false;
        }
        else if ( ( command | 32 ) == 's' )
        {
            int p, d;
            commands >> p;
            commands >> d;
            makeStep ( p - 1, d );
            if ( isFinished() )
            {
                log_ ( "Congrats! You won !!!" )
                char a;
                std::cin >> a;
                reset();
            }
        }
        else if ( ( command | 32 ) == 'l' )
        {
            int l = 7;
            commands >> l;
            setBoundLevel ( l );
        }
        else if ( ( command | 32 ) == 'n' )
        {
            reset();
        }
        else if ( ( command | 32 ) == 'u' )
        {
            undoStep();
        }
        else if ( ( command | 32 ) == 'r' )
        {
            redoStep();
        }
        else if ( ( command | 32 ) == 'p' )
        {
            swapPlayers();
        }
        else if ( ( command | 32 ) == 'x' )
        {
            exit = true;
        }
        else if ( ( command | 32 ) == 'g' )
        {
            swapPlayers();
            Step st = getResult().getStep();
            log_ ( st.whatIs() )
            storeStep ( st );
            CLR();
            show();
            swapPlayers();
            if ( isWinnerStep ( st ) )
            {
                log_ ( "AI won !!!" )
                char a;
                std::cin >> a;
                reset();
            }
        }
        else if ( ( command | 32 ) == 'a' )
        {
            int l1, l2;
            commands >> l1;
            commands >> l2;
            autoplay ( l1, l2 );
        }
        command = ' ';
        commands.str ( "" );
        std::cout << std::flush;
    }
}
void BasicUI::makeStep ( uint8_t token )
{
    Step st;
    getStep ( token, st );
    storeStep ( st );
}

void BasicUI::makeStep ( uint8_t P, uint8_t D )
{
    Step st;
    getStep ( P, D, st );
    storeStep ( st );
}

void BasicUI::autoplay ( const int& L1, const int& L2 )
{
    CLR();
    show();
    while ( !isFinished() )
    {
        setBoundLevel ( isPlayerTurn() ? L1 : L2 );
        Step st;
        st = getResult().getStep();
        storeStep ( st );
        CLR();
        show();
        swapPlayers();
    }
    log3_ ( "ai levels: ", L1, L2 )
    log3_ ( !isPlayerTurn() ? "Player 1" : "Player 2","win.", stepCount() )
    log_ ( "Again ? (y/n)" )
    char c;
    std::cin >> c;
    reset();
    if ( ( c | 32 ) == 'y' )
    {
        autoplay ( L1, L2 );
    }
}

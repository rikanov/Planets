/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2019  <copyright holder> <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "view2d.h"

static const int STONE_SIZE = 60;
static const int OFFSET_X = 19;
static const int OFFSET_Y = 21;
static const int STEP_X = 88;
static const int STEP_Y = 88;
static const int PLANET_SIZE = 60;

static inline int sgn ( const int& x )
{
    return x == 0 ? 0 : ( x > 0 ? 1 : -1 );
}

bool View2D::SDL_Initialized = false;

View2D::View2D ( const char* name,const int w, const int h, Engine& B )
    :SCR_WIDTH ( w )
    ,SCR_HEIGHT ( h )
    ,_winName ( name )
    ,_engine ( B )
{
    if ( !SDL_Initialized )
    {
        init();
    }
    createWindow();
}

void View2D::init()
{
    if ( SDL_Init ( SDL_INIT_VIDEO ) != 0 )
    {
        std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
        exit ( 1 );
    }
    SDL_Initialized = true;
    clog ( "SDL initialized" )
}

void View2D::createWindow()
{
    _win = SDL_CreateWindow ( _winName,SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_CENTERED,
                              SCR_WIDTH,SCR_HEIGHT,SDL_WINDOW_SHOWN );
    if ( _win == nullptr )
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() <<std::endl;
        exit ( 2 );
    }
    _render = SDL_CreateRenderer ( _win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if ( _render == nullptr )
    {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        exit ( 3 );
    }
    loadTextureImage();
    clog ( "window created" )
}

void View2D::loadTextureImage()
{
    int w,h;
    _boardBackground = IMG_LoadTexture ( _render, "graphics/background.png" );
    if ( _boardBackground == nullptr )
    {
        std::cerr << "IMG_LoadTexture Error: "<< SDL_GetError() << std::endl;
        exit ( 5 );
    }
    _boardTexture  = IMG_LoadTexture ( _render, "graphics/board.png" );
    if ( _boardTexture == nullptr )
    {
        std::cerr << "IMG_LoadTexture Error: "<< SDL_GetError() << std::endl;
        exit ( 5 );
    }
    _stone[0]  = IMG_LoadTexture ( _render, "graphics/stone0.png" );
    if ( _boardTexture == nullptr )
    {
        std::cerr << "IMG_LoadTexture Error: "<< SDL_GetError() << std::endl;
        exit ( 5 );
    }
    _stone[1]  = IMG_LoadTexture ( _render, "graphics/stone1.png" );
    if ( _boardTexture == nullptr )
    {
        std::cerr << "IMG_LoadTexture Error: "<< SDL_GetError() << std::endl;
        exit ( 5 );
    }
    SDL_QueryTexture ( _boardTexture, NULL, NULL, &w, &h );

    _boardPosition.x = ( SCR_WIDTH-w ) / 2;
    _boardPosition.y = ( SCR_HEIGHT-h ) / 2;
    _boardPosition.w = w;
    _boardPosition.h = h;
}

void View2D::showStones( ) const
{
    for ( int team = 0; team < 2; ++team )
    {
        for ( int tID = 0; tID < 5; ++tID )
        {
            SDL_Rect pos;
            if ( team == _selected_team && tID == _selected_ID )
            {
                int mx, my;
                SDL_GetMouseState ( &mx, &my );
                pos.h = STONE_SIZE;
                pos.w = STONE_SIZE;
                pos.x = mx  - STONE_SIZE / 2;
                pos.y = my  - STONE_SIZE / 2;
            }
            else
            {
                pos = __stones[team][tID];
            }
            SDL_RenderCopy ( _render, _stone[team], NULL, &pos );
        }
    }
    SDL_RenderPresent ( _render );
}

void View2D::refreshStones() const
{
    for ( int team = 0; team < 2; ++team )
        for ( int ID = 0; ID < 5; ++ID )
        {
            __stones[team][ID] = getPosition ( team, ID );
        }
}

SDL_Rect View2D::getPosition ( const int& team, const int& ID ) const
{
    uint8_t col, row;
    team ? _engine.getPlayerCollection()->getPos ( ID, row, col )  :  _engine.getProgramCollection()->getPos ( ID, row, col );
    SDL_Rect result = getDirectPosition ( row, col );
    return result;
}

SDL_Rect View2D::getDirectPosition ( const int& row, const int& col ) const
{
    SDL_Rect result;
    result.x = OFFSET_X + ( col - 1 ) * STEP_X;
    result.y = OFFSET_Y + ( row - 1 ) * STEP_Y;
    result.w = STONE_SIZE;
    result.h = STONE_SIZE;
    result.y = SCR_HEIGHT - result.y - STONE_SIZE; // vertical reflection
    return result;
}

bool View2D::pickUp ( const int& coX, const int& coY )
{
    bool result = false;
    noPickUp();
    for ( uint8_t T = 0 /**/; T < 2; ++T )
        for ( uint8_t i = 0; i < 5; ++i )
        {
            const int x = __stones[T][i].x + STONE_SIZE / 2;
            const int y = __stones[T][i].y + STONE_SIZE / 2;
            if ( abs ( coX - x ) < STONE_SIZE / 2 && abs ( coY - y ) < STONE_SIZE / 2 )
            {
                result = true;
                _selected_team = T;
                _selected_ID = i;
                T  = 2; // break outer loop
                break;
            }
        }
    return result;
}

void View2D::glidingEffect ( const Step& step )
{
}

void View2D::show ( ) const
{
    SDL_RenderClear ( _render );
    SDL_RenderCopy ( _render, _boardBackground, NULL,NULL );
    SDL_RenderCopy ( _render,_boardTexture,NULL,&_boardPosition );
    refreshStones();
    showStones();
}

void View2D::reset()
{
    SDL_Event event;
    SDL_FlushEvents ( SDL_MOUSEMOTION, SDL_MOUSEWHEEL );
    SDL_WaitEvent ( &event );
    while ( event.button.button != SDL_PRESSED )
    {
        SDL_PollEvent ( &event );
    }
    SDL_Delay ( 500 );
    _engine.reset();
    show();
}

void View2D::placeStone ( SDL_Event &event )
{
    SDL_PollEvent ( &event );
    int mx, my;
    SDL_GetMouseState ( &mx, &my );
    if ( pickUp ( mx, my ) && _selected_team == 1 )
    {
        do
        {
            SDL_FlushEvents ( SDL_MOUSEMOTION, SDL_MOUSEWHEEL );
            show();
            SDL_PollEvent ( &event );
        }
        while ( event.button.button == SDL_PRESSED );
        SDL_GetMouseState ( &mx, &my );
        int col = ( mx - OFFSET_X ) / STEP_X + 1;
        int row = ( my - OFFSET_Y ) / STEP_Y + 1;
        Step S;
        if ( _engine.getStep ( _selected_ID, 8 - row /*invert*/, col, S ) )
        {
            noPickUp();
            _engine.storeStep ( S );
            show();
            if ( _engine.isWinnerStep ( S ) )
            {
                reset();
            }
            else
            {
                _engine.swapPlayers();
                S = _engine.getResult().getStep();
                _engine.storeStep ( S );
                show();
                if ( _engine.isWinnerStep ( S ) )
                {
                    reset();
                }
                else
                {
                    _engine.swapPlayers();
                }
            }
        }
        else
        {
            noPickUp();
            show();
        }
    }
}

void View2D::select()
{
    SDL_Event event;
    show();
    do
    {
        SDL_WaitEvent ( &event );
        if ( event.type == SDL_QUIT )
        {
            return;
        }
        if ( event.type == SDL_KEYDOWN )
        {
            switch ( event.key.keysym.sym ) // ToDo
            {
            case SDLK_LEFT:
                break;
            case SDLK_RIGHT:
                break;
            case SDLK_ESCAPE:
                return;
            default:
                ;
            }
        }
        if ( event.type == SDL_MOUSEBUTTONDOWN )
        {
            placeStone ( event );
        }
    }
    while ( true );
}
View2D::~View2D()
{
    SDL_DestroyTexture ( _boardBackground );
    std::cout << _winName <<" board background deleted " << std::endl;
    SDL_DestroyTexture ( _boardTexture );
    std::cout << _winName <<" board texture deleted " << std::endl;
    SDL_DestroyRenderer ( _render );
    std::cout << _winName <<" render deleted " << std::endl;
    SDL_DestroyWindow ( _win );
    std::cout << _winName <<" window closed " << std::endl;
    std::cout << std::endl << _winName <<" destructor finished... " << std::endl;
}

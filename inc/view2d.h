/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2018  <copyright holder> <email>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#ifndef VIEW2D_H
#define VIEW2D_H

#include "sdl_dep.h"
#include "engine.h"

static const int NUMBER_OF_STONES = 5;
class View2D
{
    static bool SDL_Initialized;
    static void init();

    int SCR_WIDTH;
    int SCR_HEIGHT;
    const char * _winName;
    SDL_Window * _win = nullptr;
    SDL_Renderer * _render = nullptr;
    SDL_Texture * _stone[2] = {};
    SDL_Texture * _boardTexture = nullptr;
    SDL_Texture * _boardBackground;
    SDL_Rect _boardPosition;

    Engine & _engine;

    // moving one stone with mouse
    uint8_t _selected_team = 0xFF;
    uint8_t _selected_ID = 0xFF;

    mutable SDL_Rect __stones [/*teams*/ 2][/*stone IDs*/  NUMBER_OF_STONES];
    SDL_Rect getPosition ( const int& team, const int& ID ) const;
    SDL_Rect getDirectPosition ( const int& col, const int& row ) const;
    bool pickUp ( const int& coX, const int& coY );
    void noPickUp()
    {
        _selected_team = 0xFF;
        _selected_ID = 0xFF;
    }
    void placeStone ( SDL_Event& );
    void refreshStones() const;
    void showStones() const;
    void glidingEffect ( const Step& );

    void createWindow();
    void loadTextureImage();

    void show ( ) const;

public:
    View2D ( const char* name,const int w, const int h, Engine& );
    ~View2D();
    void play();
    void reset();
};

#endif // VIEW2D_H

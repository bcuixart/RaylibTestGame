#ifndef COLORMANAGER_HH
#define COLORMANAGER_HH

#include <iostream>

#include <raylib.h>
#include <raymath.h>

#define BACKGROUND_PALETTES 13
#define ROCKET_PALETTES 2

class ColorManager {
public:
    ColorManager();

    void NextPalette();

    Color GetRocketBaseColor() const;
    Color GetRocketTopColor() const;
    Color GetRocketWindowColor() const;
    Color GetRocketPropeller000Color() const;
    Color GetRocketPropeller001Color() const;
    Color GetRocketPropeller002Color() const;

    Color GetRocketFireColor() const;

    Color GetBackgroundColor() const;
    Color GetCoinColor() const;

    Color GetBGStarColor() const;
    Color GetAsteroid000Color() const;
    Color GetAsteroid001Color() const;

private:

    const Color COLORS_ROCKET[ROCKET_PALETTES] = {
            {213, 167, 247, 255 },
            {189, 129, 237, 255 },
    };

    const Color COLORS_FIRE[ROCKET_PALETTES] = {
            {229, 197, 247, 255},
            {229, 197, 247, 255},
    };

    const Color COLORS_BACKGROUND[BACKGROUND_PALETTES] = {
            {133, 60, 217, 255},
            {125, 43, 115, 255},
            {99, 0, 102, 255},
            {121, 19, 19, 255},
            {171, 97, 20, 255},
            {146, 143, 44, 255},
            {78, 160, 8, 255},
            {9, 93, 5, 255},
            {19, 146, 94, 255},
            {27, 151, 161, 255},
            {27, 100, 161, 255},
            {37, 53, 153, 255},
            {38, 38, 38, 255},
    };

    const Color COLORS_COIN[BACKGROUND_PALETTES] = {
            {236, 176, 246, 255},
            {240, 102, 226, 255},
            {232, 0, 240, 255},
            {223, 121, 121, 255},
            {255, 231, 171, 255},
            {248, 245, 146, 255},
            {228, 252, 116, 255},
            {77, 226, 61, 255},
            {121, 248, 196, 255},
            {161, 255, 255, 255},
            {161, 219, 255, 255},
            {153, 162, 255, 255},
            {242, 242, 242, 255},
    };

    const Color COLORS_BGSTARS[BACKGROUND_PALETTES] = {
            {229, 197, 248, 255},
            {197, 85, 186, 255},
            {191, 0, 197, 255},
            {166, 64, 64, 255},
            {223, 166, 80, 255},
            {191, 188, 88, 255},
            {157, 220, 35, 255},
            {28, 162, 21, 255},
            {64, 191, 139, 255},
            {91, 201, 212, 255},
            {93, 153, 212, 255},
            {100, 111, 199, 255},
            {127, 127, 127, 255},
    };

    const Color COLORS_ASTEROID_000[BACKGROUND_PALETTES] = {
            {190, 130, 238, 255},
            {163, 70, 154, 255},
            {158, 0, 163, 255},
            {166, 64, 64, 255},
            {223, 166, 80, 255},
            {191, 188, 88, 255},
            {157, 220, 35, 255},
            {28, 162, 21, 255},
            {64, 191, 139, 255},
            {91, 201, 212, 255},
            {93, 153, 212, 255},
            {100, 111, 199, 255},
            {127, 127, 127, 255},
    };

    const Color COLORS_ASTEROID_001[BACKGROUND_PALETTES] = {
            {150, 76, 225, 255},
            {133, 57, 125, 255},
            {128, 0, 133, 255},
            {146, 44, 44, 255},
            {203, 136, 50, 255},
            {172, 168, 69, 255},
            {121, 199, 20, 255},
            {19, 134, 13, 255},
            {44, 172, 120, 255},
            {63, 180, 190, 255},
            {63, 132, 190, 255},
            {76, 88, 177, 255},
            {89, 89, 89, 255},
    };

    int colorSelectedRocketBase = 0;
    int colorSelectedRocketTop = 1;
    int colorSelectedRocketWindow = 1;
    int colorSelectedRocketPropeller000 = 1;
    int colorSelectedRocketPropeller001 = 1;
    int colorSelectedRocketPropeller002 = 1;
    int colorSelectedRocketFire = 1;

    int colorSelectedBackground = 0;
    int colorSelectedCoin = 0;
    int colorSelectedAsteroid = 0;

};


#endif

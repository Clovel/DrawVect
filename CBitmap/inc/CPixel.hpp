/*
 *  CPixel.hpp
 *  P_Bitmap
 *
 *  Created by Le Gal on 24/10/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CPIXEL_HPP
#define CPIXEL_HPP

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

class CPixel
{
    private:
        int red;
        int green;
        int blue;

    public:
        CPixel(int r, int g, int b);
        CPixel();

        void    Red(int r);
        void    Green(int g);
        void    Blue(int b);

        int Red();
        int Green();
        int Blue();

        void RGB(int r, int g, int b);
};

#endif /*CPIXEL_HPP*/

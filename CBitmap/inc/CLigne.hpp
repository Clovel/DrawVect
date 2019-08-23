/*
 *  CLigne.hpp
 *  P_Bitmap
 *
 *  Created by Le Gal on 24/10/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "CPixel.hpp"

#ifndef CLIGNE_HPP
#define CLIGNE_HPP

class CLigne
{
    private:
        CPixel **ligne;
        int taille;

    public:
        CLigne(int _taille);

        CLigne();

        ~CLigne();

        int size();

        CPixel *getPixel(int position);
};

#endif /*CLIGNE_HPP*/

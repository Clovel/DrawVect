// Clovis Durand & Camille Magnan
// ENSEIRB-Matmeca, E2
// 2017

// PG208 - Projet Dessin Vectoriel

// Point.cpp
// Point class source file.

#include "Point.hpp"

// Con/Destructeurs
Point::Point(Coord const        c,
             std::string const  couleur,
             unsigned int const transparence) : Forme(c, couleur, transparence)
{
    //
}

// Afficheurs

// Accesseurs

// Mutateurs

// Draw
void Point::draw(CImage *img)
{
    RGB_t RGB_temp;

    RGB_temp = applyTransparency(img, getCoord1().getAbscisse(), getCoord1().getOrdonnee());
    img->drawPixel(getCoord1().getAbscisse(),
                   getCoord1().getOrdonnee(),
                   RGB_temp.r, RGB_temp.g, RGB_temp.b);
}

// Méthodes publiques Diverses

// Attributs/Variables membres

// Méthodes privées diverses

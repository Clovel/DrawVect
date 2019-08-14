// Clovis Durand & Camille Magnan
// ENSEIRB-Matmeca, E2
// 2017

// PG208 - Projet Dessin Vectoriel

// Point.hpp
// Point class header file.

#ifndef POINT_HPP
#define POINT_HPP

#include "Forme.hpp"

class Point: public Forme
{
    public:
        // Con/Destructeurs
        Point(Coord const           c,
              std::string const     couleur,
              unsigned int const    transparence);
        // Afficheurs

        // Accesseurs

        // Mutateurs

        // Draw
        void draw(CImage *img);

        // Méthodes publiques Diverses

//private:
        // Attributs/Variables membres

        // Méthodes privées diverses
};

#endif //POINT_HPP

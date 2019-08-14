// Clovis Durand & Camille Magnan
// ENSEIRB-Matmeca, E2
// 2017

// PG208 - Projet Dessin Vectoriel

// Rectangle_p.hpp
// Rectangle_p class header file.

#ifndef RECTANGLE_P_HPP
#define RECTANGLE_P_HPP

#include "Rectangle.hpp"

class Rectangle_p: public Rectangle
{
    public:
        // Con/Destructeurs
        Rectangle_p(Coord const         c1,
                    unsigned int const  longueur,
                    unsigned int const  hauteur,
                    std::string const   couleur,
                    unsigned int const  transparence);

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

#endif /* RECTANGLE_P_HPP */

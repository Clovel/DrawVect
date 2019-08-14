// Clovis Durand & Camille Magnan
// ENSEIRB-Matmeca, E2
// 2017

// PG208 - Projet Dessin Vectoriel

// Carre_p.hpp
// Carre class header file.

#ifndef CARRE_P_HPP
#define CARRE_P_HPP

#include "Rectangle_p.hpp"

class Carre_p: public Rectangle_p
{
    public:
        // Constructeur
        Carre_p(Coord const         c1,
                unsigned int const  c,
                std::string const   couleur,
                unsigned int const  transparence);
};

#endif /* CARRE_P_HPP */

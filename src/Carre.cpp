// Clovis Durand & Camille Magnan
// ENSEIRB-Matmeca, E2
// 2017

// PG208 - Projet Dessin Vectoriel

// Carre.cpp
// Carre class header file.

#include "Carre.hpp"

Carre::Carre(Coord const        c1,
             unsigned int const c,
             std::string const  couleur,
             unsigned int       transparence) : Rectangle(c1, c, c, couleur, transparence)
{
}

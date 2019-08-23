// Clovis Durand & Camille Magnan
// ENSEIRB-Matmeca, E2
// 2017

// PG208 - Projet Dessin Vectoriel

// Triangle.cpp
// Triangle class source file.

#include "Triangle.hpp"

// Constructeurs
Triangle::Triangle(Ligne const  l,
                   Coord const  c)
{
    setCoord1(l.getCoord1());
    setCoord2(l.getCoord2());
    setCoord3(c);
    setCouleur(l.getCouleur());
    setTransparence(l.getTransparence());
}

// Afficheurs

// Accesseurs
Coord Triangle::getCoord3(void) const
{
    return m_c3;
}

// Mutateurs
void Triangle::setCoord3(Coord const &c)
{
    m_c3 = c;
}

// Draw
void Triangle::draw(CImage *img)
{
    Ligne   l1(getCoord1(), getCoord2(), getCouleur(), getTransparence());
    Ligne   l2(getCoord1(), getCoord3(), getCouleur(), getTransparence());
    Ligne   l3(getCoord2(), getCoord3(), getCouleur(), getTransparence());

#ifdef DEBUG
    std::cout << "[DEBUG] : l1 : " << l1 << std::endl;
    std::cout << "[DEBUG] : l2 : " << l2 << std::endl;
    std::cout << "[DEBUG] : l3 : " << l3 << std::endl;
#endif //DEBUG

    l1.draw(img);
    l2.draw(img);
    l3.draw(img);
}

// Méthodes publiques diverses

// Méthodes privées diverses

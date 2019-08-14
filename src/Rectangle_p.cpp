// Clovis Durand & Camille Magnan
// ENSEIRB-Matmeca, E2
// 2017

// PG208 - Projet Dessin Vectoriel

// Rectangle_p.cpp

#include "Rectangle_p.hpp"

// Con/Destructeurs
Rectangle_p::Rectangle_p(Coord const        c1,
                         unsigned int const longueur,
                         unsigned int const hauteur,
                         std::string const  couleur,
                         unsigned int const transparence) : Rectangle(c1,
                                                                      longueur,
                                                                      hauteur,
                                                                      couleur,
                                                                      transparence)
{
}

// Afficheurs

// Accesseurs

// Mutateurs

// Draw
void Rectangle_p::draw(CImage *img)
{
#ifdef DEBUG
    std::cout << "[DEBUG] : This shape is a full rectangle\n";
#endif //DEBUG

    int y0  = getCoord1().getOrdonnee();
    int y1  = getLigne1().getCoord2().getOrdonnee();
    int x0  = getCoord1().getAbscisse();
    int x1  = getLigne2().getCoord2().getAbscisse();

    for (int i = y0; i <= y1; i++) {
        Coord   c1_temp(x0, i), c2_temp(x1, i);
        Ligne   l_temp(c1_temp, c2_temp, getCouleur(), getTransparence());
        l_temp.draw(img);
    }
}

// Méthodes publiques Diverses

// Attributs/Variables membres

// Méthodes privées diverses

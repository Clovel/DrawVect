// Clovis Durand & Camille Magnan
// ENSEIRB-Matmeca, E2
// 2017

// PG208 - Projet Dessin Vectoriel

// Rectangle.cpp
// Rectangle class source file.

#include "Rectangle.hpp"

// Con/Destructeur --------------------------------------------------
Rectangle::Rectangle(Coord const        c1,
                     unsigned int const longueur,
                     unsigned int const hauteur,
                     std::string const  couleur,
                     unsigned int const transparence)
{
    // Droit
    setCoord1(c1);
    setTransparence(transparence);
    setCouleur(couleur);
    calcul_lignes(longueur, hauteur);
}

/*Rectangle::Rectangle(Ligne const l1,
 *  int const dist,
 * std::string const couleur,
 *  unsigned int const transparence)
 * {
 *  // De biais
 *  setLigne1(l1);
 *  setCoord1(l1.getCoord1());
 *  setCouleur(couleur);
 *  setTransparence(transparence);
 *  calcul_lignes(dist);
 * }*/

// Afficheurs -------------------------------------------------------

// Accesseurs -------------------------------------------------------
Ligne Rectangle::getLigne1(void) const
{
    return m_l1;
}

Ligne Rectangle::getLigne2(void) const
{
    return m_l2;
}

Ligne Rectangle::getLigne3(void) const
{
    return m_l3;
}

Ligne Rectangle::getLigne4(void) const
{
    return m_l4;
}

// Mutateurs --------------------------------------------------------
void Rectangle::setLigne1(Ligne const &l)
{
    m_l1 = l;
}

void Rectangle::setLigne2(Ligne const &l)
{
    m_l2 = l;
}

void Rectangle::setLigne3(Ligne const &l)
{
    m_l3 = l;
}

void Rectangle::setLigne4(Ligne const &l)
{
    m_l4 = l;
}

// Draw -------------------------------------------------------------
void Rectangle::draw(CImage *img)
{
#ifdef DEBUG
    std::cout << "[DEBUG] : This shape is a simple rectangle\n";
#endif //DEBUG

    m_l1.draw(img);
    m_l2.draw(img);
    m_l3.draw(img);
    m_l4.draw(img);
}

// Méthodes publiques diverses --------------------------------------

// Méthodes protégées diverses --------------------------------------
void Rectangle::calcul_lignes(unsigned int const &longueur, unsigned int const &hauteur)
{
    Coord   c1(getCoord1());
    Coord   c2(c1.getAbscisse(), c1.getOrdonnee() + hauteur);
    Coord   c3(c1.getAbscisse() + longueur, c1.getOrdonnee() + hauteur);
    Coord   c4(c1.getAbscisse() + longueur, c1.getOrdonnee());

    setLigne1(Ligne(c1, c2, getCouleur(), getTransparence()));
    setLigne2(Ligne(c2, c3, getCouleur(), getTransparence()));
    setLigne3(Ligne(c3, c4, getCouleur(), getTransparence()));
    setLigne4(Ligne(c4, c1, getCouleur(), getTransparence()));
}

void Rectangle::calcul_lignes(int const &dist)
// Pour rectangle de biais (avec angle)
{
    int     opp     = getLigne1().getCoord2().getOrdonnee() - getCoord1().getOrdonnee();
    int     adj     = getLigne1().getCoord2().getAbscisse() - getCoord1().getAbscisse();
    double  angle   = asin((double(opp)) / (double(adj)));

    int     y   = int(getLigne1().getCoord1().getOrdonnee() + cos(angle) * dist);
    int     x   = int(getLigne1().getCoord1().getAbscisse() - sin(angle) * dist);
    Coord   c2  = Coord(x, y);

    setLigne1(Ligne(getCoord1(), c2, getCouleur(), getTransparence()));

    y   = int(getLigne1().getCoord2().getOrdonnee() + cos(angle) * dist);
    x   = int(getLigne1().getCoord2().getAbscisse() - sin(angle) * dist);
    Coord c3 = Coord(x, y);

    setLigne3(Ligne(getLigne1().getCoord2(), c3, getCouleur(), getTransparence()));

    setLigne4(Ligne(c2, c3, getCouleur(), getTransparence()));
}

// Opérateurs

// Fonctions exterieures a la classe

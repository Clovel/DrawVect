// Camille Magnan & Clovis Durand
// PG208 - Projet Dessin Vectoriel

#ifndef COORD_HPP
#define COORD_HPP

#include <iostream>

// Classe Coord permet de definir un point "mathemmatique"

class Coord
{
    public:
        // Con/Destructeurs
        Coord(int const x = 0, int const y = 0);                  // Valeur par defaut sur le proto pas sur le code cpp

        // Afficheurs
        void    showCoord(void) const;
        void    printCoord(std::ostream &flux) const;

        // Accesseurs
        int getAbscisse(void) const;
        int getOrdonnee(void) const;

        // Mutateurs
        void    setAbscisse(int const &x);
        void    setOrdonnee(int const &y);

    private:
        int m_x, m_y;
};

// Operateurs
std::ostream &operator<<(std::ostream &out, Coord const &c);

#endif /* COORD_HPP */

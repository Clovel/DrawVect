// Camille Magnan & Clovis Durand
// PG208 - Projet Dessin Vectoriel

#ifndef LIGNE_HPP // Pour ne pas l'inclure plusieurs fois
#define LIGNE_HPP

#include "Forme.hpp"                // Pour heritage

// ATTENTION, heritage pas encore implemente

class Ligne: public Forme
{
    public:
        // Con/Destructeurs
        Ligne();
        Ligne(Coord const           c1,
              Coord const           c2,
              std::string const     couleur,
              unsigned int const    transparence);

        // Afficheurs
        void printInfoLigne(std::ostream &flux) const;

        // Accesseurs
        Coord           getCoord2(void) const;
        unsigned int    getLongueur(void) const;

        // Mutateurs
        void    setCoord2(Coord const &c2);
        void    setCoords(Coord const &c1, Coord const &c2);

        // Draw
        void draw(CImage *img);

        // Méthodes publiques Diverses

    private:
        // Attributs/Variables membres
        Coord m_c2;

        // Méthodes privée diverses
};

// Opérateurs
std::ostream &operator<<(std::ostream &flux, Ligne const &l);

#endif /* LIGNE_HPP */

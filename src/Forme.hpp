// Clovis Durand & Camille Magnan
// ENSEIRB-Matmeca, E2
// 2017

// PG208 - Projet Dessin Vectoriel

// Forme.hpp
// Forme class header file.

#ifndef FORME_HPP // Pour ne pas l'inclure plusieurs fois
#define FORME_HPP

#include "Coord.hpp"    // Point mathématique
#include "CImage.hpp"   // Pour dessiner (sert pour les descendants de class Forme)

#include <string>
#include <cmath>
#include <iostream>

#define MIN(X, Y)   ((X < Y) ? X : Y)
#define MAX(X, Y)   ((X > Y) ? X : Y)

// Sert a retourner 3 uInt en sortie d'une fcn
// On ne peut retourner un tableau en C/C++
typedef struct RGB {
    unsigned int    r;
    unsigned int    g;
    unsigned int    b;
} RGB_t;

class Forme
{
    public:
        // Con/Destructeurs
        Forme();
        Forme(Coord const           c1,
              std::string const     couleur,
              unsigned int const    transparence);

        // Accesseurs
        Coord           getCoord1(void) const;
        std::string     getCouleur(void) const;
        unsigned int    getTransparence(void) const;
        RGB_t           getRGB(void) const; // Traduction string -> RGB

        // Mutateurs
        void    setCoord1(Coord const &c1);
        void    setCouleur(std::string const &couleur);
        void    setTransparence(unsigned int const &transparence);

        // Fonctions publiques diverses

        RGB_t           applyTransparency(CImage *img, int const x, int const y);
        virtual void    draw(CImage *img) = 0; // Declaration : ELLE EXISTE

    private:
        Coord m_c1;
        std::string m_couleur;
        unsigned int m_transparence;
};

#endif //FORME_HPP

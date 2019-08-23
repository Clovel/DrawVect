// Clovis Durand & Camille Magnan
// ENSEIRB-Matmeca, E2
// 2017

// PG208 - Projet Dessin Vectoriel

// Ractangle.hpp
// Rectangle class header file.

#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "Ligne.hpp"

class Rectangle: public Forme
{
    public:
        //Constructeur
        Rectangle(Coord const           c1,
                  unsigned int const    longueur,
                  unsigned int const    hauteur,
                  std::string const     couleur,
                  unsigned int const    transparence); // Droit

        /*Rectangle(Ligne const l1,
         *  int const dist,
         *  std::string const couleur,
         *  unsigned int const transparence); // De biais*/

        // Afficheurs

        // Accesseurs
        Ligne   getLigne1(void) const;
        Ligne   getLigne2(void) const;
        Ligne   getLigne3(void) const;
        Ligne   getLigne4(void) const;

        // Mutateurs
        void    setLigne1(Ligne const &l);
        void    setLigne2(Ligne const &l);
        void    setLigne3(Ligne const &l);
        void    setLigne4(Ligne const &l);

        // Draw
        void draw(CImage *img);

        // Méthodes publiques diverses

    private:
        // Variables membres/attributs
        Ligne m_l1;
        Ligne m_l2;
        Ligne m_l3;
        Ligne m_l4;

        // Ordre pour le rectangle droit
        //           m_l2
        //      +-------------+
        //      |             |
        // m_l1 |             | m_l3
        //      |             |
        //      +-------------+
        //           m_l4

    protected:
        // Méthodes protégées diverses
        void    calcul_lignes(unsigned int const &longueur, unsigned int const &hauteur);
        void    calcul_lignes(int const &dist);
};

// Opérateurs

// Fonctions exterieures a la classe

#endif /* RECTANGLE_HPP */

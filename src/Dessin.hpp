// Clovis Durand & Camille Magnan
// ENSEIRB-Matmeca, E2
// 2017

// PG208 - Projet Dessin Vectoriel

// Dessin.hpp
// Dessin class header file.

#ifndef DESSIN_HPP
#define DESSIN_HPP

#include "Forme.hpp"
#include "CImage.hpp"
#include "Coord.hpp"

//Includes des classes de formes
#include "Ligne.hpp"
#include "Rectangle.hpp"
#include "Rectangle_p.hpp"
#include "Triangle.hpp"
#include "Cercle.hpp"
#include "Cercle_p.hpp"
#include "Carre.hpp"
#include "Carre_p.hpp"
#include "Point.hpp"

#include <vector>
#include <string>       /* For stoi */
#include <fstream>

class Dessin
{
    public:
        // Con/Destructeur
        Dessin();
        ~Dessin();

        // Accesseurs
        Forme                       *getFormeFromIdx(unsigned int const &index) const;
        std::vector<Forme *>        getFormes(void) const;
        std::vector<unsigned int>   getH(void) const;
        std::vector<unsigned int>   getL(void) const;
        float                       getScalingRatio(void) const;

        // Mutateurs
        void    setForme(Forme *f, unsigned int const &index);
        void    addForme(Forme *f);
        void    addH(unsigned int const &a);
        void    addL(unsigned int const &a);
        void    setScalingRatio(float const &scl);

        // Fonction Load depuis un fichier .vec
        bool loadVec(std::string const &filename);

        // Fonctions publiques diverses
        void    drawAll(CImage *img) const;
        void    printVector(std::vector<unsigned int> a) const;

    private:
        std::vector<Forme *> m_formes; // Va contenir toutes les formes

        // Définition de la taille de l'image
        // Pour la hauteur
        std::vector<unsigned int> m_h;

        // Pour la largeur
        std::vector<unsigned int> m_l;

        // Facteur d'échelle
        float m_scalingRatio;

        // Fonctions privées diverses
        Forme   *loadForme(std::string ligne);
        void    bubbleSort(std::vector<unsigned int> &a);
};

#endif /* DESSIN_HPP */

// On utlise des "Formes *" car Forme est une classe dite "Absraite"

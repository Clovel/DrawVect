// Clovis Durand & Camille Magnan
// ENSEIRB-Matmeca, E2
// 2017

// PG208 - Projet Dessin Vectoriel

// main.cpp
// main source file

#include "CBitmap.hpp"

#include "Ligne.hpp"
#include "Rectangle.hpp"
#include "Rectangle_p.hpp"
#include "Triangle.hpp"
#include "Cercle.hpp"
#include "Cercle_p.hpp"
#include "Carre.hpp"
#include "Carre_p.hpp"
#include "Dessin.hpp"
#include "Point.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>       // C++ string
#include <cstring>      // C string (for strcmp)
#include <cstdlib>      // C atof to convert argv (char const *) to float

// L'image doit etre carré d'apres le code de CImage fourni
#define WIDTH   768
#define HEIGHT  768

int main(int argc, char *argv[])
{
    if (argc == 1) {
        std::cerr << "[ERROR]  : Not enough arguments" << std::endl;
    } else {
        std::cout << "[DEBUG] : " << argv[0] << ", " << argv[1] << std::endl;
        if ((strcmp(argv[0], "test") == 0) || (strcmp(argv[0], "DEBUG") == 0)) {
            std::cout << "[INFO]  : P_Bitmap exection start (" << __DATE__ << " - " << __TIME__ << ")" << std::endl;
            std::cout << "[INFO]  : Number of arguments = " << argc << std::endl;

            std::cout << "[INFO]  : CBitmap object creation" << std::endl;
            CBitmap     *image      = new CBitmap();
            std::string filename2   = "Sortie_test.bmp";

            std::cout << "[INFO]  : CImage pointer extraction" << std::endl;
            CImage *img = new CImage(HEIGHT, WIDTH);

            // Dessine une ligne diagonale de (0, 0) a (200, 200),
            // i.e. de en bas a gauche à en haut a droite
            // Sert de témoin pour savoir si on arrive tjr a dessiner
            for (int i = 0; i < 200; i++) {
                CPixel *p = img->getPixel(i, i);
                p->RGB(255, 255, 255);
            }

            // Test dessin Ligne
            Coord   c1(300, 300);
            Coord   c2(500, 400);
            Coord   c3(600, 100);

            std::cout << "[INFO]  : Creation of the drawing" << std::endl;
            Dessin dessin_test; // Construit le dessin

            // Declaration des formes
            std::cout << "[INFO]  : Declaration of every shape" << std::endl;
            Ligne       l(c1, c2, "BLANC", 100);
            Rectangle   rect(c1, 100, 200, "ROSE", 100);
            Cercle      circ(c1, 125, "BLANC", 100);
            Cercle_p    circp(c3, 90, "BLEU", 100);
            Rectangle_p rectp(c1, 30, 50, "BLANC", 100);

            dessin_test.addForme(&l);
            dessin_test.addForme(&rect);
            dessin_test.addForme(&circ);
            dessin_test.addForme(&circp);
            dessin_test.addForme(&rectp);

            dessin_test.drawAll(img);

            /* TEST DIRECT DES FORMES
             * // Test Ligne                                   // OK
             * Ligne l(c1, c2, "BLANC", 100);
             *  std::cout << "[DRAW]  : Drawing [l]" << std::endl;
             * l.draw(img); // Dessine sur l'image
             *
             * // Test rectangle droit                         // OK
             * Rectangle rect(c1, 100, 200, "ROSE", 100);
             *  std::cout << "[DRAW]  : Drawing [rect]" << std::endl;
             * rect.draw(img);
             *
             * // Test cercle                                  // OK
             * Cercle circ(c1, 125, "BLANC", 100);
             *  std::cout << "[DRAW]  : Drawing [circ]" << std::endl;
             * circ.draw(img);
             *
             * // Test cercle plein                            // OK
             * Cercle_p circp(c3, 90, "BLEU", 100);
             *  std::cout << "[DRAW]  : Drawing [circp]" << std::endl;
             * circp.draw(img);
             *
             * // Test rectangle plein                         // NOK
             * Rectangle_p rectp(c1, 30, 50, "BLANC", 100);
             *  std::cout << "[DRAW]  : Drawing [rectp]" << std::endl;
             *  std::cout << "[DEBUG] : l1 à 4 : " << rectp.getLigne1() << ", ";
             *  std::cout << rectp.getLigne2() << ", ";
             *  std::cout << rectp.getLigne3() << ", ";
             *  std::cout << rectp.getLigne4() << "\n";
             * rectp.draw(img);
             *
             */

            image->setImage(img); // Met l'image dessinée dans l'objet CBitmap
            std::cout << "[INFO]  : CBitmap image saving" << std::endl;
            image->SaveBMP(filename2); // Enregistre le CBitmap

            return 1;
        } else { // Un nom de fichier a ete precise.
            // On déclare un dessin
            std::cout << "[INFO]  : Drawing creation" << std::endl;
            Dessin dessin; // Construit le dessin

            std::string filename = argv[1]; // On recupere le nom de fichier

            if (argc == 3) {
                dessin.setScalingRatio(atof(argv[2]));
            } else {
                dessin.setScalingRatio(1.);
            }

            if (dessin.loadVec(filename)) {
                std::cout << "[INFO]  : P_Bitmap exection start (" << __DATE__ << " - " << __TIME__ << ")" << std::endl;
                std::cout << "[INFO]  : Number of arguments = " << argc << std::endl;

                std::cout << "[INFO]  : CBitmap object creation" << std::endl;
                CBitmap     *image      = new CBitmap();
                std::string filename2   = "Sortie_vec.bmp";

                std::cout << "[INFO]  : CImage pointer extraction" << std::endl;

                unsigned int    n       = dessin.getH().size();
                unsigned int    height  = dessin.getH()[n - 1] + 4 - dessin.getH()[n - 1] % 4;
                unsigned int    width   = dessin.getL()[n - 1] + 4 - dessin.getL()[n - 1] % 4;
                CImage          *img    = new CImage(height, width);

                std::cout << "[INFO]  : " << filename << " loaded. " << std::endl;
                std::cout << "[INFO]  : Drawing all info given by [" << filename << "]" << std::endl;
                dessin.drawAll(img);

                image->setImage(img); // Met l'image dessinée dans l'objet CBitmap
                std::cout << "[INFO]  : CBitmap image saving" << std::endl;
                image->SaveBMP(filename2); // Enregistre le CBitmap

                return 1;
            } else {
                std::cout << "[ERROR] : " << filename << " failed to load. " << std::endl;
            }
        }
    }
}

/*
 *  CBitmap.cpp
 *  CBitmap
 *
 *  Created by Le Gal on 24/10/06.
 *  Copyright 2006 ENSEIRB. All rights reserved.
 *
 */

#include "CBitmap.hpp"

CBitmap::CBitmap() :
    bfType(19778),
    bfReserved1(0),
    bfReserved2(0),
    bfOffBits(54),
    biSize(40),
    biPlanes(1),
    biBitCount(24),
    biCompression(0),
    biXPelsPerMeter(2835),
    biYPelsPerMeter(2835),
    biClrUsed(0),
    biClrImportant(0)
{
    std::cout << "Creating a CBitmap()" << std::endl;
}

CImage *CBitmap::getImage()
{
    return image;
}

void CBitmap::setImage(CImage *_image)
{
    image       = _image;
    biHeight    = _image->size();
    biWidth     = _image->getLigne(0)->size();
    biSizeImage = biHeight * biWidth * biBitCount / 8;
    bfSize      = 54 + biSizeImage;
}

bool CBitmap::LoadBMP(std::string name)
{
    std::cout << "Starting picture loading..." << std::endl;
    std::ifstream myfile(name.c_str(), std::ios::in | std::ios::binary);

    if (myfile.is_open()) {
        myfile.read((char *)(&bfType), 2);
        myfile.read((char *)(&bfSize), 4);
        myfile.read((char *)(&bfReserved1), 2);
        myfile.read((char *)(&bfReserved2), 2);
        myfile.read((char *)(&bfOffBits), 4);
        myfile.read((char *)(&biSize), 4);
        myfile.read((char *)(&biWidth), 4);
        myfile.read((char *)(&biHeight), 4);
        myfile.read((char *)(&biPlanes), 2);
        myfile.read((char *)(&biBitCount), 2);
        myfile.read((char *)(&biCompression), 4);
        myfile.read((char *)(&biSizeImage), 4);
        myfile.read((char *)(&biXPelsPerMeter), 4);
        myfile.read((char *)(&biYPelsPerMeter), 4);
        myfile.read((char *)(&biClrUsed), 4);
        myfile.read((char *)(&biClrImportant), 4);

/* On va maintenant creer l'image         a proprement parler ... */

        char t[4];

        biHeight    = abs(biHeight);
        biWidth     = abs(biWidth);

        image = new CImage(biHeight, biWidth);

        int lectures = 0;

        for (int y = 0; y < biHeight; y++) {
            for (int x = 0; x < biWidth; x++) {
                lectures += 3;

//myfile.read(t, 3);

                CPixel *p = image->getLigne(y)->getPixel(x);
//std::cout << "Tagging pixel (" << y << ", " << x << ")" << std::endl;
                t[0]    = myfile.get();
                t[1]    = myfile.get();
                t[2]    = myfile.get();
                p->RGB((unsigned char)t[2], (unsigned char)t[1], (unsigned char)t[0]);
            }

/* On doit gerer le cas ou la largeur n'est pas un multiple de 4... */
            if (biWidth % 4 != 0) {
                for (int x = 0; x < biWidth % 4; x++) {
                    t[0] = myfile.get();
                    std::cout << "Lecture d'un octet de bourage (ligne%4 != 0);" << std::endl;
                }
            }
/* Fin de la gestion des lignes de taille non modulo 4 */
        }

        std::cout << "Nombre de pixels lus : " << lectures << std::endl;
        int nombre = 0;
        while (myfile.eof() == false) {
            nombre++;
            myfile.get();
        }
        std::cout << "Position dans le fichier : " << myfile.tellg() << std::endl;
        std::cout << "Nombre de donnes  lire : " << biSizeImage << std::endl;
        std::cout << "Nombre de donnes lues   : " << lectures << " (" << 3 * (biHeight) * (biWidth) + 54 << ")" << std::endl;
        std::cout << "Il restait " << nombre << " donnes  lire !" << std::endl;
    } else {
        std::cout << "Warning, unable to open the file : " << name << std::endl;
        return false;
    }

    return true;
}

bool CBitmap::SaveBMP(std::string name)
{
    std::cout << "INFO : Saving Bitmap..." << std::endl;
    std::ofstream myfile(name.c_str(), std::ios::out | std::ios::binary);

    if (myfile.is_open()) {
        myfile.write((char *)(&bfType), 2);
        myfile.write((char *)(&bfSize), 4);
        myfile.write((char *)(&bfReserved1), 2);
        myfile.write((char *)(&bfReserved2), 2);
        myfile.write((char *)(&bfOffBits), 4);
        myfile.write((char *)(&biSize), 4);
        myfile.write((char *)(&biWidth), 4);
        myfile.write((char *)(&biHeight), 4);
        myfile.write((char *)(&biPlanes), 2);
        myfile.write((char *)(&biBitCount), 2);
        myfile.write((char *)(&biCompression), 4);
        myfile.write((char *)(&biSizeImage), 4);
        myfile.write((char *)(&biXPelsPerMeter), 4);
        myfile.write((char *)(&biYPelsPerMeter), 4);
        myfile.write((char *)(&biClrUsed), 4);
        myfile.write((char *)(&biClrImportant), 4);

        /* On va maintenant creer l'image  proprement parler ... */
        char t[3];
        for (int y = 0; y < biHeight; y++) {
            CLigne *ligne = image->getLigne(image->size() - y - 1);
            for (int x = 0; x < biWidth; x++) {
                CPixel *p = image->getLigne(y)->getPixel(x);

                //CPixel* p = ligne->getPixel(x);
                (void)ligne;

                t[0]    = p->Blue();
                t[1]    = p->Green();
                t[2]    = p->Red();

                myfile.write(t, 3);
            }

            /* On doit gerer le cas ou la largeur n'est pas un multiple de 4...  */
            if (biWidth % 4 != 0) {
                std::cout << " largeur n'est pas multiple de 4 : " << biWidth << std::endl;
                for (int x = 0; x < (biWidth % 4); x++) {
                    t[0]    = 0;
                    t[1]    = 0;
                    t[2]    = 0;
                    myfile.write(t, 1);
                    std::cout << "  Ecriture d'un byte de bourage (colonne%4 != 0);" << std::endl;
                }
            }
            /* Fin de la gestion des lignes de taille non modulo 4 */
        }
        myfile.close();
    } else {
        std::cout << "Warning, unable to open the file : " << name << std::endl;
        return false;
    }
    std::cout << "INFO : Picture saved !" << std::endl;
    return true;
}

void CBitmap::dump()
{
    std::cout   << "bfType          : " << bfType << std::endl
                << "bfSize          : " << bfSize << std::endl
                << "bfReserved1     : " << bfReserved1 << std::endl
                << "bfReserved2     : " << bfReserved2 << std::endl
                << "bfOffBits       : " << bfOffBits << std::endl
                << "biSize          : " << biSize << std::endl
                << "biWidth         : " << biWidth << std::endl
                << "biHeight        : " << biHeight << std::endl
                << "biPlanes        : " << biPlanes << std::endl
                << "biBitCount      : " << biBitCount << std::endl
                << "biCompression   : " << biCompression << std::endl
                << "biSizeImage     : " << biSizeImage << std::endl
                << "biXPelsPerMeter : " << biXPelsPerMeter << std::endl
                << "biYPelsPerMeter : " << biYPelsPerMeter << std::endl
                << "biClrUsed       : " << biClrUsed << std::endl
                << "biClrImportant  : " << biClrImportant << std::endl;
}

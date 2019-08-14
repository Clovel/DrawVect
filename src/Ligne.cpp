// Camille Magnan & Clovis Durand
// ENSEIRB-Matmeca, E2
// 2017

// PG208 - Projet Dessin Vectoriel

// Ligne.cpp
// Definition des méthodes relatives a

#include "Ligne.hpp"

// Con/Destructeur --------------------------------------------------

Ligne::Ligne()
{
    setCouleur("blanc");
    setTransparence(0);
}

Ligne::Ligne(Coord const c1, Coord const c2,
             std::string const couleur,
             unsigned int const transparence)
{
    setCoords(c1, c2);
    setCouleur(couleur);
    setTransparence(transparence);
}

// Afficheurs -------------------------------------------------------
void Ligne::printInfoLigne(std::ostream &flux) const
{
    flux << getCoord1() << " to " << getCoord2();
}

// Accesseurs -------------------------------------------------------
Coord Ligne::getCoord2(void) const
{
    return m_c2;
}

unsigned int Ligne::getLongueur(void) const
// Calcule et retourne la longueur de la ligne
// Si le repere de coordonnees est entier, alors le resultat est un uInt
{
    return (unsigned int)sqrt((double)pow(getCoord2().getAbscisse() - getCoord1().getAbscisse(), 2)
                              + (double)pow(getCoord2().getOrdonnee() - getCoord1().getOrdonnee(), 2));
}

// Mutateurs --------------------------------------------------------
void Ligne::setCoord2(Coord const &c2)
{
    m_c2 = c2;
}

void Ligne::setCoords(Coord const &c1, Coord const &c2)
{
    setCoord1(c1);
    setCoord2(c2);
}

// Draw -------------------------------------------------------------
void Ligne::draw(CImage *img)
// Algorithme général optimisé de trace de segment de Bresenham
{
#ifdef DEBUG
    std::cout << "[DEBUG] : This shape is a line\n";
#endif //DEBUG

    int     dx, dy;     // Distances
    RGB_t   RGB_temp;   // COULEUR

    // Coordonnées
    int x0(getCoord1().getAbscisse());
    int y0(getCoord1().getOrdonnee());
    int x1(getCoord2().getAbscisse());
    int y1(getCoord2().getOrdonnee());
#ifdef DEBUG
    std::cout << "x0 = " << x0 << std::endl;
    std::cout << "y0 = " << y0 << std::endl;
    std::cout << "x1 = " << x1 << std::endl;
    std::cout << "y1 = " << y1 << std::endl;
#endif //DEBUG

    if ((dx = x1 - x0) != 0) {
        if (dx > 0) { // Vers la droite
            if ((dy = y1 - y0) != 0) {
                if (dy > 0) { // vers le haut
                    // Vecteur oblique dans le premier quandran
                    if (dx >= dy) {
                        // Vecteur diagonal oblique proche de l'horizontale dans le 1er octant
                        int e = dx;
                        dx  *= 2; // e est positif
                        dy  *= 2;
                        while (true) { // deplacements horizontaux
                            RGB_temp = applyTransparency(img, x0, y0);
                            img->drawPixel(x0, y0, RGB_temp.r, RGB_temp.g, RGB_temp.b); // Primitive poit le dessin du point
                            if ((++x0) == x1) {
                                break;
                            }
                            if ((e -= dy) < 0) {
                                y0++; // deplacement diagonal
                                e += dx;
                            }
                        }
                    } else {
                        // Vecteur oblique proche de la verticale, dans le 2nd octant
                        int e = dy; // e est positif
                        dy  *= 2;
                        dx  *= 2;
                        while (true) { // Deplacements verticaux
                            RGB_temp = applyTransparency(img, x0, y0);
                            img->drawPixel(x0, y0, RGB_temp.r, RGB_temp.g, RGB_temp.b);
                            if ((++y0) == y1) {
                                break;
                            }
                            if ((e -= dx) < 0) {
                                x0++; // deplacement diagonal
                                e += dy;
                            }
                        }
                    }
                } else { // dy < 0 (et dx > 0)
                    // Vecteur oblique dans le 4e quadran
                    if (dx >= -dy) {
                        // Vecteur diagonal ou oblique proche de l'horizontale, dans le 8e octant
                        int e = dx; // e est positif
                        dx  *= 2;
                        dy  *= 2;
                        while (true) { // deplacements horizontaux
                            RGB_temp = applyTransparency(img, x0, y0);
                            img->drawPixel(x0, y0, RGB_temp.r, RGB_temp.g, RGB_temp.b);

                            if ((++x0) == x1) {
                                break;
                            }
                            if ((e += dy) < 0) {
                                y0--; // deplacement diagonal
                                e += dx;
                            }
                        }
                    } else {
                        // Vecteur oblique proche de la verticale, dans le 7e octant
                        int e = dy; // e est negatif
                        dy  *= 2;
                        dx  *= 2;
                        while (true) { //deplacements verticaux
                            RGB_temp = applyTransparency(img, x0, y0);
                            img->drawPixel(x0, y0, RGB_temp.r, RGB_temp.g, RGB_temp.b);
                            if ((--y0) == y1) {
                                break;
                            }
                            if ((e += dx) > 0) {
                                x0++; // deplacement diagonal
                                e += dy;
                            }
                        }
                    }
                }
            } else { // dy = 0 (et dx > 0)
                do {
                    RGB_temp = applyTransparency(img, x0, y0);
                    img->drawPixel(x0, y0, RGB_temp.r, RGB_temp.g, RGB_temp.b);
                } while ((++x0) != x1);
            }
        } else { // dx < 0
            if ((dy = y1 - y0) != 0) {
                if (dy > 0) {           // Vecteur oblique dans le 2nd quadran
                    if (-dx >= dy) {    // Vecteur diag ou oblique proche de l'horizontale, dans le 4eme octant
                        int e = dx;
                        dx  *= 2;
                        dy  *= 2;
                        while (true) { // deplacements horizontalaux
                            RGB_temp = applyTransparency(img, x0, y0);
                            img->drawPixel(x0, y0, RGB_temp.r, RGB_temp.g, RGB_temp.b);
                            if ((--x0) == x1) {
                                break;
                            }
                            if ((e += dy) >= 0) {
                                y0++; // deplacement diagonal
                                e += dx;
                            }
                        }
                    } else {        // vecteur oblique proche de la verticale, dans le 3e octant
                        int e = dy; // e est positif
                        dy  *= 2;
                        dx  *= 2;
                        while (true) { // deplacements verticaux
                            RGB_temp = applyTransparency(img, x0, y0);
                            img->drawPixel(x0, y0, RGB_temp.r, RGB_temp.g, RGB_temp.b);
                            if ((++y0) == y1) {
                                break;
                            }
                            if ((e += dx) <= 0) {
                                x0--; // deplacement diagonal
                                e += dy;
                            }
                        }
                    }
                } else { // dy < 0 (et dx < 0)
                    // vecteur oblique dans le 3e cadran
                    if (dx <= dy) { // Vecteur diagonal ou oblique proche de l'horizontal, dans le 5e octant
                        int e = dx; // e est negatif
                        dx  *= 2;
                        dy  *= 2;
                        while (true) { // deplacements horizontaux
                            RGB_temp = applyTransparency(img, x0, y0);
                            img->drawPixel(x0, y0, RGB_temp.r, RGB_temp.g, RGB_temp.b);
                            if ((--x0) == x1) {
                                break;
                            }
                            if ((e -= dy) >= 0) {
                                y0--; // deplacement diagonal
                                e += dx;
                            }
                        }
                    } else {        // vecteur oblique proche de la verticale, dans le 6e octant
                        int e = dy; // e est negatif
                        dy  *= 2;
                        dx  *= 2;
                        while (true) { // deplacements verticaux
                            RGB_temp = applyTransparency(img, x0, y0);
                            img->drawPixel(x0, y0, RGB_temp.r, RGB_temp.g, RGB_temp.b);
                            if (--y0 == y1) {
                                break;
                            }
                            if ((e -= dx) >= 0) {
                                x0--; // deplacement diagonal
                                e += dy;
                            }
                        }
                    }
                }
            } else { // dy = 0 (et dx < 0)
                // Vecteur horizontal vers la gauche
                do {
                    RGB_temp = applyTransparency(img, x0, y0);
                    img->drawPixel(x0, y0, RGB_temp.r, RGB_temp.g, RGB_temp.b);
                } while (--x0 != x1);
            }
        }
    } else { // dx = 0
        if ((dy = y1 - y0) != 0) {
            if (dy > 0) { // Vecteur vertical croissant
                do {
                    RGB_temp = applyTransparency(img, x0, y0);
                    img->drawPixel(x0, y0, RGB_temp.r, RGB_temp.g, RGB_temp.b);
                } while (++y0 != y1);
            } else { // dy < 0 (et dx = 0)
                // Vecteur vertical décroissant
                do {
                    RGB_temp = applyTransparency(img, x0, y0);
                    img->drawPixel(x0, y0, RGB_temp.r, RGB_temp.g, RGB_temp.b);
                } while (--y0 != y1);
            }
        } else { // c'est un point, donc un simple pixel
            RGB_temp = applyTransparency(img, x0, y0);
        }
        img->drawPixel(x0, y0, RGB_temp.r, RGB_temp.g, RGB_temp.b);
    }
}

// Opérateurs -------------------------------------------------------
std::ostream &operator<<(std::ostream &flux, Ligne const &l)
{
    l.printInfoLigne(flux);
    return flux;
}

// Fonction diverses ------------------------------------------------

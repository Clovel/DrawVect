// Clovis Durand & Camille Magnan
// ENSEIRB-Matmeca, E2
// 2017

// PG208 - Projet Dessin Vectoriel

// Dessin.hpp
// Dessin class sources file.

#include "Dessin.hpp"

Dessin::Dessin() : m_scalingRatio(1)
{
    // Constructeur
}

Dessin::~Dessin()
{
    // Destructeur
    // Parcourir tout les elements du vecteur et free les allocations faites avec "new" : "delete"
    for (unsigned int i = 0; i < m_formes.size(); i++) {
        delete m_formes[i];
    }
    m_formes.clear();
}

// Accesseurs
Forme *Dessin::getFormeFromIdx(unsigned int const &index) const
{
#ifdef DEBUG
    std::cout << "[DEBUG] : Fetching shape with getFormeFromIdx(" << index << ")\n";
#endif // DEBUG
    return m_formes[index];
}

std::vector<Forme *> Dessin::getFormes(void) const
{
    return m_formes;
}

std::vector<unsigned int> Dessin::getH(void) const
{
    return m_h;
}

std::vector<unsigned int> Dessin::getL(void) const
{
    return m_l;
}

float Dessin::getScalingRatio(void) const
{
    return m_scalingRatio;
}

// Mutateurs

void Dessin::setForme(Forme *f, unsigned int const &index)
{
    if (index < m_formes.size()) {
        m_formes[index] = f;
    } else {
        std::cout << "[ERROR]  : Index not in vector size. \n";
        std::cout << "           Vector size is " << m_formes.size() << std::endl;
        std::cout << "           wheras index is " << index << std::endl;
    }
}

void Dessin::addForme(Forme *f)
{
    m_formes.push_back(f);
}

void Dessin::addH(unsigned int const &a)
{
    m_h.push_back(a);
}

void Dessin::addL(unsigned int const &a)
{
    m_l.push_back(a);
}

void Dessin::setScalingRatio(float const &scl)
{
    m_scalingRatio = scl;
}

// Fonction Load depuis un fichier .vec
bool Dessin::loadVec(std::string const &filename)
{
    std::ifstream   file(filename);
    std::string     ligne;

#ifdef DEBUG
    std::cout << "[DEBUG] : loadVec(" << filename << ")\n";
    unsigned int i = 0;
#endif // DEBUG

    if (file) {
        while (getline(file, ligne)) {
            // On parcours toutes les lignes du fichier
            // On charge toutes les formes correspondantes

#ifdef DEBUG
            std::cout << "[DEBUG] : Fetch line #" << i++ << ", contents are : " << ligne << std::endl;
#endif      // DEBUG

            unsigned int pos = ligne.find("#"); // Commentaire

            if ((pos != 0)) { // Attention ne gère pas les lignes vides
#ifdef DEBUG
                std::cout << "[DEBUG] : Adding info from : " << ligne << std::endl;
#endif          // DEBUG
                Forme *tempshape = loadForme(ligne);
                addForme(tempshape);
            }
        }

        // On trie les vecteurs d'extremes pour en recuperer les maximum et minimum.
#ifdef DEBUG
        std::cout << "[DEBUG] : Print du contenu des vecteur avant le tri à bulles\n";
        std::cout << "[DEBUG] : m_l : ";
        printVector(m_l);
        std::cout << "[DEBUG] : m_h : ";
        printVector(m_h);
#endif  // DEBUG

        bubbleSort(m_l);
        bubbleSort(m_h);

#ifdef DEBUG
        std::cout << "[DEBUG] : Print du contenu des vecteur après le tri à bulles\n";
        std::cout << "[DEBUG] : m_l : ";
        printVector(m_l);
        std::cout << "[DEBUG] : m_h : ";
        printVector(m_h);
#endif  // DEBUG

        return 1;
    } else {
        return 0;
    }
}

// Fonctions publiques diverses

void Dessin::drawAll(CImage *img) const
{
    for (unsigned int i = 0; i < getFormes().size(); i++) {
#ifdef DEBUG
        std::cout << "[DEBUG] : # of the shape in file : " << i << std::endl;
#endif  // DEBUG
        getFormeFromIdx(i)->draw(img);
#ifdef DEBUG
        std::cout << "[DEBUG] : Just drew shape #" << i << std::endl;
#endif  // DEBUG
    }
#ifdef DEBUG
    std::cout << "[DEBUG] : Drew every shape in vector" << std::endl;
#endif // DEBUG
}

void Dessin::printVector(std::vector<unsigned int> a) const
{
    for (unsigned int i = 0; i < a.size(); i++) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}

// Fonctions privées diverses
Forme *Dessin::loadForme(std::string ligne)
{
    std::vector<std::string>    infos;
    int                         taille = ligne.size();

    // On récupere le type de forme
    int pos = ligne.find(":"); // Curseur

    infos.push_back(ligne.substr(0, pos));
    ligne = ligne.substr(pos + 1, taille - pos - 1);

#ifdef DEBUG
    std::cout << "[DEBUG] : Type of shape is : " << infos[0] << std::endl;
#endif // DEBUG

    if ((infos[0] == "CERCLES")
        || (infos[0] == "DISQUES")
        || (infos[0] == "CERCLEP")) {
        // La forme en question est un cercle plein
        // Ex : DISQUES:150,150,150,GOLD,0;

#ifdef DEBUG
        std::cout << "[DEBUG] : This shape is a full circle\n";
#endif  //DEBUG

        // On récupère le reste des infos
        for (unsigned int i = 0; i < 5; i++) {  // Recuperation des 3 int
            int pos = ligne.find(",");          // Curseur
            infos.push_back(ligne.substr(0, pos));
            ligne = ligne.substr(pos + 1, taille - pos - 1);
        }

        int             x           = (int)(stoi(infos[1]) * getScalingRatio());            // x : abscisse
        int             y           = (int)(stoi(infos[2]) * getScalingRatio());            // y : ordonnée
        unsigned int    r           = (unsigned int)(stoi(infos[3]) * getScalingRatio());   // r : rayon
        std::string     colorstring = infos[4];                                             // couleur sous forme de string
        unsigned int    trsp        = (unsigned int)stoi(infos[5]);

        // ajout au vecteur recadrage de l'image
        addH(y + r);
        addH(MAX(0, y - r));
        addL(x + r);
        addL(MAX(0, x - r));

        Coord c1(x, y);

        return new Cercle_p(c1, r, colorstring, trsp); // circp; //On retourne l'adresse de l'objet
    } else if ((infos[0] == "DISQUE")
               || (infos[0] == "CERCLE")) {
        // La forme en question est un cercle simple
        // Ex : DISQUE:150,150,150,GOLD,0;

#ifdef DEBUG
        std::cout << "[DEBUG] : This shape is a simple circle\n";
#endif  //DEBUG

        // On récupère le reste des infos
        for (unsigned int i = 0; i < 5; i++) {  // Recuperation des 3 int
            int pos = ligne.find(",");          // Curseur
            infos.push_back(ligne.substr(0, pos));
            ligne = ligne.substr(pos + 1, taille - pos - 1);
        }

        int             x           = (int)(stoi(infos[1]) * getScalingRatio());            // x : abscisse
        int             y           = (int)(stoi(infos[2]) * getScalingRatio());            // y : ordonnée
        unsigned int    r           = (unsigned int)(stoi(infos[3]) * getScalingRatio());   // r : rayon
        std::string     colorstring = infos[4];                                             // couleur sous forme de string
        unsigned int    trsp        = (unsigned int)stoi(infos[5]);

        addH(y + r);
        addH(MAX(0, y - r));
        addL(x + r);
        addL(MAX(0, x - r));

        Coord c1(x, y);

        return new Cercle(c1, r, colorstring, trsp); // circ; //On retourne l'adresse de l'objet
    } else if (infos[0] == "LIGNE") {
        // La forme en question est une ligne
        // Ex : LIGNE:100,125,50,75,BLEU,0;

#ifdef DEBUG
        std::cout << "[DEBUG] : This shape is a line\n";
#endif  //DEBUG

        // On récupère le reste des infos
        for (unsigned int i = 0; i < 6; i++) {  // Recuperation des 3 int
            int pos = ligne.find(",");          // Curseur
            infos.push_back(ligne.substr(0, pos));
            ligne = ligne.substr(pos + 1, taille - pos - 1);
        }

        int             x0          = (int)(stoi(infos[1]) * getScalingRatio());
        int             y0          = (int)(stoi(infos[2]) * getScalingRatio());
        int             x1          = (int)(stoi(infos[3]) * getScalingRatio());
        int             y1          = (int)(stoi(infos[4]) * getScalingRatio());
        std::string     colorstring = infos[5];
        unsigned int    trsp        = (unsigned int)stoi(infos[6]);

        addH(y0);
        addH(y1);
        addL(x0);
        addL(x1);

        Coord   c1(x0, y0);
        Coord   c2(x1, y1);

        return new Ligne(c1, c2, colorstring, trsp); // l;
    } else if (infos[0] == "RECTANGLE") {
        // La forme en question est un rectangle simple
        // Ex : RECTANGLE:100,120,30,40,BLANC,1;

#ifdef DEBUG
        std::cout << "[DEBUG] : This shape is a simple rectangle\n";
#endif  //DEBUG

        // On récupère le reste des infos
        for (unsigned int i = 0; i < 6; i++) {  // Recuperation des 3 int
            int pos = ligne.find(",");          // Curseur
            infos.push_back(ligne.substr(0, pos));
            ligne = ligne.substr(pos + 1, taille - pos - 1);
        }

        int             x           = (int)(stoi(infos[1]) * getScalingRatio());
        int             y           = (int)(stoi(infos[2]) * getScalingRatio());
        int             longueur    = (int)(stoi(infos[3]) * getScalingRatio());
        int             hauteur     = (int)(stoi(infos[4]) * getScalingRatio());
        std::string     colorstring = infos[5];
        unsigned int    trsp        = (unsigned int)stoi(infos[6]);

        addH(y);
        addH(y + hauteur);
        addL(x);
        addL(x + longueur);

        Coord c1(x, y);

        return new Rectangle(c1, longueur, hauteur, colorstring, trsp); // rect;
    } else if ((infos[0] == "RECTANGLES")
               || (infos[0] == "RECTANGLEP")) {
        // La forme en question est un rectangle plein
        // Ex : RECTANGLES:100,120,30,40,BLANC,1;

#ifdef DEBUG
        std::cout << "[DEBUG] : This shape is a full rectangle\n";
#endif  //DEBUG

        // On récupère le reste des infos
        for (unsigned int i = 0; i < 6; i++) {  // Recuperation des 3 int
            int pos = ligne.find(",");          // Curseur
            infos.push_back(ligne.substr(0, pos));
            ligne = ligne.substr(pos + 1, taille - pos - 1);
        }

        int             x           = (int)(stoi(infos[1]) * getScalingRatio());
        int             y           = (int)(stoi(infos[2]) * getScalingRatio());
        int             longueur    = (int)(stoi(infos[3]) * getScalingRatio());
        int             hauteur     = (int)(stoi(infos[4]) * getScalingRatio());
        std::string     colorstring = infos[5];
        unsigned int    trsp        = (unsigned int)stoi(infos[6]);

        addH(y);
        addH(y + hauteur);
        addL(x);
        addL(x + longueur);

        Coord c1(x, y);

        return new Rectangle_p(c1, longueur, hauteur, colorstring, trsp); //rectp;
    } else if (infos[0] == "CARRE") {
        // La forme en question est un carre simple
        // Ex : CARRE:100,100,150,ROUGE,100;

#ifdef DEBUG
        std::cout << "[DEBUG] : This shape is a simple square\n";
#endif  //DEBUG

        // On récupère le reste des infos
        for (unsigned int i = 0; i < 5; i++) {  // Recuperation des 3 int
            int pos = ligne.find(",");          // Curseur
            infos.push_back(ligne.substr(0, pos));
            ligne = ligne.substr(pos + 1, taille - pos - 1);
        }

        int             x           = (int)(stoi(infos[1]) * getScalingRatio());
        int             y           = (int)(stoi(infos[2]) * getScalingRatio());
        unsigned int    cote        = (unsigned int)(stoi(infos[3]) * getScalingRatio());
        std::string     colorstring = infos[4];
        unsigned int    trsp        = (unsigned int)stoi(infos[5]);

        addH(y);
        addH(y + cote);
        addL(x);
        addL(x + cote);

        Coord c1(x, y);

        return new Carre(c1, cote, colorstring, trsp); // carre;
    } else if ((infos[0] == "CARRES")
               || (infos[0] == "CARREP")) {
        // La forme en question est un carre plein
        // Ex : CARREP:100,100,150,ROUGE,100;

#ifdef DEBUG
        std::cout << "[DEBUG] : This shape is a full square\n";
#endif  //DEBUG

        // On récupère le reste des infos
        for (unsigned int i = 0; i < 6; i++) {  // Recuperation des 3 int
            int pos = ligne.find(",");          // Curseur
            infos.push_back(ligne.substr(0, pos));
            ligne = ligne.substr(pos + 1, taille - pos - 1);
        }

        int             x           = (int)(stoi(infos[1]) * getScalingRatio());
        int             y           = (int)(stoi(infos[2]) * getScalingRatio());
        unsigned int    cote        = (unsigned int)(stoi(infos[3]) * getScalingRatio());
        std::string     colorstring = infos[4];
        unsigned int    trsp        = (unsigned int)stoi(infos[5]);

        addH(y);
        addH(y + cote);
        addL(x);
        addL(x + cote);

        Coord c1(x, y);

        return new Carre_p(c1, cote, colorstring, trsp); // carrep;
    } else if (infos[0] == "TRIANGLE") {
        // La forme en question est un carre plein
        // Ex : TRIANGLE:100,100,200,200,100,300,BLUE,100

#ifdef DEBUG
        std::cout << "[DEBUG] : This shape is a simple triangle\n";
#endif  //DEBUG

        // On récupère le reste des infos
        for (unsigned int i = 0; i < 8; i++) {  // Recuperation des 3 int
            int pos = ligne.find(",");          // Curseur
            infos.push_back(ligne.substr(0, pos));
            ligne = ligne.substr(pos + 1, taille - pos - 1);
        }

        int             x0          = (int)(stoi(infos[1]) * getScalingRatio());
        int             y0          = (int)(stoi(infos[2]) * getScalingRatio());
        int             x1          = (int)(stoi(infos[3]) * getScalingRatio());
        int             y1          = (int)(stoi(infos[4]) * getScalingRatio());
        int             x2          = (int)(stoi(infos[5]) * getScalingRatio());
        int             y2          = (int)(stoi(infos[6]) * getScalingRatio());
        std::string     colorstring = infos[7];
        unsigned int    trsp        = (unsigned int)stoi(infos[8]);

        Coord   c1(x0, y0);
        Coord   c2(x1, y1);
        Ligne   l(c1, c2, colorstring, trsp);
        Coord   c3(x2, y2);

        addH(MAX(MAX(y0, y1), y2));
        addH(MIN(MIN(y0, y1), y2));
        addL(MAX(MAX(x0, x1), x2));
        addL(MIN(MIN(x0, x1), x2));

        return new Triangle(l, c3); // carrep;
    } else if ((infos[0] == "POINT")
               || (infos[0] == "PIXEL")) {
        // La forme en question est un point
        // Ex : PIXEL:100,100,ROUGE,100;

#ifdef DEBUG
        std::cout << "[DEBUG] : This shape is a pixel/point\n";
#endif  //DEBUG

        // On récupère le reste des infos
        for (unsigned int i = 0; i < 4; i++) {  // Recuperation des 3 int
            int pos = ligne.find(",");          // Curseur
            infos.push_back(ligne.substr(0, pos));
            ligne = ligne.substr(pos + 1, taille - pos - 1);
        }

        int             x           = (int)(stoi(infos[1]) * getScalingRatio());
        int             y           = (int)(stoi(infos[2]) * getScalingRatio());
        std::string     colorstring = infos[3];
        unsigned int    trsp        = (unsigned int)stoi(infos[4]);

        addH(y);
        addL(x);

        Coord c1(x, y);

        return new Point(c1, colorstring, trsp); // carrep;
    } else {
        // Mauvaise entrée, on ne fait rien ?
        // Ou commentaire avec # (ou autre caractère)
        return NULL;
    }
}

void Dessin::bubbleSort(std::vector<unsigned int> &a)
{
    // Maximum à l'indice le plus fort
    // Minimum à l'indice le plus faible
    bool swapp = 1;

    while (swapp) {
        swapp = 0;

        for (unsigned int i = 0; i < a.size() - 1; i++) {
            if (a[i] > a[i + 1]) {
                a[i]        += a[i + 1];
                a[i + 1]    = a[i] - a[i + 1];
                a[i]        -= a[i + 1];

                swapp = 1;
            }
        }
    }
}

#ifndef __NOEUD_H__
#define __NOEUD_H__

#include <string>
#include <stdexcept>
#include <iostream>

class Noeud{
    private:
        char value;
        Noeud* right;
        Noeud* left;
    public:
        /*Constructeur et destructeur*/
        Noeud();
        Noeud(char);
        creationNoeud();
        ~Noeud();

        /*Méthodes pour la valeur*/
        char getValue() const;
        void setValue(const char);

        /*Méthodes pour obtenir les autres éléments*/
        void setRight(Noeud*);
        Noeud* getRightElt() const;
        bool rightEmpty() const;

        void setLeft(Noeud*);
        Noeud* getLeftElt() const;
        bool leftEmpty() const;

        /*Autre méthodes*/
        std::ostream& print(std::ostream&) const; /* Retourne simplement le contenu du noeud */
};

#endif
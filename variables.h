#ifndef __VARIABLES_H__
#define __VARIABLES_H__

#include <string>
#include <stdexcept>
#include <iostream>
#include "arbre.h"

class Arbre; // Déclaration avancée
//Dans mon cas obligatoire car Arbre et Variables ont besoin de l'un et l'autre
//Ce n'est pas une notion qu'on a vu en cours, c'est une solution que j'ai trouvé sur internet

/*Variables associe une expression (arbre) à une lettre
Cette structure de variable sera chaîné, car elle permettra aux expressions de savoir
Ce que vaut une lettre dans une formule*/
class Variables{
    private:
        char name;
        Arbre* tree;
        Variables* next;
    public:
        /*Constructeurs et destructeurs*/
        Variables();
        ~Variables();

        /*Méthodes pour la lettre associé*/
        char getName() const;
        void setName(const char);
        bool isNameNull() const;
        /*Méthodes pour l'arbre associé*/
        Arbre* getTree() const;
        void setTree(Arbre*);
        bool isTreeNull() const;
        /*Méthodes pour l'enchaînement de variables*/
        Variables* getNext() const;
        void setNext(Variables*);
        bool isNextNull() const;

        /*Autres méthodes*/
        void inputCinFormula(char=NULL,std::string="") throw(std::invalid_argument);
        bool letterExist(char) const;
        void executeAll();
        Arbre* getTreeFromLetter(char) const;
};

#endif
#ifndef __ARBRE_H__
#define __ARBRE_H__

/* L'arbre sera une méthode de "controlle" de la structure
Permettant de savoir sa composition en général*/

#include <string>
#include <stdexcept>
#include <iostream>
#include "noeud.h"
#include "variables.h"

class Variables; // Déclaration avancée
//Dans mon cas obligatoire car Arbre et Variables ont besoin de l'un et l'autre
//Ce n'est pas une notion qu'on a vu en cours, c'est une solution que j'ai trouvé sur internet

class Arbre{
    private:
        std::string inputChain;
        Noeud* startPoint;
        Variables* listVar;
    public:
        Arbre();
        Arbre(std::string,Variables*);
        ~Arbre();

        std::string getInputChain() const;
        void setInputChain(std::string);

        Noeud* getStartPoint() const;
        void setStartPoint(Noeud*);
        bool startPointEmpty() const;

        Variables* getListVar() const;

        void createTree()throw(std::invalid_argument);
        Noeud* buildRecursiveTree(std::string,int);

        /*Autres méthodes*/
        static bool isOperator(const char); //En mode statique pour qu'elle soit utilisable de partout
        std::ostream& display(std::ostream&) const;
        int parentheseOperator(std::string,int=0);
        float calcul(Noeud* =nullptr) const throw(std::invalid_argument);
        int whichOperator(char) const;
};

#endif
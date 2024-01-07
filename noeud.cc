#include "noeud.h"

using namespace std;

Noeud::Noeud(){
    this->value='0'; //Initialisé à 0, car dans l'arbre une valeure nulle correspondra à un 0
    this->right=NULL;
    this->left=NULL;
}

Noeud::Noeud(char valeur){
    this->value=valeur;
    this->right=NULL;
    this->left=NULL;
}

Noeud::~Noeud(){
    if (!this->leftEmpty()){
        delete this->getLeftElt();
    }
    if (!this->rightEmpty()){
        delete this->getRightElt();
    }
}

/*
=====================
| Valeur du noeud : |
=====================
*/
char Noeud::getValue() const{
    return this->value;
}

void Noeud::setValue(char caractere){
    this->value=caractere;
}

/*
========================
| Méthodes de gauche : |
========================
*/
bool Noeud::leftEmpty() const{
    return this->getLeftElt() == NULL;
}

Noeud* Noeud::getLeftElt() const{
    return this->left;
}

void Noeud::setLeft(Noeud* autreNoeud){
    this->left=autreNoeud;
}

/*
========================
| Méthodes de droite : |
========================
*/
bool Noeud::rightEmpty() const{
    return this->getRightElt() == NULL;
}

Noeud* Noeud::getRightElt() const{
    return this->right;
}

void Noeud::setRight(Noeud* autreNoeud){
    this->right=autreNoeud;
}

/*
=====================
| Autres méthodes : |
=====================
*/

std::ostream& Noeud::print(std::ostream& o) const{
    o << "Valeur du Noeud : " << this->getValue() <<endl;
    o << "||| Valeur de gauche ||| Valeur de droite |||" << endl;
    o << "||| ";
    if (!this->leftEmpty()) {
        o << this->getLeftElt()->getValue();
    } else {
        o << "NULL";
    }
    o << " ||| ";
    if (!this->rightEmpty()) {
        o << this->getRightElt()->getValue();
    } else {
        o << "NULL";
    }
    o << " ||| " << endl;

    if (!this->leftEmpty()) {
        this->getLeftElt()->print(o);
    }
    if (!this->rightEmpty()) {
        this->getRightElt()->print(o);
    }

    return o;
}
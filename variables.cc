#include "variables.h"
#include "arbre.h"
#include <cctype> //Pour la fonction isdigit

using namespace std;

Variables::Variables(){
    this->name=NULL;
    this->tree=NULL;
    this->next=NULL;
}

Variables::~Variables(){
    if (!this->isTreeNull()){
        delete this->tree;
    }
    if (!this->isNextNull()){
        delete this->next;
    }
}

/*Méthodes pour la Lettre*/
char Variables::getName() const{
    return this->name;
}

void Variables::setName(const char nom){
    this->name=nom;
}

bool Variables::isNameNull() const{
    return this->getName() == NULL;
}

/*Méthodes pour l'arbre associé*/
Arbre* Variables::getTree() const{
    return this->tree;
}

void Variables::setTree(Arbre* arbre){
    this->tree=arbre;
}

bool Variables::isTreeNull() const{
    return this->tree == NULL;
}

/*Méthodes pour l'enchaînement de variables*/
Variables* Variables::getNext() const{
    return this->next;
}

void Variables::setNext(Variables* var){
    this->next=var;
}

bool Variables::isNextNull() const{
    return this->next == NULL;
}

/*
===================
| Autres méthodes |
===================
*/
void Variables::inputCinFormula(char input,std::string formula) throw(std::invalid_argument){
    while (input==NULL){
        std::cout << "Entrez un nom de variable valide : ";
        cin >> input;
        if (isdigit(input) ||
        Arbre::isOperator(input) ||
        input=='(' ||
        input==')'){
            input=NULL;
        }
    }
    if (this->letterExist(input)){
        std::string errorMsg = "La lettre '" + std::to_string(input) + "' existe déjà";
        throw std::invalid_argument(errorMsg);
    } else {
        if (!this->isNameNull()){
            Variables* varTemp = new Variables;
            varTemp->setName(this->getName());
            varTemp->setNext(this->getNext());
            varTemp->setTree(this->getTree());
            this->setNext(varTemp);
        }
        this->setName(input);
        if (formula==""){
            std::cout << "Entrez une formule : ";
            cin >> formula;
        }
        Arbre* tempTree = new Arbre(formula,this);
        tempTree->createTree();
        this->setTree(tempTree);
    }
}

bool Variables::letterExist(char letter) const{
    if (this->getName()==letter){
        return true;
    } else if (!this->isNextNull()){ //Si le prochain n'est pas nul
        //On regarde si le prochain a bien cette lettre
        return this->getNext()->letterExist(letter);
    }
    //Sinon ça veut dire que la lettre n'a pas été définie :
    return false;
}

void Variables::executeAll(){
    //Retourne une chaîne de caractère calculant chaque variable
    std::cout << this->getName() << " = " <<
        this->getTree()->getInputChain() << " = " <<
        this->getTree()->calcul() << std::endl;
    if (!this->isNextNull()){ //Si il y a d'autres variables
        this->getNext()->executeAll();
    }
}

Arbre* Variables::getTreeFromLetter(char caractere) const{
    //On admet que la lettre existe bien
    if (this->getName()==caractere){ //Si le caractère est bon
        return this->getTree(); //On retourne son arbre associé
    } else { //Sinon
        return this->getNext()->getTreeFromLetter(caractere);
        //On cherche dans la variable suivante
    }
}
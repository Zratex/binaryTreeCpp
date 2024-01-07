#include "arbre.h"
#include "variables.h"
#include "noeud.h"
#include <cctype> //Pour la fonction isdigit
#include <cmath> //Pour la fonction modulo

using namespace std;

Arbre::Arbre(){
    this->inputChain="";
    this->startPoint=nullptr;
    this->listVar=nullptr;
}

Arbre::Arbre(std::string entree,Variables* listeDesVariables){
    this->inputChain=entree;
    this->startPoint=nullptr;
    this->listVar=listeDesVariables;
}

Arbre::~Arbre(){
    if (!this->startPointEmpty()){
        delete this->startPoint;
    }
}

/*
========================
| Definition Variables |
========================
*/
Variables* Arbre::getListVar() const{
    return this->listVar;
}

/*
===========================================
| Definition chaîne de charactères entrée |
===========================================
*/
std::string Arbre::getInputChain() const{
    return this->inputChain;
}

void Arbre::setInputChain(std::string entree){
    this->inputChain=entree;
}

/*
=========================
| Definition startPoint |
=========================
*/

Noeud* Arbre::getStartPoint() const{
    return this->startPoint;
}

bool Arbre::startPointEmpty() const{
    return this->startPoint == nullptr;
}

void Arbre::setStartPoint(Noeud*racine){
    this->startPoint=racine;
}

/* =====================
| Fonctions de process |
========================
 */
Noeud* Arbre::buildRecursiveTree(std::string expression,int index=0){
    /*L'index permet de savoir où est ce que l'on est dans la chaîne de caractères*/
    if (index>=this->getInputChain().size()){
        /*On arrête la récursivité quand on a atteins la limite*/
        return nullptr;
    }
    if (expression==""){
        return NULL;
    } else if (parentheseOperator(expression)!=-1){ //Si il y a une opération dans l'expression entrée
        //ça veut dire qu'il y a un opérateur majoritaire
        index=parentheseOperator(expression); //On attribut l'index à l'indice de l'opérateur
        Noeud* nouveauNoeud = new Noeud(expression[index]); //On créer un noeud avec ce caractère
        nouveauNoeud->setLeft(this->buildRecursiveTree(
            expression.substr(0,index) //Ce qui précède l'opérateur
            ));
        nouveauNoeud->setRight(this->buildRecursiveTree(
            expression.substr(index+1,expression.length()-1) //Ce qui succède l'opérateur
            ));
        return nouveauNoeud; //On retourne le noeud de l'opérateur
    } else if (expression[index]=='(' ||
        expression[index]==')'){ //Si il y a une parenthèse
        //on passe juste à l'élément suivant
        return this->buildRecursiveTree(expression,index+1);
    } else if (isdigit(expression[index])) { //Si c'est un chiffre
        Noeud* nouveauNoeud = new Noeud(expression[index]);
        //Comme notre sens de lecture dans ce programme est de gauche à droite
        if (isdigit(expression[index+1])){ //Si le prochain élément est un chiffre
            //Alors ça veut dire qu'on a un nombre
            //Donc on va simplement attribuer cet élément à droite de notre chiffre
            nouveauNoeud->setRight(this->buildRecursiveTree(expression,index+1));
        }
        return nouveauNoeud; //On retourne le chiffre
    } else { //ça veut dire que c'est une lettre
        Noeud* nouveauNoeud = new Noeud(expression[index]);
        return nouveauNoeud;
    }
}

void Arbre::createTree() throw(std::invalid_argument){
    if (this->getInputChain().empty()){
        throw std::invalid_argument("Impossible de générer une chaîne valide avec un input qui est null");
    }
    /*Génération de la structure de l'arbre*/
    this->setStartPoint(this->buildRecursiveTree(this->getInputChain()));
}

/* === Autre méthodes === */
bool Arbre::isOperator(const char o){
    return o == '+' || o == '-' || o == '/' || o == '*' || o == '%';
}

std::ostream& Arbre::display(std::ostream& o) const{
    o << "===== Affichage de l'arbre : " << this->getInputChain() << " =====" << endl;
    this->getStartPoint()->print(o);
    return o;
}

int Arbre::parentheseOperator(std::string input,int skip){
    //Cherche l'opérateur majoritaire de cette parenthèse
    //Puis retourne son index
    if (input==""){ //Si la chaîne est vide :
        return -1;
    }
    int parentheseCount=0;
    int index=-1; //Skip correspond au nombre de fois qu'on a skip un caractère dû aux parenthèses
    for (char& caractere : input){
        index+=1;
        if (caractere=='('){
            parentheseCount+=1;
        } else if (caractere==')'){
            parentheseCount-=1;
        } else if ((this->isOperator(caractere))&&(parentheseCount==0)){
            return index+skip;
        }
    }
    //Si on a pas trouvé d'opérateur après le parcours
    //cela veut peut être dire qu'on est à l'intérieur d'une parenthèse :
    if (input[0]=='('){ //Si le premier élément est une parenthèse ouvrante
        if (input[input.length()-1]==')'){ //Si le dernier élément est aussi une parenthèse fermante
            //On relance la fonction avec comme entrée la même chose sans les parenthèses :
            return this->parentheseOperator(input.substr(1,input.length()-2),1);
            //2 car on enlève 2 caractères
        } else {
            //Sinon, on relance la fonction avec juste une parenthèse ouvrante en moins :
            return this->parentheseOperator(input.substr(1),2);
            //C'est possible dans ce genre de cas :
            // "(3-(5*97)))" La dernière parenthèse peut être absente à cause
            //Du fait que ce soit juste la droite de l'expression qui soit envoyé pour traiter la partie de droite d'un opérateur
        }
    } else if (input[input.length()-1]==')') {
        return this->parentheseOperator(input.substr(0,input.length()-2),1);
    }
    //Si il n'y a vraiment pas d'opérateur :
    return -1;
}

float Arbre::calcul(Noeud* NoeudEntree) const throw(std::invalid_argument){
    if (NoeudEntree==nullptr){
        NoeudEntree=this->getStartPoint();
    }
    if (this->isOperator(NoeudEntree->getValue())){ //Si c'est un opérateur
        float RightValue = this->calcul(NoeudEntree->getRightElt()); //On calcul l'élément de droite puis on le sauvegarde
        float LeftValue = this->calcul(NoeudEntree->getLeftElt()); //Pareil à gauche
        switch (this->whichOperator(NoeudEntree->getValue())){
            /*Première fois que j'utilise un switch case
            Je ne sais pas si j'ai besoin du break, par précautions je le met*/
            case 1: //Addition
                return LeftValue+RightValue;
                break;
            case 2: //Soustraction
                return LeftValue-RightValue;
                break;
            case 3: //Multiplication
                return LeftValue*RightValue;
                break;
            case 4: //Division
                if (RightValue==0){
                    std::string errorMsg = std::to_string(LeftValue) + "/" + std::to_string(RightValue) + " : Division par 0 impossible";
                    throw std::invalid_argument(errorMsg);
                } else {
                    return LeftValue/RightValue;
                }
                break;
            case 5: //Modulo
                if (RightValue==0){
                    std::string errorMsg = std::to_string(LeftValue) + "%" + std::to_string(RightValue) + " : Division par 0 impossible";
                    throw std::invalid_argument(errorMsg);
                } else {
                    float temp = fmod(LeftValue,RightValue); //Modulo qu'on met en float une fois calculé
                    return temp;
                }
                break;
        }
    } else if (isdigit(NoeudEntree->getValue())){ //Si c'est un chiffre
        if (!NoeudEntree->rightEmpty()){ //Si il contient aussi un chiffre
            std::string temp = NoeudEntree->getValue() +
                std::to_string(this->calcul(NoeudEntree->getRightElt()));
            return std::stof(temp); //On convertit notre chaîne de nombre
        } else {
            //On convertit le caractère en float
            float temp = NoeudEntree->getValue() - '0';
            //-0 pour avoir un nombre constant depuis la table ASCII
            //Techniquement provenant de ce post : https://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c
            return temp;
        }
    } else { //Il ne devrait rester que les lettres
        if (this->getListVar()->letterExist(NoeudEntree->getValue())){ //Si la lettre existe
            //On récupère la valeur de la lettre :
            return this->getListVar()->getTreeFromLetter(NoeudEntree->getValue())->calcul();
        }
    }
}

int Arbre::whichOperator(char Loperator) const{
    //Retourne quel est l'opérateur entré
    if (Loperator=='+'){
        return 1;
    } else if (Loperator=='-'){
        return 2;
    } else if (Loperator=='*'){
        return 3;
    } else if (Loperator=='/'){
        return 4;
    } else if (Loperator=='%'){
        return 5;
    }
}
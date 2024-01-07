#include "variables.h"
#include <iostream>
using namespace std;

int main() {
    Variables var;
    var.inputCinFormula('a',"((2*59)+(3-(5*97)))");
    var.inputCinFormula('b',"((66*0)%3)");
    var.inputCinFormula('e',"699");
    var.inputCinFormula('k',"((a+9)*(686/8))");
    var.inputCinFormula('d',"((k*k)-(5*b))");
    var.inputCinFormula('z',"((b-(d/e))+8)");
    var.executeAll();
}
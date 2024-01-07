# Projet Dev Efficace
Réalisé par **Bryan Fouliard** pour le projet de développement efficace en S3 (C++) du BUT Informatique de Reims.
## Compilation
Le projet a été réalisé sur Windows. Il faudra donc manuellement recompiler le projet pour qu'il soit executable sur une machine en base UNIX.

Ce qui a été ajouté dans le makefile pour fonctionner sur Windows, est que devant chaque ligne du `g++` pour tourner sur Windows `-std=gnu++11` (ce qui explique la présence du fichier `a.exe`). Lors du rendu de ce dépôt, ce paramètre a été retiré pour correctement fonctionner sur Mac/Linux lors de la prochaine compilation.

## Implémentation
Le projet a été implémenté sous une forme d'arbre binaire. Un arbre binaire est donc l'expression mathématique, et chaque élément est représenté sous forme de noeuds.
La classe `Variables` a été implémentée pour prendre en compte les variables du projet, et faciliter l'entrée du prompt. Sa structuration de données est une pile chaînée, associant une lettre à un arbre.
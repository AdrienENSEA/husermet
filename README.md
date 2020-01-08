# Projet Logiciel Transversal

## USE
```console
$ git clone https://github.com/Solanna13/husermet
$ cd husermet
$ mkdir build
$ cd build
$ cmake ..
$ make
```
S'il y a des problèmes avec OpenGL, il faut désactiver l'accélération 3D dans les paramètres d’affichage de la VM. <br>
<br>

## 1.1 Présentation générale
Prise en main de c++
```console
$ ./../bin/client hello
```

## 1.Final Description et Conception des états
Diagramme de classes d'état
Tests unitaires et Couverture de code
```console
$ make unittest
$ make code-coverage
```

## 2.1 Description et Conception du Rendu
Diagramme de classes pour le rendu
Affichage automatique de différents états
```console
$ ./../bin/client render
```

## 2.2 Règles de changement d’états et moteur de jeu
Diagramme de classes pour le moteur de jeu <br>
Comment jouer ?
1. Choisir une attaque pour le premier Pokémon avec la souris
2. Choisir une cible avec les flèches droite ou gauche
3. Faire de même pour le deuxième Pokémon <br>
On peut aussi choisir de changer de Pokémon en cliquant sur le Pokémon à échanger
On peut annuler son choix tant que l'on a pas choisi l'action des deux Pokémon. Pour cela il suffit de cliquer sur le Pokémon dont on veut choisir l'action.
```console
$ ./../bin/client engine
```

## 2.Final Intelligence Artificielle Random
Intelligence Artificielle choisissant ses actions au hasard
```console
$ ./../bin/client random_ai
```

## 3.1 Intelligence Artificielle Heuristic
Intelligence Artificielle choisissant ses actions de manière à maximiser les dégâts
```console
$ ./../bin/client heuristic_ai
```

## 3.Final Intelligence Artificielle avancée
Intelligence Artificielle choisissant ses actions de manière à maximiser les dégâts sur plusieurs tours
```console
$ ./../bin/client deep_ai
```
## 4.1 Modularisation
Moteur de jeu et moteur de rendu dans deux thread différents
```console
$ ./../bin/client thread
```
Enregistrement des commandes durant 5 tours de jeu <br>
Exécution des commandes enregistrées
```console
$ ./../bin/server record
$ ./../bin/client play
```
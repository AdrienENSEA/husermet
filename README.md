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
Diagramme de classes pour le moteur de jeu
Comment jouer ? <br>
1. Choisir une attaque pour le premier Pokémon avec la souris
2. Choisir une cible avec les flèches droite ou gauche
3. Faire de même pour le deuxième Pokémon
On peut aussi choisir de changer de Pokémon en cliquant sur le Pokémon à échanger
```console
$ ./../bin/client engine
```

## 2.Final Intelligence Artificielle Random
```console
$ ./../bin/client
```

## 3.1 Intelligence Artificielle Heuristic
```console
$ ./../bin/client
```

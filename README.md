# plt

USE <br/>
$ git clone https://github.com/Solanna13/plt <br/>
$ cd plt <br/>
$ mkdir build <br/>
$ cd build <br/>
$ cmake .. <br/>
$ make <br/>
$ cd ../bin <br/>
$ ./client render<br/>
<br>
S'il y a des problèmes avec OpenGL, il faut désactiver l'accélération 3D dans les paramètres d’affichage de la VM. <br>
<br>
Pour exécuter les tests unitaires : 
$ make unittest depuis le dossier build <br/>

Pour vérifier la couverture de code : 
$ make code-coverage depuis le dossier build <br/>

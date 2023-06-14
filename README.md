## DESCRIPTION:

Vous êtes un cycliste qui s'est perdu dans un canyon et vous devez vous en échapper sans tomber de votre
fidèle destrier.

Le mode boss est réglé de manière à être suffisament simple pour suivre l'histoire en même temps.

Il est conseillé de jouer sur un terminal en plein écran pour un meilleure expériences.

## COMPILATION:

Pour lancer le jeu sans aucune option : `make run`
Pour lancer le mode histoire : `make run boss=1`
Pour lancer le mode full-option : `make run ap=1 rainbow=1 debug=1`

 ## OPTIONS: à bien rajouter sans espaces
Il est conseillé de lancer la compilation avec une option à la fois pour commencer avant de les ajouter.
Il est possible d'ajouter les options suivantes a la suite de make run:

- `debug=1`   | Permets d'obtenir des informations sur le jeu non utiles au joueur
- `rainbow=1` | Mets un peu de couleur au canyon
- `ap=1`      | Active l'autopilote
- `boss=1`    | Mode qui désactive les précédentes si activées et lance un mode "Histoire"

## VARIABLES:

Il est également possible de modifier certaines variables de départ du jeu:

- `cn=int`    | Modifie la taille initiale du canyon (doit être supérieur ou égal à 3),                   par défaut cn=20
- `hz=int`    | Permets de modifier le taux de rafraichissement (doit être supérieur ou égal à 3),        par défaut sinon hz=50
- `border=c`  | Permets de modifier le caractère utilisé pour les murs du canyon (à mettre sans "" ni '') par défaut border=*
- `skin=c`    | De même pour changer le caractère du personnage                                           par défaut skin=T

## TO-DOS

Voici quelques améliorations que nous aurions voulu ajouter:

- Une musique de fond pendant le jeu mais nécessite une librairie externe
- Un mode adapté pour une configuration de terminal en portrait type "smartphones"
- Une liste des scores mais un peu trop compliqué avec le fait de pouvoir changer la vitesse etc il aurait fallu des catégories
- Un multijoueur 
- Des obstacles aléatoires et autres évenements pour le mode boss 

Auteurs : Chambe Vivien et Adjamé Rozen


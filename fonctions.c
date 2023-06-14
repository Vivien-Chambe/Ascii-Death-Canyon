#include <ncurses.h>
#include <stdlib.h>
#include "fonctions.h"

// variables globales
int perso_x = 0;//pour l'initialiser au centre ensuite
int level[255];  //tableau contenant les indices gauche du canyon 
int canyon_size = CANYON_SIZE; // On place CANYON_SIZE dans une variable car on va la faire décroitre
int speed_modifier = 0;  // pour la vitesse


void init_level(){
    // Spec : Renvoie la liste level avec l'initialisation en canyon ligne droite
    //E,S : none, none
    for(int i = 0; i<LINES;i++){
        level[i] = (COLS/2)-(canyon_size/2); // le debut du canyon est au centre en ligne droite
    }
} 

int new_line(){
    // Spec : genere et renvoie aleatoirement la coordonnee gauche suivante du canyon
    // E: none
    // S: int coord_gauche
    int coord_gauche;
    int num = rand() % 3 + 1; //on recupere un nombre aleatoire entre 1 et 3
    if(num == 1){coord_gauche = level[0] - 1;} //on cree la ligne a gauche
    else if(num == 2){coord_gauche = level[0];} //on cree la ligne au centre
    else{coord_gauche = level[0]+1;} //on cree la ligne a droite
    // pour ne pas depasser de l'ecran :
    if(coord_gauche < 0){coord_gauche++;}  //si on est tout a gauche on decale a droite 
    #ifdef BOSS_RUSH
    else if(coord_gauche + canyon_size +1 >= COLS-50){coord_gauche--;}//si on est a la barre du boss on decale a gauche
    #else
    else if(coord_gauche + canyon_size +1 >= COLS){coord_gauche--;} //si on est tout a droite on decale a gauche
    #endif
    return coord_gauche;
}


void update_level(){
    // Spec : effectue le defilement d'une ligne du tableau et en ajoute une nouvelle aleatoire
    // E,S : none , none
    for(int i = LINES ; i>0;i--){
        level[i] = level[i-1]; // on descend tout les coordonnes du tableaux de une pour le defilement
    }
    level[0] = new_line(); // et on met la nouvelle ligne au debut du tableau
}

void show_level(){
    // Spec : affiche le canyon a l'ecran / ce en couleur si rainbow active
    // E,S : none, none 
    for(int i = 0;i < LINES; i++){
            #ifdef RAINBOW
            int random = rand()%7+1;  //pour chaque ligne on affiche une couleur de canyon differente aleatoire
            attron(COLOR_PAIR(random));
            #endif
            mvprintw(i,level[i],BORDER); //affiche la colonne gauche du canyon
            mvprintw(i,level[i] + canyon_size +1,BORDER); //puis la droite. Le +1 sert à ne pas compter la derniere case du canyon comme un mur mais avoir réellement canyon_size espaces.
            #ifdef RAINBOW
            attroff(COLOR_PAIR(random));
            #endif
    }
}

int check_collision(){
    // Spec : renvoie la position de l'impact si il y en a un ou 0
    // E : none
    // S : int 0 ou x =la position de l'impact
    int relative_pos = COLS/2+perso_x;  //trouve la position relative du joueur
    if(relative_pos == level[LINES-5] || relative_pos == (level[LINES-5]+canyon_size)){ // check si on touche un des deux murs du canyon
        return COLS/2+perso_x;  //si oui renvoie cette position
    }
    else{return 0;} //sinon renvoie 0
}

void update_perso_position(int c){
    // Spec : augmente ou baisse l'indice de position du joueur selon les entrees utilisateurs
    // E : int c entre par l'utilisateur
    // S : none
    switch (c)
    {
    case KEY_LEFT: //si le joueur a appuyer su la fleche de gauche
        perso_x --;
        break;
    case KEY_RIGHT: //si le joueur a appuyer su la fleche de droite
        perso_x ++;
        break;
    
    default:
        break;
    }
}


void show_perso(int spedd){
    #ifdef RAINBOW
    attron(COLOR_PAIR(spedd%7+1));
    #endif
    int relative_pos = COLS/2+perso_x;// Si perso_x est à 0 alors avec cette formule ça le place au centre donc peu importe la taille de la fenetre c'est au milieu.
    mvprintw(LINES-5,relative_pos,SKIN);
    #ifdef RAINBOW
    attroff(COLOR_PAIR(spedd%7+1));
    #endif
}

// Jusqu'à canyon_size = 3 l'autopilot fonctionne
void autopilot(){
    // Spec : calcule et met a jour la position que l'autopilot doit adopter
    // E,S : none , none
    int relative_pos = COLS/2+perso_x; //Si perso_x est à 0 alors avec cette formule on le place au centre
    if(relative_pos - level[LINES-6] <= canyon_size/2){
        perso_x++;
    }
    else{perso_x--;}
}

int update_score(int score){
    // Spec : augmente le score de 1
    // E : int score 
    // S : none
    return score + 1;
}

void print_score(int score){
    // Spec : affiche le score a l'ecran
    // E : int score 
    // S : none
    mvprintw(0,0,"Score  : %d",score);
}

int adjust_difficulty(int score){
    // Spec : met a jour a la difficulte en  fonction du score (taille du canyon/vitesse du joueur)
    // E : none
    // S : int speed_modifier 
    if(score%500 == 0 && canyon_size>4){ //tant que la taille du canyon est plus grande que 4 on la diminue tout les 500 de scores
        canyon_size--;
    }
    if(score%200 == 0 && speed_modifier < 10 && HZ_RATE*1000-speed_modifier*3000>3000){ //tout les 200 et tant que speed est inferieur a 10 et que l'on reste a une vitesse raisonnable on augmente spedd
        speed_modifier++;
    }
    return speed_modifier;
}

//fonction de debug 
void debug(int pablo_health){
    // Spec : affiche les informations de debug 
    // E,S : none , none
    mvprintw(1,0,"Canyon size : %d",canyon_size); //la taille actuelle du canyon
    mvprintw(2,0,"Spedd Modifier : %d",speed_modifier); // l'indice de speed actuel
    mvprintw(3,0,"LINES : %d COLS: %d",LINES,COLS); //le nombre de lignes et colonnes
    mvprintw(4,0,"GaucheC : %d DroiteC: %d",level[0],level[0]+canyon_size+1); // les coord de gauche et droite du canyon
    mvprintw(5,0,"Pablo Health : %d",pablo_health); // l'indice de speed actuel


}



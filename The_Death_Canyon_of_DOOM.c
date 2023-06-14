#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "fonctions.h"
#include "ascii_art.h"
#include "boss.h"



int main(){
    srand(time(NULL)); //Nous initiallisons la seed avec time car il n'est pas necessaire dans notre jeu d'avoir un meilleur prng 
    //(nous souhaitons juste que le joueur n'ait pas l'impression d'avoir les meme seed en boucles)
    initscr(); //Initialise la fenetre de "travail"
    keypad(stdscr, true); //Autorise les entrées utilisateurs
    noecho(); //Désactive l'affichage des entrées utilisateur
    cbreak(); //Désactive le bloquage de la prise en compte des entrees utilisateurs
    color_creation(); //met en route l'utilisation des couleurs
    start_screen(); // affiche le menu d'acceuil
    curs_set(0); //Désactive l'affichage du curseur
    timeout(0);  // N'attends pas un getch() pour avancer
    
    int play = 1; // variables pour l'etat de la partie
    int c;  // variable pour recuperer les entrees utilisateurs pendant le jeu 
    int score = 1;
    int pablo_health = 10; // definit la vie initiale de Pablo
    int canyon_size = CANYON_SIZE;
    
    int speed_modifier = adjust_difficulty(score); // l'indice de vittesse
    
    int cpt=1;
    //Initialisation
    show_perso(speed_modifier); // affiche le cycliste a sa position initiale
    init_level(); // affiche les premiers murs du canyon (ligne droite) en fonction de la taille du canyon
    //
    //Boucle du jeu
    while (play == 1){
        c =  getch();
        if(c == 'q'){play = 0;break;} //on verifie si le joueur souhaite quitter le jeu et si oui on quiite

        // Update le jeu (Coordonnées)
        #ifdef AUTOPILOT 
        autopilot(); //mise en route de l'autopilot qui calcule la position suivante du cycliste
        #else 
        else{update_perso_position(c);} //sinon met a jour les coordonnees du cycliste en fonction des entrees du joueur
        #endif
        update_level(); //calcule et met a jour le tableau contenant le canyon
        #ifndef BOSS_RUSH
        speed_modifier = adjust_difficulty(score); //met a jour l'indice de vitesse
        #endif
        erase();  //efface la fenetre
        //

        //Affichage 
        
        
        score = update_score(score); // augmente le score
        print_score(score); //affiche le score actuel du joueur
        show_perso(speed_modifier); //affiche la nouvelle position du joueur 
        show_level(); //affiche le nouveau canyon
        
        #ifdef BOSS_RUSH
        boss_screen(); //affiche la bordure separant pablo du canyon

        //animation de Pablo
        if (score == 1950 ){cpt =-1;} //on l'arrete des qu'il est mort
        if (score%10 ==0 && cpt>=0 ){cpt = 0;} //frame 1
        if (score%20 ==0 && cpt>=0){cpt = 1;} //frame 2
        if (cpt ==1 ){print_Pablo();}  //frame 1
        else{print_Pablo2();} //frame 2

        print_pablo_health(pablo_health); //affiche la vie de Pablo
        print_pablo_dialogue(score); //affiche la phrase de dialogue de Pablo
        
        pablo_health = pablo_health - events(score,pablo_health,canyon_size); //on change la vie de Pablo si on est au bon score
       
        if(score>10300){play=0;break;} //finit le jeu apres avoir atteint un certain score
        #endif
        
    
        #ifdef DEBUG
        debug(pablo_health,events(score,pablo_health,canyon_size)); //affiche les informations de debug
        #endif

        //Fin de jeu
        if(check_collision()!=0){
            timeout(-1);
            play = 0;
            death_message(score); //affiche la fin du jeu
            refresh(); //affiche les changements sur l'ecran
            sleep(3);
            break;
        }
        
        //
        refresh(); //affiche les changements sur l'ecran
        usleep(HZ_RATE*1000 - speed_modifier*3000);
        //
    }
    getch();
    endwin();

    return 0;

}
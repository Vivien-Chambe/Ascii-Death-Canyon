#include <ncurses.h>

#include "boss.h"
#include "fonctions.h"

void boss_screen(){
    // Spec : initialise la bordure separant Pablo du canyon
    // E,S : none , none
    int nouvelle_bordure = COLS-50;
    for(int i = 0; i<=LINES;i++){
        mvprintw(i,nouvelle_bordure,"|");
    }
}

void color_burnt_pablo(){
    // Spec : change les couleurs pour faire Pablo brule 
    // E,S : none , none

    start_color();
    use_default_colors();
    init_pair(1,COLOR_MAGENTA,-1);
    init_pair(2,COLOR_RED,-1);
    init_pair(3,COLOR_YELLOW,-1);
    init_pair(4,COLOR_CYAN,-1);
    init_pair(5,COLOR_BLUE,-1);
    init_pair(6,COLOR_WHITE,-1);
    init_pair(7,COLOR_GREEN,-1);
}


void print_pablo_health(int pablo_health){
    // Spec : affiche la vie actuelle de Pablo
    // E : int pablo_health
    // S : none
    mvprintw(30,COLS-28,"[");
    mvprintw(30,COLS-18,"]");
    attron(COLOR_PAIR(7));
    for(int i = 1;i<pablo_health;i++){
        mvprintw(30,COLS-28+i,"#");
    }
    attroff(COLOR_PAIR(7));
}
int events(int score,int pablo_health,int canyon_size){
    // Spec : renvoie les degats inflige a Pablo par rapport au score du joueur
    // E : int score,int pablo_health,int canyon_size
    // S : int value
    if(pablo_health>0){
        if(score==680){return 2;} //se prend la balle
        else if(score==780){return 2;} //boit de la tequilla
        else if(score==1170){return 2;} // se prend le caillou
        else if(score==1700){return 4;} // se prend la foudre
        else{return 0;} //autrement
    }
    else{return 0;}

}




void print_pablo_dialogue(int score){
    // Spec : affiche les dialogues de Pablo et si necessaire fait l'interaction souhaite
    // E : int score
    // S : none

    //texte intro 
    if(score>=100 && score <= 150){mvprintw(33,COLS-28,"Hola amigo!");}
    else if (score>=150 && score <= 200){mvprintw(33,COLS-35,"Bienvenue dans mon canyon");}
    else if (score>=200 && score <= 250){mvprintw(33,COLS-29,"Je suis Pablo");}
         
    else if (score>=300 && score <= 350){mvprintw(33,COLS-36,"On dirait que tu t'es perdu");}
    else if (score>=350 && score <= 400){mvprintw(33,COLS-35,"Comment es tu arrivé là???");}
    else if (score>=400 && score <= 450){mvprintw(33,COLS-40,"Tu ferais mieux de faire demi tour");}
    //texte menace 
    else if (score>=600 && score <= 650){mvprintw(33,COLS-36,"Tu oses défier mon autorité?");}
    //texte balle
    else if (score>=680 && score <= 720){attron(COLOR_PAIR(2)); mvprintw(14,COLS-40,"*PAN*"); attroff(COLOR_PAIR(2));}//-2 hp  joueur qui tire sur Pablo  
    //texte tequilla
    else if (score>=700 && score <= 750){mvprintw(33,COLS-27,"AAARGH!");} 
    else if (score>=750 && score <= 780){mvprintw(33,COLS-31,"Comment oses tu?");}
    else if (score>=780 && score <= 820){mvprintw(33,COLS-34,"*Boit un shot de tequila*");} // -2 hp
    else if (score>=820 && score <= 860){mvprintw(33,COLS-30,"AAAH C'EST PIRE");}
    //texte eboulement
    else if (score>=870 && score <= 920){mvprintw(33,COLS-32,"Tu vas le regretter");}
    else if (score>=920 && score <= 960){mvprintw(33,COLS-31,"Le canyon m'obéit!!");}
    else if (score>=960 && score <= 1010){mvprintw(33,COLS-35,"Tout va s'ebouler ahahaha");}
    else if (score>=1010 && score <= 1060){mvprintw(33,COLS-33,"*Retrecit le canyon*");}
    //texte caillou
    else if (score>=1170 && score <= 1220){mvprintw(33,COLS-35,"AH j'ai pris un caillou"); mvprintw(34,COLS-29,"sur la tête");} //-2  hp
    else if (score>=1220 && score <= 1290){mvprintw(33,COLS-37,"C'est pas moi l'intrus c'est lui!!");}
    else if (score>=1340 && score <= 1400){mvprintw(33,COLS-43,"Ce n'est pas grave je t'aurais quand meme");}
    //texte eclair
    else if (score>=1400 && score <= 1450){mvprintw(LINES/2,(COLS-50)/2,"*Le ciel s'assombrit*");}
    else if (score>=1500 && score <= 1550){mvprintw(33,COLS-38,"Tu crois que j'ai peur de la météo?");}
    else if (score>=1550 && score <= 1600){mvprintw(33,COLS-28,"Au contraire");}
    else if (score>=1700 && score <= 1730){mvprintw(LINES/2,(COLS-50)/2,"*La foudre frappe Pablo*");} //-4 hp
    else if (score>=1730 && score <= 1800){color_burnt_pablo(); mvprintw(33,COLS-29,"!!!AAAAAAH!!!!");} //On change les couleurs de Pablo il devient bruler
    else if (score>=1800 && score <= 1850){mvprintw(33,COLS-29,"Bien joué mais...");}
    else if (score>=1850 && score <= 1950){mvprintw(33,COLS-28,"I'LL BE BACK");}
    else if (score>=1950 && score <= 2000){mvprintw(33,COLS-40,"*Le corps de Pablo s'arrete de bouger*");}
    else if (score>=2000 && score <= 2050){mvprintw(33,COLS-40,"Ses graines ont disparu il a du fuir...");}
    else if (score>=2050 && score <= 10000){
        autopilot(); //des que le jeu est fini ont declenche l'autopilot
        win_Pablo_message(); //affiche le message de victoire contre Pablo
        mvprintw((LINES/2) + 9,(COLS-46)/2 + 3,"Press q to quit");
        }

    
    else if (score>=10000 && score <= 10050){mvprintw(33,COLS-40,"Que fais tu encore dans ce canyon?");}
    else if (score>=10050 && score <= 10300){mvprintw(33,COLS-38,"Il n'y a plus rien a voir ici ");}
}



void win_Pablo_message(){
    // Spec : affiche l'ecran de fin du jeu
    // E,S : none , none
    
    mvprintw((LINES/2),((COLS-49)/2),  "         ## #           ");
    mvprintw((LINES/2)+1,((COLS-49)/2),"         ####         ");
    mvprintw((LINES/2)+2,((COLS-49)/2),"_________##_________ ");
    mvprintw((LINES/2)+3,((COLS-49)/2),"|                    |");
    mvprintw((LINES/2)+4,((COLS-49)/2),"|    YOU WIN!        |");
    mvprintw((LINES/2)+5,((COLS-49)/2),"|                    |");
    mvprintw((LINES/2)+6,((COLS-49)/2),"| You defeated Pablo |");
    mvprintw((LINES/2)+7,((COLS-49)/2),"|____________________|");
}


void print_Pablo(){
    // Spec : affiche la premiere frame de Pablo dans sa zone
    // E,S : none , none

    mvprintw(4, COLS-26,"PABLO");
    //Big Cactus
    attron(COLOR_PAIR(2));
    mvprintw(6, COLS-40,"             / '-'  /");
    mvprintw(7, COLS-40,"            ;       ;");
    mvprintw(8, COLS-40,"         /'-|       |-' |");
    mvprintw(9, COLS-40,"        |   |_______P   |");
    mvprintw(10, COLS-40,"        |   '-------'   /");
    mvprintw(11, COLS-40,"         '.___.....___.'");
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(3));
    mvprintw(12, COLS-40,"             | ;  : ;|");
    mvprintw(13, COLS-40,"            _|;__;__.|_");
    attroff(COLOR_PAIR(3));
    attron(COLOR_PAIR(1));
    mvprintw(14, COLS-40,"           |     Y     |");
    mvprintw(15, COLS-40,"           |___.'^'.___|");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(3));
    mvprintw(16, COLS-40,"             |_  ;  _|      .--.");
    mvprintw(17, COLS-40," .--.        {^^^^^^^}     /;   |");
    mvprintw(18, COLS-40,"/   ;|       {       }    | ;   |");
    mvprintw(19, COLS-40,"|  ; |       {       }    |     |");
    mvprintw(20, COLS-40,"|;   |       ;-.__.'|    |:  ; |");
    mvprintw(21, COLS-40,"| ;  |      |;  ;   |_____/ ;  |");
    mvprintw(22, COLS-40,"|   '.'-----'      ' -_   .'   /");
    mvprintw(23, COLS-40,"|  '.   - _  ' ;  ;  _  -    .'");
    mvprintw(24, COLS-40," '.   -     - ;  ;   .------`");
    mvprintw(25,COLS-40,"   `--------.      ; |");
    mvprintw(26, COLS-40,"            |;  ,    |");
    mvprintw(27, COLS-40,"            |;  ,    |");
    attroff(COLOR_PAIR(3));
}
void print_Pablo2(){
    // Spec : affiche la deuxieme frame de Pablo dans sa zone
    // E,S : none , none

    mvprintw(4, COLS-26,"PABLO");
    //Big Cactus
    attron(COLOR_PAIR(2));
    mvprintw(6, COLS-40,"             / '-'  /");
    mvprintw(7, COLS-40,"            ;       ;");
    mvprintw(8, COLS-40,"         /'-|       |-' |");
    mvprintw(9, COLS-40,"        |   |_______P   |");
    mvprintw(10, COLS-40,"        |   '-------'   /");
    mvprintw(11, COLS-40,"         '.___.....___.'");
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(3));
    mvprintw(12, COLS-40,"             | ;  : ;|");
    mvprintw(13, COLS-40,"            _|;__;__.|_");
    attroff(COLOR_PAIR(3));
    attron(COLOR_PAIR(1));
    mvprintw(14, COLS-40,"           |     Y     |");
    mvprintw(15, COLS-40,"           |___.'^'.___|");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(3));
    mvprintw(16, COLS-40,"             |_  ;  _|   .--.");
    mvprintw(17, COLS-40,"    .--.     {^^^^^^^}  /;   |");
    mvprintw(18, COLS-40,"  /    ;|    {       }  | ;   |");
    mvprintw(19, COLS-40," | ;   |     {       }   |     |");
    mvprintw(20, COLS-40," |;   |      ;-.__.'|     |:  ; |");
    mvprintw(21, COLS-40,"| ;  |      |;  ;   |_____/ ;  |");
    mvprintw(22, COLS-40,"|   '.'-----'      ' -_   .'   /");
    mvprintw(23, COLS-40,"|  '.   - _  ' ;  ;  _  -    .'");
    mvprintw(24, COLS-40," '.   -     - ;  ;   .------`");
    mvprintw(25,COLS-40,"   `--------.      ; |");
    mvprintw(26, COLS-40,"            |;  ,    |");
    mvprintw(27, COLS-40,"            |;  ,    |");
    attroff(COLOR_PAIR(3));
}


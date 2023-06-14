#define NBR_PHRASES 3


void boss_screen(); //initialise la bordure separant Pablo du canyon

void color_burnt_pablo(); //change la definition des couleurs pour bruler Pablo

void print_pablo_health(int pablo_health); //affiche la vie actuelle de Pablo

void print_pablo_dialogue(); //affiche la ligne de dialogue de Pablo en fonction du score

int events(int score,int pablo_health,int canyon_size);

void win_Pablo_message(); //affiche le message de fin de jeu

void print_Pablo(); //affiche la premiere frame de Pablo dans sa zone

void print_Pablo2();//affiche la deuxieme frame de Pablo dans sa zone

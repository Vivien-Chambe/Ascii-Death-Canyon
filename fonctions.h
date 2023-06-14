

#ifdef BOSS_RUSH //Si on est en mod boss on désactive l'autopilot et les paramètres modifiés par l'utilisateur
#undef AUTOPILOT
#undef HERTZ_RATE
#undef CANYON_SIZE
#undef BORDER
#endif

#ifndef SKIN
#define SKIN "T"  // Perso Character
#endif

#ifndef BORDER
#define BORDER "*"   // Border Character
#endif

#ifndef CANYON_SIZE
#define CANYON_SIZE 20 // Border Size
#endif

#ifndef HZ_RATE
#define HZ_RATE 50 // Speed Rate
#endif


void init_level();// Crée un couloir droit pour le début de partie

void update_perso_position();// Mets à jour la position du perso en fonction de l'entrée de l'utilisateur

void autopilot();// Mode démo permettant un défilement continue sans erreur

void show_perso(int spedd);// Affiche la position du personnage en fonction de sa position relative

int new_line();//Crée la nouvelle ligne du haut à partir de la précédente en allant a droite/a gauche ou tout droit

void update_level();// Décale toutes les lignes pour créer un défilement et ajoute une nouvelle ligne grâce a new_line

void show_level();// Print le niveau de haut en bas en parcourant le tableau level 

int check_collision();// Vérifie à chaque "frame" si le joueur est en collision avec le bord gauche|droit du canyon

void print_score(int score);// Indique le score en temps réel au joueur

int update_score(int score);// Mets à jour le score

int adjust_difficulty();// Augmente la difficulté en réduisant la taille du canyon jusqu'à un minimum de 4, et la vitesse de défilement du canyon


//fonction de Debug
void debug();// Fonction qui affiche des informations nécessaires au debug (Taille du canyon,vitesse,nombre de lignes|colonnes)
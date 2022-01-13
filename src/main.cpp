/******* Autheurs: *******
Julien Paris - M2BB
Alice Laigle - M2BB
*************************/

#include "../Classes/centreRadio.hpp"

int main(int argc, const char* argv[]){
    
    if(argc != 2){ //vérification de la présence de l'argument lors de l'appel du script
        std::cerr << "[UsageError] USAGE: ./main <chemin d'accès vers fichier de sauvegarde>" << std::endl;
        return 1;
    }

    t_Centre_Radio* myCenter = new t_Centre_Radio(argv[1]); // chargement du centre radio
    t_Praticien_ptr myUsr = myCenter->login(); //login et récupération du profil praticien
    myCenter->affiche_entete(); //premier affichage de l'en-tête après connexion
    myCenter->menu(myUsr); // affichage du menu

    myCenter->sauvegarder_etat(argv[1]); // sauvegarde de l'état du centre radio à la fin de l'exécution

    std::cout << "[ExitSuccess] EXIT" << std::endl;
    return 0;
}
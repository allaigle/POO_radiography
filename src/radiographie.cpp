/******* Auteurs: *******
Julien Paris - M2BB
Alice Laigle - M2BB
*************************/

#include "../Classes/centreRadio.hpp"

//********************************************//
// ***** DATE *****
//********************************************//

//Getters 

/**
 * \brief renvoie la date sous forme de chaîne de caractères jj/mm/aaaa (en ajoutant des 0 si mois < 10 ou année < 1000)
 */
std::string t_Date::get_str_date() const{
    std::string jour = std::to_string(this->jour);
    std::string mois = std::to_string(this->mois);
    std::string annee = std::to_string(this->annee);
    
    if(jour.length() < 2){ jour = '0'+jour; } //ajoute un 0 en amont si numéro jour > 9
    if(mois.length() < 2) { mois = '0'+mois; } // ajout un 0 en amont numéro mois > 9
    if(annee.length() < 4){ //corrige la date en ajoutant les 0 seulement si la taille de la date est < 4
        short nb_o = 4-annee.length(); //nombre de 0 à ajouter pour une date de taille correcte 4 maximum.
        for(unsigned short i=0; i<nb_o; i++){
                annee = '0'+annee;
        }
    }  
    return jour+'/'+mois+'/'+annee;
}

unsigned short t_Date::get_jour() const{
    return this->jour;
}

unsigned short t_Date::get_mois() const{
    return this->mois;
}

unsigned short t_Date::get_annee() const{
    return this->annee;
}

//Setters

void t_Date::set_date(const unsigned short jour, const unsigned short mois, const unsigned short annee){
    this->jour = jour;
    this->mois = mois;
    this->annee = annee;
}

// Opérateurs sur dates

/**
 * \brief comparaison de 2 dates. (égalité)
 * \param date2 date avec laquelle comparer la date courante
 * \return booléen: true si jour, mois, année des dates sont égaux, false sinon
 */
bool t_Date::operator==(t_Date const& date2) const{ //définition de l'opérateur == pour les dates
    return(this->jour == date2.jour && this->mois == date2.mois && this->annee == date2.annee);
}

/**
 * \brief comparaison de 2 dates (strictement inférieur)
 * \param date2 date avec laquelle comparer la date courante
 * \return booléen: true si jour, mois, année de la date courante sont < aux jour, mois, années de date2
 */
bool t_Date::operator<(t_Date const& date2) const{
    return (this->jour < date2.jour && this->mois < date2.mois && this->annee < date2.annee);
}

//********************************************//
// ***** CLICHE *****
//********************************************//

//Getters

unsigned short t_Cliche::get_numero_prise() const{
    return this->numero_prise;
}

unsigned int t_Cliche::get_num_exam_cliche() const{
    return this->num_exam_cliche;
}

const std::string& t_Cliche::get_nom_cliche() const{
    return this->nom_cliche; //renvoie la chaîne de caractères correspondant au nom de fichier seulement 
}

const std::string& t_Cliche::get_chemin_acces_cliche() const{
    return this->chemin_acces_cliche; //renvoie la chaîne de caractères du chemin d'accès complet vers le fichier cliché
}

//Setters

void t_Cliche::set_numero_prise(const unsigned short new_num){ // éditer le numéro de prise d'un cliché, non utilisé ici mais utile pour des améliorations ultérieures
     this->numero_prise = new_num;
}

//********************************************//
// ***** COMPTE_RENDU_MEDICAL *****
//********************************************//

// Getters

const std::string& t_Compte_Rendu_Medical::get_mdp() const{
    return this->mdp; //renvoie le mot de passe d'un compte-rendu
}

const std::string& t_Compte_Rendu_Medical::get_nom_fichier() const{
    return this->nom_fichier; // renvoie le nom de fichier d'un compte-rendu
}

const std::string& t_Compte_Rendu_Medical::get_chemin_acces_compte_rendu() const{
    return this->chemin_acces_compte_rendu; //renvoie le chemin d'accès complet vers un compte-rendu
}

//Setters

void t_Compte_Rendu_Medical::set_mdp(const std::string& new_mdp){
    this->mdp = new_mdp; //modifier le mot de passe d'un compte-rendu, non utilisé ici mais utile pour une amélioration ultérieure
}

// Méthodes

/**
 * \brief affiche le compte-rendu medical d'une radio d'un patient en vérifiant si le mot de passe d'accès est correct
 */

void t_Compte_Rendu_Medical::affiche_compte_rendu() const{
    
    std::ifstream fin; //flux stockant le fichier
    std::string s; //stocke la ligne courante dans le fichier
    short nb_essai = 3; // nombre d'essai restant pour ouvrir le fichier
    std::string input_mdp;

    while(nb_essai > 0){ //tant que le nombre de tentatives restantes est > 0 et que le mdp est incorrect
        // demande du mot de passe
        std::cout << std::endl;
        std::cout << "Mot de passe: ";
        std::cin >> input_mdp;
        std::cout << std::endl;

        if(input_mdp == this->mdp){ //si le mot de passe est correct
            fin.open(this->get_chemin_acces_compte_rendu(), std::ios_base::in); // ouverture du fichier de compte-rendu
            if(fin.is_open()){
                std::cout << "-----------------------------------------" << std::endl;
                std::cout << "Compte rendu: " << "\""+this->nom_fichier+"\":" << std::endl;
                std::cout << "-----------------------------------------\n" << std::endl;
                //lecture du fichier de compte-rendu
                getline(fin, s, '\n');
                while(fin){
                    std::cout << s << std::endl;
                    getline(fin, s, '\n');
                }
                fin.close();
                fin.clear();
                return; // fin procédure
            }
            else{ //sinon, si fichier non ouvert en lecture
                std::cerr << "[FileNotFoundError] Impossible d'ouvrir le fichier " << this->get_chemin_acces_compte_rendu() << std::endl; //message d'erreur
                fin.clear(); // vide le flux
                return; //fin procédure
            }
        }
        else{ //si mot de passe incorrect
            nb_essai--; //décrémente le nombre de tentatives restantes
            if(nb_essai > 0){
                std::cout << "[InvalidPassword] Le mot de passe d'ouverture pour le compte rendu " << "\""+nom_fichier+"\"" << " est incorrect. Veuillez réessayer (" << nb_essai << " essai(s) restant(s).)" << std::endl;
            }
            else{ //si le nombre de tentatives restantes == 0
                std::cout << "[CANCEL] Mot de passe incorrect. Nombre maximum de tentatives infructueuses dépassé." << std::endl;
                return; 
            }
        }
    }
}

//********************************************//
// ***** RADIOGRAPHIE *****
//********************************************//

// Getters

unsigned int t_Radiographie::get_num_exam_unique() const{
    return this->num_exam_unique;
}

bool t_Radiographie::get_etat() const{
    return this->etat;
}

t_Date& t_Radiographie::get_date_radio(){
    return this->date_radio;
}

vector_t_Cliche_ptr* t_Radiographie::get_vector_cliches() const{
    return this->vector_cliches_ptr; // this pointeur sur radio, this->vector_cliches = valeur de vecteur_cliches = pointeur sur vector_t_Cliche_ptr
}

const t_type_Radio& t_Radiographie::get_type_Radio() const{
    return this->type_Radio;
}

t_Compte_Rendu_Medical& t_Radiographie::get_compte_rendu(){ //renvoie l'instance du compte-rendu de la radio
    return this->compte_rendu;
}

const std::string& t_Radiographie::get_chemin_acces_radio() const{
    return this->chemin_acces_radio;
}

// Setters

void t_Radiographie::set_etat(const bool new_etat){
    this->etat = new_etat; //modifie l'état de la radio, non utilisé ici mais utile pour une amélioration ultérieure
}

void t_Radiographie::set_type_radio(const t_type_Radio& new_type){
    this->type_Radio = new_type; // modifie le type de la radio, non utilisé ici mais utile pour une amélioration ultérieure
}

//Méthodes

/**
 * \brief renvoie le type de la radio sous forme d'une chaîne de caractères
 */
std::string t_Radiographie::get_str_type_radio() const{
    switch(this->type_Radio){
        case 0: return "Radiographie conventionelle à rayon X"; break;
        case 1: return "Echographie à ultrasons"; break;
        case 2: return "IRM"; break;
        default: break;
    }
    return "Type radio inconnu"; // message récupéré si type_Radio incorrect
}

/**
 * \brief renvoie l'état de la radio sous forme d'une chaîne de caractères
 */
std::string t_Radiographie::get_str_etat() const{
    if(this->etat) return "effectuée";
    return "planifiée"; // if not etat
}

/**
 * \brief affichage d'une radio
 */
void t_Radiographie::affiche_radio(){
    bool existe_cliches = false; // permet de savoir si des clichés existent dans la radio
    std::cout << "-----------------------" << std::endl;
    std::cout << "N° EXAMEN: " << std::to_string(this->num_exam_unique) << std::endl;
    std::cout << "-----------------------" << std::endl;
    std::cout << "- Type: " << this->get_str_type_radio() << std::endl;
    std::cout << "- Etat: " << this->get_str_etat() << std::endl;
    std::cout << "- Date: " << this->get_date_radio().get_str_date() << std::endl;
    std::cout << "- Compte-rendu: " << this->get_compte_rendu().get_nom_fichier() << std::endl;
    std::cout << "- Liste des clichés: " << std::endl; //affichage de la liste des clichés
    for(auto it = this->get_vector_cliches()->begin(); it != this->get_vector_cliches()->end(); it++){
        existe_cliches = true; // indique que des clichés existent et que le message "Aucun cliché" ne doit pas être affiché
        std::cout << std::to_string((*it)->get_numero_prise()) <<"- " << (*it)->get_nom_cliche() << std::endl; //affichage du numéro de prise et nom du cliché
    }
    if(!(existe_cliches)){ // si aucun fichier n'existe 
        std::cout << "Aucun cliché, la radio n'a pas encore été effectuée." << std::endl;
    }
    std::cout << "-----------------------\n" << std::endl;
}

/**
 * \brief renvoie une chaîne de caractères correspondant à l'entier associé au type radio (enum)
 */
std::string t_Radiographie::get_str_int_type_radio() const{
    switch(this->type_Radio){
        case 0: return "0"; break;
        case 1: return "1"; break;
        case 2: return "2"; break;
        default: break;
    }
    return "X"; // code pour int type_Radio inconnu
}

/**
 * \brief renvoie la valeur 0/1 sous forme de chaîne correspondant à la valeur booléenne (0: false, 1: true)
 */
std::string t_Radiographie::get_str_bool_etat() const{ //renvoie sous forme d'une chaîne de caractères la valeur du booléen (0 ou 1)
    if(this->etat) return "1";
    return "0";
}

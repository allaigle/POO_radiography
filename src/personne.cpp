/******* Auteurs: *******
Julien Paris - M2BB
Alice Laigle - M2BB
*************************/

#include "../Classes/centreRadio.hpp"

//********************************************//
// ***** PERSONNE *****
//********************************************//

 //Getters
const std::string& t_Personne::get_nom() const{
    return this->nom;
}

const std::string& t_Personne::get_prenom() const{
    return this->prenom;
}

unsigned short t_Personne::get_age() const{
    return this->age;
}

bool t_Personne::get_sexe() const{
    return this->sexe;
}

t_Date& t_Personne::get_date_naissance(){ // retourne la date sous la forme de t_Date
    return this->date_naissance;
}

//Setters
void t_Personne::set_nom(const std::string& new_nom){
    this->nom = new_nom;
}

void t_Personne::set_prenom(const std::string& new_prenom){
    this->prenom = new_prenom;
    
}

void t_Personne::set_age(const unsigned short new_age){
    this->age = new_age;
}

void t_Personne::set_sexe(const bool new_sexe){
    this->sexe = new_sexe;
}

 //Methods

/**
 * \brief retourne l'âge sous forme d'une chaîne de caractères pour affichage
 */
std::string t_Personne::get_str_age() const{
    return std::to_string(this->age);
}

/**
 * \brief le sexe de la personne sous forme d'une chaîne de caractères
 */
std::string t_Personne::get_str_sexe() const{ //renvoie le sexe en str en fonction de la valeur du booléen sexe
    if(this->sexe) return "Homme";
    return "Femme"; //sinon
}

/**
 * \brief renvoie la valeur 0/1 sous forme d'une chaîne de caractères correspondant à la valeur booléenne (nécessaire pour sauvegarder l'état du centre radio)
 */
std::string t_Personne::get_str_bool_sexe() const{
    if(this->sexe) return "1";
    return "0"; //sinon
}

/**
 * \brief permet d'éditer le sexe à partir d'une chaîne de caractères "H" ou "F" et non directement à partir des valeurs booléennes
 */
bool t_Personne::set_sexe_via_str(const std::string& new_sexe){ // pour ensuite utiliser set sexe en utilisant str H/F.
    if(new_sexe == "H") return true; else return false;
}

//********************************************//
// ***** PATIENTS *****
//********************************************//

// Getters

const std::string& t_Patient::get_dossier_medical_nom() const{
    return this->dossier_medical_nom; //retourne le nom de fichier du dossier médical du patient, sans le chemin d'accès
}

vector_t_Radiographie_ptr* t_Patient::get_vector_radios() const{
    return this->vector_radios_ptr; //retourne le pointeur sur vecteur de radios
}

const std::string& t_Patient::get_chemin_acces_patient() const{
    return this->chemin_acces_patient; //retourne le chemin d'accès pour le dossier du patient
}

const std::string& t_Patient::get_chemin_acces_dossier_medical() const{
    return this->chemin_acces_dossier_medical; // retourner le chemin d'accès pour le dossier médical du patient
}

// Méthodes

/**
 * \brief égalité entre patients
 */
bool t_Patient::operator==(t_Patient const& p2) const{
    return (this->get_nom() == p2.get_nom() && this->get_prenom() == p2.get_prenom());
}

/**
 * \brief permet l'affichage du dossier médical d'un patient
 */
void t_Patient::afficher_dossier_medical() const{
    std::ifstream fin; //flux stockant le fichier
    std::string s; //stocke la ligne courante dans le fichier

    fin.open(this->chemin_acces_dossier_medical);
    if(fin.is_open()){
        std::cout << "----------------------------------------------------" << std::endl;
        std::cout << "Dossier médical pour le patient " << "\""+this->get_prenom()+" "+this->get_nom()+"\"" << std::endl;
        std::cout << "----------------------------------------------------\n" << std::endl;
        getline(fin, s, '\n');
        while(fin){
            std::cout << s << std::endl;
            getline(fin, s, '\n');
        }
        fin.close();
        fin.clear();
    }else{
        std::cerr << "[FileNotFoundError] Impossible d'ouvrir le fichier " << "\""+(this->chemin_acces_dossier_medical)+"\"" << std::endl; //message d'erreur
        fin.clear(); // vide le flux
    }
    std::cout << std::endl;

}

/**
 * \brief compare les radios via leur numéro d'examen unique
 * \return renvoie vrai si le numéro d'examen de r1 est < à celui de r2, sinon renvoie faux
 */
bool compare_radios_num_exam(const t_Radiographie_ptr r1, const t_Radiographie_ptr r2){
    return (r1->get_num_exam_unique() < r2->get_num_exam_unique());
}

/**
 * \brief compare les radios via leur date
 * \return renvoie vrai la date de la radio r1 est < à celle de la radio r2
 */
bool compare_radios_date(const t_Radiographie_ptr r1, const t_Radiographie_ptr r2){
    return (r1->get_date_radio() < r2->get_date_radio());
}

/**
 * \brief affichage d'un patient et de ses radios triées selon une fonction de tri (compare_radios) passée en paramètre
 * \param func_tri_radio pointeur sur une fonctions booléenne de tri de radios prenant en paramètre 2 pointeurs sur t_Radiographie
 */
void t_Patient::affiche_patient(bool (*func_tri_radio)(const t_Radiographie_ptr, const t_Radiographie_ptr)){

    //affichage des informations du patient
    std::cout << "##################################################\n" << std::endl;
    std::cout << "NOM: " << this->nom << " / " << "PRENOM: " << this->prenom << std::endl;
    std::cout << "SEXE: " << this->get_str_sexe() << std::endl;
    std::cout << "AGE: " << this->get_str_age() << std::endl;
    std::cout << "NAISSANCE: " << this->date_naissance.get_str_date() << std::endl;
    std::cout << "DOSSIER MEDICAL: " << this->dossier_medical_nom << std::endl << std::endl;

    //affichage des radios
    std::cout << "RADIOS: " << "total: " << std::to_string((this->vector_radios_ptr)->size()) << std::endl;

    std::sort(this->vector_radios_ptr->begin(), this->vector_radios_ptr->end(), func_tri_radio); //tri des radios
    for(auto it = (this->vector_radios_ptr)->begin(); it != (this->vector_radios_ptr)->end(); it++){
        (*it)->affiche_radio(); //affichage de la radio
    }
    std::cout << "##################################################\n" << std::endl;
}

//********************************************//
// ***** PRATICIEN *****
//********************************************//

// Getters

const std::string& t_Praticien::get_mdp() const{
    return this->mdp;
}

const std::string& t_Praticien::get_id() const{
    return this->id;
}

//Setters

void t_Praticien::set_mdp(const std::string& new_mdp){
    this->mdp = new_mdp;
}

void t_Praticien::set_id(const std::string& new_id){
    this->id = new_id;
}

// Methods

/**
 * \brief comparaison de deux praticiens selon leur nom/prenom et id.
 * \return renvoie un booléen: true si noms/prenoms et id des praticiens sont égaux, sinon faux.
 */
bool t_Praticien::operator==(t_Praticien const& p2) const{
    return (this->get_nom() == p2.get_nom() && this->get_prenom() == p2.get_prenom() && this->get_id() == p2.get_id());
}

/**
 * \brief affiche les informations sur un praticien
 */
void t_Praticien::affiche_praticien() const{
    std::cout << "##################################################" << std::endl;
    std::cout << "NOM: " << this->nom << " / " << "PRENOM: " << this->prenom << std::endl;
    std::cout << "SEXE: " << this->get_str_sexe() << std::endl;
    std::cout << "AGE: " << this->get_str_age() << std::endl;
    std::cout << "NAISSANCE: " << this->date_naissance.get_str_date() << std::endl;
    std::cout << "IDENTIFIANT: " << this->id << std::endl; //A ENLEVER A LA FIN
    std::cout << "MOT DE PASSE: " << this->mdp << std::endl;
    std::cout << "##################################################" << std::endl;
}

/**
 * \brief interface pour modification de l'id du praticien
 */
void t_Praticien::modifier_id(){
    std::string new_id;

    // Demande des informations de recherche (nom et prenom du patient)
    std::cin.ignore(1,'\n'); //enlever retour ligne du buffer avant getline
    std::cout << "Ancien identifiant: " << this->get_id() << std::endl;
    std::cout << "Nouvel identifiant: ";
    getline(std::cin, new_id);

    for(unsigned int i=0; i<new_id.length(); i++){ //si l'id contient un espace, on n'accepte pas la saisie
        if(new_id[i] == ' '){
            std::cerr << "\n[FAILED] Impossible de mettre à jour l'id (présence d'espaces dans le nouvel id).\n" << std::endl;
            return; // fin de procédure si espaces dans id
        }
    }
    
    if(new_id != ""){ //si un nouvel id a bien été saisi, si le champs n'a pas été laissé vide alors modification de l'id et affichage d'un message de confirmation (appuyer sur la touche entrée sans avoir saisi de valeur : laisse la possibilité d'annuler la modification de l'id)
        this->set_id(new_id); // mise à jour de l'id
        std::cout << std::endl;
        std::cout << "[SUCCESS] L'identifiant a été mis à jour." << std::endl;
        std::cout << "--> Votre identifiant est désormais " << "\""+this->get_id()+"\"\n" << std::endl;
        return;
    }// sinon, si annulation de la saisie
    std::cerr << "\n[CANCEL] Aucune modifications n'ont été apportées à l'identifiant.\n" << std::endl;

    
}

/**
 * \brief interface pour modification du mot de passe du praticien
 */
void t_Praticien::modifier_mdp(){
    std::string new_mdp;
    std::string old_mdp;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //efface le flux en entier
    std::cout << "Ancien mot de passe: "; //demande de l'ancien mot de passe
    getline(std::cin, old_mdp);
    
    for(unsigned int i=0; i<old_mdp.length(); i++){ //si le mot de passe contient un espace, on n'accepte pas la saisie
        if(old_mdp[i] == ' '){
            std::cerr << "\n[FAILED] Impossible de mettre à jour le mot de passe. (présence d'espaces dans l'ancien mot de passe).\n" << std::endl;
            return; // fin de procédure si espaces dans mdp
        }
    }

    std::cout << "Nouveau mot de passe: "; // demande du nouveau mot de passe
    getline(std::cin, new_mdp);

    for(unsigned int i=0; i<new_mdp.length(); i++){ //si le mot de passe contient un espace, on n'accepte pas la saisie
        if(new_mdp[i] == ' '){
            std::cerr << "\n[FAILED] Impossible de mettre à jour le mot de passe. (présence d'espaces dans le nouveau mot de passe).\n" << std::endl;
            return; // fin de procédure si espaces dans mot de passe
        }
    }
    
    if(old_mdp != "" && new_mdp != ""){ // si les 2 champs ont bien été remplis, on vérifie que l'ancien mdp est correct, et met à jour le mot de passe (appuyer sur entrée sans mettre de valeur permet d'annuler la modification du mot de passe)
        if(old_mdp == this->get_mdp()){ // mise à jour du mot de passe
            this->set_mdp(new_mdp);
            std::cout << "\n[SUCCESS] Votre mot de passe a été mis à jour.\n" << std::endl;
        }else{
            std::cerr << "\n[FAILED] Ancien mot de passe incorrecte. Impossible de mettre à jour le mot de passe.\n" << std::endl;
        } 
        return;
    } //sinon si annulation modification du mot de passe
    
    std::cout << "\n[CANCEL] Aucune modification n'a été apportée à votre mot de passe.\n" << std::endl;
    
}

/**
 * \brief modifier les informations personnelles d'un praticien (nom, prénom, âge, sexe etc...)
 */
void t_Praticien::modifier_infos_perso(){
    std::string new_nom, new_prenom, new_sexe, new_date_naissance;
    unsigned short j; //jour de naissance
    unsigned short m; //mois de naissance
    unsigned short a; //année de naissance

    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << "###### Modifier mes informations personnelles ######" << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "Modifier les informations que vous souhaitez. Pour ne pas modifier un champs, laissez le champs vide et appuyez sur \"entrée\"." << std::endl << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //enlever ce qu'il y a dans le flux cin
    // demande de saisie du nouveau nom, prénom, sexe, date de naissance
    std::cout << "Modifier nom: ";
    getline(std::cin, new_nom);
    std::cout << "Modifier prenom: ";
    getline(std::cin, new_prenom);
    std::cout << "Modifier sexe (H/F): ";
    getline(std::cin, new_sexe);
    std::cout <<"Modifier la date de naissance (jj/mm/aaaa): ";
    getline(std::cin, new_date_naissance);

    int scan_val = std::sscanf(new_date_naissance.c_str(), "%2hu%*1[/]%2hu%*1[/]%4hu", &j, &m, &a); //scan_val contient le nombre de valeurs correctement assignées
    // vérifie la saisie correcte de new_nom, new_prenom, new_sexe. Si présence d'espaces dans les chaînes, ou chaîne uniquement constituée d'espaces, affecte la valeur "" à ces variables
    // on ne vérifie pas l'absence de caractère, car si absence de caractère alors new_nom, new_prenom, new_sexe = "" par défaut.
    // permet par la suite de faire les mises à jour nom, prénom, sexe seulement si les new_prenom, new_nom, new_sexe sont différents de la chaîne vide ""
    // cela permet de ne pas avoir à modifier l'intégralité des informations, on peut appuyer sur entrée pour ne pas modifier une information
    
    //vérifie la présence d'espaces dans le nouveau nom
    for(unsigned int i=0; i<new_nom.length(); i++){
        if(new_nom[i] == ' '){
            new_nom = "";
            break;
        }
    }

    // vérifie la présence d'espaces dans le nouveau prénom
    for(unsigned int i=0; i<new_prenom.length(); i++){
        if(new_prenom[i] == ' '){
            new_prenom = "";
            break;
        }
    }

    // vérifie la présence d'espaces dans la nouvelle date de naissance
    for(unsigned int i=0; i<new_date_naissance.length(); i++){
        if(new_date_naissance[i] == ' '){
            new_date_naissance = "";
            break;
        }
    }
    
    // affichage des modifications apportées
    std::cout << std::endl;
    std::cout << "------------------------" << std::endl;
    std::cout << "Modifications apportées:" << std::endl;
    std::cout << "------------------------" << std::endl;

    // si aucun champs n'a été rempli (ou présence d'espaces dans ces champs), annulation de la modification du praticien et affichage d'un message
    if (new_nom == "" && new_prenom == "" && new_sexe == "" && new_date_naissance == ""){
        std::cout << "\n[CANCEL] Aucune modification n'a été apportée à vos informations personnelles." << std::endl << std::endl;
        return; // fin de procédure si rien n'a été modifié
    }

    // vérification du renseignement de chacun des champs + affichage des modifications apportées champs par champs

    if(new_nom != ""){
        this->set_nom(new_nom); //mise à jour du nom
        std::cout << "Nouveau nom: " << this->get_nom() << std::endl;
    }

    if(new_prenom != ""){
        this->set_prenom(new_prenom); //mise à jour du prénom
        std::cout << "Nouveau prenom: " << "\""+this->get_prenom()+"\"" << std::endl;
    }

    if(new_sexe != ""){
        if(new_sexe=="H" || new_sexe=="F"){ //vérifie que le sexe correspont à "H" ou "F"
            this->set_sexe(this->set_sexe_via_str(new_sexe)); // mise à jour du sexe via une chaîne de caractères
            std::cout << "Nouveau sexe: " << "\""+this->get_str_sexe()+"\"" << std::endl;
        }else{
            std::cerr << "[TypingError] La modification du sexe n'a pas été prise en compte (valeur saisie incorrecte)." << std::endl;
        }
    }

    // Vérification du format de la saisie de la date
    if(new_date_naissance != ""){
        if(scan_val == 3){ //si scan a réussi à récupérer 3 unsigned short
            this->get_date_naissance().set_date(j, m, a); // mise à jour de la date de naissance
            std::cout << "Nouvelle date de naissance: " << "\""+this->get_date_naissance().get_str_date()+"\"" << std::endl;
        }else{
            std::cerr << "[TypingError] La modification de la date de naissance n'a pas été prise en compte. La date saisie n'est pas au format jj/mm/aaaa." << std::endl;
        }
    }
    std::cout << std::endl;
}

/**
 * \brief interface pour configuration du compte praticien
 */
void t_Praticien::modifier_compte_prat(const std::string& nom_centre){

    short choix;

    std::cout << "-----------------------------------" << std::endl;
    std::cout << "###### Configurer mon compte ######" << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    std::cout << std::endl;

    std::cout << "1 - Modifier mon identifiant" << std::endl;
    std::cout << "2 - Modifier mon mot de passe" << std::endl;
    std::cout << "3 - Modifier mes informations personnelles" << std::endl;
    std::cout << "4 - Retour" << std::endl;
    std::cout << "Sélectionner: ";
    std::cin >> choix;
    std::cout << std::endl;
    
    if(!std::cin){ //vérifie que la valeur saisie est correcte (un entier short), sinon vide le flux et redemande la saisie
        std::cerr << "Saisie incorrecte.\n" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //efface le flux en entier
        return; //fin de procédure si saisie incorrecte.
    }

    switch(choix){
        case 1: this->modifier_id(); break;
        case 2: this->modifier_mdp(); break;
        case 3: 
            std::system("clear");
            std::cout << "==========================================================" << std::endl;
            std::cout << "                CENTRE RADIO " << "\""+nom_centre+"\"" << std::endl;
            std::cout << "==========================================================\n" << std::endl;
            this->modifier_infos_perso(); break; 
        case 4: 
            std::system("clear");
            std::cout << "==========================================================" << std::endl;
            std::cout << "                CENTRE RADIO " << "\""+nom_centre+"\"" << std::endl;
            std::cout << "==========================================================\n" << std::endl;
            return; 
        break;
        default: std::cerr << "Aucune option disponible pour la valeur saisie." << std::endl << std::endl; break;
    }
}
/******* Autheurs: *******
Julien Paris - M2BB
Alice Laigle - M2BB
*************************/

#include "../Classes/centreRadio.hpp"

//********************************************//
// ***** CENTRE RADIO *****
//********************************************//

// Getters

const std::string& t_Centre_Radio::get_nom() const{
    return this->nom;
}

/**
 * \brief permet d'obtenir l'adresse du centre radio
 * \return std::string obtenue par concaténation du numéro de rue, de la rue et de la ville
 */
std::string t_Centre_Radio::get_adresse() const{
    return (this->num_rue)+" "+(this->rue)+" - "+(this->ville);
}

vector_t_Patient_ptr* t_Centre_Radio::get_vector_patients() const{
    return this->vector_patients_ptr; //retourne un pointeur sur le vecteur de pointeurs de patients
}

vector_t_Praticien_ptr* t_Centre_Radio::get_vector_praticien() const{
    return this->vector_praticiens_ptr; // retourne un pointeur sur le vecteur de pointeurs de praticiens
}

// Setters 

void t_Centre_Radio::set_nom(const std::string& new_nom){ // non utilisé, mais utile pour une amélioration future du logiciel
    this->nom = new_nom;
}

/**
 * \brief permet d'éditer l'adresse du centre radio
 * \return std::string obtenue par concaténation du numéro de rue, de la rue et de la ville
 */
void t_Centre_Radio::set_adresse(const std::string& new_num_rue, const std::string& new_rue, const std::string& new_ville){ // non utilisé, mais utile pour une amélioration future du logiciel
    this->num_rue = new_num_rue;
    this->rue = new_rue;
    this->ville = new_ville;
}

// Méthodes

/**
 * \brief affichage de l'en-tête des menus
 */
void t_Centre_Radio::affiche_entete() const{
    std::cout << "==========================================================" << std::endl;
    std::cout << "                CENTRE RADIO " << "\""+this->get_nom()+"\"" << std::endl;
    std::cout << "==========================================================\n" << std::endl;
}

/**
 * \brief permet la connexion du praticien au centre radio
 * \return t_Praticien_ptr: pointeur sur le praticien qui s'est connecté
 */
t_Praticien_ptr t_Centre_Radio::login() const{

    std::string usr_id, usr_mdp; //identifiant et mot de passe entrés par l'utilisateur
    std::system("clear"); //efface le terminal au lancement.
    
    //demande des informations de connexion tant que les saisies sont incorrectes
    do{
        this->affiche_entete();
        // demande des informations de connexion
        std::cout << "--------------" << std::endl;
        std::cout << "| CONNEXION: |" << std::endl;
        std::cout << "--------------" << std::endl;
        std::cout << "Identifiant: "; 
        getline(std::cin, usr_id);
        std::cout << "Mot de passe: ";
        getline(std::cin, usr_mdp);

        // chercher l'id et le mdp entrés par l'utilisateur dans l'ensemble des praticiens
        for(auto it_prat = (this->vector_praticiens_ptr)->begin(); it_prat != (this->vector_praticiens_ptr)->end(); it_prat++){ 
            if( (usr_id == (*it_prat)->get_id()) && (usr_mdp == (*it_prat)->get_mdp()) ) { //si un praticien correspondant à l'id et au mdp a été trouvé
                std::system("clear"); //efface le terminal
                std::cout << "[LOGIN SUCCESS] -> Bienvenue " << (*it_prat)->get_prenom()+" !" << std::endl << std::endl;;
                return (*it_prat); // fin de procédure si id et mdp corrects, retourne le pointeur sur le praticien qui vient de se connecteer
            }
        }
        //si les informations de connexions sont incorrectes, affiche un message d'erreur et on redemande une saisie
        std::system("clear"); //efface le terminal
        std::cout << "[LOGIN FAILED] Mot de passe ou identifiant incorrect, veuillez réessayer.\n" << std::endl;
    }while(true);
}

/**
 * \brief sauvegarde l'état actuel du centre radio dans un fichier texte
 * \param output_filepath chemin d'accès vers le fichier de sauvegarde (passé en argument de ligne de commande de shell)
 */
void t_Centre_Radio::sauvegarder_etat(const std::string& output_filepath) const{
    
    std::ofstream fout;

    fout.open(output_filepath, std::ios_base::out); //ouverture fichier

    if(fout.is_open()){ //si le fichier est bien ouvert
        // écriture des informations du centre radio
        fout << "centre_radio;" << this->nom << ";" << this->ville << ";" << this->rue << ";" << this->num_rue << ";" << std::endl; // écriture des informations sur le centre radio
        
        //écriture des informations des praticiens
        for(auto it_prat = (this->vector_praticiens_ptr)->begin(); it_prat != (this->vector_praticiens_ptr)->end(); it_prat++){ // écriture des informations sur l'ensemble des praticiens
            fout << "praticien;" << (*it_prat)->get_nom() << ";" << (*it_prat)->get_prenom() << ";";
            fout << (*it_prat)->get_str_age() << ";" << (*it_prat)->get_str_bool_sexe() << ";" << std::to_string((*it_prat)->get_date_naissance().get_jour()) << ";";
            fout << std::to_string((*it_prat)->get_date_naissance().get_mois()) << ";" << std::to_string((*it_prat)->get_date_naissance().get_annee()) << ";";
            fout << (*it_prat)->get_id() << ";" << (*it_prat)->get_mdp() << ";" << std::endl;
        }

        //écriture des informations des patients
        for(auto it_patient = (this->vector_patients_ptr)->begin(); it_patient != (this->vector_patients_ptr)->end(); it_patient++){ // écriture des informations sur l'ensemble des patients
            fout << "patient;" << (*it_patient)->get_nom() << ";" << (*it_patient)->get_prenom() << ";" << (*it_patient)->get_str_age() << ";" << (*it_patient)->get_str_bool_sexe() << ";" << std::to_string((*it_patient)->get_date_naissance().get_jour()) << ";";
            fout << std::to_string((*it_patient)->get_date_naissance().get_mois()) << ";" << std::to_string((*it_patient)->get_date_naissance().get_annee()) << ";" << std::endl;

            //écriture des informations des radios par patients
            for(auto it_radio = ((*it_patient)->get_vector_radios())->begin(); it_radio !=  ((*it_patient)->get_vector_radios())->end(); it_radio++){ //écriture des informations sur l'ensemble des radios du patient
                fout << "radio;" << std::to_string((*it_radio)->get_num_exam_unique()) << ";" << (*it_radio)->get_str_bool_etat() << ";";
                fout << std::to_string((*it_radio)->get_date_radio().get_jour()) << ";" << std::to_string((*it_radio)->get_date_radio().get_mois()) << ";" << std::to_string((*it_radio)->get_date_radio().get_annee()) << ";";
                fout << (*it_radio)->get_str_int_type_radio() << ";" << (*it_radio)->get_compte_rendu().get_mdp() << ";" << std::to_string((*it_radio)->get_vector_cliches()->size()) << ";" << std::endl;
            }
        }
    }else{
        std::cerr << "[FileNotFoundError] Impossible d'ouvrir le fichier " << "\""+output_filepath+"\"" << std::endl; // en cas d'erreur
        fout.clear(); // vide le flux
    }
}

/**
 * \brief fonction de comparaison pour le tri des patients selon leur nom ou prénom en cas d'égalité
 * \param t_Patient_ptr 2 pointeurs sur t_patient
 * \return true si nom_patient1 < nom_patient2. En cas d'égalité des noms, on regarde les prénoms
 */
bool compare_patient(const t_Patient_ptr p1, const t_Patient_ptr p2){
    if (p1->get_nom() < p2->get_nom()) {
        return true;
    }
    else if (p1->get_nom() > p2->get_nom()){
        return false;
    }
    else{
        return (p1->get_prenom() < p2->get_prenom());
    }
}

/**
 * \brief affichage des patients triés selon leur nom et prénom et affichage des radios triées par date ou par numéro d'examen pour chaque patient
 */
void t_Centre_Radio::afficher_vector_patient_trie() const{
    std::system("clear"); //clear du shell
    this->affiche_entete();
    std::cout << "--------------------------------------------------------------------" << std::endl;
    std::cout << "###### Afficher les caractéristiques des radios par patients  ######" << std::endl;
    std::cout << "--------------------------------------------------------------------\n" << std::endl;

    // choix de la méthode de tri
    int choix;
    std::cout << "Trier les radios selon: " << std::endl;
    std::cout << "-----------------------" << std::endl;
    std::cout << "1 - Numéro d'examen unique" << std::endl;
    std::cout << "2 - Date de l'examen" << std::endl;
    std::cout << "3 - Retour" << std::endl;
    std::cout << "Sélectionner: ";
    int scan_value = scanf("%d", &choix);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //efface le flux en entier au cas où d'autres caractères seraient dedans

    if(scan_value != 1){ //si saisie du choix incorrecte
        std::cerr << "\n[TypingError] Vous devez entrer un nombre associée à une option.\n" << std::endl;
        return;
    }

    std::sort(this->get_vector_patients()->begin(), this->get_vector_patients()->end(), compare_patient); //tri des patients selon leur nom ou prénom si égalité entre les noms
    std::cout << std::endl;
    switch(choix){
        case 1:
            std::cout << "Affichage des radios triées selon le numéro d'examen: " << std::endl;
            for(auto it_patient = this->get_vector_patients()->begin(); it_patient != this->get_vector_patients()->end(); it_patient++){
                (*it_patient)->affiche_patient(&compare_radios_num_exam); //affichage des patients avec radios triées selon leur numéro d'examen unique
            } 
            break;
        case 2: 
        std::cout << "Affichage des radios triées selon la date d'examen: " << std::endl;
            for(auto it_patient = this->get_vector_patients()->begin(); it_patient != this->get_vector_patients()->end(); it_patient++){
                (*it_patient)->affiche_patient(&compare_radios_date); //affichage des patients avec radios triées selon leur date
            }
            break;
        case 3: std::system("clear"); this->affiche_entete(); return; break;
        default: std::cerr << "[FAILED] Aucune option ne correspond à la valeur saisie.\n" << std::endl; return; break;
    }
}

/**
 * \brief affichage des informations du centre radio (infos centre + infos patients (+ radios) + infos praticiens)
 */
void t_Centre_Radio::affiche_centre_radio() const{
    // affichage des informations du centre radio
    std::cout << "=========================================================" << std::endl;
    std::cout << "               INFORMATIONS DU CENTRE RADIO" << std::endl;
    std::cout << "=========================================================\n" << std::endl;
    std::cout << "Nom: " << "\""+this->get_nom()+"\"" << std::endl;
    std::cout << "Adresse: " << this->get_adresse() << std::endl;
    std::cout << "Nombre de praticiens: " << (this->vector_praticiens_ptr)->size() << std::endl;
    std::cout << "Nombre de patients: " << (this->vector_patients_ptr)->size() << std::endl << std::endl;

    // affichage des informations des praticiens
    std::cout << "==========================================================" << std::endl;
    std::cout << "********************** PRATICIENS ************************" << std::endl;
    std::cout << "==========================================================" << std::endl << std::endl;
    
    // parcours du vecteur de praticiens et affichage de chaque praticien
    for(auto it_prat = (this->vector_praticiens_ptr)->begin(); it_prat != (this->vector_praticiens_ptr)->end(); it_prat++){
        (*it_prat)->affiche_praticien();
        std::cout << std::endl;
    }

    // affichage des informations des patients (infos patients + radios)
    std::cout << "==========================================================" << std::endl;
    std::cout << "*********************** PATIENTS *************************" << std::endl;
    std::cout << "==========================================================" << std::endl << std::endl;
    
    std::sort(this->get_vector_patients()->begin(), this->get_vector_patients()->end(), compare_patient); //tri des patients selon leur nom ou prénom si égalité entre les noms
    
    // parcours du vecteur de patients et affichage des patients
    for(auto it_patient = (this->vector_patients_ptr)->begin(); it_patient != (this->vector_patients_ptr)->end(); it_patient++){
        (*it_patient)->affiche_patient(&compare_radios_date); // affichage des patients et des radios triées selon la fonction de tri des radios utilisée (tri selon le numéro d'examen unique ou selon la date)
    }
}

/**
 * \brief menu principal du centre radio
 * \param myPrat pointeur sur le praticien qui s'est connecté
 */
void t_Centre_Radio::menu(t_Praticien_ptr myPrat){
    unsigned short choix_nb;

    while(true){
        std::cout << "---------------" << std::endl;
        std::cout << "MENU PRINCIPAL|" << std::endl;
        std::cout << "---------------" << std::endl;
        std::cout << "1 - Rechercher" << std::endl;
        std::cout << "2 - Afficher" << std::endl;
        std::cout << "3 - Ajouter" << std::endl;
        std::cout << "4 - Supprimer" << std::endl;
        std::cout << "5 - Configurer mon compte" << std::endl;
        std::cout << "6 - Quitter" << std::endl;
        std::cout << "Selectionner: ";
        std::cin >> choix_nb; //choix utilisateur

        if(!std::cin){ //vérifie que la valeur saisie est correcte (un entier short), sinon vide le flux et redemande la saisie
            std::system("clear");
            this->affiche_entete();
            std::cout << "[TypingError] Saisie incorrecte veuillez réessayer.\n" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //efface le flux en entier
            continue;
        }
        std::cout << std::endl;

        switch(choix_nb){
            case 1: this->rechercher(); break; //accède au menu de recherche
            case 2: this->afficher(); break; //accède au menu d'affichage
            case 3: this->ajouter(); break; //accède au menu ajouter
            case 4: this->supprimer(); break; //accède au menu supprimer
            case 5: std::system("clear"); this->affiche_entete(); myPrat->modifier_compte_prat(this->get_nom()); break; //accède au menu de configuration du compte praticien
            case 6: std::cout << "Fermeture de l'application..." << std::endl; return; break; //quitter
            default: std::system("clear"); this->affiche_entete(); std::cout << "[FAILED] Aucune option disponible pour la valeur saisie, veuillez réessayer.\n" << std::endl; break; //si saisie incorrecte
        }
    }    
}

/**
 * \brief rechercher un patient via son nom et prénom et affiche les radios triées selon leur date
 */
void t_Centre_Radio::rechercher_radios_patient() const{
    std::string prenom_patient;
    std::string nom_patient;

    std::system("clear"); //clear du shell
    this->affiche_entete(); //affichage de l'en-tête du centre radio
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "###### Rechercher les radios d'un patient ######" << std::endl;
    std::cout << "------------------------------------------------\n" << std::endl;

    // Demande des informations de recherche (nom et prénom du patient)
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//efface le flux en entier
    std::cout << "Nom du patient: ";
    getline(std::cin, nom_patient);
    nom_patient[0] = std::toupper(nom_patient[0]); // mise en majuscule de la première lettre du prénom en cas d'oubli (tous les prénoms commencent obligatoirement par une majuscule dans notre centre)
    std::cout << "Prenom du patient: ";
    getline(std::cin, prenom_patient); 
    prenom_patient[0] = std::toupper(prenom_patient[0]); // mise en majuscule de la première lettre du nom en cas d'oubli (tous les noms commencent obligatoirement par une majuscule dans notre centre)

    for(auto it_patient = this->get_vector_patients()->begin(); it_patient !=  this->get_vector_patients()->end(); it_patient++){ // parcours du vecteur de patients
        if( ((*it_patient)->get_prenom() == prenom_patient) && ((*it_patient)->get_nom() == nom_patient) ){ // si un patient avec nom et prénom saisis est trouvé
            std::cout << std::endl;
            std::cout << "Patient trouvé." << std::endl;
            (*it_patient)->affiche_patient(&compare_radios_date); //affichage du patient et de ses radios triées selon leur date
            return; //fin de procédure quand patient trouvé
        }
    }//sinon
    std::cout << std::endl;
    std::cerr << "[FAILED] Aucun patient " << "\""+prenom_patient+" "+nom_patient+"\"" << " n'a été trouvé.\n" << std::endl;
}

/**
 * \brief recherche une radio dans le centre en fonction du numéro d'examen unique
 */
void t_Centre_Radio::rechercher_radio_num_exam() const{
    unsigned searched_num_exam; //numéro d'examen à chercher
    std::string str_num_exam; //numéro d'examen à chercher sous forme de chaîne de caractères

    std::system("clear"); //clear du shell
    this->affiche_entete(); //affichage en-tête centre radio (numéro d'examen unique)
    std::cout << "---------------------------------------------------------" << std::endl;
    std::cout << "###### Rechercher une radio via le numéro d'examen ######" << std::endl;
    std::cout << "---------------------------------------------------------\n" << std::endl;
    
    //Demande des informations de recherche (numéro d'examen)
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //efface le flux en entier
    std::cout << "Numéro d'examen: ";
    getline(std::cin, str_num_exam);
    int scan_val = std::sscanf(str_num_exam.c_str(),"%u", &searched_num_exam); //récupération du numéro d'examen sous forme de unsigned int.

    if(scan_val != 1){ // vérification d'une saisie correcte
        std::cerr << "\n[TypingError] Saisie incorrecte. Le numéro d'examen doit être sous la forme d'un nombre entier." << std::endl << std::endl;
        return;
    }

    std::cout << std::endl;
    // parcours du vecteur de radio de chaque patient jusqu'à trouver le numéro d'examen saisi
    for(auto it_patient = this->get_vector_patients()->begin(); it_patient !=  this->get_vector_patients()->end(); it_patient++){
        for(auto it_radio = (*it_patient)->get_vector_radios()->begin(); it_radio != (*it_patient)->get_vector_radios()->end(); it_radio++){
            if((*it_radio)->get_num_exam_unique() == searched_num_exam){ //si une radio avec le numéro d'examen saisi a été trouvée
                std::cout << "Radio trouvée pour le patient " << "\""+(*it_patient)->get_prenom() << " " << (*it_patient)->get_nom()+"\":" << std::endl; //affichage du patient associé à la radio
                (*it_radio)->affiche_radio(); //affichage de la radio
                return; // fin de procédure quand radio trouvée
            }
        }
    }
    //sinon
    std::cerr << "[FAILED] Aucune radio avec le numéro d'examen saisi n'a été trouvé.\n" << std::endl;
}

/**
 * \brief recherche une radio dans l'ensemble du centre radio en fonction du numéro d'examen unique
 */
void t_Centre_Radio::rechercher_radio_date_exam() const{
    unsigned short j, m, a;
    bool trouve = false; //vérifie si au moins une radio a été trouvée

    std::system("clear"); //clear du shell
    this->affiche_entete(); //affichage en-tête centre radio (numéro d'examen unique)
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "###### Rechercher les radios selon une date ######" << std::endl;
    std::cout << "--------------------------------------------------\n" << std::endl;

    //Demande des informations de recherche (date)
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //efface le flux en entier
    std::cout << "Saisissez une date (jj/mm/aaaa): ";
    int scan_val = std::scanf("%2hu%*1[/]%2hu%*1[/]%4hu", &j, &m, &a); //scan_val contient le nombre de valeurs correctement assignées
    
    //effacement du flux pour éviter que des éléments d'une saisie erronée (si saisie trop longue) restent dedans et accèdent à des options d'autres menus sans rien avoir choisi
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //efface le flux en entier
    
    // Vérification du format de la saisie
    if(scan_val != 3){
        std::cout << std::endl;
        std::cerr << "[TypingError] La saisie n'est pas au format date jj/mm/aaaa.\n" << std::endl;
        return;
    }
    //sinon
    t_Date searched_date = t_Date(j,m,a); //création de la date à chercher
    
    std::cout << std::endl;

    //parcours du vecteurs de patients
    for(auto it_patient = this->get_vector_patients()->begin(); it_patient != this->get_vector_patients()->end(); it_patient++){
        // parcours du vecteur de radios pour chaque patient
        for(auto it_radio = (*it_patient)->get_vector_radios()->begin(); it_radio != (*it_patient)->get_vector_radios()->end(); it_radio++){
            if((*it_radio)->get_date_radio() == searched_date){ // si une radio a été trouvée à la date saisie
                trouve = true;
                std::cout << "Radio trouvée pour le patient: " << "\""+(*it_patient)->get_prenom() << " " << (*it_patient)->get_nom()+"\":" << std::endl;
                (*it_radio)->affiche_radio(); //affichage de la radio
                //pas d'arrêt de procédure quand radio trouvée pour laisser la possibilité de trouver plusieurs radios à une même date
            }
        }
    }

    //si aucune radio n'a été trouvée, message d'erreur et fin de procédure
    if(!trouve){
        std::cout << "[FAILED] Aucune radio planifiée / effectuée à la date saisie." << std::endl << std::endl;
    }
}

/**
 * \brief ajouter un patient au centre radio
 */
void t_Centre_Radio::ajouter_patient(){
    
    char nom_char[40]; //nom_patient
    char prenom_char[40]; //prenom_patient
    char sexe[2]; //sexe patient
    unsigned short j, m, a, age; // variable pour jour, mois, année de la date et âge du patient
    
    std::system("clear"); //clear du shell
    this->affiche_entete(); //affichage en-tête centre radio (numéro d'examen unique)
    std::cout << "--------------------------------" << std::endl;
    std::cout << "###### Ajouter un patient ######" << std::endl;
    std::cout << "--------------------------------\n" << std::endl;
    
    // Demande de saisie des informations du patient
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //efface le flux en entier avant la saisie
    
    // Demande du nom du patient
    std::cout << "Nom: ";
    std::scanf("%40s", nom_char);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //efface le flux en entier après la saisie
    std::string nom = nom_char; // récupération d'une string à partir du tableau de char

    // vérifie la présence d'espaces dans le nom du patient, si présence d'espace, échec création patient
    for(int i=0; i<nom.length(); i++){
            if(nom[i] == ' '){
                std::cout << std::endl;
                std::cerr << "[TypingError] Les espaces sont interdits dans le nom d'un patient.\n" << std::endl;
                std::cerr << "Echec de la création du patient.\n" << std::endl;
                return;
            }
    }
    nom[0] = std::toupper(nom[0]); //ajoute la majuscule au premier caractère du nom si oubliée

    // Demande du prénom du patient
    std::cout << "Prenom: ";
    std::scanf("%40s", prenom_char);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //efface le flux en entier avant la saisie pour éviter tout résidu dans le flux
    std::string prenom = prenom_char;// récupération d'une string à partir du tableau de char

    //vérifie la présence d'espace dans le prénom du patient, si présence d'espace, échec de la création du patient
    for(int i=0; i<prenom.length(); i++){
        if(prenom[i] == ' '){
            std::cout << std::endl;
            std::cerr << "[TypingError] Les espaces sont interdits dans le prenom d'un patient.\n" << std::endl;
            std::cerr << "Echec de la création du patient.\n" << std::endl;
            return;
        }
    }

    prenom[0] = std::toupper(prenom[0]); //ajoute la majuscule au premier caractère du prénom si oubliée

    // Demande de l'âge du patient
    std::cout << "Age: ";
    int scan_age = std::scanf("%hu", &age);
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //efface le flux en entier après la saisie pour éviter tout résidu dans le flux
    
    // vérifie la saisie correcte d'un unsigned short, sinon échec de la création du patient
    if(scan_age != 1){
        std::cout << std::endl;
        std::cerr << "[TypingError] Saisie incorrecte de l'age du patient à créer." << std::endl;
        std::cerr << "Echec de la création du patient.\n" << std::endl;
        return;
    }

    // Demande du sexe du patient
    std::cout << "Sexe (H/F): ";
    std::scanf("%c", sexe);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //efface le flux en entier après la saisie

    sexe[0] = std::toupper(sexe[0]); // pour accepter les saisies "h" ou "f"

    bool sexe_bool; // stocke le booléen associé au sexe
    
    // vérification de la saisie du sexe + affectation de la bonne valeur booléene à sexe_bool
    if(sexe[0] == 'H'){ // retrouve le booléen associé au sexe entré sous forme de char
        sexe_bool = true;
    }else if(sexe[0] == 'F'){
        sexe_bool = false;
    }else{
        std::cout << std::endl;
        std::cerr << "[TypingError] Saisie incorrecte du sexe du patient à créer." << std::endl;
        std::cerr << "Echec de la création du patient.\n" << std::endl;
        return;
    }

    // Demande de la date de naissance du patient
    std::cout << "Date de naissance (jj/mm/aaaa): ";
    int scan_date = std::scanf("%2hu%*1[/]%2hu%*1[/]%4hu", &j, &m, &a); //scan_date contient le nombre de valeurs correctement assignées
    
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //efface le flux en entier après les saisies
    
    // Vérification du format de la saisie de la date, si mauvais format, échec de la création du patient
    if(scan_date != 3){
        std::cout << std::endl;
        std::cerr << "[TypingError] La saisie de la date n'est pas au format date jj/mm/aaaa.\n" << std::endl;
        std::cerr << "Echec de la création du patient.\n" << std::endl;
        return;
    }

    // création du patient si les saisies précédentes se sont bien passées
    t_Patient_ptr new_patient = new t_Patient(nom, prenom, age, sexe_bool, j, m, a);

    // vérifie qu'un patient du même nom n'existe pas déjà
    for(auto it_patient = this->get_vector_patients()->begin(); it_patient != this->get_vector_patients()->end(); it_patient++){
        if((**it_patient) == (*new_patient)){
            std::cerr << "\n[ERROR] Ce patient existe déjà. Abandon de la création du patient.\n" << std::endl;
            return; //fin de procédure si le patient existe déjà
        }
    }
    
    // Création de l'arborescence pour le patient créer
    std::string command = "mkdir -p "+new_patient->get_chemin_acces_patient(); //commande bash pour création arborescence
    int success = std::system(command.c_str()); //exécute la commande et récupère le code de sortie de la commande
    
    // Vérifie si la création de l'arborescence a fonctionnée
    if(success == 0){
        std::cout << "[SUCCESS] L'arborescence du patient \""+prenom+" "+nom+"\""+" a bien été créée.\n" << std::endl;
    }else{ //sinon affichage d'un message d'erreur et suppression du patient créé.
        std::cerr << "[CreateDirError] Impossible de créer l'arborescence pour le patient \""+prenom+" "+nom+"\".\n Impossible de créer le patient.\n" << std::endl;
        new_patient->~t_Patient();
        new_patient = nullptr;
        return; //arrêt de la procédure car si pas d'arborescence, on ne pourra pas créer le fichier du dossier médical
    }// sinon arborescence créée avec succès
    
    // Création du fichier dossier medical
    std::ofstream fout(new_patient->get_chemin_acces_dossier_medical()); //Création du fichier dossier médical

    if(fout.is_open()){ // si le fichier est ouvert, écriture dans le fichier (complétion automatique)
        fout << "***********************" << std::endl;
        fout << "*** Dossier medical ***" << std::endl;
        fout << "***********************" << std::endl;
        fout << std::endl;
        fout << "*** Patient ***" << std::endl;
        fout << "Nom : " << new_patient->get_nom() << std::endl;
        fout << "Prenom : " << new_patient->get_prenom() << std::endl;
        fout << "Age : " << new_patient->get_age() << std::endl;
        fout << "Sexe : " << new_patient->get_str_sexe() << std::endl;
        fout << "Date de naissance : " << new_patient->get_date_naissance().get_str_date() << std::endl;
        fout << std::endl;
        fout << "*** Antecedents medicaux ***" << std::endl;

        // Demande de saisie pour les informations qui ne peuvent pas être complétées automatiquement et écriture de la suite du fichier avec les informations saisies
        std::cout << "Veuillez compléter les informations manquantes du dossier médical (laissez les champs vides pour complétion ultérieure).\n" << std::endl;
        
        std::string allergies;
        std::cout << "Allergies : ";
        getline(std::cin, allergies, '\n');
        std::cout << std::endl;
        fout << "Allergies : " << allergies << std::endl;

        std::string traitements;
        std::cout << "Traitements : ";
        getline(std::cin, traitements, '\n');
        std::cout << std::endl;
        fout << "Traitements : " << traitements << std::endl;
       
        std::string chirurgies;
        std::cout << "Chirurgies passées : ";
        getline(std::cin, chirurgies, '\n');
        std::cout << std::endl;
        fout << "Chirurgies passées : " << chirurgies << std::endl;

        std::string atcd;
        std::cout << "Antécédents familiaux : ";
        getline(std::cin, atcd, '\n');
        std::cout << std::endl;
        fout << "Antécedents familiaux : " << atcd << std::endl;

        std::string avc;
        std::cout << "Risques familiaux d'AVC : ";
        getline(std::cin, avc, '\n');
        std::cout << std::endl;
        fout << "Risques familiaux d'AVC : " << avc << std::endl;
        fout << std::endl;

        fout << "*** Informations supplémentaires ***" << std::endl;

        std::cout << "Informations supplémentaires : " << std::endl;

        std::cout << "Note : ";
        std::string note;
        getline(std::cin, note, '\n');
        std::cout << std::endl;
        fout << "Note : " << note << std::endl;

        std::cout << "[SUCCESS] Le dossier médical \"" << new_patient->get_chemin_acces_dossier_medical() << "\" a bien été créé." << std::endl;

        this->get_vector_patients()->push_back(new_patient); //ajout du patient au vecteur de patients si toute l'arborescence et le dossier médical ont bien été créés
        std::cout << "\n[SUCCESS] Le patient " << "\""+prenom+" "+nom+"\"" << " a bien été ajouté.\n" << std::endl;
        fout.clear();
        fout.close(); // fermeture fichier en cas de succès écriture
    }else{
        std::cerr << "[CreateFileError] Impossible de créer le dossier medical du patient " << "\""+prenom+" "+nom+"\".\n" << std::endl;
        std::string suppr_command = "rm -r "+new_patient->get_chemin_acces_patient();
        std::system(suppr_command.c_str()); // si impossible de créer le dossier medical du patient, on supprime l'arborescence créée.
        // désallocation de la mémoire du patient si impossible de créer le dossier médical
        new_patient->~t_Patient();
        new_patient = nullptr;
        return; // fin de procédure si impossible de créer le dossier médical
    }
}

/**
 * \brief supprimer un patient du centre radio
 */
void t_Centre_Radio::supprimer_patient(){
    std::string prenom_patient;
    std::string nom_patient;

    std::system("clear"); //clear du shell
    this->affiche_entete(); //affichage en-tête centre radio
    std::cout << "----------------------------------" << std::endl;
    std::cout << "###### Supprimer un patient ######" << std::endl;
    std::cout << "----------------------------------\n" << std::endl;

    // Demande des informations de recherche (nom et prénom du patient)
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//efface le flux en entier
    std::cout << "Nom du patient: ";
    getline(std::cin, nom_patient);
    nom_patient[0] = std::toupper(nom_patient[0]);
    std::cout << "Prenom du patient: ";
    getline(std::cin, prenom_patient);
    prenom_patient[0] = std::toupper(prenom_patient[0]);

    for(auto it_patient = this->get_vector_patients()->begin(); it_patient != this->get_vector_patients()->end(); it_patient++){ //navigation dans le vecteur de patients pour trouver un patient avec les nom/prénom renseignés
        if((*it_patient)->get_nom() == nom_patient && (*it_patient)->get_prenom() == prenom_patient){ //si patient trouvé
            std::string command = "rm -r "+(*it_patient)->get_chemin_acces_patient(); // pour supprimer l'arborescence du patient
            int success = std::system(command.c_str());
            if(success == 0){ //si la suppression de l'arborescence s'est bien passée, on peut supprimer le patient de l'application
                (*it_patient)->~t_Patient(); //appel du destructeur de patient
                this->get_vector_patients()->erase(it_patient); //supprime le patient du vecteur de patients
                std::cout << "\n[SUCCESS] Le patient " << "\""+prenom_patient+" "+nom_patient+"\"" << " a été supprimé.\n" << std::endl;
                return; //arrêt de la recherche et de la procédure
            }else{ //sinon affichage d'un message d'erreur et fin de procédure
                std::cout << "\n[FAILED] Echec de la suppression du patient " << "\""+prenom_patient+" "+nom_patient+"\"." << std::endl;
                return;
            } 
        }
    }//sinon, si aucun patient avec nom et prénom saisis n'a été trouvé, affichage d'un message d'erreur
    std::cout << "[FAILED] Aucun patient " << "\""+prenom_patient+" "+nom_patient+"\" n'a été trouvé.\n" << std::endl;
}

/**
 * \brief ajouter un praticien au centre radio
 */
void t_Centre_Radio::ajouter_praticien(){
    char nom_char[40]; 
    char prenom_char[40];
    char id_char[40];
    char mdp_char[60];
    char sexe[2];
    unsigned short j, m, a, age;

    std::system("clear"); //clear du shell
    this->affiche_entete(); //affichage en-tête centre radio (numéro d'examen unique)
    std::cout << "----------------------------------" << std::endl;
    std::cout << "###### Ajouter un praticien ######" << std::endl;
    std::cout << "----------------------------------\n" << std::endl;
    
    // Demande de saisie des informations du praticien
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //efface le flux en entier avant la saisie
    
    // Demande du nom
    std::cout << "Nom: ";
    std::scanf("%40s", nom_char);
    std::string nom = nom_char; // récupération d'une string à partir du tableau de char

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //efface le flux en entier après la saisie

    // vérifie la présence d'espaces dans le nom du praticien, si présence, affichage d'un message d'erreur et abandon de la suppression praticien
    for(int i=0; i<nom.length(); i++){
            if(nom[i] == ' '){
                std::cout << std::endl;
                std::cerr << "[TypingError] Les espaces sont interdits dans le nom d'un praticien.\n" << std::endl;
                std::cerr << "Echec de la création du praticien.\n" << std::endl;
                return;
            }
    }
    nom[0] = std::toupper(nom[0]); //ajoute la majuscule au premier caractère du nom si oubliée

    // Demande du prénom
    std::cout << "Prenom: ";
    std::scanf("%40s", prenom_char);
    std::string prenom = prenom_char;// récupération d'une string à partir du tableau de char
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //efface le flux en entier après la saisie pour éviter tout résidu dans le flux

    // vérifie la présence d'un espace dans le prénom du praticien, si présence, affichage d'un message d'erreur et abandon de la suppression du praticien
    for(int i=0; i<prenom.length(); i++){
        if(prenom[i] == ' '){
            std::cout << std::endl;
            std::cerr << "[TypingError] Les espaces sont interdits dans le prenom d'un praticien.\n" << std::endl;
            std::cerr << "Echec de la création du praticien.\n" << std::endl;
            return;
        }
    }

    prenom[0] = std::toupper(prenom[0]); //ajoute la majuscule au premier caractère du prénom si oubliée

    // Demande de l'âge
    std::cout << "Age: ";
    int scan_age = std::scanf("%hu", &age);
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //efface le flux en entier après la saisie pour éviter tout résidu dans le flux
    
    // vérification de la saisie de l'âge (unsigned short), sinon affichage d'un message d'erreur
    if(scan_age != 1){
        std::cout << std::endl;
        std::cerr << "[TypingError] Saisie incorrecte de l'age du praticien à créer." << std::endl;
        std::cerr << "Echec de la création du praticien.\n" << std::endl;
        return;
    }

    // Demande de saisie du sexe
    std::cout << "Sexe (H/F): ";
    std::scanf("%c", sexe);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //efface le flux en entier après la saisie

    sexe[0] = std::toupper(sexe[0]); // mise en majuscule pour accepter les saisies "h" ou "f"

    bool sexe_bool; // stocke le booléen associé au sexe
    
    // vérification de la saisie du sexe et association de la bonne valeur booléenne à sexe_bool
    if(sexe[0] == 'H'){ // retrouve le booléen associé au sexe entré sous forme de char
        sexe_bool = true;
    }else if(sexe[0] == 'F'){
        sexe_bool = false;
    }else{ // sinon affichage d'un message d'erreur et échec de la création du patient
        std::cout << std::endl;
        std::cerr << "[TypingError] Saisie incorrecte du sexe du praticien à créer." << std::endl;
        std::cerr << "Echec de la création du praticien.\n" << std::endl;
        return;
    }

    // Demande de saisie de la date
    std::cout << "Date de naissance (jj/mm/aaaa): ";
    int scan_date = std::scanf("%2hu%*1[/]%2hu%*1[/]%4hu", &j, &m, &a); //scan_date contient le nombre de valeurs correctement assignées
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //efface le flux en entier après la saisie
    
    // Vérification du format de la date saisie, affichage d'un message d'erreur en cas d'échec
    if(scan_date != 3){
        std::cout << std::endl;
        std::cerr << "[TypingError] La saisie de la date n'est pas au format date jj/mm/aaaa.\n" << std::endl;
        std::cerr << "Echec de la création du patient.\n" << std::endl;
        return;
    }

    // Demande du mot de passe pour le nouveau praticien
    std::cout << "Mot de passe: ";
    std::scanf("%60s", mdp_char);
    std::string mdp = mdp_char;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

    // Vérifie la présence d'espaces dans le mot de passe, si présence, affichage d'un message d'erreur et échec de la création du praticien
    for(int i=0; i<mdp.length(); i++){
        if(mdp[i] == ' '){
            std::cout << std::endl;
            std::cerr << "[TypingError] Les espaces sont interdits dans un mot de passe.\n" << std::endl;
            std::cerr << "Echec de la création du praticien.\n" << std::endl;
            return;
        }
    }   

    // Demande de saisie de l'identifiant du praticien
    std::cout << "Identifiant: ";
    std::scanf("%40s", id_char);
    std::string id = id_char;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //efface le flux en entier après les saisies

    // vérifie la présence d'espaces dans l'id du praticien, si présence, affichage d'un message d'erreur et échec de la création du praticien
    for(int i=0; i<id.length(); i++){
        if(id[i] == ' '){
            std::cout << std::endl;
            std::cerr << "[TypingError] Les espaces sont interdits dans un identifiant.\n" << std::endl;
            std::cerr << "Echec de la création du praticien\n" << std::endl;
            return;
        }
    }

    t_Praticien_ptr new_prat = new t_Praticien(nom, prenom, age, sexe_bool, j, m, a, id, mdp); // création d'un nouveau praticien
    
    // Vérification si un praticien a le même identifiant, si les noms et prénoms existent
    for(auto it_prat = this->get_vector_praticien()->begin(); it_prat != this->get_vector_praticien()->end(); it_prat++){
        if((**it_prat) == (*new_prat)){
            std::cerr << "\n[ERROR] Ce praticien existe déjà. Abandon de la création du praticien.\n" << std::endl;
            return; //fin de procédure si le praticien existe déjà
        }
    }

    this->get_vector_praticien()->push_back(new_prat); //ajout du praticien au vecteur de praticiens
    std::cout << "\nLe praticien " << "\""+prenom+" "+nom+"\"" << " a bien été ajouté.\n" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "Récapitulatif des informations saisies:" << std::endl;
    std::cout << "---------------------------------------\n" << std::endl;
    new_prat->affiche_praticien(); // récapitulatif des informations saisies pour le nouveau praticien créé
    std::cout << std::endl;
}

/**
 * \brief supprimer un praticien du centre radio
 */
void t_Centre_Radio::supprimer_praticien(){
    std::string id_praticien;
    std::string mdp_praticien;

    std::system("clear"); //clear du shell
    this->affiche_entete(); //affichage en-tête centre radio
    std::cout << "------------------------------------" << std::endl;
    std::cout << "###### Supprimer un praticien ######" << std::endl;
    std::cout << "------------------------------------\n" << std::endl;
    std::cout << "Veuillez saisir l'identifiant et le mot de passe du praticien à supprimer.\n" << std::endl; //pour plus de sécurité, besoin de l'identifiant et du mot de passe du praticien à supprimer

    // Demande des informations de recherche (id et mdp du praticien à supprimer)
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//efface le flux en entier
    std::cout << "Identifiant praticien: ";
    getline(std::cin, id_praticien);
    std::cout << "Mot de passe praticien: ";
    getline(std::cin, mdp_praticien);
    std::cout << std::endl;

    for(auto it_prat = this->get_vector_praticien()->begin(); it_prat != this->get_vector_praticien()->end(); it_prat++){ //navigation dans le vecteur de praticiens pour trouver id et mdp du praticien
        if( id_praticien == (*it_prat)->get_id() && mdp_praticien == (*it_prat)->get_mdp()){ //si le praticien a été trouvé
            std::cout << "Le praticien " << "\"" << (*it_prat)->get_nom() << " " << (*it_prat)->get_prenom() << "\"" << " correspond à l'identifiant et au mot de passe saisi." << std::endl;
            
            // demande de confirmation de suppression du praticien
            std::cout << "Voulez-vous vraiment le supprimer ? Y/N: ";
            char choix;
            std::scanf("%c", &choix);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //efface le flux en entier après la saisie
            if(choix == 'Y'){
                (*it_prat)->~t_Praticien(); //appel du destructeur de praticien
                this->get_vector_praticien()->erase(it_prat); // supprime le praticien du vecteur de praticien
                std::cout << "\n[SUCCESS] Le praticien " << "\""+(*it_prat)->get_prenom()+" "+(*it_prat)->get_nom()+"\"" << " a été supprimé.\n" << std::endl;
                return; //arrêts de la recherche et de la procédure
            }
            
            std::cerr << "\n[CANCEL] Suppression du praticien interrompue.\n" << std::endl;
            return; //arrêt de la recherche car praticien trouvé mais annulation de la suppression du praticien
        }
    }// sinon : si aucun praticien avec l'id et le mdp recherchés n'existe
    std::cout << "[FAILED] Aucun praticien ne correspond à l'identifiant et au mot de passe donnés.\n" << std::endl;
}

/**
 * \brief ajouter une radio à un patient du centre radio
 */
void t_Centre_Radio::ajouter_radio(){
    std::system("clear"); //clear du shell
    this->affiche_entete(); //affichage en-tête du centre radio
    std::cout << "-------------------------------" << std::endl;
    std::cout << "###### Ajouter une radio ######" << std::endl;
    std::cout << "-------------------------------\n" << std::endl;

    std::string nom_patient, prenom_patient, mdp;
    unsigned short etat_nb, j, m, a, nb_clich;
    int type_radio;
    bool etat;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //efface le flux en entier avant la saisie

    // demande de saisie du patient auquel ajouter la radio
    std::cout << "Patient concerné:" << std::endl;
    std::cout << "-----------------" << std::endl;
    std::cout << "Nom patient: ";
    getline(std::cin, nom_patient, '\n');
    std::cout << "Prenom patient: ";
    getline(std::cin, prenom_patient, '\n');
    std::cout << std::endl;

    // ajout des majuscules aux nom et prénom en cas d'oubli
    prenom_patient[0] = std::toupper(prenom_patient[0]);
    nom_patient[0] = std::toupper(nom_patient[0]);
    
    // demande de saisie des informations de la radio
    std::cout << "Informations de la radio:" << std::endl;
    std::cout << "-------------------------" << std::endl;
    std::cout << "Etat: (0: planifiée, 1: effectuée): ";
    int scan_etat = std::scanf("%hu", &etat_nb);
    std::cout << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //efface le flux en entier après la saisie

    // affecte la bonne valeur booléenne à l'état de la radio
    if(scan_etat == 1){
        switch(etat_nb){ //vérifie la saisie correcte de l'état
            case 0: etat = false; break;
            case 1: etat = true; break;
            default: // en cas d'erreur de saisie, affichage d'un message d'erreur et abandon de la création de la radio
                std::cerr << "[TypingError] Saisie incorrecte de l'état de la radio.\n" << std::endl;
                std::cerr << "[FAILED] Echec de la création de la radio.\n" << std::endl;
            return;
            break;
        }
    }else{ //sinon : si erreur de saisie, affichage d'un message d'erreur et abandon de la création de la radio
        std::cerr << "[TypingError] Saisie incorrecte de l'état de la radio.\n" << std::endl;
        std::cerr << "[FAILED] Echec de la création de la radio.\n" << std::endl;
        return;
    }

    // demande de saisie de la date de la radio
    std::cout <<"Date radio (jj/mm/aaaa): ";
    int scan_date = std::scanf("%2hu%*1[/]%2hu%*1[/]%4hu", &j, &m, &a);
    std::cout << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //efface le flux en entier après la saisie
    
    // Vérification du format de la saisie, si erreur, affichage d'un message d'erreur et échec de la création de la radio
    if(scan_date != 3){
        std::cerr << "[TypingError] La saisie de la date n'est pas au format date jj/mm/aaaa.\n" << std::endl;
        std::cerr << "[FAILED] Echec de la création de la radio.\n" << std::endl;
        return;
    }

    t_Date date_radio_tdate = t_Date(j, m, a); // création d'une date radio pour recherche le numéro d'examen unique
    unsigned int num_exam = this->generer_num_exam_unique(date_radio_tdate); //générer un numéro d'examen unique à partir de la date de la radio

    // demande de saisie du type de radio
    std::cout << "Type radio (0: Rayon X, 1: Ultrason, 2: IRM): ";
    std::scanf("%d", &type_radio);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //efface le flux en entier après la saisie
    std::cout << std::endl;

    //vérification du type radio saisi, en cas de saisie incorrecte, affiche un message d'erreur et échec de la création de la radio
    if(!(type_radio == 0 || type_radio == 1 || type_radio == 2)){ //si le type radio n'est ni 0, 1 ou 2
        std::cout << std::endl;
        std::cerr << "[TypingError] La saisie du type de la radio est incorrecte.\n" << std::endl;
        std::cerr << "[FAILED] Echec de la création de la radio.\n" << std::endl;
        return;
    }

    // demande de saisie d'un nouveau mot de passe pour le compte rendu de la radio en cours de création
    std::cout << "Mot de passe du compte rendu: ";
    getline(std::cin, mdp, '\n');
    std::cout << std::endl;

    for(int i=0; i<mdp.length(); i++){ //Vérification de la présence d'espaces dans le mot de passe du compte rendu, si présence, affichage d'un message d'erreur et échec de la création de la radio
        if(mdp[i] == ' '){
            std::cerr << "[TypingError] Les espaces sont interdits dans un mot de passe.\n" << std::endl;
            std::cerr << "[FAILED] Echec de la création de la radio.\n" << std::endl;
            return;
        }
    }

    if(etat){ //si la radio est effectuée, on demande le nombre de clichés (clichés présent seulement dans des radios effectuées)
        std::cout << "Nombre de clichés: ";
        int scan_nb = std::scanf("%hu", &nb_clich);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //efface le flux en entier après la saisie
        std::cout << std::endl;

        if(scan_nb != 1){ //vérification saisie correcte du nombre (nb) de clichés, si saisie incorrecte, affichage d'un message d'erreur et échec de création de la radio
            std::cerr << "[TypingError] La saisie du nombre de clichés est incorrecte.\n" << std::endl;
            std::cerr << "[FAILED] Echec de la création de la radio.\n" << std::endl;
        return;
        }
    }else{
        nb_clich = 0; // aucun cliché si l'état est "planifiée"
    }
    
    //recherche du patient saisi dans le vecteur de patients
    for(auto it_patient = this->get_vector_patients()->begin(); it_patient != this->get_vector_patients()->end(); it_patient++){
        if( (*it_patient)->get_nom() == nom_patient && (*it_patient)->get_prenom() == prenom_patient){
            t_Radiographie_ptr new_radio = new t_Radiographie(num_exam, etat, j, m, a, (t_type_Radio)type_radio, mdp, (*it_patient)->get_chemin_acces_patient()); //création de la radio
            
            //ajout clichés au vecteur de clichés en fonction du nb de clichés
            for(unsigned short i = 1; i<=nb_clich; i++){
                t_Cliche_ptr new_clich = new t_Cliche(i, new_radio->get_num_exam_unique(), new_radio->get_chemin_acces_radio()); // création d'un cliché
                new_radio->get_vector_cliches()->push_back(new_clich); //ajouter un cliché
            }

            //création de l'arborescence radio pour le patient en question
            std::string command = "mkdir -p "+new_radio->get_chemin_acces_radio()+"cliches/"; //création des sous-répertoires radios et clichés du patient
            int success = std::system(command.c_str()); //execution commande création arborescence radio
            
            // vérifie le succès de la création de l'arborescence pour la radio
            if(success == 0){
                std::cout << "[SUCCESS] L'arborescence pour la radio " << new_radio->get_num_exam_unique() << " a bien été créée." << std::endl;

                // Création des fichiers de clichés (png) au bon endroit dans l'arborescence de la radio
                for(auto it_cliche = new_radio->get_vector_cliches()->begin(); it_cliche != new_radio->get_vector_cliches()->end(); it_cliche++){ //parcours du vecteur de clichés de la radio
                   
                    std::string command_cliche = "touch "+((*it_cliche)->get_chemin_acces_cliche()); // création de la commande de création du fichier de cliché
                    int success_cliche_file = std::system(command_cliche.c_str()); // création du fichier de cliché
    
                    if (success_cliche_file != 0){ //vérification de la création du fichier cliché, sinon pas de création de radio et désallocation mémoire + suppression de l'arborescence précédemment créée
                        std::cerr << "[CreateFileError] Impossible de créer le cliché " << "\""+(*it_cliche)->get_chemin_acces_cliche()+"\". Abandon de la création de la radio.\n" << std::endl;
                        std::string suppr_command = "rm -r "+new_radio->get_chemin_acces_radio();
                        std::system(suppr_command.c_str()); // si impossible de créer les clichés, on supprime l'arborescence créée.
                        // désallocation de la mémoire pour new_radio
                        new_radio->~t_Radiographie();
                        new_radio = nullptr;
                        return;
                    }else{ // sinon affichage d'un message de succès pour la création du cliché
                        std::cout << "[SUCCESS] Cliché créé: " << "\""+(*it_cliche)->get_chemin_acces_cliche()+"\".\n" << std::endl;
                    }
                }

                // Création du fichier de compte-rendu pour la radio
                std::ofstream fout(new_radio->get_compte_rendu().get_chemin_acces_compte_rendu());

                if(fout.is_open()){ // si le fichier est ouvert, écriture dans le fichier (avec complétion automatique pour plusieurs champs)
                    fout << "****************************" << std::endl;
                    fout << "*** Compte Rendu Médical ***" << std::endl;
                    fout << "****************************\n" << std::endl;
                    fout << "*** Patient ***" << std::endl;
                    fout << "Nom : " << (*it_patient)->get_nom() << std::endl;
                    fout << "Prenom : " << (*it_patient)->get_prenom() << std::endl;
                    fout << "Age : " << (*it_patient)->get_str_age() << std::endl;
                    fout << "Sexe : " << (*it_patient)->get_str_sexe() << std::endl;
                    fout << "Date de naissance : " << (*it_patient)->get_date_naissance().get_str_date() << std::endl;
                    fout << std::endl;
                    fout << "*** Radiographie ***" << std::endl;
                    fout << "Numero d'examen unique : " << new_radio->get_num_exam_unique() << std::endl;
                    fout << "Etat : " << new_radio->get_str_etat() << std::endl;
                    fout << "Date : " << new_radio->get_date_radio().get_str_date() << std::endl;
                    fout << "Type de radiographie : " << new_radio->get_str_type_radio() << std::endl;
                    fout << "Nombre de clichés : " << std::to_string(nb_clich) << std::endl;
                    fout << std::endl;
                    fout << "*** Informations ***" << std::endl;
                    if(new_radio->get_etat()){ //seulement si la radio a été effectuée alors demande la saisie d'une note
                        std::cout << "Ajouter une note au compte rendu rendu medical de la radio: " << std::endl;
                        std::string note;
                        getline(std::cin, note, '\n');
                        std::cout << std::endl;
                        fout << "Note : " << note << std::endl;
                    }else{ // Pas de saisie de note si la radio n'a pas été effectuée, juste écriture dans le fichier de la ligne "Note :"
                        fout << "Note : " << std::endl;
                    }

                    std::cout << "[SUCCESS] Le compte rendu " << "\""+new_radio->get_compte_rendu().get_nom_fichier()+"\" " << "a été créé avec succès." << std::endl;
                    fout.clear();
                    fout.close();
                }else{ //si pas de création fichier compte-rendu, désallocation mémoire t_Radiographie
                    std::cerr << "[CreateFileError] Impossible d'éditer le compte rendu medical pour la radio \"" << std::to_string(new_radio->get_num_exam_unique())+"\". Abandon de la création de la radio.\n" << std::endl;
                    std::string suppr_command = "rm -r "+new_radio->get_chemin_acces_radio();
                    std::system(suppr_command.c_str()); // si impossible de créer les clichés, on supprime l'arborescence créée.
                    // désallocation mémoire
                    new_radio->~t_Radiographie();
                    new_radio = nullptr;
                    return;
                }

                (*it_patient)->get_vector_radios()->push_back(new_radio); // ajout de la radio au vecteur de radios du patient si l'arborescence ainsi que le compte-rendu ont bien été créés
                std::cout << "[SUCCESS] La radio " << "\""+std::to_string(new_radio->get_num_exam_unique())+"\"" << " a bien été enregistrée pour le patient " << "\""+(*it_patient)->get_prenom()+" "+(*it_patient)->get_nom()+"\"." << std::endl;
                return;
            }else{ // sinon si impossible de créer l'arborescence de la radio, affichage d'un message d'erreur et désallocation de la mémoire
                std::cerr << "[CreateDirError] Impossible de créer l'arborescence pour la radio " << new_radio->get_num_exam_unique() << ". Abandon de la création de la radio.\n" << std::endl;
                new_radio->~t_Radiographie();
                new_radio = nullptr;
                return;
            }
        }
    }
    //si aucun patient trouvé, affichage d'un message d'erreur
    std::cerr << "[FAILED] Aucun patient " << "\""+prenom_patient+" "+nom_patient+"\" " << "n'existe dans le centre radio. Abandon de la création de la radio." << std::endl;
}

/**
 * \brief génère un numéro d'examen unique pour une nouvelle radio
 * \param date_radio date de la radio
 * \return unsigned numéro d'examen unique
 */
unsigned t_Centre_Radio::generer_num_exam_unique(t_Date& date_radio) const{ //pas besoin unsigned short
    std::string try_num_exam = std::to_string(date_radio.get_jour())+std::to_string(date_radio.get_mois())+std::to_string(date_radio.get_annee()); //créer un numéro d'examen avec la date sous forme de chaîne de caractère
    unsigned nb_essais = 0;
    
    label: //label pour goto
        //navigation dans le vecteur de radios de chaque patient du vecteur de patients
        for(auto it_patient = this->get_vector_patients()->begin(); it_patient != this->get_vector_patients()->end(); it_patient++){
            for(auto it_radio = (*it_patient)->get_vector_radios()->begin(); it_radio != (*it_patient)->get_vector_radios()->end(); it_radio++){
                if ((*it_radio)->get_num_exam_unique() == atoi(try_num_exam.c_str())){ //si le numéro d'examen essayé existe déjà dans le centre radio
                    nb_essais+=1; //incrémentation de l'indice du numéro d'examen
                    if(nb_essais-1 != 0){ //si ce n'est pas le premier essai alors on remplace le dernier chiffre par nb_essais+1
                        try_num_exam[try_num_exam.length()-1] = (std::to_string(nb_essais)).c_str()[0]; //std::to_string(nb_essais); //reformation du numéro d'examen
                    }else{ //si c'est le premier essai on concatène 1 au num_exam_radio
                        try_num_exam+= std::to_string(nb_essais);
                    }
                    goto label; //retourne avant les boucles for (au label:) pour recommencer la recherche avec le nouveau numéro d'examen à tester
                } 
            }
        }
    return atoi(try_num_exam.c_str());
}

/**
 * \brief supprimer une radio
 */
void t_Centre_Radio::supprimer_radio(){
    std::system("clear"); //clear du shell
    this->affiche_entete(); //affichage en-tête centre radio
    std::cout << "---------------------------------" << std::endl;
    std::cout << "###### Supprimer une radio ######" << std::endl;
    std::cout << "---------------------------------\n" << std::endl;

    std::string nom_patient, prenom_patient;

    // Demande de saisie des informations du patient pour lequel supprimer la radio
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //efface le flux en entier avant la saisie
    std::cout << "Patient concerné:" << std::endl;
    std::cout << "-----------------" << std::endl;

    // Demande de saisie du nom
    std::cout << "Nom patient: ";
    getline(std::cin, nom_patient, '\n');
    std::cout << "Prenom patient: ";

    // Demande de saisie du prénom
    getline(std::cin, prenom_patient, '\n');
    std::cout << std::endl;

    //ajout des majuscules au noms de patient en cas d'oubli
    prenom_patient[0] = std::toupper(prenom_patient[0]);
    nom_patient[0] = std::toupper(nom_patient[0]);

    t_Patient_ptr patient = nullptr; //pointeur temporaire sur le patient trouvé, initialisation à nullptr

    // navigation dans le vecteur de patients pour trouver le patient recherché
    for(auto it_patient = this->get_vector_patients()->begin(); it_patient != this->get_vector_patients()->end(); it_patient++){
        if( (*it_patient)->get_nom() == nom_patient && (*it_patient)->get_prenom() == prenom_patient){
            std::cout << "Liste des radiographies de " << "\""+prenom_patient << " " << nom_patient+"\"" << std::endl;
            (*it_patient)->affiche_patient(&compare_radios_date); //affichage de la liste des radiographies pour le patient en question
            patient = (*it_patient); //récupération d'un pointeur sur le patient trouvé
            break; // arrête la boucle quand le patient a été trouvé
        }
    }

    if(patient == nullptr){ //si aucun patient trouvé, affichage d'un message d'erreur et échec de la suppression de la radio
        std::cout << "[FAILED] Aucun patient " << "\""+prenom_patient+" "+nom_patient+"\" " << "n'existe dans le centre radio. Abandon de la suppression de la radio.\n" << std::endl;
        return; //fin de procédure si aucun patient ne correspond à la recherche
    }

    unsigned num_exam; //num exam de la radio à supprimer

    // Demande du numéro d'examen de la radio à supprimer
    std::cout << "Entrez le numéro d'examen de la radio à supprimer: ";
    int scan_value = std::scanf("%u", &num_exam);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //efface le flux en entier après la saisie

    std::cout << std::endl;

    // vérifie la saisie du numéro d'exaxmen (unsigned int), si erreur, affichage d'un message d'erreur et échec de la suppression de la radio
    if(scan_value != 1){
        std::cerr << "[TypingError] La saisie du numéro d'examen de la radio est incorrecte. Abandon de la suppression de la radio.\n" << std::endl;
        return; //fin de procédure si saisie incorrecte.
    }

    for(auto it_radio = patient->get_vector_radios()->begin(); it_radio != patient->get_vector_radios()->end(); it_radio++){ //parcours des radios du patient pour rechercher la radio correspondant au numéro d'examen unique
        if(num_exam == (*it_radio)->get_num_exam_unique()){ //si la radio existe pour ce patient
            //demande de confirmation de suppression de la radio
            std::cout << "Voulez-vous vraiment supprimer la radio " << (*it_radio)->get_num_exam_unique() << " ? (Y/n): ";
            char choix;
            std::scanf("%c", &choix);
            std::cout << std::endl;
            if(choix == 'Y'){ //si suppression validée
                //suppression arborescence
                std::string suppr_command = "rm -r "+(*it_radio)->get_chemin_acces_radio();
                int suppr = std::system(suppr_command.c_str());
                if(suppr == 0){
                    // suppression de la radio dans le centre
                    (*it_radio)->~t_Radiographie(); //destruction de la radiographie
                    patient->get_vector_radios()->erase(it_radio); //supprime la radio du vecteur radio du patient
                    std::cout << "[SUCCESS] Radiographie " << "\""+std::to_string(num_exam) << "\" a bien été supprimée." << std::endl;
                    return; //fin de procédure std::cout << "[SUCCESS] L'arborescence pour la radio \"" << (*it_radio)->get_num_exam_unique() << "\" a bien été supprimée." << std::endl;
                }else{// si la suppression de l'arborescence n'a pas fonctionnée
                    std::cout << "[FAILED] Echec de la suppression de la radio" << "\""+(*it_radio)->get_num_exam_unique() << "\"\n" << std::endl;
                    return;
                }
            }else{ // si l'utilisateur a annulé la suppression de la radio
                std::cout << "[CANCEL] Annulation de la suppression de la radio.\n" << std::endl;
                return; //fin de procédure
            }
        }
    } // sinon si aucune radio avec le numéro d'examen recherché n'existe
    std::cout << "[FAILED] Aucune radio " << "\""+std::to_string(num_exam)+"\"" << "trouvée pour le patient " << "\""+patient->get_prenom()+" "+patient->get_nom()+"\".\n" << std::endl;
}

/**
 * \brief afficher le compte rendu d'une radio
 */
void t_Centre_Radio::acceder_compte_rendu_radio() const{
    std::string nom_patient, prenom_patient;
    
    std::system("clear"); //clear du shell
    this->affiche_entete(); //affichage en-tête centre radio
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "###### Accéder au compte rendu d'une radio ######" << std::endl;
    std::cout << "-------------------------------------------------\n" << std::endl;

    //Demande des informations sur le patient concerné
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //efface le flux en entier
    std::cout << "Nom du patient: ";
    getline(std::cin, nom_patient);
    nom_patient[0] = std::toupper(nom_patient[0]);
    std::cout << "Prenom du patient: ";
    getline(std::cin, prenom_patient);
    prenom_patient[0] = std::toupper(prenom_patient[0]);
    std::cout << std::endl;

    t_Patient_ptr myPatient = nullptr; // pointeur sur patient pour garder en mémoire le patient recherché, initialisé à nullptr
    
    //navigation dans le vecteur de patients et recherche du patient demandé
    for(auto it_patient = this->get_vector_patients()->begin(); it_patient !=  this->get_vector_patients()->end(); it_patient++){
        if( ((*it_patient)->get_prenom() == prenom_patient) && ((*it_patient)->get_nom() == nom_patient) ){ //si patient trouvé, affichage des différents comptes-rendus disponibles
            myPatient = (*it_patient); // on garde en mémoire le patient trouvé

            // affichage de la liste des comptes-rendus disponibles pour ce patient
            std::cout << "Comptes-rendus disponibles pour le patient " << "\""+prenom_patient+" "+nom_patient+"\":" << std::endl;
            for(auto it_radio = (*it_patient)->get_vector_radios()->begin(); it_radio != (*it_patient)->get_vector_radios()->end(); it_radio++){
                std::cout << "- "+(*it_radio)->get_compte_rendu().get_nom_fichier() << std::endl;
            }
            break; //arrêt de la recherche quand le patient a été trouvé 
        }
    }

    unsigned searched_num_exam;
    if(myPatient != nullptr){ //si le patient a bien été trouvé, alors demande de la saisie d'un numéro de radio
        std::cout << "\nNuméro d'examen du compte rendu à afficher: ";
        int scan_val = std::scanf("%u", &searched_num_exam);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //efface le flux en entier après la saisie
        
        if(scan_val != 1){ //vérification de la saisie du numéro d'examen
            std::cerr << "\n[TypingError] Saisie incorrecte. Le numéro d'examen doit être sous la forme d'un nombre entier." << std::endl << std::endl;
            return;
        }

        // parcours du vecteur de radios du patient jusqu'à trouver le numéro d'examen saisi
        for(auto it_radio = myPatient->get_vector_radios()->begin(); it_radio != myPatient->get_vector_radios()->end(); it_radio++){
            if((*it_radio)->get_num_exam_unique() == searched_num_exam){ //si le numéro d'examen recherché correspond à un des numéros d'examens des radios du patient demandé
                (*it_radio)->get_compte_rendu().affiche_compte_rendu(); //affichage du compte-rendu de la radio
                std::cout << std::endl;
                return; // fin de procédure quand radio trouvée
            }
        }
    }else{ // si aucun patient n'a été trouvé
        std::cerr << "[FAILED] Aucun patient " << "\""+prenom_patient+" "+nom_patient+"\"" << " n'existe dans le centre radio.\n" << std::endl;
        return;
    }//sinon, si la radio n'a pas été trouvée
    std::cerr << "\n[FAILED] Aucune radio " << "\""+std::to_string(searched_num_exam)+"\"" << " n'a été trouvée pour le patient " << "\""+prenom_patient+" "+nom_patient+"\"." << " Impossible d'afficher le compte-rendu.\n" << std::endl;
}

/**
 * \brief afficher le dossier médical d'un patient
 */
void t_Centre_Radio::acceder_dossier_medical_patient() const{
    std::string nom_patient, prenom_patient;
    
    std::system("clear"); //clear du shell
    this->affiche_entete(); //affichage en-tête centre radio
    std::cout << "-----------------------------------------------------" << std::endl;
    std::cout << "###### Accéder au dossier médical d'un patient ######" << std::endl;
    std::cout << "-----------------------------------------------------\n" << std::endl;

    // demande de saisie du nom et prénom pour le patient concerné
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //efface le flux en entier
    std::cout << "Nom du patient: ";
    getline(std::cin, nom_patient);
    nom_patient[0] = std::toupper(nom_patient[0]);
    std::cout << "Prenom du patient: ";
    getline(std::cin, prenom_patient);
    prenom_patient[0] = std::toupper(prenom_patient[0]);
    std::cout << std::endl;

    //navigation dans le vecteur de patients pour rechercher le patient demandé
    for(auto it_patient = this->get_vector_patients()->begin(); it_patient !=  this->get_vector_patients()->end(); it_patient++){
        if( ((*it_patient)->get_prenom() == prenom_patient) && ((*it_patient)->get_nom() == nom_patient) ){ //si le patient est trouvé
            (*it_patient)->afficher_dossier_medical(); //affichage du dossier médical
            return;
        }
    }//sinon, si aucun patient nec orrespond à la recherche

    std::cout << "[FAILED] Aucun patient " << "\""+prenom_patient+" "+nom_patient+"\"" << " n'existe dans le centre radio.\n" << std::endl;
}

/**
 * \brief menu rechercher
 */

void t_Centre_Radio::rechercher(){
    std::system("clear"); //clear du shell
    this->affiche_entete(); //affichage en-tête centre radio
    std::cout << "-------------------------------" << std::endl;
    std::cout << "###### Menu de recherche ######" << std::endl;
    std::cout << "-------------------------------\n" << std::endl;
    
    std::cout << "1 - Rechercher les radios d'un patient via son nom et son prenom" << std::endl;
    std::cout << "2 - Rechercher une radio via le numéro d'examen" << std::endl;
    std::cout << "3 - Rechercher les radios selon une date" << std::endl;
    std::cout << "4 - Retour" << std::endl;
    std::cout << "Sélectionner: ";

    unsigned short choix_nb;
    std::cin >> choix_nb; //saisie de l'utilisateur
    std::cout << std::endl;

     if(!std::cin){ //vérifie que la valeur saisie est correcte (un entier short), sinon vide le flux et retour au menu principal
        std::cout << "[TypingError] Saisie incorrecte.\n" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //efface le flux en entier
        return; //fin de procédure retour au menu principal
    }

    switch(choix_nb){
            case 1: this->rechercher_radios_patient(); break;
            case 2: this->rechercher_radio_num_exam(); break;
            case 3: this->rechercher_radio_date_exam(); break;
            case 4: std::system("clear"); this->affiche_entete(); return; break;
            default: std::cout << "[FAILED] Aucune option ne correspond à la valeur saisie.\n" << std::endl; return; break;
    }
}

/**
 * \brief menu afficher (patients et radios, dossier médical, compte-rendu, toutes les informations du centre)
 */
void t_Centre_Radio::afficher(){
    std::system("clear"); //clear du shell
    this->affiche_entete(); //affichage en-tête centre radio
    std::cout << "-------------------------------" << std::endl;
    std::cout << "###### Menu d'affichage ######" << std::endl;
    std::cout << "-------------------------------\n" << std::endl;
    
    std::cout << "1 - Afficher les caractéristiques des radios par patients" << std::endl; 
    std::cout << "2 - Afficher le dossier médical d'un patient" << std::endl;
    std::cout << "3 - Afficher le compte rendu d'une radio" << std::endl;
    std::cout << "4 - Afficher toutes les informations du centre radio" << std::endl;
    std::cout << "5 - Retour" << std::endl;
    std::cout << "Sélectionner: ";

    unsigned short choix_nb;
    std::cin >> choix_nb; //saisie de l'utilisateur
    std::cout << std::endl;

     if(!std::cin){ //vérifie que la valeur saisie est correcte (un entier short), sinon vide le flux et retour menu principal
        std::cout << "[TypingError] Saisie incorrecte.\n" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //efface le flux en entier
        return; //fin de procédure retour au menu principal
    }

    switch(choix_nb){
        case 1: this->afficher_vector_patient_trie(); break;
        case 2: this->acceder_dossier_medical_patient(); break;
        case 3: this->acceder_compte_rendu_radio(); break;
        case 4: this->affiche_centre_radio(); break;
        case 5: std::system("clear"); this->affiche_entete(); return; break;
        default: std::cout << "[FAILED] Aucune option ne correspond à la valeur saisie.\n" << std::endl; return; break;
    }
}

/**
 * \brief menu ajouter (patient, radio, praticien)
 */
void t_Centre_Radio::ajouter(){
    std::system("clear"); //clear du shell
    this->affiche_entete(); //affichage en-tête centre radio
    std::cout << "--------------------------" << std::endl;
    std::cout << "###### Menu ajouter ######" << std::endl;
    std::cout << "--------------------------\n" << std::endl;

    std::cout << "1 - Ajouter un patient" << std::endl;
    std::cout << "2 - Ajouter une radio" << std::endl;
    std::cout << "3 - Ajouter un praticien" << std::endl;
    std::cout << "4 - Retour" << std::endl;
    std::cout << "Sélectionner: ";

    unsigned short choix_nb;
    std::cin >> choix_nb; //saisie de l'utilisateur
    std::cout << std::endl;

     if(!std::cin){ //vérifie que la valeur saisie est correcte (un entier short), sinon vide le flux et retour menu principal
        std::cout << "[TypingError] Saisie incorrecte.\n" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //efface le flux en entier
        return; //fin de procédure retour au menu principal
    }

    switch(choix_nb){
        case 1: this->ajouter_patient(); break;
        case 2: this->ajouter_radio(); break;
        case 3: this->ajouter_praticien(); break;
        case 4: std::system("clear"); this->affiche_entete(); return; break;
        default: std::cout << "[FAILED] Aucune option ne correspond à la valeur saisie.\n" << std::endl; return; break;
    }
}

/**
 * \brief menu supprimer (patient, radio, praticien)
 */
void t_Centre_Radio::supprimer(){
    std::system("clear"); //clear du shell
    this->affiche_entete(); //affichage en-tête centre radio
    std::cout << "----------------------------" << std::endl;
    std::cout << "###### Menu supprimer ######" << std::endl;
    std::cout << "----------------------------\n" << std::endl;

    std::cout << "1 - Supprimer un patient" << std::endl;
    std::cout << "2 - Supprimer une radio" << std::endl;
    std::cout << "3 - Supprimer un praticien" << std::endl;
    std::cout << "4 - Retour" << std::endl;
    std::cout << "Sélectionner: ";

    unsigned short choix_nb;
    std::cin >> choix_nb; //saisie de l'utilisateur
    std::cout << std::endl;

     if(!std::cin){ //vérifie que la valeur saisie est correcte (un entier short), sinon vide le flux et retour menu principal
        std::cout << "[TypingError] Saisie incorrecte.\n" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //efface le flux en entier
        return; //fin de procédure retour au menu principal
    }

    switch(choix_nb){
        case 1: this->supprimer_patient(); break;
        case 2: this->supprimer_radio(); break;
        case 3: this->supprimer_praticien(); break;
        case 4: std::system("clear"); this->affiche_entete(); return; break;
        default: std::cout << "[FAILED] Aucune option ne correspond à la valeur saisie.\n" << std::endl; return; break;
    }
}

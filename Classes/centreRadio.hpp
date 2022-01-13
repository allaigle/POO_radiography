/******* Auteurs: *******
Julien Paris - M2BB
Alice Laigle - M2BB
*************************/

#ifndef centreRadio_hpp
#define centreRadio_hpp

#include "personne.hpp"

class t_Centre_Radio {
    
    private:
        std::string nom;
        std::string ville;
        std::string rue;
        std::string num_rue;
        vector_t_Patient_ptr* vector_patients_ptr; //aggrégation externe: pointeur sur vecteur de t_Patient_ptr
        vector_t_Praticien_ptr* vector_praticiens_ptr; //aggrégation externe: pointeur sur vecteur de t_Praticien_ptr

	public:
        //Getter
        const std::string& get_nom() const;
        std::string get_adresse() const;
        vector_t_Patient_ptr* get_vector_patients() const;
        vector_t_Praticien_ptr* get_vector_praticien() const;

        //Setter
        void set_nom(const std::string&);
        void set_adresse(const std::string&, const std::string&, const std::string&);

        //Méthodes
        t_Praticien_ptr login() const; // connexion au centre radio, renvoie un pointeur sur le profil praticien
        void sauvegarder_etat(const std::string&) const; // sauvegarder l'état du centre radio
        void affiche_entete() const;
        void affiche_centre_radio() const;

        //ANCIENNES FONCTIONS PRATICIEN
        void menu(t_Praticien_ptr); //menu principal
        void rechercher_radios_patient() const; // rechercher les radios selon le nom et prenom d'un patient
        void rechercher_radio_num_exam() const; // rechercher les radios selon le numéro d'examen
        void rechercher_radio_date_exam() const; // rechercher les radios selon la date d'examen
        void afficher_vector_patient_trie() const; // affiche le vecteur de patient dans l'ordre alphabétique
        void ajouter_patient(); // ajouter un patient au centre radio
        void supprimer_patient(); // supprimer un patient du centre radio
        void ajouter_praticien(); // ajouter un praticien au centre radio
        void supprimer_praticien(); //supprimer un praticien du centre radio
        void ajouter_radio(); // ajouter une radio à un patient
        void supprimer_radio(); // supprimer la radio d'un patient
        unsigned generer_num_exam_unique(t_Date&) const; // générer un numéro d'examen unique à partir de la date de la radio
        void acceder_compte_rendu_radio() const; // accéder au compte-rendu d'une radio
        void acceder_dossier_medical_patient() const; // accéder au dossier médical d'un patient

        void afficher(); // menu d'affichage
        void rechercher(); // menu de recherche
        void ajouter(); // menu ajouter
        void supprimer(); // menu de suppression
        
        // Constructeur pour charger centre radio à partir d'un fichier (en argument de la commande de shell au lancement du programme)
        /**
        * \brief chargement du centre radio à partir d'un fichier
        * \param file chemin d'accès vers le fichier de sauvegarde
        */
        
        t_Centre_Radio(const std::string& file){
            std::ifstream fin; // flux de lecture du fichier de sauvegarde
            std::string s; // stocke la ligne courante
            std::string value; // stocke la valeur courante lue dans le fichier csv
            std::string delimiter = ";"; // delimiteur de valeur dans le fichier de sauvegarde
            size_t pos; // position du délimiteur dans la chaîne s
            unsigned short cpt; // compteur pour connaître la colonne du fichier de sauvgarde dans laquelle on se trouve pour assigner la valeur (value) à la bonne variable

            //variables temporaires nécessaires à la création de personnes (patients et praticiens) et de dates
            std::string nom, prenom, id_prat, mdp_prat, nom_dossier_medical;
            unsigned short age, j, m, a; //jour, mois, année pour les dates de naissance ou d'examen
            bool sexe;

            //variables temporaires pour création d'une radio
            unsigned int num_exam_unique;
            bool etat;
            t_type_Radio type_Radio;

            //variable temporaire pour création du compte-rendu associé à la radio
            std::string mdp;
            
            //variable temporaire pour création d'un cliché
            int nb_cliches;

            int cpt_patient = -1; //compteur du nombre de patients chargés pour connaître la case du vecteur de patients dans lequel ajouter la radio. initialisé à -1 car le premier patient sera à la case 

            //allocation dynamique des vecteurs de patients et de praticiens
            this->vector_praticiens_ptr = new vector_t_Praticien_ptr;
            this->vector_patients_ptr = new vector_t_Patient_ptr;

            // lecture du fichier
            fin.open(file, std::ios_base::in);
            if(fin.is_open()){
                getline(fin, s, '\n'); // premier getline pour rentrer dans la boucle
                
                while(fin){ //tant qu'on peut lire le fichier

                    // récupération de l'en-tête de ligne      
                    pos = s.find(delimiter); //recherche du premier délimiteur
                    value = s.substr(0,pos); // récupération de la valeur de la première colonne
                    cpt = 0; //remise du cpt à 0 pour chaque ligne lue 

                    // Construction de centre radio
                    if(value =="centre_radio"){ //si on est sur la ligne centre_radio
                        s.erase(0, pos + delimiter.length()); // efface de s la valeur "centre_radio"
                        
                        while((pos = s.find(delimiter)) != std::string::npos){ //tant qu'on peut trouver un délimiteur sur la ligne
                            value = s.substr(0, pos); //récupération de la valeur courante
                            
                            switch(cpt){ //selon l'itération, associe "value" à la bonne variable
                                case 0: this->nom = value; break;
                                case 1: this->ville = value; break;
                                case 2: this->rue = value; break;
                                case 3: this->num_rue = value; break;
                                default: std::cerr << "[LoadingError] Une erreur est survenue lors du chargement du centre radio. (cpt out of range)"<< std::endl; exit(2); break;
                            }

                            s.erase(0, pos + delimiter.length()); // efface la valeur courante de la ligne s, la nouvelle valeur se trouve en position 0 de s
                            cpt++;
                        }

                    // Construction des praticiens
                    }else if(value == "praticien"){
                        s.erase(0, pos + delimiter.length()); // efface de s la valeur "praticien"

                        while((pos = s.find(delimiter)) != std::string::npos){ //tant qu'on peut trouver un délimiteur sur la ligne
                            value = s.substr(0, pos);
                            
                            switch(cpt){
                                case 0: nom = value; break;
                                case 1: prenom = value; break;
                                case 2: age = (unsigned short)atoi(value.c_str()); break; //conversion de l'âge en unsigned short
                                case 3: sexe = (value=="1"); break; //si value == "1" renvoie true sinon renvoie false
                                case 4: j = (unsigned short)atoi(value.c_str()); break; // conversion du jour naissance en unsigned short
                                case 5: m = (unsigned short)atoi(value.c_str()); break; // conversion du mois naissance en unsigned short
                                case 6: a = (unsigned short)atoi(value.c_str()); break; // conversion de l'année de naissance en unsigned short
                                case 7: id_prat = value; break;
                                case 8: mdp_prat = value; break;
                                default: std::cerr << "[LoadingError] Une erreur est survenue lors du chargement d'un praticien. (cpt out of range)"<< std::endl; exit(2); break;
                            }

                            s.erase(0, pos + delimiter.length()); // efface la valeur courante de la ligne s, la nouvelle valeur se trouve en position 0 de s
                            cpt++;
                        }
                        t_Praticien_ptr current_prat = new t_Praticien(nom, prenom, age, sexe, j, m, a, id_prat, mdp_prat); //instanciation praticien et son pointeur
                        (this->vector_praticiens_ptr)->push_back(current_prat); //ajout du pointeur sur praticien au vecteur de pointeurs sur praticien

                    // Construction des patients
                    }else if(value == "patient"){
                        s.erase(0, pos + delimiter.length()); // efface de s la valeur "patient"

                        while((pos = s.find(delimiter)) != std::string::npos){
                            value = s.substr(0, pos); // efface de s la valeur "patient" 

                            switch(cpt){
                                case 0: nom = value; break;
                                case 1: prenom = value; break;
                                case 2: age = (unsigned short)atoi(value.c_str()); break;
                                case 3: sexe = (value=="1"); break;
                                case 4: j = (unsigned short)atoi(value.c_str()); break;
                                case 5: m = (unsigned short)atoi(value.c_str()); break;
                                case 6: a = (unsigned short)atoi(value.c_str()); break;
                                default: std::cerr << "[LoadingError] Une erreur est survenue lors du chargement d'un patient. (cpt out of range)" << std::endl; exit(2); break;
                            }

                            s.erase(0, pos + delimiter.length());
                            cpt++;
                        }
                        t_Patient_ptr current_patient = new t_Patient(nom, prenom, age, sexe, j, m, a); // création d'une instance de patient et son pointeur
                        (this->vector_patients_ptr)->push_back(current_patient); //ajout du patient au vecteur de patient_ptr
                        cpt_patient++; // incrémentation du nombre de patients chargés dans le vecteur
                    
                    // Construction des radios du dernier patient créé
                    }else if(value == "radio"){
                        s.erase(0, pos + delimiter.length());

                        while((pos = s.find(delimiter)) != std::string::npos){
                            value = s.substr(0, pos);

                            switch(cpt){
                                case 0: num_exam_unique = (unsigned int)atoi(value.c_str()); break;
                                case 1: etat = (value=="1"); break;
                                case 2: j = (unsigned short)atoi(value.c_str()); break;
                                case 3: m = (unsigned short)atoi(value.c_str()); break;
                                case 4: a = (unsigned short)atoi(value.c_str()); break;
                                case 5: type_Radio = t_type_Radio(atoi(value.c_str())); break;
                                case 6: mdp = value; break;
                                case 7: nb_cliches = atoi(value.c_str()); break; //récupère le nombre de clichés pour cette radiographie
                                default: std::cerr << "[LoadingError] Une erreur est survenue lors du chargement d'une radio. (cpt out of range)" << std::endl; exit(2);break;
                            }

                            s.erase(0, pos + delimiter.length());
                            cpt++;
                        }
                        t_Radiographie_ptr current_radio = new t_Radiographie(num_exam_unique, etat, j, m, a, type_Radio, mdp,((this->vector_patients_ptr)->at(cpt_patient))->get_chemin_acces_patient());

                        for(unsigned short i=1; i<=nb_cliches; i++){ // i = numero_prise, générer en fonction du nombre de clichés dans la radiographie
                                t_Cliche_ptr current_cliche = new t_Cliche(i, current_radio->get_num_exam_unique(), current_radio->get_chemin_acces_radio()); // création d'un cliché
                                (current_radio->get_vector_cliches())->push_back(current_cliche); // ajout du cliché au vecteur de clichés
                        }
                        (((this->vector_patients_ptr)->at(cpt_patient))->get_vector_radios())->push_back(current_radio); //ajoute la radio au bon patient (dernier patient créé)   
                    }

                    getline(fin, s, '\n'); //récupération de la ligne suivante
                } //end while fin
            } // end if file open
        }
        
        // Destructeur
        ~t_Centre_Radio(){
            for(size_t i=0; i<(this->vector_patients_ptr)->size();i++){
                (this->vector_patients_ptr)->at(i)->~t_Patient(); //désallocation des patients du vecteur de patients
                delete (this->vector_patients_ptr)->at(i);
            }

            for(size_t j=0; j<(this->vector_praticiens_ptr)->size(); j++){
                (this->vector_praticiens_ptr)->at(j)->~t_Praticien(); //désallocation des praticiens du vecteur de praticiens
                delete (this->vector_praticiens_ptr)->at(j); 
            }
            delete this->vector_patients_ptr; //désallocation du pointeur sur le vecteur de patients
            delete this->vector_praticiens_ptr; //désallocation du pointeur sur le vecteur de praticiens
        }
};

typedef t_Centre_Radio* t_Centre_Radio_ptr;


// Fonction de comparaison pour tri du vecteur de patients dans l'ordre alphabétique
bool compare_patient(const t_Patient_ptr, const t_Patient_ptr); // compare 2 patients - pour le tri du vecteur de patients selon le patient

#endif


/******* Auteurs: *******
Julien Paris - M2BB
Alice Laigle - M2BB
*************************/

#ifndef personne_hpp
#define personne_hpp

#include "radiographie.hpp"

class t_Personne {
    
    protected: 
        std::string nom;
        std::string prenom;
        unsigned short age;
        bool sexe; //false: F, true: H
        t_Date date_naissance;

	public:	
        //Getters
        const std::string& get_nom() const;
        const std::string& get_prenom() const;
        unsigned short get_age() const;
        bool get_sexe() const;
        t_Date& get_date_naissance();

        //Setters
        void set_nom(const std::string&);
        void set_prenom(const std::string&);
        void set_age(const unsigned short);
        void set_sexe(const bool);
       
        //Méthodes
        std::string get_str_age() const;
        std::string get_str_sexe() const;
        std::string get_str_bool_sexe() const; //renvoie la chaîne de caractères associée au sexe sous forme de valeur booléenne
        bool set_sexe_via_str(const std::string&); //renvoie le booléen correspondant au sexe sous forme de str (pour set le sexe en fonction d'une chaîne de caractères)

        // Constructeur
        t_Personne(const std::string nom, const std::string prenom, const unsigned short age, const bool sexe, const unsigned short jour, const unsigned short mois, const unsigned short annee):date_naissance(jour, mois, annee){
            this->nom = nom;
            this->prenom = prenom;
            this->age = age;
            this->sexe = sexe;
        }
        // Destructeur
        virtual ~t_Personne(){}
};

class t_Patient:public t_Personne { //classe patient héritant de la classe t_Personne
    
    private:
        std::string dossier_medical_nom;
        std::string chemin_acces_patient; // chemin d'accès au dossier du patient
        std::string chemin_acces_dossier_medical;
        vector_t_Radiographie_ptr* vector_radios_ptr; //aggrégation externe, pointeur sur vecteur de t_Radiographie_ptr

    public:
        //Getter
        const std::string& get_dossier_medical_nom() const;
        vector_t_Radiographie_ptr* get_vector_radios() const; //récupérer un pointeur sur le vecteur de radios du patient
        const std::string& get_chemin_acces_patient() const; // retourne le chemin d'accès pour le répertoire du patient
        const std::string& get_chemin_acces_dossier_medical() const; // retourne le chemin d'accès vers le dossier medical

        //Méthodes
        void afficher_dossier_medical() const; //affiche le contenu du dossier medical
        void affiche_patient(bool (*func_tri_radio)(const t_Radiographie_ptr, const t_Radiographie_ptr)); //affichage patient
        bool operator==(t_Patient const&) const; //égalité entre patients
        
        // Constructeur
        t_Patient(const std::string nom, const std::string prenom, const unsigned short age, const bool sexe, const unsigned short jour, const unsigned short mois, const unsigned short annee):t_Personne(nom, prenom, age, sexe, jour, mois, annee){
            this->dossier_medical_nom = "dossier_medical_"+(this->prenom)+"_"+(this->nom)+".txt"; //automatisation de la génération du nom du dossier medical
            this->chemin_acces_patient = "Centre_Radio/Patients/"+(this->prenom)+"_"+(this->nom)+"/";
            this->chemin_acces_dossier_medical = (this->chemin_acces_patient)+(this->dossier_medical_nom);
            this->vector_radios_ptr = new vector_t_Radiographie_ptr; //instanciation d'un vector vide
        }
        // Destructeur
        ~t_Patient(){
            for(size_t i=0; i<(this->vector_radios_ptr)->size(); i++){
                (this->vector_radios_ptr)->at(i)->~t_Radiographie(); //désallocation de tous les pointeurs du vecteur de radios
            }
            delete this->vector_radios_ptr; //désallocation du pointeur sur le vecteur de radios
        }

};

typedef t_Patient* t_Patient_ptr; //pointeur sur t_Patient
typedef std::vector<t_Patient_ptr> vector_t_Patient_ptr; // vecteur de t_Patient_ptr

class t_Praticien:public t_Personne{ //classe héritant de la classe t_Personne
    
    private:
        std::string id;
        std::string mdp;

    public:
        // Getters
        const std::string& get_id() const;
        const std::string& get_mdp() const;

        // Setters
        void set_id(const std::string&);
        void set_mdp(const std::string&);

        //Méthodes

        bool operator==(t_Praticien const&) const;
        void affiche_praticien() const;

        // méthodes pour configuration compte praticien avec interface
        void modifier_mdp();
        void modifier_id();
        void modifier_infos_perso();
        void modifier_compte_prat(const std::string&);

        // Constructeur
        t_Praticien(const std::string nom, const std::string prenom, const unsigned short age, const bool sexe, const unsigned short jour, const unsigned short mois, const unsigned short annee, const std::string id, const std::string mdp):t_Personne(nom, prenom, age, sexe, jour, mois, annee){
            this->id = id;
            this->mdp = mdp;
        }

        // Destructeur
        ~t_Praticien(){}

};

typedef t_Praticien* t_Praticien_ptr; // pointeur sur t_Praticien
typedef std::vector<t_Praticien_ptr> vector_t_Praticien_ptr; // vecteur de pointeurs sur t_Praticien

// Fonctions de comparaison pour tri des vecteurs de radios selon le numéro d'examen unique ou la date d'examen
bool compare_radios_num_exam(const t_Radiographie_ptr, const t_Radiographie_ptr);
bool compare_radios_date(const t_Radiographie_ptr, const t_Radiographie_ptr);

#endif
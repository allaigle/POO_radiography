/******* Auteurs: *******
Julien Paris - M2BB
Alice Laigle - M2BB
*************************/

#ifndef radiographie_hpp
#define radiographie_hpp

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <limits>
#include <algorithm>
#include <stdio.h>

class t_Date {
    private:
        unsigned short jour, mois, annee;

    public: 
        //Getters
        std::string get_str_date() const;
        unsigned short get_jour() const;
        unsigned short get_mois() const;
        unsigned short get_annee() const;

        //Setters
        void set_date(const unsigned short, const unsigned short, const unsigned short);

        //Méthodes
        bool operator==(t_Date const&) const;
        bool operator<(t_Date const&) const;

        // Constructeurs
        t_Date(const t_Date& d){ // constructeur de recopie // Pour un prochain développement ?
            this->jour = d.jour;
            this->mois = d.mois;
            this->annee = d.annee;
        } 

        t_Date(const unsigned short jour, const unsigned short mois, const unsigned short annee){ //constructeur utilisé
            this->jour = jour;
            this->mois = mois;
            this->annee = annee;
        }

        // Destructeur
        ~t_Date(){}
};

class t_Cliche {

    private :
        unsigned short numero_prise;
        unsigned int num_exam_cliche; // = au num_exam_unique de la radiographie à laquelle le fichier est associée
        std::string nom_cliche;
        std::string chemin_acces_cliche;
        std::string chemin_acces_radio;

    public:
        // Getters
        unsigned short get_numero_prise() const;
        unsigned int get_num_exam_cliche() const;
        const std::string& get_nom_cliche() const;
        const std::string& get_chemin_acces_cliche() const;
        
        //Setters
        void set_numero_prise(const unsigned short);

        //Constructeur
        t_Cliche(const unsigned short numero_prise, const unsigned int num_exam_cliche, const std::string chemin_acces_radio){ // num_exam_cliche = num_exam unique de la radio à laquelle est associée le cliché
            this->numero_prise = numero_prise;
            this->num_exam_cliche = num_exam_cliche;
            this->nom_cliche = "cliche_"+std::to_string(this->num_exam_cliche)+"_"+std::to_string(this->numero_prise)+".png"; // automatisation de la construction du nom du cliché
            this->chemin_acces_radio = chemin_acces_radio;
            this->chemin_acces_cliche = (this->chemin_acces_radio)+"cliches/"+(this->nom_cliche);
        }
        //Destructeur
        ~t_Cliche(){}
};

typedef t_Cliche* t_Cliche_ptr; // pointeur sur t_Cliche
typedef std::vector<t_Cliche_ptr> vector_t_Cliche_ptr; // vecteur de pointeur sur t_Cliche

class t_Compte_Rendu_Medical {

    private : 
        std::string mdp;
        std::string nom_fichier;
        std::string chemin_acces_compte_rendu;

    public:
        //Getters
        const std::string& get_mdp() const;
        const std::string& get_nom_fichier() const;
        const std::string& get_chemin_acces_compte_rendu() const;

        //Setters
        void set_mdp(const std::string&);

        //Méthodes
        void affiche_compte_rendu() const; //affichage du compte-rendu si mdp correct - lit un fichier txt - besoin du reste du chemin d'accès en paramètre pour arriver à nom_fichier
        
        //Constructeur
        t_Compte_Rendu_Medical(const std::string mdp, const unsigned int num_exam_compte_rendu, std::string chemin_acces_patient){ //num_exam_compte_rendu correspond au numéro d'examen unique de la radio
            this->mdp = mdp;
            this->nom_fichier = "compte_rendu_"+std::to_string(num_exam_compte_rendu)+".txt"; //automatisation de la génération nom dossier médical en fonction du num_exam_unique (= au num_exam_compte_rendu) de la radio
            this->chemin_acces_compte_rendu = chemin_acces_patient+"radios/"+std::to_string(num_exam_compte_rendu)+"/"+(this->nom_fichier);

        }

        //Destructeur 
        ~t_Compte_Rendu_Medical(){}
};

// Enumération des types de radios
enum t_type_Radio {
    RAYON_X, //0
    ULTRASONS, //1
    IRM  //2
}; 

class t_Radiographie {
        
    private :
        unsigned int num_exam_unique;
        bool etat; //False: planifiée, True: effectuée
        t_Date date_radio;
        vector_t_Cliche_ptr* vector_cliches_ptr; //aggrégation externe, pointeur sur vecteur de pointeurs de clichés
        t_type_Radio type_Radio;
        t_Compte_Rendu_Medical compte_rendu;
        std::string chemin_acces_radio; //chemin d'accès relatif vers la radio
        std::string chemin_acces_patient;

    public:
        //Getters
        unsigned int get_num_exam_unique() const;
        bool get_etat() const;
        t_Date& get_date_radio();
        vector_t_Cliche_ptr* get_vector_cliches() const;
        const t_type_Radio& get_type_Radio() const;
        t_Compte_Rendu_Medical& get_compte_rendu();
        const std::string& get_chemin_acces_radio() const;

        //Setters
        void set_etat(const bool);
        void set_type_radio(const t_type_Radio&);

        //Méthodes
        std::string get_str_type_radio() const; // renvoie le type de la radio sous forme de chaîne de caractères
        std::string get_str_int_type_radio() const; // renvoie une chaîne de caractères correspondant à l'entier associé au type radio (enum)
        std::string get_str_etat() const; // renvoie l'état de la radio sous forme d'une chaîne de caractères
        std::string get_str_bool_etat() const; // renvoie la valeur 0/1 sous forme d'une chaîne correspondant à la valeur booléenne (0: false, 1: true)
        void affiche_radio(); //affichage de la radio
        
        // Constructeur
        // le même num_exam_unique est utilisé pour créer le compte-rendu et la radio (car le compte rendu est associé à la radio)
        // toute radiographie possède obligatoirement un compte-rendu (vide si la radiographie est planifiée (et donc pas encore effectuée))
        t_Radiographie(const unsigned int num_exam_unique, const bool etat, const unsigned short jour, const unsigned short mois, const unsigned short annee, t_type_Radio type, const std::string mdp, const std::string chemin_acces_patient): date_radio(jour, mois, annee), compte_rendu(mdp, num_exam_unique, chemin_acces_patient){ 
            this->num_exam_unique = num_exam_unique;
            this->etat = etat;
            this->type_Radio = type;
            this->vector_cliches_ptr = new vector_t_Cliche_ptr;
            this->chemin_acces_patient = chemin_acces_patient;
            this->chemin_acces_radio = (this->chemin_acces_patient)+"radios/"+std::to_string(this->num_exam_unique)+"/";
        }
        // Destructeur
        ~t_Radiographie(){
            for(size_t i=0; i<(this->vector_cliches_ptr)->size(); i++){
                delete (this->vector_cliches_ptr)->at(i); //désallocation de tous les clichés du vecteur de clichés
            }
            delete this->vector_cliches_ptr; //désallocation du pointeur sur le vecteur de clichés
        }
};

typedef t_Radiographie* t_Radiographie_ptr; // pointeur sur t_Radiographie
typedef std::vector<t_Radiographie_ptr> vector_t_Radiographie_ptr; // vecteur de t_Radiographie_ptr

#endif
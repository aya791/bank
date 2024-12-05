#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Pour sleep() sous Unix/Linux, utilisez <windows.h> pour Windows


void asciiART()
{
    printf("\n\n\n\n\n\n\n");
    printf("\t\t\t      #    #####   #     #           #####     #    #     # #   #\n");
    printf("\t\t\t     # #   #    #  #     #           #    #   # #   ##    # #  #\n");
    printf("\t\t\t    #   #  #    #  #     #           #    #  #   #  # #   # # #\n");
    printf("\t\t\t   ####### #####   ####### ********* #####  ####### #  #  # ##\n");
    printf("\t\t\t   #     # #   #   #     #           #    # #     # #   # # # #\n");
    printf("\t\t\t   #     # #    #  #     #           #    # #     # #    ## #  #\n");
    printf("\t\t\t   #     # #     # #     #           #####  #     # #     # #   #\n");



    printf("\n\n\n\t\t\t\t[");
    for(int i = 0; i < 3; i++)
    {
        printf("##############");
        sleep(1);
    }
    printf("]");
    system("cls");

}
 typedef struct {
    int jour;
    int mois;
    int annee;
} date;
typedef struct {
    int empno;         // Numéro employé
    char NOM[50];      // Nom de l'employé
    char prenom[50];   // Prénom de l'employé
    date naissance;    // Date de naissance
    char adresse[100]; // Adresse
    char tel[100];     // Téléphone
    char mot_passe[100]; // Mot de passe
    char email[100];
} employe;

int numeroExiste(int empno) {
    FILE *fichier = fopen("employes.dat", "rb"); // Ouvrir le fichier en mode lecture binaire
    if (fichier == NULL) {
        // Si le fichier n'existe pas encore, aucun employé n'a été enregistré
        return 0; // Le numéro n'existe pas
    }

    employe e;
    // Parcourir le fichier pour chercher un employé avec le même numéro
    while (fread(&e, sizeof(employe), 1, fichier) == 1) {
        if (e.empno == empno) {
            fclose(fichier);
            return 1; // Le numéro existe déjà
        }
    }

    fclose(fichier);
    return 0; // Le numéro n'existe pas
}

void ajouterEmploye() {
    employe e;
    FILE *fichier = fopen("employes.dat", "ab"); // Ouvrir le fichier en mode ajout binaire
    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier.\n");
        return;
    }

    // Vérification de l'unicité de empno
    int unique = 0;
    do {
        printf("Entrez le numéro de l'employé (unique) : ");
        scanf("%d", &e.empno);

        if (numeroExiste(e.empno) == 1) {
            printf("Erreur : Ce numéro d'employé existe déjà. Veuillez en saisir un autre.\n");
        } else {
            unique = 1; // Le numéro est unique
        }
    } while (unique == 0);

    // Saisie des autres informations de l'employé
    printf("Entrez le nom de l'employé : ");
    scanf("%s", e.NOM);

    printf("Entrez le prénom de l'employé : ");
    scanf("%s", e.prenom);

    printf("Entrez la date de naissance (jour mois année) : ");
    scanf("%d %d %d", &e.naissance.jour, &e.naissance.mois, &e.naissance.annee);

    printf("Entrez l'adresse de l'employé : ");
    scanf(" %[^\n]", e.adresse); // Lire une chaîne avec des espaces

    printf("Entrez le numéro de téléphone de l'employé : ");
    scanf("%s", e.tel);

    // Saisie et vérification de l'adresse e-mail
    int emailValide = 0;
    do {
        printf("Entrez l'adresse e-mail de l'employé (doit se terminer par @gmail.com) : ");
        scanf("%s", e.email);

        // Vérification que l'e-mail se termine par "@gmail.com"
        char *suffix = "@gmail.com";
        int lenEmail = strlen(e.email);
        int lenSuffix = strlen(suffix);

        if (lenEmail > lenSuffix && strcmp(e.email + lenEmail - lenSuffix, suffix) == 0) {
            emailValide = 1; // L'e-mail est valide
        } else {
            printf("Erreur : L'adresse e-mail doit se terminer par '@gmail.com'. Veuillez réessayer.\n");
        }
    } while (emailValide == 0);

    printf("Entrez le mot de passe de l'employé : ");
    scanf("%s", e.mot_passe);

    // Écriture des informations dans le fichier
    fwrite(&e, sizeof(employe), 1, fichier);

    printf("Employé ajouté avec succès !\n");

    fclose(fichier); // Fermer le fichier
    getchar();
}

void afficherEmploye() {
    // Déclarer une variable de type employe pour stocker les données lues
    employe e;

    // Ouvrir le fichier en mode lecture binaire
    FILE *fichier = fopen("employes.dat", "rb");

    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier.\n");
        return;
    }

    printf("\n===== Liste des Employés =====\n");

    // Lire chaque employé depuis le fichier et l'afficher
    while (fread(&e, sizeof(employe), 1, fichier) == 1) {
        printf("Numéro de l'employé : %d\n", e.empno);
        printf("Nom : %s\n", e.NOM);
        printf("Prénom : %s\n", e.prenom);
        printf("Date de naissance : %02d/%02d/%04d\n", e.naissance.jour, e.naissance.mois, e.naissance.annee);
        printf("Adresse : %s\n", e.adresse);
        printf("Numéro de téléphone : %s\n", e.tel);
        printf("Adresse e-mail : %s\n", e.email);
        printf("Mot de passe : %s\n", e.mot_passe);
        printf("-------------------------------\n");
    }

    fclose(fichier); // Fermer le fichier après utilisation
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> // Nécessaire pour SYSTEMTIME et GetLocalTime
#include "bank.h"










int main()
{
    asciiART();
   debut:

       //ajouterEmploye();
       //afficherEmploye();
       //creerCompte();
        afficherComptes();
        //deposerMontant();
        //effectuerRetrait();
         afficherTransactionsParId();




    return 0;
}

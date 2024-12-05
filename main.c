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
    int empno;         // Num�ro employ�
    char NOM[50];      // Nom de l'employ�
    char prenom[50];   // Pr�nom de l'employ�
    date naissance;    // Date de naissance
    char adresse[100]; // Adresse
    char tel[100];     // T�l�phone
    char mot_passe[100]; // Mot de passe
    char email[100];
} employe;

int numeroExiste(int empno) {
    FILE *fichier = fopen("employes.dat", "rb"); // Ouvrir le fichier en mode lecture binaire
    if (fichier == NULL) {
        // Si le fichier n'existe pas encore, aucun employ� n'a �t� enregistr�
        return 0; // Le num�ro n'existe pas
    }

    employe e;
    // Parcourir le fichier pour chercher un employ� avec le m�me num�ro
    while (fread(&e, sizeof(employe), 1, fichier) == 1) {
        if (e.empno == empno) {
            fclose(fichier);
            return 1; // Le num�ro existe d�j�
        }
    }

    fclose(fichier);
    return 0; // Le num�ro n'existe pas
}

void ajouterEmploye() {
    employe e;
    FILE *fichier = fopen("employes.dat", "ab"); // Ouvrir le fichier en mode ajout binaire
    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier.\n");
        return;
    }

    // V�rification de l'unicit� de empno
    int unique = 0;
    do {
        printf("Entrez le num�ro de l'employ� (unique) : ");
        scanf("%d", &e.empno);

        if (numeroExiste(e.empno) == 1) {
            printf("Erreur : Ce num�ro d'employ� existe d�j�. Veuillez en saisir un autre.\n");
        } else {
            unique = 1; // Le num�ro est unique
        }
    } while (unique == 0);

    // Saisie des autres informations de l'employ�
    printf("Entrez le nom de l'employ� : ");
    scanf("%s", e.NOM);

    printf("Entrez le pr�nom de l'employ� : ");
    scanf("%s", e.prenom);

    printf("Entrez la date de naissance (jour mois ann�e) : ");
    scanf("%d %d %d", &e.naissance.jour, &e.naissance.mois, &e.naissance.annee);

    printf("Entrez l'adresse de l'employ� : ");
    scanf(" %[^\n]", e.adresse); // Lire une cha�ne avec des espaces

    printf("Entrez le num�ro de t�l�phone de l'employ� : ");
    scanf("%s", e.tel);

    // Saisie et v�rification de l'adresse e-mail
    int emailValide = 0;
    do {
        printf("Entrez l'adresse e-mail de l'employ� (doit se terminer par @gmail.com) : ");
        scanf("%s", e.email);

        // V�rification que l'e-mail se termine par "@gmail.com"
        char *suffix = "@gmail.com";
        int lenEmail = strlen(e.email);
        int lenSuffix = strlen(suffix);

        if (lenEmail > lenSuffix && strcmp(e.email + lenEmail - lenSuffix, suffix) == 0) {
            emailValide = 1; // L'e-mail est valide
        } else {
            printf("Erreur : L'adresse e-mail doit se terminer par '@gmail.com'. Veuillez r�essayer.\n");
        }
    } while (emailValide == 0);

    printf("Entrez le mot de passe de l'employ� : ");
    scanf("%s", e.mot_passe);

    // �criture des informations dans le fichier
    fwrite(&e, sizeof(employe), 1, fichier);

    printf("Employ� ajout� avec succ�s !\n");

    fclose(fichier); // Fermer le fichier
    getchar();
}

void afficherEmploye() {
    // D�clarer une variable de type employe pour stocker les donn�es lues
    employe e;

    // Ouvrir le fichier en mode lecture binaire
    FILE *fichier = fopen("employes.dat", "rb");

    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier.\n");
        return;
    }

    printf("\n===== Liste des Employ�s =====\n");

    // Lire chaque employ� depuis le fichier et l'afficher
    while (fread(&e, sizeof(employe), 1, fichier) == 1) {
        printf("Num�ro de l'employ� : %d\n", e.empno);
        printf("Nom : %s\n", e.NOM);
        printf("Pr�nom : %s\n", e.prenom);
        printf("Date de naissance : %02d/%02d/%04d\n", e.naissance.jour, e.naissance.mois, e.naissance.annee);
        printf("Adresse : %s\n", e.adresse);
        printf("Num�ro de t�l�phone : %s\n", e.tel);
        printf("Adresse e-mail : %s\n", e.email);
        printf("Mot de passe : %s\n", e.mot_passe);
        printf("-------------------------------\n");
    }

    fclose(fichier); // Fermer le fichier apr�s utilisation
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> // N�cessaire pour SYSTEMTIME et GetLocalTime
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

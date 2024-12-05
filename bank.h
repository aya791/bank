#ifndef BANK_H_INCLUDED
#define BANK_H_INCLUDED

 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

 typedef struct {
    int jour;
    int mois;
    int annee;
} Date; // Nom mod

 typedef struct {
    char identifiant[6];     // Identifiant (5 chiffres + '\0')
    char code[7];            // Code personnel (4 à 6 chiffres + '\0')
    char nom[100];           // Nom de l'utilisateur
    char prenom[100];        // Prénom de l'utilisateur
    char tele[20];           // Numéro de téléphone
    char ville[50];          // Ville de résidence
    char email[100];         // Email (vérifié pour se terminer par '@gmail.com')
    char sex[2];             // Sexe ('M' ou 'F' + '\0')
    char numeroCompte[17];   // Numéro de compte (16 chiffres + '\0')
    Date date_naissance[3];   // Date de naissance (jour, mois, année)
    double solde;            // Solde initial (0.0)
    char rib[40];            // RIB complet (code banque, code ville, numéro de compte)
} utilisateur;
int verifierNumeroCompte(const char *numeroCompte) {
    // Vérifier que la longueur est exactement de 16 caractères
    if (strlen(numeroCompte) != 16) {
        return 0; // Longueur invalide
    }

    // Vérifier que chaque caractère est un chiffre
    for (int i = 0; i < 16; i++) {
        if (!isdigit(numeroCompte[i])) {
            return 0; // Caractère non numérique trouvé
        }
    }

    return 1; // Numéro de compte valide
}


int trouverCodeVille(const char *nomVille) {
    FILE *file = fopen("villes.dat", "r");
    if (!file) {
        printf("Erreur : Impossible d'ouvrir le fichier des villes.\n");
        return -1; // Indique une erreur
    }

    char ville[50]; // Pour stocker le nom de la ville dans le fichier
    int codeVille;  // Pour stocker le code de la ville dans le fichier

    // Lire chaque ligne du fichier
    while (fscanf(file, "%s %d", ville, &codeVille) != EOF) {
        if (strcmp(ville, nomVille) == 0) {
            fclose(file); // Fermer le fichier après avoir trouvé la ville
            return codeVille; // Retourner le code de la ville
        }
    }

    fclose(file); // Fermer le fichier si la ville n'est pas trouvée
    return -1; // Ville non trouvée
}



int verifierIdentifiant(const char *identifiant) {
    // Vérifier que la longueur est exactement de 5 caractères
    if (strlen(identifiant) != 5) {
        return 0; // Longueur invalide
    }

    // Vérifier que chaque caractère est un chiffre
    for (int i = 0; i < 5; i++) {
        if (!isdigit(identifiant[i])) {
            return 0; // Caractère non numérique trouvé
        }
    }

    return 1; // Identifiant valide
}

   // Fonction pour obtenir la date actuelle
date time() {
    date d;
    SYSTEMTIME Time;
    GetLocalTime(&Time);
    d.jour = Time.wDay;
    d.mois = Time.wMonth;
    d.annee = Time.wYear;
    return d;
}
    // Fonction pour vérifier la validité du code
int verifierCode(const char *cod) {
    int longueur = strlen(cod);

    if (longueur < 4 || longueur > 6) return 0; // Longueur invalide
    for (int i = 0; i < longueur; i++) {
        if (!isdigit(cod[i])) return 0; // Doit contenir uniquement des chiffres
    }

    return 1; // Code valide
}

void creerCompte() {
    FILE *fp;
    utilisateur newUser;
    char tempCode[7];

    // Ouvrir le fichier binaire
    fp = fopen("utilisateurs.dat", "ab+");
    if (fp == NULL) {
        printf("Erreur d'ouverture du fichier binaire\n");
        exit(1);
    }

    // Saisie de l'identifiant avec vérification
    do {
        printf("Entrez votre identifiant (5 chiffres) : ");
        scanf("%s", newUser.identifiant);

        if (!verifierIdentifiant(newUser.identifiant)) {
            printf("Identifiant invalide. Il doit contenir exactement 5 chiffres.\n");
        }
    } while (!verifierIdentifiant(newUser.identifiant));

    // Saisie et validation du code personnel
    do {
        printf("Entrez un code personnel (4 à 6 chiffres) : ");
        scanf("%s", newUser.code);

        if (!verifierCode(newUser.code)) {
            printf("Code invalide. Il doit contenir entre 4 et 6 chiffres.\n");
        }
    } while (!verifierCode(newUser.code));

    // Confirmation du code
    do {
        printf("Confirmez le code : ");
        scanf("%s", tempCode);

        if (strcmp(newUser.code, tempCode) != 0) {
            printf("Les codes ne correspondent pas. Veuillez réessayer.\n");
        }
    } while (strcmp(newUser.code, tempCode) != 0);

    // Saisie des informations personnelles
    printf("Entrez votre nom : ");
    scanf("%s", newUser.nom);

    printf("Entrez votre prénom : ");
    scanf("%s", newUser.prenom);

    printf("Entrez votre numéro de téléphone : ");
    scanf("%s", newUser.tele);

    // Saisie et recherche de la ville
    printf("Entrez votre ville : ");
    scanf("%s", newUser.ville);
    int codeVille = trouverCodeVille(newUser.ville);
    if (codeVille == -1) {
        printf("Ville non trouvée.\n");
        fclose(fp);

        exit(1);     // Quitter le programme avec un code d'erreur
    }
    // Saisie et validation du numéro de compte à 16 chiffres
    do {
        printf("Entrez votre numéro de compte à 16 chiffres : ");
        scanf("%s", newUser.numeroCompte);

        if (!verifierNumeroCompte(newUser.numeroCompte)) {
            printf("Numéro de compte invalide. Il doit contenir exactement 16 chiffres.\n");
        }
    } while (!verifierNumeroCompte(newUser.numeroCompte));

    // Saisie et validation du sexe
    do {
        printf("Entrez votre sexe (M/F) : ");
        scanf(" %c", &newUser.sex[0]); // Lire un seul caractère
        newUser.sex[1] = '\0';         // Terminer la chaîne

        if (newUser.sex[0] != 'M' && newUser.sex[0] != 'F') {
            printf("Saisie invalide. Entrez 'M' pour masculin ou 'F' pour féminin.\n");
        }
    } while (newUser.sex[0] != 'M' && newUser.sex[0] != 'F');

    // Saisie et validation de l'email
    do {
        printf("Entrez votre email (doit se terminer par @gmail.com) : ");
        scanf("%s", newUser.email);

        // Obtenir le pointeur vers les 10 derniers caractères de l'email
        char *finEmail = newUser.email + strlen(newUser.email) - 10;

        // Vérifier si la chaîne se termine par "@gmail.com"
        if (strlen(newUser.email) < 10 || strcmp(finEmail, "@gmail.com") != 0) {
            printf("Email invalide. L'email doit se terminer par '@gmail.com'.\n");
        } else {
            break; // Email valide, on sort de la boucle
        }
    } while (1);

    // Saisie de la date de naissance
    printf("Entrez votre date de naissance (jour mois année) : ");
    scanf("%d %d %d", &newUser.date_naissance[0], &newUser.date_naissance[1], &newUser.date_naissance[2]);

    // Initialisation du solde
    newUser.solde = 0.0;

    // Composition du RIB avec un code banque de 3 chiffres
    sprintf(newUser.rib, "123-%03d-%s", codeVille, newUser.numeroCompte);

    // Écriture de l'utilisateur dans le fichier binaire
    fwrite(&newUser, sizeof(utilisateur), 1, fp);
    printf("\nCompte créé avec succès ! RIB : %s\n", newUser.rib);

    fclose(fp); // Fermer le fichier
}

void afficherComptes() {
    FILE *fp;
    utilisateur user;

    // Ouvrir le fichier binaire en mode lecture
    fp = fopen("utilisateurs.dat", "rb");
    if (fp == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier des utilisateurs.\n");
        return;
    }

    printf("Lecture du fichier binaire...\n");

    printf("\t\t=============================\n");
    printf("\t\t    LISTE DES UTILISATEURS\n");
    printf("\t\t=============================\n\n");

    // Lecture et affichage des informations des utilisateurs
    while (fread(&user, sizeof(utilisateur), 1, fp) == 1) {
        printf("Identifiant      : %s\n", user.identifiant);
        printf("Nom              : %s\n", user.nom);
        printf("Prénom           : %s\n", user.prenom);
        printf("Téléphone        : %s\n", user.tele);
        printf("Ville            : %s\n", user.ville);
        printf("Email            : %s\n", user.email);
        printf("Sexe             : %s\n", user.sex);
        printf("Date de Naissance: %02d/%02d/%04d\n",
               user.date_naissance[0], user.date_naissance[1], user.date_naissance[2]);
        printf("Solde            : %.2f MAD\n", user.solde);
        printf("RIB              : %s\n", user.rib);
        printf("-------------------------------\n");
    }

    fclose(fp); // Fermer le fichier
    printf("\nFin de la liste des utilisateurs.\n");
}


Date obtenirDateActuelle() {
    SYSTEMTIME Time;
    GetLocalTime(&Time);
    Date d;
    d.jour = Time.wDay;
    d.mois = Time.wMonth;
    d.annee = Time.wYear;
    return d;
}

typedef struct {
    char identifiant[20];
    char nom[100];
    char prenom[100];
    double montant;
    double nouveauSolde;
    char type[100];
    Date dateTransaction;
    char motif[100];  // Date de la transaction
} Transaction;




void deposerMontant() {
    FILE *fp = fopen("utilisateurs.dat", "r+b");
    if (fp == NULL) {
        printf("Erreur d'ouverture du fichier des utilisateurs.\n");
        return;
    }

    utilisateur usr;
    char identifiant[20];
    double montant;
    int trouve = 0;

    printf("Entrez l'identifiant de l'utilisateur : ");
    fflush(stdin);
    gets(identifiant);

    printf("Entrez le montant à déposer : ");
    scanf("%lf", &montant);

    while (fread(&usr, sizeof(utilisateur), 1, fp)) {
        if (strcmp(usr.identifiant, identifiant) == 0) {
            trouve = 1;
            usr.solde += montant;
            fseek(fp, -sizeof(utilisateur), SEEK_CUR);
            fwrite(&usr, sizeof(utilisateur), 1, fp);

            printf("\nDépôt effectué avec succès!\n");
            printf("Détails du dépôt:\n");
            printf("Identifiant: %s\n", usr.identifiant);
            printf("Nom: %s\n", usr.nom);
            printf("Prénom: %s\n", usr.prenom);
            printf("Montant déposé: %.2f\n", montant);
            printf("Nouveau solde: %.2f\n", usr.solde);

            Transaction trans;
            strcpy(trans.identifiant, usr.identifiant);
            strcpy(trans.nom, usr.nom);
            strcpy(trans.prenom, usr.prenom);
            trans.montant = montant;
            trans.nouveauSolde = usr.solde;
            strcpy(trans.type, "Dépôt");
            trans.dateTransaction = obtenirDateActuelle();
            enregistrerTransaction(trans);
            break;
        }
    }

    fclose(fp);

    if (!trouve) {
        printf("Utilisateur non trouvé.\n");
    }
}


void enregistrerTransaction(Transaction trans) {
    FILE *fp = fopen("transactions.dat", "ab");
    if (fp == NULL) {
        printf("Erreur d'ouverture du fichier des transactions.\n");
        return;
    }

    fwrite(&trans, sizeof(Transaction), 1, fp);
    fclose(fp);

    printf("Transaction enregistrée le %02d/%02d/%04d.\n",
           trans.dateTransaction.jour,
           trans.dateTransaction.mois,
           trans.dateTransaction.annee);
}
void effectuerRetrait() {
    FILE *fp = fopen("utilisateurs.dat", "r+b");
    if (fp == NULL) {
        printf("Erreur lors de l'ouverture du fichier des utilisateurs.\n");
        return;
    }

    utilisateur usr;
    char identifiant[20];
    double montant;
    int trouve = 0;

    printf("Entrez votre identifiant pour effectuer un retrait : ");
    fflush(stdin);
    gets(identifiant);
    printf("Entrez le montant à retirer : ");
    scanf("%lf", &montant);

    while (fread(&usr, sizeof(utilisateur), 1, fp)) {
        if (strcmp(usr.identifiant, identifiant) == 0) {
            trouve = 1;
            if (usr.solde >= montant) {
                usr.solde -= montant;
                fseek(fp, -sizeof(utilisateur), SEEK_CUR);
                fwrite(&usr, sizeof(utilisateur), 1, fp);

                printf("\nRetrait effectué avec succès!\n");
                printf("Détails du retrait:\n");
                printf("Identifiant: %s\n", usr.identifiant);
                printf("Nom: %s\n", usr.nom);
                printf("Prénom: %s\n", usr.prenom);
                printf("Montant retiré: %.2f\n", montant);
                printf("Nouveau solde: %.2f\n", usr.solde);

                // Enregistrer la transaction
                Transaction trans;
                strcpy(trans.identifiant, usr.identifiant);
                strcpy(trans.nom, usr.nom);
                strcpy(trans.prenom, usr.prenom);
                trans.montant = -montant;  // Négatif pour indiquer un retrait
                trans.nouveauSolde = usr.solde;
                strcpy(trans.type, "Retrait");
                trans.dateTransaction = obtenirDateActuelle();
                enregistrerTransaction(trans);
            } else {
                printf("Solde insuffisant pour effectuer ce retrait.\n");
            }
            break;
        }
    }

    fclose(fp);

    if (!trouve) {
        printf("Identifiant non trouvé.\n");
    }
}

void afficherHistoriqueParId() {
    FILE *fp = fopen("transactions.dat", "rb");
    if (fp == NULL) {
        printf("Erreur lors de l'ouverture du fichier des transactions.\n");
        return;
    }

    Transaction trans;
    char identifiantRecherche[20];
    int found = 0;

    printf("Entrez votre identifiant pour voir l'historique des transactions : ");
    fflush(stdin);
    gets(identifiantRecherche);

    while (fread(&trans, sizeof(Transaction), 1, fp)) {
        if (strcmp(trans.identifiant, identifiantRecherche) == 0) {
            if (!found) {
                printf("\nHistorique des transactions pour %s:\n", identifiantRecherche);
                printf("Date       | Montant   | Nouveau Solde | Motif\n");
                printf("----------------------------------------------------\n");
                found = 1;
            }
            printf("%02d/%02d/%04d | %+.2f | %.2f | %s\n",
                   trans.dateTransaction.jour,
                   trans.dateTransaction.mois,
                   trans.dateTransaction.annee,
                   trans.montant,
                   trans.nouveauSolde,
                   trans.motif);
        }
    }

    if (!found) {
        printf("Aucune transaction trouvée pour l'identifiant '%s'.\n", identifiantRecherche);
    }

    fclose(fp);
}






void afficherTransactionsParId() {
    FILE *fp = fopen("transactions.dat", "rb");
    if (fp == NULL) {
        printf("Erreur lors de l'ouverture du fichier des transactions.\n");
        return;
    }

    Transaction trans;
    char identifiantRecherche[20];
    int found = 0;

    printf("Entrez l'identifiant pour voir toutes les transactions : ");
    if (fgets(identifiantRecherche, sizeof(identifiantRecherche), stdin) == NULL) {
        printf("Erreur de lecture de l'identifiant.\n");
        fclose(fp);
        return;
    }
    identifiantRecherche[strcspn(identifiantRecherche, "\n")] = 0;  // Eliminer le newline

    printf("\nTransactions pour %s:\n", identifiantRecherche);
    printf("| Date       | Montant   | Nouveau Solde | Type      | Motif                     |\n");
    printf("|------------|-----------|---------------|-----------|---------------------------|\n");

    while (fread(&trans, sizeof(Transaction), 1, fp) == 1) {  // S'assurer de la condition de boucle
        if (strcmp(trans.identifiant, identifiantRecherche) == 0) {
            printf("| %02d/%02d/%04d | %9.2f | %13.2f | %-9s | %-25s |\n",
                   trans.dateTransaction.jour,
                   trans.dateTransaction.mois,
                   trans.dateTransaction.annee,
                   trans.montant,
                   trans.nouveauSolde,
                   trans.type,
                   trans.motif[0] ? trans.motif : "Pas de motif spécifié");
            found = 1;
        }
    }

    if (!found) {
        printf("| Aucune transaction trouvée pour cet identifiant.                                  |\n");
    }

    fclose(fp);
}

































#endif // BANK_H_INCLUDED

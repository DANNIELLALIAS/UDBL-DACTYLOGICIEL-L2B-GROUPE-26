#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TAILLE_MAX 75
#define NB_MOTS_DEFAUT 7 // nombre de mots dans le tableau par défaut

// Déclaration des fonctions
void afficherAide();
void configurerJeu(char* nomFichier);
void jouerPartie();

int main()
{
    // Affichage du titre et des noms d'auteurs
    printf("\t\tUDBL - DACTYLOGICIEL\n");
   printf("========================================================================================================================");
    printf("\t\trealise Par MUKAZ KALAU GAEL, NGOY RAMAZANI DANNIELLA,MUSAO MBUYI GENISIA, MUSAU MPIMPI DELIVE\n\n");
        printf("========================================================================================================================");
    int choix = 0;

    // Boucle tant que l'utilisateur ne choisit pas de quitter
    while (choix != 4)
    {
        sleep (5);
        // Affichage du menu principal
        printf("Ecran d'acueil\n");
        printf("1. Demarrer\n");
        printf("2. Configurer\n");
        printf("3. Aide\n");
        printf("4. Quitter\n");
        printf("Votre choix : ");


        // Lecture du choix de l'utilisateur
        scanf("%d", &choix);
        fflush(stdin); // Nettoyage du buffer de saisie
        printf("========================================================================================================================");

        switch (choix)
        {
            case 1:
                jouerPartie();
                break;
            case 2:
                printf("Entrez le nom du fichier de configuration : ");
                char nomFichier[TAILLE_MAX];
                scanf("%s", nomFichier);
                configurerJeu(nomFichier);
                break;
            case 3:
                afficherAide();
                break;
            case 4:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide\n");
                break;
        }
    }

    return 0;
}

// Fonction qui affiche l'aide du jeu
void afficherAide()
{
    printf("UDBL - DACTYLOGICIEL\n");
    printf("Version 3.0\n");
    printf("Developpe par MUKAZ KALAU GAEL, NGOY RAMAZANI DANNIELLA,MUSAO MBUYI GENISIA, MUSAU MPIMPI DELIVE\n");
    printf("Concu en juin 2024\n\n");
    printf("Ce jeu permet de tester la rapidite de frappe au clavier de deux joueurs.\n");
    printf("Chaque joueur doit saisir les mots qui s affichent a l ecran dans l'ordre propose.\n");
    printf("Le joueur qui termine le plus rapidement gagne la partie.\n\n");
}

// Fonction qui configure le jeu en ajoutant des mots dans le fichier texte
void configurerJeu(char* nomFichier)
{
    FILE* fichier = fopen(nomFichier, "a");
    if (fichier == NULL)
    {
        printf("Erreur : impossible d'ouvrir le fichier %s\n", nomFichier);
        return;
    }

    char mot[TAILLE_MAX] = "7";
    printf("Entrez les mots a ajouter au fichier (terminer par une ligne vide) :\n");

    // Lecture des mots à ajouter
    while (fgets(mot, TAILLE_MAX, stdin) && mot[0] != '\n')
    {
        // Suppression du caractère de fin de ligne (si présent)
        int longueur = strlen(mot);
        if (mot[longueur - 1] == '\n')
        {
            mot[longueur - 1] = '\0';
        }

        // Ecriture du mot dans le fichier
        fprintf(fichier, "%s\n", mot);
    }

    fclose(fichier);
}

// Fonction qui joue une partie du jeu
void jouerPartie()
{
    char mots[NB_MOTS_DEFAUT][TAILLE_MAX] = {"interanticonstitutionnellement", "psychomagnadepressive", "cartaphorteque", "psychopate", "macrafignard", "psychose", "malade"};

    int nbMots = 0;

    // Lecture du nombre de mots à saisir
    printf("\nEntrez le nombre de mots a saisir (max %d) : ", NB_MOTS_DEFAUT);
    scanf("%d", &nbMots);

    fflush(stdin); // Nettoyage du buffer de saisie

    if (nbMots > NB_MOTS_DEFAUT)
    {
        printf("\nAttention : le nombre de mots saisi est supérieur au nombre de mots disponibles dans le tableau par defaut.\n");
        printf("Le jeu sera lance avec %d mots seulement.\n", NB_MOTS_DEFAUT);
        nbMots = NB_MOTS_DEFAUT;
    }

    // Lecture des pseudos des joueurs
    char joueur1[TAILLE_MAX], joueur2[TAILLE_MAX];
    printf("\nEntrez le pseudo du joueur 1 : ");
    scanf("%s", joueur1);
    printf("Entrez le pseudo du joueur 2 : ");
    scanf("%s", joueur2);
    printf("=======================================================================================================================");

    int temps1 = 0, temps2 = 0;
    clock_t debut, fin;

    // Générer des mots aléatoires à partir du tableau et saisie des mots par les joueurs
    for (int i = 0; i < nbMots; i++)
    {
        char mot[TAILLE_MAX];
        strcpy(mot, mots[i]);

        // Début du chronomètre pour le premier joueur
        printf("\n%s, tapez le mot suivant : %s\n", joueur1, mot);
        debut = clock();
        do
        {
            scanf("%s", mot);
            fin = clock();
        }
        while (strcmp(mot, mots[i]) != 0);

        // Calcul du temps de saisie pour le premier joueur
        double tempsEcoule = (double) (fin - debut) / CLOCKS_PER_SEC * 1000;
        temps1 += tempsEcoule;

        // Début du chronomètre pour le deuxième joueur
        printf("%s, tapez le mot suivant : %s\n", joueur2, mots[i]);
        debut = clock();

        // Saisie du mot par le deuxième joueur
        do
        {
            scanf("%s", mot);
            fin = clock();
        }
        while (strcmp(mot, mots[i]) != 0);

        // Calcul du temps de saisie pour le deuxième joueur
        tempsEcoule = (double) (fin - debut) / CLOCKS_PER_SEC * 1000;
        temps2 += tempsEcoule;
    }

    // Affichage des résultats
    printf("\nTemps de saisie pour %s : %d ms\n", joueur1, temps1);
    printf("Temps de saisie pour %s : %d ms\n", joueur2, temps2);

    if (temps1 < temps2)
    {
        printf("\n%s est plus rapide et a gagner la partie !\n", joueur1);
    }
    else if (temps2 < temps1)
    {
        printf("\n%s est plus rapide et a gagner la partie !\n", joueur2);
    }
    else
    {
        printf("\nMatch nul : les deux joueurs ont fini en meme temps.\n");
    }
}

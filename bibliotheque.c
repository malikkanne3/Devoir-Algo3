#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Livre {
    int id;
    char titre[50];
    int annee;
    struct Livre *suivant;
} Livre;

typedef struct Liste {
    Livre *premier;
    int nb_livres;
} Liste;

// Initialiser la liste
void initialiser_liste(Liste *liste)
{
    liste->premier = NULL;
    liste->nb_livres = 0;
}

// Insérer en tête 
void inserer_entete(Liste *liste, int id, char titre[], int annee)
{
    Livre *nouveau = (Livre*) malloc(sizeof(Livre));
    
    nouveau->id = id;
    strcpy(nouveau->titre, titre);
    nouveau->annee = annee;

    nouveau->suivant = liste->premier;
    liste->premier = nouveau;

    liste->nb_livres++;
}

//  Insérer en fin 
void inserer_fin(Liste *liste, int id, char titre[], int annee)
{
    Livre *nouveau = (Livre*) malloc(sizeof(Livre));

    nouveau->id = id;
    strcpy(nouveau->titre, titre);
    nouveau->annee = annee;
    nouveau->suivant = NULL;

    if(liste->premier == NULL)
        liste->premier = nouveau;
    else
    {
        Livre *p = liste->premier;
        while(p->suivant != NULL)
            p = p->suivant;

        p->suivant = nouveau;
    }

    liste->nb_livres++;
}

// Rechercher par identifiant 
Livre* rechercher(Liste *liste, int id)
{
    Livre *p = liste->premier;

    while(p != NULL)
    {
        if(p->id == id)
            return p;

        p = p->suivant;
    }

    return NULL;
}

// Supprimer par identifiant
void supprimer(Liste *liste, int id)
{
    if(liste->premier == NULL) return;

    Livre *p = liste->premier;
    Livre *precedent = NULL;

    while(p != NULL && p->id != id)
    {
        precedent = p;
        p = p->suivant;
    }

    if(p == NULL) return;

    if(precedent == NULL)
        liste->premier = p->suivant;
    else
        precedent->suivant = p->suivant;

    free(p);
    liste->nb_livres--;
}

// Afficher tous les livres
void afficher(Liste *liste)
{
    Livre *p = liste->premier;

    printf("\n----LISTE DES LIVRES ------\n");

    if(p == NULL) {
        printf("La liste est vide.\n");
    } else {
        while(p != NULL)
        {
            printf("ID : %d | TITRE : %s | ANNEE : %d\n",
                   p->id, p->titre, p->annee);
            p = p->suivant;
        }
    }

    printf("Nombre total de livres : %d\n", liste->nb_livres);
    printf("\n\n");
}


void trier_annee(Liste *liste)
{
    if(liste->premier == NULL || liste->premier->suivant == NULL) 
        return;

    Livre *p, *q;

    int tmp_id, tmp_annee;
    char tmp_titre[50];

    for(p = liste->premier; p->suivant != NULL; p = p->suivant)
    {
        for(q = p->suivant; q != NULL; q = q->suivant)
        {
            if(p->annee > q->annee)
            {
        
                tmp_id = p->id;
                p->id = q->id;
                q->id = tmp_id;

                
                strcpy(tmp_titre, p->titre);
                strcpy(p->titre, q->titre);
                strcpy(q->titre, tmp_titre);

                tmp_annee = p->annee;
                p->annee = q->annee;
                q->annee = tmp_annee;
            }
        }
    }
}

void liberer_liste(Liste *liste)
{
    Livre *courant = liste->premier;
    Livre *suivant;

    while(courant != NULL)
    {
        suivant = courant->suivant;
        free(courant);
        courant = suivant;
    }

    liste->premier = NULL;
    liste->nb_livres = 0;
}


int main()
{
    Liste l;
    initialiser_liste(&l);

    
    inserer_entete(&l, 1, "LanguageC", 1999);
    inserer_entete(&l, 5, "Java", 2005);

    
    inserer_fin(&l, 3, "Python", 2014);
    inserer_fin(&l, 4, "PHP", 2010);
    inserer_fin(&l, 2, "Javascript", 1995);

    printf(" LISTE INITIALE : ");
    afficher(&l);

    
    Livre *res = rechercher(&l, 3);
    if(res != NULL)
        printf("Livre trouvé : %s (%d)\n\n", res->titre, res->annee);
    else
        printf("Livre non trouvé.\n\n");

    printf("=== APRÈS SUPPRESSION DU LIVRE ID=4 ===");
    supprimer(&l, 4);
    afficher(&l);

    printf("=== APRÈS TRI PAR ANNÉE ===");
    trier_annee(&l);
    afficher(&l);

    
    liberer_liste(&l);

    return 0;

}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Structure de l'Element
typedef struct Element{
    int valeur;
    struct Element *suivant;
}Element;

// Structure de controle de la file
typedef struct File{
    Element *sommet;
    Element *queue;
}File;

// 1. Fonction pour enfiler une valeur
void enfiler(File *f, int nombre)
{
    Element *nouveau = malloc(sizeof(Element));
    if ((f == NULL) || (nouveau == NULL)) {
        exit(EXIT_FAILURE);
    }
    nouveau->valeur = nombre;
    nouveau->suivant = NULL;

    if (f->sommet == NULL) {
        f->sommet = nouveau;  
        f->queue = nouveau; 
    } else {
        (f->queue)->suivant = nouveau;
        f->queue = nouveau;
    }
}
// 2. Fonction pour defiler une valeur
int defiler(File *f){
    int val =-1;
    if (f ==NULL)
    {
        printf("File vide \n");
        exit(EXIT_FAILURE);
    }
    if(f->sommet ==NULL){
        printf("Liste vide \n");
        return 0;
    }
    Element *toDelete = f->sommet;
    f->sommet= (f->sommet)->suivant;
    val = toDelete->valeur;

    if(f->sommet ==NULL){
        f->queue = NULL;
    }
    free(toDelete);
    return val;
    
}

// 3. Fonction pour afficher les valeurs de la file
void afficher(File *f) {
    if (f == NULL || f->sommet == NULL) {
        printf("File vide\n");
        return;
    }

    Element *courant = f->sommet;
    printf("Valeur enfiler : ");
    while (courant != NULL) {
        printf("%d ", courant->valeur);
        courant = courant->suivant;
    }
    printf("\n");
}

// 4. Une fonction qui retourne le nombre d'Elements dans la file
int nbreElements(File *f) {
    if (f == NULL || f->sommet == NULL) {
        return 0;
    }

    int compteur = 0;
    Element *courant = f->sommet;

    while (courant != NULL) {
        compteur++;
        courant = courant->suivant;
    }

    return compteur;
}





int main(){

    File f;
    f.sommet = NULL;
    f.queue = NULL;

    enfiler(&f, 10);
    enfiler(&f, 20);
    enfiler(&f, 30);

    afficher(&f); 

    int val = defiler(&f);
    printf("Valeur defilee : %d\n", val); 
    afficher(&f); 
    return 0;


}



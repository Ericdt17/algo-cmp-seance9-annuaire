#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "annuaire.h"

#define TAILLE_TABLE 1024

typedef struct Node {
    char email[EMAIL_MAX];
    int id;
    struct Node *next;
} Node;

static Node *table[TAILLE_TABLE] = { NULL };

/* djb2 : h = 5381, puis h = h * 33 + caractere */
unsigned long hachage(const char *email)
{
    unsigned long h = 5381;
    int c;

    while ((c = (unsigned char)*email++))
        h = h * 33 + (unsigned long)c;

    return h;
}

void hash_insert(const char *email, int id)
{
    unsigned long i = hachage(email) % TAILLE_TABLE;
    Node *n = malloc(sizeof(Node));
    if (n == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    snprintf(n->email, EMAIL_MAX, "%s", email);
    n->id = id;
    n->next = table[i]; /* insertion en tete : d'abord lier l'ancienne chaine */
    table[i] = n;       /* puis faire pointer la table vers le nouveau */
}

bool hash_search(const char *email)
{
    unsigned long i = hachage(email) % TAILLE_TABLE;
    for (Node *n = table[i]; n != NULL; n = n->next)
        if (strcmp(n->email, email) == 0)
            return true;
    return false;
}

void hash_free(void)
{
    for (int i = 0; i < TAILLE_TABLE; i++) {
        Node *n = table[i];
        while (n != NULL) {
            Node *suiv = n->next; /* sauver next AVANT free */
            free(n);
            n = suiv;
        }
        table[i] = NULL;
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "annuaire.h"

static User *annuaire = NULL;
static int taille = 0;
static int capacite = 0;

void seq_insert(const char *email, int id)
{
    if (taille == capacite) {
        int nouvelle;
        if (capacite == 0)
            nouvelle = 16;          /* premiere allocation */
        else
            nouvelle = capacite * 2; /* on double quand c'est plein */

        User *tmp = realloc(annuaire, (size_t)nouvelle * sizeof(User));
        if (tmp == NULL) {
            perror("realloc");
            exit(EXIT_FAILURE);
        }
        annuaire = tmp;
        capacite = nouvelle;
    }

    snprintf(annuaire[taille].email, EMAIL_MAX, "%s", email);
    annuaire[taille].id = id;
    taille++;
}

bool seq_search(const char *email)
{
    for (int i = 0; i < taille; i++)
        if (strcmp(annuaire[i].email, email) == 0)
            return true;
    return false;
}

void seq_free(void)
{
    free(annuaire);
    annuaire = NULL;
    taille = 0;
    capacite = 0;
}

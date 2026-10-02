#include <stdio.h>
#include "annuaire.h"

static void afficher(const char *titre, bool obtenu)
{
    printf("%s -> %s\n", titre, obtenu ? "true" : "false");
}

int main(void)
{
    /* --- tests sur annuaire avec 5 adresses --- */
    seq_insert("alice@mail.com", 1);
    seq_insert("bob@mail.com", 2);
    seq_insert("carole@mail.com", 3);
    seq_insert("david@mail.com", 4);
    seq_insert("eve@mail.com", 5);

    afficher("alice presente", seq_search("alice@mail.com"));
    afficher("carole presente", seq_search("carole@mail.com"));
    afficher("eve presente", seq_search("eve@mail.com"));
    afficher("inconnu absente", seq_search("inconnu@mail.com"));
    afficher("zoe absente", seq_search("zoe@mail.com"));

    seq_free();

    /* --- test sur annuaire vide --- */
    afficher("annuaire vide", seq_search("alice@mail.com"));

    return 0;
}

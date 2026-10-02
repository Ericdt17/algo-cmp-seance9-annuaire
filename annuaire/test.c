#include <stdio.h>
#include "annuaire.h" /* notre type User (guillemets = fichier du projet) */

int main(void)
{
    User u; /* on cree une variable User en memoire */

    /* on COPIE la chaine dans le tableau u.email (on ne peut pas faire u.email = "...") */
    snprintf(u.email, EMAIL_MAX, "%s", "alice@gmail.com");
    u.id = 1; /* l'id, lui, s'assigne directement */

    /* on verifie que ca a bien ete range */
    printf("email = "alice@gmail.com");
    printf("id    = %d\n", u.id);

    return 0;
}

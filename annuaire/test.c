#include <stdio.h>
#include "annuaire.h"

static int nb_ok = 0;
static int nb_total = 0;

static void verifier(const char *titre, bool obtenu, bool attendu)
{
    nb_total++;
    if (obtenu == attendu) {
        printf("[OK]    %s\n", titre);
        nb_ok++;
    } else {
        printf("[ECHEC] %s (obtenu=%s, attendu=%s)\n",
               titre,
               obtenu ? "true" : "false",
               attendu ? "true" : "false");
    }
}

int main(void)
{
    /* 1. annuaire vide */
    verifier("seq : annuaire vide", seq_search("alice@mail.com"), false);
    verifier("hash : annuaire vide", hash_search("alice@mail.com"), false);

    /* 2. inserer les memes 5 utilisateurs dans les deux structures */
    const char *emails[] = {
        "alice@mail.com",
        "bob@mail.com",
        "carole@mail.com",
        "david@mail.com",
        "eve@mail.com",
    };
    for (int i = 0; i < 5; i++) {
        seq_insert(emails[i], i + 1);
        hash_insert(emails[i], i + 1);
    }

    /* 3. les cinq adresses trouvees par les deux approches */
    for (int i = 0; i < 5; i++) {
        char titre[80];
        snprintf(titre, sizeof titre, "seq trouve %s", emails[i]);
        verifier(titre, seq_search(emails[i]), true);
        snprintf(titre, sizeof titre, "hash trouve %s", emails[i]);
        verifier(titre, hash_search(emails[i]), true);
    }

    /* 4. deux adresses absentes */
    verifier("seq absente inconnu", seq_search("inconnu@mail.com"), false);
    verifier("hash absente inconnu", hash_search("inconnu@mail.com"), false);
    verifier("seq absente zoe", seq_search("zoe@mail.com"), false);
    verifier("hash absente zoe", hash_search("zoe@mail.com"), false);

    /* 5. seule la casse differre */
    verifier("seq casse Alice", seq_search("Alice@mail.com"), false);
    verifier("hash casse Alice", hash_search("Alice@mail.com"), false);

    /* liberer toute la memoire */
    seq_free();
    hash_free();

    printf("\nResultat : %d / %d tests OK\n", nb_ok, nb_total);
    return (nb_ok == nb_total) ? 0 : 1;
}

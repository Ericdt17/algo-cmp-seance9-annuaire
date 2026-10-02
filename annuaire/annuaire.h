#ifndef ANNUAIRE_H
#define ANNUAIRE_H

#include <stdbool.h>

/* taille max d'un email (on laisse de la place pour le '\0' final) */
#define EMAIL_MAX 100

/* un User = juste un email + un numero d'id */
typedef struct {
    char email[EMAIL_MAX]; /* tableau de caracteres, pas un pointeur */
    int id;
} User;

/* approche sequentielle (tableau dynamique) */
void seq_insert(const char *email, int id);
bool seq_search(const char *email);
void seq_free(void);

#endif

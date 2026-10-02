#ifndef ANNUAIRE_H
#define ANNUAIRE_H

#include <stdio.h>

/* taille max d'un email (on laisse de la place pour le '\0' final) */
#define EMAIL_MAX 100

/* un User = juste un email + un numero d'id */
typedef struct {
    char email[EMAIL_MAX]; /* tableau de caracteres, pas un pointeur */
    int id;
} User;

#endif

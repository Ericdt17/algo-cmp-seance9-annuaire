# TP Socle — Un annuaire, deux approches

Projet : `annuaire/` (tableau dynamique vs table de hachage)

---

## Exercice 0 — Recap

Plus petit programme : type `User` dans `annuaire.h`, mini `test.c`, comprendre pourquoi `=` ne marche pas sur un tableau de `char`.

### Questions

**Q3** — Compile + lance : résultat observé

```
email = alice@gmail.com
id    = 1
```

**Q4** — Avec `u.email = "..."` : résultat observé

```
error: array type 'char[100]' is not assignable
```

**Q5** — Pourquoi pas `=` sur un tableau de `char` ?

```
On ne peut pas faire = sur un tableau de char : ce n'est pas un pointeur libre.
L'adresse du tableau est fixe ; il faut copier la chaîne (snprintf).
```

---

## Exercice 1 — Recap

Avant de coder : grille d’analyse (entrées, sorties, contraintes, volume, fréquence) sur le problème « e-mail déjà utilisé ? ».

### Questions

| Point | Réponse |
| --- | --- |
| Entrées | Une adresse e-mail (chaîne) à vérifier |
| Sorties | Un booléen : l’e-mail est déjà utilisée ou non |
| Contraintes | Réponse correcte ; temps et mémoire acceptables |
| Volume | Nombre d’utilisateurs déjà inscrits |
| Fréquence | Combien de fois on appelle cette vérification |

**Q2** — Quels points aident à choisir une structure de données ?

```
Volume, fréquence (et contraintes temps/mémoire) aident à choisir la structure.
Entrées et sorties ne changent pas selon la structure choisie.
```

**Q3** — 30 employés vs 5 M comptes : quels 2 points les distinguent ?

```
Volume et fréquence.
```

---

## Exercice 2 — Recap

Annuaire en tableau dynamique : `seq_insert` / `seq_free`, capacité qui démarre à 16 et double.

### Questions

**Suite des capacités (40 insertions)**

```


```

**Q5** — Combien de `realloc` pour 40 ? Pour 1000 ?

```


```

---

## Exercice 3 — Recap

Recherche séquentielle (`seq_search` + `strcmp`), cas favorable / moyen / défavorable.

### Questions

| Recherche | Attendu | Obtenu |
| --- | --- | --- |
| Adresse présente | true | |
| Adresse absente | false | |
| Annuaire vide | false | |

**Q4** — Remplacer `strcmp` par `==` : observation

```


```

**Q5** — Nb de comparaisons (favorable / moyen / défavorable)

| Cas | Nb | Donnée |
| --- | --- | --- |
| Favorable | | |
| Moyen | | |
| Défavorable | | |

---

## Exercice 4 — Recap

Fonction de hachage djb2 : calculer un indice plutôt que parcourir.

### Questions

| Adresse | Indice (`% 1024`) |
| --- | --- |
| alice@mail.com | |
| bob@mail.com | |
| carole@mail.com | |
| david@mail.com | |
| eve@mail.com | |

**Q3** — alice 3 fois de suite

```


```

**Q4** — user1 vs user2 : voisins ?

```


```

**Q5** — `int` à la place de `unsigned long`

```


```

**Q6** — Deux adresses, même indice ? Défaut ?

```


```

---

## Exercice 5 — Recap

Table de hachage avec chaînage : `hash_insert` / `hash_search` / `hash_free`.

### Questions

| Recherche | Attendu | Obtenu |
| --- | --- | --- |
| Adresse présente | true | |
| Adresse absente | false | |
| Annuaire vide | false | |

**Q3** — Insertion en tête inversée : observation

```


```

**Q4** — Pourquoi sauver `n->next` avant `free(n)` ?

```


```

---

## Exercice 6 — Recap

Banc de test commun : les deux approches doivent donner le même résultat.

### Questions

**Sortie de `./test`**

```


```

**Code de retour**

```


```

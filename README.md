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
16 (insertions 1→16), puis 32 (17→32), puis 64 (33→40)
```

**Q5** — Combien de `realloc` pour 40 ? Pour 1000 ?

```
40 insertions : 3 fois (0→16, 16→32, 32→64)
1000 insertions : 7 fois (16, 32, 64, 128, 256, 512, 1024)
```

---

## Exercice 3 — Recap

Recherche séquentielle (`seq_search` + `strcmp`), cas favorable / moyen / défavorable.

### Questions

| Recherche | Attendu | Obtenu |
| --- | --- | --- |
| Adresse présente | true | true |
| Adresse absente | false | false |
| Annuaire vide | false | false |

**Q4** — Remplacer `strcmp` par `==` : observation

```
Le programme compile (éventuellement avec un warning selon le compilateur).
La recherche renvoie toujours false : == compare les adresses, pas le contenu des chaînes.
```

**Q5** — Nb de comparaisons (favorable / moyen / défavorable)

| Cas | Nb | Donnée |
| --- | --- | --- |
| Favorable | 1 | L’e-mail est en première position |
| Moyen | ~n/2 | L’e-mail est au milieu |
| Défavorable | n | Absent, ou en dernière position |

---

## Exercice 4 — Recap

Fonction de hachage djb2 : calculer un indice plutôt que parcourir.

### Questions

| Adresse | Indice (`% 1024`) |
| --- | --- |
| alice@mail.com | 19 |
| bob@mail.com | 104 |
| carole@mail.com | 747 |
| david@mail.com | 189 |
| eve@mail.com | 181 |

**Q3** — alice 3 fois de suite

```
Toujours le même indice (19). Indispensable : sinon on ne retrouverait pas l'élément après l'avoir rangé.
```

**Q4** — user1 vs user2 : voisins ?

```
Non. user1 -> 453, user2 -> 742. Des chaînes proches ne donnent pas des indices voisins.
```

**Q5** — `int` à la place de `unsigned long`

```
david@mail.com et eve@mail.com changent : indices négatifs (-835 et -843).
Utiliser cet indice pour accéder au tableau = accès hors limites / crash.
```

**Q6** — Deux adresses, même indice ? Défaut ?

```
Oui, deux adresses différentes peuvent donner le même indice (collision).
Ce n'est pas un défaut : c'est normal, on gère avec le chaînage (exo 5).
```

---

## Exercice 5 — Recap

Table de hachage avec chaînage : `hash_insert` / `hash_search` / `hash_free`.

### Questions

| Recherche | Attendu | Obtenu |
| --- | --- | --- |
| Adresse présente | true | true |
| Adresse absente | false | false |
| Annuaire vide | false | false |

**Q3** — Insertion en tête inversée : observation

```
Si on inverse les 2 lignes (table[i]=n puis n->next=table[i]),
n->next pointe vers lui-même : la chaîne existante est perdue (+ fuite mémoire).
Les recherches des éléments précédents échouent / comportement incorrect.
```

**Q4** — Pourquoi sauver `n->next` avant `free(n)` ?

```
Après free(n), lire n->next est interdit (mémoire déjà libérée).
Il faut : suiv = n->next; free(n); n = suiv;
```

---

## Exercice 6 — Recap

Banc de test commun : les deux approches doivent donner le même résultat.

### Questions

**Sortie de `./test`**

```
[OK]    seq : annuaire vide
[OK]    hash : annuaire vide
[OK]    seq trouve alice@mail.com
[OK]    hash trouve alice@mail.com
[OK]    seq trouve bob@mail.com
[OK]    hash trouve bob@mail.com
[OK]    seq trouve carole@mail.com
[OK]    hash trouve carole@mail.com
[OK]    seq trouve david@mail.com
[OK]    hash trouve david@mail.com
[OK]    seq trouve eve@mail.com
[OK]    hash trouve eve@mail.com
[OK]    seq absente inconnu
[OK]    hash absente inconnu
[OK]    seq absente zoe
[OK]    hash absente zoe
[OK]    seq casse Alice
[OK]    hash casse Alice

Resultat : 18 / 18 tests OK
```

**Code de retour**

```
0
```

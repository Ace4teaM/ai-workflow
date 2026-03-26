# Processus exécution de systèmes découplés

## Contexte

### Sujet

Un processus d'exécution à systèmes multiples découplé et synchroniser.

Cette explication un peu barbare doit permettre de créer une base pour un moteur de jeu vidéo tout en conservant une abstraction forte avec les systèmes implémentés.

Ont définit plusieurs systèmes indépendants, par exemple:

* système de rendu 3d utilisant les technologies GPU pour représenter un monde virtuel
* système de rendu sonore utilisant les technologies spatiales pour produire un son réaliste
* système de physique classique pour simuler les interactions fortes de l'univers virtuel
* système de navigation pour simuler le déplacement intelligent d'objets dans l'espace
* système métier pour définir les informations du monde 
* ...

Chaque système possède ses états:

* rendu 3d : maillages, textures, shaders 
* rendu sonore : bruitages, musiques
* physique : masses, objets, forces, coordonnées
* navigation : chemins, zone d'effet
* métier : entités, états, constantes

Chaque système exécute dans un thread ou processus  séparé

* calcule des états basé sur les objets (propriétés, événements)

Le couplage permet à chaque système d'exposer et échanger des données

* le système définit les données exposées
* les données échangés sont normalisés (types scalaires)
* les données échangés sont structurés de façon simple (vecteur, liste, matrice, tableau, atome)
* les données sont remplies automatiquement par le processus (les systèmes n'ont pas besoin de connaitre les interfaces externes)

### Environnement technique

Le moteur est écrit dans le langage de programmation standard `C17`, l'usage de la librairie standard est autorisé mais pas les librairies systèmes spécifiques à l'O.S hormis si c'est explicitement demandé.

### Pile de données partagés

Les données sont alloués sur le tas **(heap)**  et contient linéairement des blocs de 64 bits (la taille est ajusté au besoin).

Les données partagés contiennent les propriétés des objets et est alimenté dynamiquement par les différents systèmes.

Le processus écrit sur les 32 bits de gauche **l'identifiant incrémentiel** de type `int` et sur les 32bits suivant la taille en bytes des propriétés. Les blocs de 64 bits suivants représentes les propriétés de l'objet.

Ensuite, la mémoire commence à l'objet suivant.

### Objets

Un objet est une structure composé d'un identifiant unique (`int` auto incrémenté) et d'un pointeur vers la **pile de données partagées**.

Les objets sont donc représentés par une liste associative valeur/pointeur.

Chaque objet possède un jeu de propriétés aligné sur 64 bits (usage/valeur) construit à la volé par les systèmes embarqués.

* L'usage est un bits flags de type `int` (premier byte identifie l'indice du système, le 2eme byte identifie le type 1=int et 2=float, le 3eme et 4eme byte identifie l'usage avec une valeur 16bits géré par le système)

* La valeur est une union de type `int` , `float` ou `byte[4]`

*Exemple:*

---------------

Imaginons un objet "chaise", celui-ci à différentes propriétés dans différents systèmes: points de vie, visuel, bruitage de choc, bruitage de frottement, boite de collision, ...

**Pile de données partagés**

```
----Object 1----
64bits => [Render:MeshId:int], 0x100
64bits => [Render:TextureId:int], 0x12
64bits => [Data:PV:int], 100
64bits => [Data:NameId:int], 0x400
64bits => [Physics:BoundingBoxId:int], 0x45
64bits => [Physics:MassValue:float], 14.256
----Object 2----
...
```

### Ressources

Il s'agit des ressources internes de chaque système. Elles sont **implémentation spécifique**.

### Couplage

Le couplage est un endroit ou les systèmes peuvent échanger leurs états en cours.

Fonctionnement général:

---------------------------------------

* Chaque système calcule ses états et se positionne en attente de synchronisation

* Les systèmes écrivent leurs données en mémoire partagé dans une zone dédié (pas de lecture)

* Les systèmes lisent les données partagés par les autres systèmes
* Les systèmes réalisent un nouveau cycle

### Les objectifs

* créer un moteur exécution rapide et multi-plateforme



### Les parties prenantes (acteurs):

* Le **Développeur** doit réaliser le codage du système



## Jalons

Les parties prenantes sont organisés ainsi par ordre de dépendance:

| Acteur                  | Jalon N°1         | Jalon N°2                             | Jalon n°3                   | Jalon n°5                     |
| ----------------------- | ----------------- | ------------------------------------- | --------------------------- | ----------------------------- |
| **programmeur système** | processus général | implémentation de différents systèmes | synchronisation des données | tests unitaires et validation |

Tous ces jalons doivent être exécuté dans l'ordre mais certains jalon peuvent être décomposés ou parallélisés. 

## Workflow

### Variables

```python
niv = 4 # nombre de niveaux
anims = 8 # nombre d'animations du personnage
pieges = niv * 10 # pieges / niveau
platformes = niv * 5 # platformes / niveau
```

Chaque contexte est réinjecté dans le prompt système.

Les outils sont également injectés.

Le produit et créé dans un environnement isolé.

La validation est soit auto (prompt ou commande) soit manuelle.

Les block de code sont interprète comme du code python



**Job** est le contexte de la tâche il est utilisé lors de la recherche de contenu dans les fichiers déjà produite et filtré par **Contexte**

**Acteur** permet de mettre un nom sur le rôle du LLM

**Skills** définit le nom des skills à ajouter au contexte

**Outils** indique les outils utilisable pour réaliser la tache

**Etape** est une description générale de la tâche à accomplir

**Produit** est le résultat attendu

**Jalon** indique (en nombre d'étoile) la possible parallélisation des tâches

**Itération** indique le nombre de fois que la tache doit être réalisé (la variable ``i`` est injecté dans les descriptions)



### Jalon  1

| Job                       | Acteur      | Skills              | Outils                   | Contexte                                                  | Etape                                                        | Produit                                                  | Jalon | Itération | Validation                |
| ------------------------- | ----------- | ------------------- | ------------------------ | --------------------------------------------------------- | ------------------------------------------------------------ | -------------------------------------------------------- | ----- | --------- | ------------------------- |
| contexte générale         | Développeur | programmeur système | write_to_file            | Environnement technique, Pile de données partagés, Objets | Ecrire la structure et les fonctions de management de **la pile mémoire partagé** | 1 fichier `shared_stack.h` et 1 fichier `shared_stack.c` | *     | 1         | `build("shared_stack.c")` |
| implémentation prototypes | Développeur | programmeur système | write_to_file, read_file | Environnement technique, shared_stack.h                   | Ecrire les prototypes de fonctions en C sans l'implémentation concrète pour un système MPMC lock-free queue avec shared memory. N'utilise que les headers du C standard | 1 fichier `sync.h` avec les nouvelles fonctions          | *     | 1         | `build("sync.h")`         |
| implémentation Linux      | Développeur | programmeur système | write_to_file, read_file | Environnement technique, shared_stack.h , sync.h          | Implémenter les prototypes de fonctions de `sync.h` pour le système Linux en utilisant `atomic_init`, `atomic_store`, `shm_open` et `mmap`. Vous pouvez utiliser les librairies POSIX. | 1 fichier `linux_sync.h` avec les nouvelles fonctions    | **    | 1         | `build("linux_sync.c")`   |
| implémentation Windows    | Développeur | programmeur système | write_to_file, read_file | Environnement technique, shared_stack.h, sync.h           | Implémenter les prototypes de fonctions de `sync.h` pour le système Windows en utilisant CreateFileMapping, InterlockedExchange et MapViewOfFile. Vous pouvez utiliser les librairies WIN32. | 1 fichier `win32_sync.h` avec les nouvelles fonctions    | **    | 1         | `build("win32_sync.c")`   |

### Jalon  2

| Job  | Acteur | Skills | Outils | Contexte | Etape | Produit | Jalon | Itération | Validation |
| ---- | ------ | ------ | ------ | -------- | ----- | ------- | ----- | --------- | ---------- |
|      |        |        |        |          |       |         |       | 1         |            |

### Jalon  3

| Job  | Acteur | Skills | Outils | Contexte | Etape | Produit | Jalon | Itération | Validation |
| ---- | ------ | ------ | ------ | -------- | ----- | ------- | ----- | --------- | ---------- |
|      |        |        |        |          |       |         |       | 1         |            |

### Jalon  4

| Job  | Acteur | Skills | Outils | Contexte | Etape | Produit | Jalon | Itération | Validation |
| ---- | ------ | ------ | ------ | -------- | ----- | ------- | ----- | --------- | ---------- |
|      |        |        |        |          |       |         |       | 1         |            |

Maintenant que nous avons toutes nos données il faut planifier et réitérer sur les différents jobs pour atteindre nos objectifs

## Skills

### programmeur système

Le programmeur système est attentif aux performances et à la portabilité du code

## Tools

...

# Mise en place des agents IA

Cette démarche permet de mener un projet de façon linéaire vers un objectif. Elle ne permet pas de retour en arrière mais uniquement une progression linéaire par passes successives.

Il faut associer des Skills et outils MCP à chaque étape du processus.

Décrire les skills manquants associer les contextes (fichiers).
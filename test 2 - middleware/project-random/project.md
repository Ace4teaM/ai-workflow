# Processus exécution de systèmes découplés

## Contexte

### Sujet

Résoudre un puzzle.

### Le jeu

Tu dispose de fichiers contenant des articles de revues spécialisé. Dans ces textes ce cache une information redondante. Tu dois trouver ces informations et les écrire individuellement dans un nouveau fichier (ce sont les pièces du puzzle). Ensuite l'objectif et de replacer ces pièces dans un ordre précis, à toi de trouve lequel. 

Attention ne numérote pas les lignes écris uniquement le texte.

### Résultat attendu

Le joueur doit retrouver des noms d'animaux dans un texte et comprendre qu'il doit les classer dans l'ordre de grandeur pour résoudre le puzzle.

### Les parties prenantes (acteurs):

* Le **Joueur** doit réussir le puzzle



## Jalons

Les parties prenantes sont organisés ainsi par ordre de dépendance:

| Acteur     | Jalon N°1           | Jalon N°2          |
| ---------- | ------------------- | ------------------ |
| **Joueur** | analyser les pièces | reformer le puzzle |

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

### Fonctions

Fonctions utilisées pour la validation des étapes.

```python
#
# Recherche les lignes dans un fichier texte
#

def contains(fichier, lignes_attendues):
    """
    Vérifie que chaque ligne de 'lignes_attendues' est présente dans 'fichier'.
    Ignore la casse et les espaces en début/fin de ligne.
    
    :param fichier: chemin vers le fichier à vérifier
    :param lignes_attendues: liste de chaînes de caractères à vérifier
    :return: True si toutes les lignes sont présentes, False sinon
    """
    try:
        with open(fichier, "r", encoding="utf-8") as f:
            contenu = f.readlines()
    except FileNotFoundError:
        print(f"Erreur : le fichier {fichier} n'existe pas.")
        return False

    # Nettoyer le contenu : trim et minuscules
    contenu_nettoye = [line.strip().lower() for line in contenu]

    # Vérifier chaque ligne attendue
    for ligne in lignes_attendues:
        if ligne.strip().lower() not in contenu_nettoye:
            print(f"Ligne manquante : '{ligne}'")
            return False

    return True

#
# Vérifie l'ordre des lignes dans un fichier texte
#
def containsInOrder(fichier, lignes_attendues):
    """
    Vérifie que chaque ligne de 'lignes_attendues' est présente et dans l'ordre dans 'fichier'.
    Ignore la casse et les espaces en début/fin de ligne.
    
    :param fichier: chemin vers le fichier à vérifier
    :param lignes_attendues: liste de chaînes de caractères à vérifier
    :return: True si toutes les lignes sont présentes dans le même ordre, False sinon
    """
    try:
        with open(fichier, "r", encoding="utf-8") as f:
            contenu = f.readlines()
    except FileNotFoundError:
        print(f"Erreur : le fichier {fichier} n'existe pas.")
        return False

    # Nettoyer le contenu : trim et minuscules
    contenu_trouve  = "\n".join([line.strip().lower() for line in contenu])
    contenu_attendu = "\n".join([line.strip().lower() for line in lignes_attendues])

    return contenu_trouve == contenu_attendu
```

### Jalon  1

| Job                | Acteur | Skills | Outils                | Contexte                                                | Etape                                                        | Produit                                                      | Jalon | Itération | Validation                                                   |
| ------------------ | ------ | ------ | --------------------- | ------------------------------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ | ----- | --------- | ------------------------------------------------------------ |
| trouver les pièces | Joueur |        | write_file, read_file | Sujet, Le jeu, article1.txt, article2.txt, article3.txt | Rechercher dans les fichiers disponibles le nom des pièces du puzzle. | 1 fichier `pieces.txt` avec la liste des pièces (1 par ligne). | *     | 1         | `contains("pieces.txt", ["chien", "souris", "puce", "éléphant", "tortue"])` |

### Jalon  2

| Job                       | Acteur | Skills | Outils                | Contexte                  | Etape                                | Produit                                                      | Jalon | Itération | Validation                                                   |
| ------------------------- | ------ | ------ | --------------------- | ------------------------- | ------------------------------------ | ------------------------------------------------------------ | ----- | --------- | ------------------------------------------------------------ |
| implémentation prototypes | Joueur |        | write_file, read_file | Sujet, Le jeu, pieces.txt | Trouver l'ordre des pièces du puzzle | 1 fichier `ordre.txt` avec la liste des pièces (1 par ligne) dans l'ordre souhaité | *     | 1         | `containsInOrder("pieces.txt", ["puce", "souris", "chien", "tortue", "éléphant"])` |

Maintenant que nous avons toutes nos données il faut planifier et réitérer sur les différents jobs pour atteindre nos objectifs

## Skills

...

## Tools

...

# Mise en place des agents IA

Cette démarche permet de mener un projet de façon linéaire vers un objectif. Elle ne permet pas de retour en arrière mais uniquement une progression linéaire par passes successives.

Il faut associer des Skills et outils MCP à chaque étape du processus.

Décrire les skills manquants associer les contextes (fichiers).
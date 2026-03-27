# AI Workflow

AI Workflow vise à définir une trame de définition de projet pour l'associé à un outil d'orchestration d'IA.

Le but est purement à des fins de tests et d'apprentissage.

Ce projet utilise LangChain, un Framework pour orchestrer LLM, outils, mémoire et données dans applications intelligentes.

Jupyter est utilisé pour écrire le code d'exécution de l'orchestrateur.



**Objectif : créer un projet assisté par IA par itération successives et validation des jalons.**

> Le travail consiste à bien définir chaque étape de la construction, les dépendances, les outils, les acteurs, les rôles et les jalons.

> Lorsqu'un souhaite créer un Workflow on décrit de façon large et détaillé les connaissances métiers d'une équipe/entreprise. La richesse est dans la pertinence de rédaction des Skills et de la description des Jobs

> En résumé : Il faut décrire le processus pour créer des livrables, ajuster les livrables produits passer à l'étape suivante. Reprendre le processus à l'étape X et reformuler si besoin.



**Observations:**

L'IA travaille mieux dans un scope plus petit: optimisation de la fenêtre contextuelle, tâches précises. En effet, la mémoire de contexte d'un LLM est limité ce qui pousse les ingénieurs à développer différentes techniques de "rappels mémoires" ou "recherche RAG" pour réinjecter du contexte à une IA générative. Ici, la technique consiste à maîtriser ce point en spécifiant dès la conception le contexte à utiliser pour la tâche en cours.



**Définition:**

Alors comment décrire de façon précise un worklow pour tout type de développement informatique ?

1. Identifier le contexte (sujet, environnement technique, éléments, ...1)
1. Identifier les rôles (Développeur, scénariste, dessinateur, ... )
1. Identifier les jalons (création du scénario => dessins des artworks => programmation)
1. Définir les taches (décrire les tâches de chaque acteur, définir le contexte et le résultat attendu)

Pour découper un projet en flux de travails il faut cadrer le sujet, les objectifs et identifier les parties prenantes.

Dans ces tests nous utilisons le fichier `project.md` pour décrire le flux de travail.

Le fichier `journal.md` est utile pour visualiser l'historique des échanges avec le LLM.

# Mise en route

L'environnement virtuel exécution Python à été créé avec **Conda** et sauvegardé dans le fichier `environment.yaml` avec la commande suivante:

```shell
conda env export > environment.yaml
```

Pour restaurer l'environnement:

Ouvrir la console **Conda** dans le dossier contenant `environment.yaml` et exécuter la commande suivante:

```shell
conda env create -f environment.yaml -n ai-workflow-test
```

puis, activer l'environnement

```
conda activate ai-workflow-test
```

# Tests

| dossier             | description                                                  |
| ------------------- | ------------------------------------------------------------ |
| test 1 - chain      | test la capacité de dérouler les étapes du worklow les unes après les autres en utilisant outils et contextes |
| test 2 - middleware | test la capacité à s'insérer dans les échanges avec le LLM pour obtenir un résultat personnalisé. Ici on évalue le travail dynamiquement avant que la tâche ne soit terminée. |



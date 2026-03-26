**Objectif : créer un projet assisté par IA par itération successives et validation des jalons.**

> Le travail consiste à bien définir chaque étape de la construction, les dépendances, les outils, les acteurs, les rôles et les jalons.

> Lorsqu'in créer un Workflow on décrit de façon large et détaillé les connaissances métiers d'une équipe/entreprise. La richesse est dans la pertinence de rédaction des Skills et de la description des Jobs

> En résumé : Décrire le processus et créer des produits, ajuster les produits passer à l'étape suivante. Reprendre le processus à l'étape X et reformuler le besoin.



Comment intégrer l'IA du flux de développement ?

L'IA doit elle mener le projet ou doit t'elle s'intégrer dans un workflow plus large ?

Observations:

L'IA travaille mieux dans un scope plus petit. optimisation de la fenêtre contextuelle. tâche précise.

Alors comment décrire de façon précise un worklow pour tout type de développement informatique ?

1. Identifier le contexte

Pour découper un projet en flux de travails il faut cadrer le sujet, les objectifs et identifier les parties prenantes.



exemple N°1 Un jeu vidéo

exemple N°2 Une application desktop

exemple N°3 Un service web

exemple N°4 Un protocole de communication



4 Projets très différents avec un workflow radicalement différent.



Essayons de définir le Workflow d'un jeu vidéo:

# Cas n°1 : Le jeu vidéo

## Définition

**Le sujet**:

Une *application de jeu vidéo* m'étant en scène un *personnage jouable* dans un environnement de type *2d-platform*  en vue de coté. Le but du jeu est de survivre aux différents pièges du parcours. 



**Les objectifs**:

* réaliser 3 niveaux avec chacun un thème différent
* imaginer 10 piège par niveau pour un totale de 30
* l'application doit être multiplateforme pour PC et Nintendo Switch



**Les parties prenantes** (acteurs):

* Le **scénariste** doit imaginer le scénario et écrire les dialogues
* Le **level designer** doit imaginer les niveaux en se basant sur le scénario
* L'**artiste** doit concevoir le style graphique en se basant sur le scénario
* Le **graphiste** doit créer les graphiques numériques en se basant sur l'artiste
* Le **développeur** doit programmer le jeu en se basant sur les ressources du graphiste, du level designer et du scénariste



Les parties prenantes sont organisés ainsi par ordre de dépendance:

| Acteur             | Jalon N°1   | Jalon N°2                                   | Jalon n°3      | Jalon n°5    |
| ------------------ | ----------- | ------------------------------------------- | -------------- | ------------ |
| **Scénariste**     | le scénario |                                             |                |              |
| **Level designer** |             | les concepts des objets, joueurs et niveaux |                |              |
| **Graphiste**      |             |                                             | les graphiques |              |
| **Artiste**        |             | le style graphique                          |                |              |
| **Développeur**    |             |                                             |                | le programme |

Tous ces jalons doivent être exécuté dans l'ordre mais certains jalon peuvent être décomposés ou parallélisés. 

* Le scénario doit être existant avant tous mais il peut être décomposé en différents éléments: l'histoire générale. La définition du personnage principal. Les péripéties (niveaux).
* Les concepts peut être décomposé par niveau
* Le style graphique général, les thèmes de différents niveaux
* Les graphiques du personnage, des chaque niveau
* Le développement du projet de base, l'UI, les mécaniques de bases, les animations, les datas, les cinématiques

## Workflow

**Variables**

```
niv = 4 # nombre de niveaux
anims = 8 # nombre d'animations du personnage
pieges = niv * 10 # pieges / niveau
platformes = niv * 5 # platformes / niveau
```



**Jalon  1 : **

| Job                  | Acteur     | Skills       | Outils     | Contexte           | Etape                                              | Produit                                                      | Jalon | Itération | Validation |
| -------------------- | ---------- | ------------ | ---------- | ------------------ | -------------------------------------------------- | ------------------------------------------------------------ | ----- | --------- | ---------- |
| contexte générale    | Scénariste | story writer | write_text | sujet du projet    | Décrire l'environnement, l'époque                  | 1 Texte de 200 mots                                          | *     | 1         |            |
| histoire générale    | Scénariste | story writer | write_text | produits ci-dessus | Le Début, la Fin et la monté en puissance (milieu) | 3 Paragraphes de 200 mots chacun (Début, Fin, Milieu)        | **    | 1         |            |
| personnage principal | Scénariste | story writer | write_text | produits ci-dessus | Décrire le personnage, sa personnalité             | 1 Texte de 200 mots                                          | **    | 1         |            |
| niveau               | Scénariste | story writer | write_text | produits ci-dessus | pièges, environnement, objectif                    | Décrire 10 pièges (20 mots), 1 environnement (100 mots), 1 objectif (20 mots) | ***   | niv       |            |

**Jalon  2 : **

| Job                  | Acteur         | Skills           | Outils     | Etape                                                        | Produit                                                      | Jalon | Itération | Validation |
| -------------------- | -------------- | ---------------- | ---------- | ------------------------------------------------------------ | ------------------------------------------------------------ | ----- | --------- | ---------- |
| personnage principal | Artiste        | character design | sketch     | Décrire le style vestimentaire, l'apparence physique, ses équipements | 4 croquis (devant, derrière, coté droit, coté gauche)        | *     | 1         |            |
| charte graphique     | Artiste        | UI designer      | sketch     | Décrire le générale de l'interface utilisateur               | 1 planche avec gamme de couleur et éléments de l'UI: Bouton, Liste, Panneau, Font, Background | *     | 1         |            |
| personnage principal | Level Designer | Level  design    | write_text | Techniques (ex: double saut, voler, ...), Mouvements,        | 1 liste de 3 techniques et 3 mouvements de gameplay          | *     | 1         |            |
| niveau               | Artiste        | Artistic design  | sketch     | gamme de couleurs, les objets, les plateformes               | 1 croquis avec les différents éléments du niveau et sa palette de couleurs | **    | niv       |            |
| niveau               | Level Designer | Level  design    | write_text | mécanique des pièges, cadences de jeu, phases de jeu         | 1 liste contenant 5 éléments parmi (fonctionnement d'un piège, phase de jeu cadencé avec un début et une fin, énigme ou puzzle à résoudre pour progresser) | **    | niv       |            |

**Jalon  3 : **

| Job                  | Acteur      | Skills     | Outils               | Etape                              | Produit                                                      | Jalon | Itération  | Validation |
| -------------------- | ----------- | ---------- | -------------------- | ---------------------------------- | ------------------------------------------------------------ | ----- | ---------- | ---------- |
| personnage principal | Graphiste   | pixel arts | generate_sprite      | Créer les animations du personnage | 5 Sprites par animation : marcher, courir, sauter, tomber, mourir par projectile, mourir écrasé, mourir brulé, mourir noyé | *     | anims      |            |
| niveau               | Graphiste   | pixel arts | generate_sprite      | Créer les animations des pièges    | Sprites des différents éléments du piège                     | *     | pieges     |            |
| niveau               | Graphiste   | pixel arts | generate_sprite      | Créer les plateformes du niveau    | Sprites des différents éléments du niveau (plateformes)      | *     | platformes |            |
| niveau               | Graphiste   | pixel arts | generate_image       | Créer le Background du niveau      | Image de fond avec parallaxe et répétition                   | *     | niv        |            |
| programme            | Développeur | coding     | create_unity_project | Programme de base                  | Création du projet (première compilation)                    | *     | 1          |            |

**Jalon  4 : **

| Job                  | Acteur      | Skills                     | Outils      | Contexte                              | Etape                           | Produit                                                      | Jalon | Itération  | Validation |
| -------------------- | ----------- | -------------------------- | ----------- | ------------------------------------- | ------------------------------- | ------------------------------------------------------------ | ----- | ---------- | ---------- |
| programme            | Développeur | coding                     | Game Engine | Sprites créés aux étapes précédentes. | Programme de base               | Modification du projet: Importation des assets et choix de l'arborescence du projet | *     | 1          |            |
| UI                   | Développeur | coding,  UI Design         | Game Engine |                                       | Création du menu principal      | 1 scène UI : Menu principal avec bouton démarrer / continuer | **    | 1          |            |
| personnage principal | Développeur | coding, Sprites animations | Game Engine |                                       | Créer le contrôleur d'animation | 1 contrôleur d'animation avec les différents état des animations de mouvement | **    | 1          |            |
| niveau               | Développeur | coding, Game physics       | Game Engine |                                       | Intégrer la physique            | 1 script de composant : Gravité, masse des objets, mouvement et collisions | **    | 1          |            |
| pièges               | Développeur | coding, Level scripting    | Game Engine |                                       | Mécanique des pièges            | 1 script de composant : Intégrer la mécanique des pièges : mouvements, événements, transformations | **    | pieges     |            |
| plateformes          | Développeur | coding, Game physics       | Game Engine |                                       | Mécanique des plateformes       | 1 script de composant : résistance, rebond, accroche, ...    | **    | platformes |            |
| UI                   | Développeur | coding,  UI Design         | Game Engine |                                       | Informations de jeu ATH         | 1 scène UI avec les informations à l'écran: temps de jeu, nombre de vies | ***   | 1          |            |
| niveau               | Développeur | coding, Level design       | Game Engine |                                       | Créer la scène                  | 1 scène Game avec les plateformes, pièges et objets disposés dans l'espace | ***   | niv        |            |

Maintenant que nous avons toutes nos données il faut planifier et réitérer sur les différents jobs pour atteindre nos objectifs

Semaine 1 - Scénariste - Job 1 -> travail -> objectif atteint ? -> tests -> satisfaction ? -> OK

Semaine 1 - Scénariste - Job 2 -> travail -> objectif atteint ? -> tests -> satisfaction ? -> OK

Semaine 1 - Scénariste - Job 3 -> travail -> objectif atteint ? -> tests -> satisfaction ? -> OK

## Skills

### Unity Coding

Programmer en langages C# pour les outils Unity

### UI Design

Techniques de conceptions d'interfaces utilisateurs

### Level design

Techniques de conceptions de niveaux de jeux vidéos

### Level scripting

Techniques de scriptage des événements et progressions dans un jeu vidéo

## Tools

### generate_sprite

```python
import base64
import requests
from langchain.agents import initialize_agent, Tool
from langchain.agents import AgentType
from langchain_openai import ChatOpenAI
from openai import OpenAI

client = OpenAI()


def generate_sprite(prompt: str) -> str:
    """
    Génère un sprite et l'enregistre dans un fichier PNG.
    input = description du sprite
    """

    result = client.images.generate(
        model="gpt-image-1",
        prompt=f"pixel art sprite sheet style, game sprite, transparent background: {prompt}",
        size="512x512"
    )

    image_base64 = result.data[0].b64_json
    image_bytes = base64.b64decode(image_base64)

    filename = "sprite.png"

    with open(filename, "wb") as f:
        f.write(image_bytes)

    return f"Sprite généré et sauvegardé dans {filename}"


tools = [
    Tool(
        name="SpriteGenerator",
        func=generate_sprite,
        description="Génère un sprite pixel art pour jeu vidéo à partir d'une description"
    )
]

def test():
    llm = ChatOpenAI(temperature=0)

    agent = initialize_agent(
        tools,
        llm,
        agent=AgentType.ZERO_SHOT_REACT_DESCRIPTION,
        verbose=True
    )
    
    agent.run("génère un sprite pixel art d'un dragon rouge pour jeu vidéo")
```



# Mise en place des agents IA

Cette démarche permet de mener un projet de façon linéaire vers un objectif. Elle ne permet pas de retour en arrière mais uniquement une progression linéaire par passes successives.

Il faut associer des Skills et outils MCP à chaque étape du processus.

Décrire les skills manquants associer les contextes (fichiers).
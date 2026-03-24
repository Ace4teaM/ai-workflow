# 2D Platform Game

## Définition

### Le sujet

Une *application de jeu vidéo* m'étant en scène un *personnage jouable* dans un environnement de type *2d-platform*  en vue de coté. Le but du jeu est de survivre aux différents pièges du parcours. 



### Les objectifs

* réaliser 3 niveaux avec chacun un thème différent
* imaginer 10 piège par niveau pour un totale de 30
* l'application doit être multiplateforme pour PC et Nintendo Switch



### Les parties prenantes (acteurs):

* Le **scénariste** doit imaginer le scénario et écrire les dialogues
* Le **level designer** doit imaginer les niveaux en se basant sur le scénario
* L'**artiste** doit concevoir le style graphique en se basant sur le scénario
* Le **graphiste** doit créer les graphiques numériques en se basant sur l'artiste
* Le **développeur** doit programmer le jeu en se basant sur les ressources du graphiste, du level designer et du scénariste



## Jalons

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

| Job                  | Acteur     | Skills       | Outils     | Contexte             | Etape                                                        | Produit                                                      | Jalon | Itération | Validation                        |
| -------------------- | ---------- | ------------ | ---------- | -------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ | ----- | --------- | --------------------------------- |
| contexte générale    | Scénariste | story writer | write_text |                      | Décrire l'environnement, l'époque du scénario                | 1 Texte de 200 mots dans le fichier contexte.md              | *     | 1         | `fileExists("contexte.md")`       |
| histoire générale    | Scénariste | story writer | write_text | contexte.md          | Décrire le Début, la Fin et la monté en puissance (milieu) du scénario | 3 Paragraphes de 200 mots chacun (Début, Fin, Milieu) dans le fichier story.md | **    | 1         | `fileExists("story.md")`          |
| personnage principal | Scénariste | story writer | write_text | contexte.md story.md | Décrire le personnage et sa personnalité                     | 1 Texte de 200 mots dans le fichier main_character.md        | **    | 1         | `fileExists("main_character.md")` |
| niveau               | Scénariste | story writer | write_text | contexte.md story.md | Décrire pièges, environnement, objectif                      | Décrire 10 pièges, 1 environnement, 1 objectif dans le fichier `level_{i}.md` | ***   | `{niv}`   | `fileExists(f"level_{i}.md")`     |

### Jalon  2

| Job                  | Acteur         | Skills             | Outils     | Contexte          | Etape                                                        | Produit                                                      | Jalon | Itération | Validation                                                   |
| -------------------- | -------------- | ------------------ | ---------- | ----------------- | ------------------------------------------------------------ | ------------------------------------------------------------ | ----- | --------- | ------------------------------------------------------------ |
| personnage principal | Artiste        | character designer | sketch     | main_character.md | Décrire le style vestimentaire, l'apparence physique, ses équipements | 4 croquis (devant, derrière, coté droit, coté gauche) dans les fichiers front.bmp, back.bmp, right.bmp et left.bmp | *     | 1         | `fileExists("front.bmp") and fileExists("back.bmp") and fileExists("right.bmp") and fileExists("left.bmp")` |
| charte graphique     | Artiste        | UI designer        | sketch     |                   | Décrire le style générale de l'interface utilisateur         | 1 planche avec gamme de couleur et éléments de l'UI: Bouton, Liste, Panneau, Font, Background dans le fichier UI.bmp | *     | 1         | `fileExists("UI.bmp")`                                       |
| personnage principal | Level Designer | Level  designer    | write_text |                   | Techniques (ex: double saut, voler, ...), Mouvements,        | 1 liste de 3 techniques et 3 mouvements de gameplay dans techniques.md | *     | 1         | `fileExists("techniques.md")`                                |
| niveau               | Artiste        | Artist designer    | sketch     |                   | gamme de couleurs, les objets, les plateformes               | 1 croquis avec les différents éléments du niveau et sa palette de couleurs dans le fichier `level_{i}.bmp` | **    | `{niv}`   |                                                              |
| niveau               | Level Designer | Level  designer    | write_text |                   | mécanique des pièges, cadences de jeu, phases de jeu         | 1 liste contenant 5 éléments parmi (fonctionnement d'un piège, phase de jeu cadencé avec un début et une fin, énigme ou puzzle à résoudre pour progresser) dans `level_{i}.md` | **    | `{niv}`   |                                                              |

### Jalon  3

| Job                  | Acteur      | Skills           | Outils               | Contexte | Etape                              | Produit                                                      | Jalon | Itération      | Validation |
| -------------------- | ----------- | ---------------- | -------------------- | -------- | ---------------------------------- | ------------------------------------------------------------ | ----- | -------------- | ---------- |
| personnage principal | Graphiste   | pixel artist     | generate_sprite      |          | Créer les animations du personnage | 5 Sprites par animation : marcher, courir, sauter, tomber, mourir par projectile, mourir écrasé, mourir brulé, mourir noyé | *     | `{anims}`      |            |
| niveau               | Graphiste   | pixel artist     | generate_sprite      |          | Créer les animations des pièges    | Sprites des différents éléments du piège                     | *     | `{pieges}`     |            |
| niveau               | Graphiste   | pixel artist     | generate_sprite      |          | Créer les plateformes du niveau    | Sprites des différents éléments du niveau (plateformes)      | *     | `{platformes}` |            |
| niveau               | Graphiste   | pixel artist     | generate_image       |          | Créer le Background du niveau      | Image de fond avec parallaxe et répétition                   | *     | `{niv}`        |            |
| programme            | Développeur | game programming | create_unity_project |          | Programme de base                  | Création du projet (première compilation)                    | *     | 1              |            |

### Jalon  4

| Job                  | Acteur      | Skills                             | Outils      | Contexte                              | Etape                           | Produit                                                      | Jalon | Itération      | Validation |
| -------------------- | ----------- | ---------------------------------- | ----------- | ------------------------------------- | ------------------------------- | ------------------------------------------------------------ | ----- | -------------- | ---------- |
| programme            | Développeur | game programming                   | Game Engine | Sprites créés aux étapes précédentes. | Programme de base               | Modification du projet: Importation des assets et choix de l'arborescence du projet | *     | 1              |            |
| UI                   | Développeur | game programming,  UI Designer     | Game Engine |                                       | Création du menu principal      | 1 scène UI : Menu principal avec bouton démarrer / continuer | **    | 1              |            |
| personnage principal | Développeur | game programming, sprites animator | Game Engine |                                       | Créer le contrôleur d'animation | 1 contrôleur d'animation avec les différents état des animations de mouvement | **    | 1              |            |
| niveau               | Développeur | game programming, Game physics     | Game Engine |                                       | Intégrer la physique            | 1 script de composant : Gravité, masse des objets, mouvement et collisions | **    | 1              |            |
| pièges               | Développeur | game programming, Level scripting  | Game Engine |                                       | Mécanique des pièges            | 1 script de composant : Intégrer la mécanique des pièges : mouvements, événements, transformations | **    | `{pieges}`     |            |
| plateformes          | Développeur | game programming, Game physics     | Game Engine |                                       | Mécanique des plateformes       | 1 script de composant : résistance, rebond, accroche, ...    | **    | `{platformes}` |            |
| UI                   | Développeur | game programming,  UI Design       | Game Engine |                                       | Informations de jeu ATH         | 1 scène UI avec les informations à l'écran: temps de jeu, nombre de vies | ***   | 1              |            |
| niveau               | Développeur | game programming, Level design     | Game Engine |                                       | Créer la scène                  | 1 scène Game avec les plateformes, pièges et objets disposés dans l'espace | ***   | `{niv}`        |            |

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
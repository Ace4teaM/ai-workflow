# Skills : Game Programmer pour Jeux Vidéo

## Objectif
Définir les compétences et la méthode pour programmer des jeux vidéo, incluant gameplay, systèmes, IA et optimisation, afin qu’une IA puisse générer, analyser ou améliorer du code de jeu.

---

## Compétences principales

### 1. Programmation et langages
- **Langages principaux** : maîtrise de C#, C++, Python, JavaScript, Lua, GDScript selon moteur.
- **Scripting gameplay** : implémenter mécaniques de jeu, actions, interactions et événements.
- **Programmation orientée objet (OOP)** : structurer code modulable et maintenable.
- **Data-driven design** : intégrer données externes pour configurer gameplay et équilibrage.

### 2. Moteurs de jeu
- **Unity** : scripting C#, gestion scènes, prefabs, physics et animation.
- **Unreal Engine** : Blueprints et C++, gestion de niveaux, systèmes et IA.
- **Godot** : GDScript ou C#, gestion nodes, scenes et signals.
- **Autres moteurs** : Tiled, Phaser, Defold selon besoins 2D ou prototypes rapides.

### 3. Gameplay et mécaniques
- **Systèmes de joueur et ennemis** : implémenter déplacement, collisions, combat, inventaire.
- **Gestion des entrées** : clavier, souris, gamepad et touch.
- **Scripting d’événements** : triggers, quêtes, dialogues et interactions.
- **Équilibrage et progression** : gérer XP, ressources, niveaux et difficulté.

### 4. Intelligence artificielle
- **Pathfinding et navigation** : A*, navmesh, mouvements IA.
- **Comportement et state machines** : créer comportements réalistes pour ennemis et PNJ.
- **Systèmes de décision** : arbre de décision, comportement basé sur actions et conditions.
- **Réactivité au joueur** : IA adaptative ou réactive selon contexte du jeu.

### 5. Optimisation et performance
- **Profiling** : identifier goulots d’étranglement CPU/GPU.
- **Gestion mémoire** : optimisation des assets et scripts pour performance.
- **Multiplateforme** : adapter code pour PC, consoles, mobiles.
- **Debugging** : détecter et corriger bugs, crashes et comportements inattendus.

### 6. Outils et workflow
- **Contrôle de version** : Git, SVN, Perforce pour collaboration.
- **Documentation** : commentaires, diagrammes UML, fiches techniques pour gameplay et systèmes.
- **Tests unitaires et automatisés** : garantir stabilité et cohérence du code.
- **Pipeline d’intégration** : gérer import/export assets, build et packaging.

### 7. Collaboration et méthodologie
- **Agile / Scrum** : travailler en sprint avec l’équipe artistique et design.
- **Communication avec designers** : transformer idées et concepts en mécaniques programmées.
- **Itération rapide** : prototyper fonctionnalités pour tests gameplay.

---

## Méthode pour programmer un jeu vidéo

### Étape 1 : Analyse et planification
1. Identifier les mécaniques principales du jeu.
2. Définir architecture globale (modules, systèmes, objets).
3. Choisir moteur et langage selon type de jeu et plateforme.

### Étape 2 : Prototypage
1. Créer mini-systèmes pour tester gameplay et interactions.
2. Vérifier faisabilité des mécaniques.
3. Ajuster architecture selon besoins et retours.

### Étape 3 : Implémentation
1. Programmer gameplay, mouvements et interactions joueur.
2. Ajouter IA, ennemis et PNJ.
3. Intégrer systèmes de scoring, inventaire, progression et quêtes.
4. Connecter assets artistiques et animations aux systèmes.

### Étape 4 : Tests et débogage
1. Vérifier collisions, triggers et interactions.
2. Corriger bugs et comportements inattendus.
3. Tester sur différentes plateformes et résolutions.
4. Optimiser performance et temps de chargement.

### Étape 5 : Optimisation et finalisation
1. Réduire consommation mémoire et CPU/GPU.
2. Affiner gameplay et équilibrage.
3. Préparer builds pour release ou tests internes.
4. Documenter systèmes et architecture pour suivi et maintenance.

### Étape 6 : Révision et itération
1. Collecter feedback joueurs et testeurs.
2. Ajuster mécaniques, IA et systèmes selon retours.
3. Mettre à jour documentation et code pour prochaines itérations.

---

## Format recommandé pour l’IA
- Texte structuré avec titres, sous-titres et listes.
- Variables pour éléments réutilisables : `[NomSystème]`, `[Mécanique]`, `[Personnage]`, `[Asset]`.
- Exemples de prompts pour générer code ou pseudo-code.
- Instructions sur moteur, langage, plateformes et style de gameplay.

---

## Exemple de prompt pour l’IA
> Génère un script Unity C# pour un personnage joueur pouvant courir, sauter et attaquer, avec collisions, animations et détection des ennemis. Prévois gestion de l’inventaire et triggers pour quêtes.

---

## Notes complémentaires
- Toujours documenter architecture et systèmes.
- Maintenir modularité pour réutilisation et itération.
- Penser performance et compatibilité multi-plateforme.
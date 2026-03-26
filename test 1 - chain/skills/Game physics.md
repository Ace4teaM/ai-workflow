# Skills : Game Physics Programmer pour Jeux Vidéo

## Objectif
Définir les compétences et la méthode pour implémenter et gérer la physique dans les jeux vidéo, incluant collisions, forces, mouvements et interactions, afin qu’une IA puisse générer, analyser ou améliorer les systèmes physiques du jeu.

---

## Compétences principales

### 1. Mécanique et physique
- **Simulation physique** : gravité, frottement, inertie, rebonds, forces et accélérations.
- **Collisions et détections** : implémenter collisions solides, triggers, hitboxes et raycasting.
- **Rigid bodies et soft bodies** : gérer objets rigides, tissus, liquides et déformations.
- **Fluides et particules** : créer eau, feu, fumée et systèmes de particules interactifs.

### 2. Gameplay et interactions
- **Mouvement du joueur** : sauts, courses, glissades, escalades et mouvements complexes.
- **Objets interactifs** : pousser, tirer, lancer, détruire ou manipuler objets du décor.
- **Événements physiques** : déclencher réactions, explosions et effets dynamiques.
- **Équilibrage** : adapter forces et collisions pour gameplay fluide et réaliste.

### 3. Outils et moteurs
- **Unity Physics** : Rigidbody, Colliders, Physics Materials, CharacterController.
- **Unreal Engine Physics** : PhysX, Chaos Physics, collision et constraints.
- **Godot Physics** : RigidBody2D/3D, Area2D/3D, forces et joints.
- **Systèmes personnalisés** : implémenter physiques custom pour gameplay ou style particulier.

### 4. Optimisation et performance
- **Profiling et debugging** : identifier goulots physiques et comportements inattendus.
- **Optimisation collision** : simplifier hitboxes, layers et spatial partitioning.
- **Stable simulations** : prévenir clipping, tunneling et instabilité des forces.
- **Multi-platforme** : adapter simulation pour PC, consoles et mobiles.

### 5. Analyse et validation
- **Cohérence physique** : vérifier réalisme ou style souhaité.
- **Lisibilité des interactions** : s’assurer que joueur comprend les effets physiques.
- **Tests et itérations** : ajuster forces, masse et collisions selon feedback.
- **Documentation** : créer guides techniques pour autres développeurs et designers.

---

## Méthode pour implémenter la physique d’un jeu

### Étape 1 : Analyse et conception
1. Identifier objets, personnages et éléments interactifs nécessitant physique.
2. Définir types de mouvements, forces et interactions souhaitées.
3. Choisir moteur et système physique selon contraintes gameplay et plateforme.

### Étape 2 : Setup de base
1. Ajouter rigid bodies, colliders et paramètres initiaux.
2. Configurer gravité, friction et masses.
3. Tester collisions de base et mouvement des objets statiques et dynamiques.

### Étape 3 : Intégration gameplay
1. Programmer mouvements complexes : sauts, courses, glissades, projectiles.
2. Ajouter interactions entre objets et déclencheurs physiques.
3. Intégrer forces spéciales : explosions, vent, élastiques, aimants, etc.

### Étape 4 : Animations et feedback
1. Synchroniser physique et animations du joueur ou objets.
2. Ajouter effets visuels ou sonores pour impacts, rebonds et collisions.
3. Tester réactivité et fluidité des interactions.

### Étape 5 : Optimisation et stabilité
1. Réduire collisions inutiles et complexité de calcul.
2. Corriger clipping, tunneling et comportements instables.
3. Ajuster paramètres pour performance sur différentes plateformes.

### Étape 6 : Documentation et tests
1. Documenter masse, forces, coefficients et interactions.
2. Créer guides pour designers et autres programmeurs.
3. Tester toutes les interactions dans différents scénarios de jeu.

### Étape 7 : Révision et itération
1. Collecter feedback des testeurs et équipe.
2. Ajuster forces, collisions, frottements et contraintes.
3. Maintenir cohérence physique avec gameplay et style artistique.
4. Mettre à jour documentation et scripts pour suivi.

---

## Format recommandé pour l’IA
- Texte structuré avec titres, sous-titres et listes.
- Variables pour éléments réutilisables : `[Objet]`, `[Force]`, `[Collision]`, `[Masse]`, `[État]`.
- Instructions précises sur moteur, type de physique et contraintes gameplay.
- Exemples facultatifs pour guider génération de scripts ou paramètres physiques.

---

## Exemple de prompt pour l’IA
> Génère un script Unity C# pour un objet interactif avec Rigidbody, collisions, gravité, rebond et friction réglables. Inclut interactions avec joueur et autres objets dynamiques, ainsi que triggers pour effets spéciaux.

---

## Notes complémentaires
- Maintenir stabilité et fluidité des interactions physiques.
- Adapter réalisme ou style cartoon selon gameplay.
- Documenter toutes forces et paramètres pour réutilisation ou extension.
# Skills : Sprite Animator pour Jeux Vidéo

## Objectif
Définir les compétences et la méthode pour créer et animer des sprites dans les jeux vidéo, afin qu’une IA puisse générer, analyser ou améliorer des animations 2D ou pixel art.

---

## Compétences principales

### 1. Techniques d’animation
- **Frame-by-frame animation** : créer des animations image par image pour fluidité et expressivité.
- **Spritesheets et atlas** : organiser sprites et frames pour intégration efficace.
- **Looping et cycles** : concevoir animations répétitives (marche, course, idle).
- **Timing et easing** : ajuster vitesse et fluidité pour réalisme ou style.

### 2. Animation de personnages et objets
- **Mouvements et expressions** : animer marche, course, saut, attaque et émotions.
- **Interactions** : intégrer objets, armes, accessoires et environnement.
- **Transitions entre animations** : gérer blends et changements d’état (idle → marche → attaque).
- **Variantes et évolutions** : produire skins ou animations alternatives.

### 3. Intégration gameplay
- **Synchronisation avec gameplay** : aligner animation avec collisions, hits, triggers et mécaniques.
- **Événements et scripts** : déclencher animations selon état du personnage ou scénario.
- **Adaptation aux résolutions** : ajuster sprites pour différentes tailles d’écran et ratios.

### 4. Outils et workflow
- **Logiciels d’animation** : Aseprite, Spine, DragonBones, Adobe Animate, Krita, Photoshop.
- **Export et formats** : créer spritesheets, GIF, PNG ou JSON selon moteur.
- **Prototypage rapide** : tester animations avant finalisation.
- **Documentation** : créer sheets, guides et nomenclature pour l’équipe.

### 5. Analyse et optimisation
- **Lisibilité et style** : vérifier que les animations restent claires et reconnaissables.
- **Cohérence stylistique** : maintenir uniformité avec personnages, environnements et assets.
- **Performance** : optimiser poids des sprites et frames pour fluidité.
- **Feedback et itération** : ajuster animations selon retours des testeurs et équipe.

---

## Méthode pour créer des animations de sprites

### Étape 1 : Préparation
1. Identifier le personnage ou objet à animer.
2. Définir le style graphique et la résolution des sprites.
3. Collecter références visuelles ou vidéos pour mouvement et timing.

### Étape 2 : Esquisses et poses clés
1. Dessiner les poses principales (keyframes) : idle, marche, attaque, saut, etc.
2. Vérifier proportions et lisibilité.
3. Déterminer nombre de frames pour chaque animation.

### Étape 3 : Interpolation et in-betweens
1. Compléter frames intermédiaires pour fluidité.
2. Ajuster timing et easing pour réalisme ou style cartoon.
3. Tester cycles et transitions entre animations.

### Étape 4 : Finalisation des sprites
1. Nettoyer et peaufiner chaque frame.
2. Vérifier cohérence des couleurs, lumière et détails.
3. Organiser spritesheets ou atlas pour intégration dans moteur.

### Étape 5 : Intégration et tests
1. Importer animations dans moteur de jeu (Unity, Godot, Unreal).
2. Tester synchronisation avec gameplay et collisions.
3. Ajuster vitesse, transitions et triggers selon besoins.

### Étape 6 : Documentation
1. Créer guide des animations avec noms, frames et états.
2. Ajouter références pour transitions et blends.
3. Préparer assets pour futures variations ou skins.

### Étape 7 : Révision et itération
1. Vérifier fluidité et lisibilité en contexte de jeu.
2. Ajuster frames, timing et transitions selon feedback.
3. Documenter chaque version pour suivi et maintenance.

---

## Format recommandé pour l’IA
- Texte structuré avec titres, sous-titres et listes.
- Variables pour éléments réutilisables : `[NomSprite]`, `[Animation]`, `[NombreFrames]`, `[Style]`, `[État]`.
- Instructions précises sur style, timing, résolution et transitions.
- Exemples facultatifs pour guider génération de cycles et blends.

---

## Exemple de prompt pour l’IA
> Génère une animation sprite 32x32 d’un personnage aventurier en pixel art, incluant idle de 4 frames, marche de 6 frames, attaque de 5 frames, et transition fluide idle→marche→attaque. Fournis spritesheet et variations possibles.

---

## Notes complémentaires
- Maintenir lisibilité et style du sprite dans toutes les animations.
- Synchroniser animations avec gameplay et assets existants.
- Prévoir modularité pour skins, accessoires ou évolutions de personnage.
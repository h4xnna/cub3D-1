

https://github.com/user-attachments/assets/65c171d1-08ca-46cb-b0f6-7413933eb371

# cub3D 🏰

Un moteur de rendu en pseudo-3D inspiré du jeu Wolfenstein 3D, développé en C dans le cadre du cursus 42. Le projet implémente un algorithme de **raycasting** pour afficher un environnement en 3D à partir d'une carte 2D, avec gestion des textures, des couleurs et des déplacements du joueur.

## 📋 Sommaire

- [Aperçu](#-aperçu)
- [Fonctionnalités](#-fonctionnalités)
- [Prérequis](#-prérequis)
- [Installation](#-installation)
- [Utilisation](#-utilisation)
- [Contrôles](#-contrôles)
- [Format de la carte (.cub)](#-format-de-la-carte-cub)
- [Structure du projet](#-structure-du-projet)
- [Commandes Makefile](#-commandes-makefile)
- [Auteurs](#-auteurs)

## 🎮 Aperçu

cub3D affiche une vue en première personne d'un labyrinthe défini dans un fichier de configuration `.cub`. Le rendu repose sur un algorithme de raycasting qui projette des rayons depuis la position du joueur pour calculer la distance aux murs et déterminer la hauteur des murs affichés à l'écran, donnant l'illusion d'un environnement 3D.

## ✨ Fonctionnalités

- Rendu en temps réel par raycasting
- Textures différentes selon l'orientation des murs (nord, sud, est, ouest)
- Couleurs personnalisables pour le sol et le plafond
- Déplacement et rotation fluides du joueur
- Parsing et validation complète des fichiers de carte `.cub`
- Vérification de la fermeture de la carte (flood fill)
- Gestion propre de la fermeture du programme (libération mémoire, fermeture de la fenêtre)

## 🔧 Prérequis

Le projet a été développé et testé sous **Linux**. Les dépendances suivantes sont nécessaires :

- Un compilateur C (`cc` / `gcc`)
- `make`
- `git` (pour cloner MiniLibX automatiquement)
- Les librairies de développement X11 :

```bash
sudo apt-get update
sudo apt-get install libxext-dev libx11-dev libbsd-dev
```

> MiniLibX est cloné et compilé automatiquement par le Makefile, vous n'avez rien à faire manuellement.

## 📦 Installation

Clonez le dépôt puis compilez le projet :

```bash
git clone <url-de-votre-repo> cub3D
cd cub3D
make
```

Le Makefile va automatiquement :
1. Cloner MiniLibX si elle n'est pas déjà présente
2. Compiler MiniLibX
3. Compiler libft
4. Compiler le projet et générer l'exécutable `cub3D`

## 🚀 Utilisation

Lancez le programme en lui passant un fichier de carte `.cub` en argument :

```bash
./cub3D assets/maps/map.cub
```

Si le fichier est invalide (carte non fermée, textures manquantes, caractères incorrects, etc.), un message d'erreur explicite sera affiché dans le terminal.

## 🕹️ Contrôles

| Touche | Action |
|---|---|
| `W` | Avancer |
| `S` | Reculer |
| `A` | Se déplacer à gauche (strafe) |
| `D` | Se déplacer à droite (strafe) |
| `←` (flèche gauche) | Tourner la caméra à gauche |
| `→` (flèche droite) | Tourner la caméra à droite |
| `ESC` | Quitter le programme |
| Bouton fermeture fenêtre | Quitter le programme |

## 🗺️ Format de la carte (.cub)

Un fichier `.cub` doit contenir, dans n'importe quel ordre avant la carte :

```
NO ./assets/textures/north.xpm
SO ./assets/textures/south.xpm
WE ./assets/textures/west.xpm
EA ./assets/textures/east.xpm
F 220,100,0
C 225,30,0
```

- `NO`, `SO`, `WE`, `EA` : chemins vers les textures des murs (nord, sud, ouest, est)
- `F` : couleur du sol (floor) au format R,G,B
- `C` : couleur du plafond (ceiling) au format R,G,B

Puis la carte elle-même, composée de :
- `1` : mur
- `0` : espace vide
- `N`, `S`, `E`, `W` : position et orientation de départ du joueur
- ` ` (espace) : autorisé uniquement à l'intérieur de la carte (pas en bordure si la carte n'est pas fermée par des murs)

**Exemple complet :**

```
NO ./assets/textures/north.xpm
SO ./assets/textures/south.xpm
WE ./assets/textures/west.xpm
EA ./assets/textures/east.xpm
F 220,100,0
C 225,30,0

111111
100001
1001N1
100001
111111
```

> ⚠️ La carte doit être entièrement fermée par des murs, sinon le programme refusera de se lancer.

## 📁 Structure du projet

```
.
├── Makefile
├── main.c
├── cub3d.h
├── assets/
│   ├── libs/
│   │   ├── gnl/              # get_next_line
│   │   ├── libft/            # librairie standard 42
│   │   └── minilibx-linux/   # MiniLibX (cloné automatiquement)
│   ├── maps/                 # fichiers .cub d'exemple
│   └── textures/             # fichiers .xpm
├── game/
│   ├── camera.c
│   ├── keys.c
│   ├── player.c
│   ├── raycasting.c
│   ├── raycasting_helper.c
│   ├── render.c
│   ├── textures.c
│   └── window.c
├── parsing/
│   ├── checker.c
│   ├── file_parsing.c
│   ├── flood_fill.c
│   ├── map_parsing.c
│   ├── parsing_utils.c
│   ├── parsing_utils2.c
│   └── storage.c
└── utils/
    ├── exit.c
    ├── free.c
    └── print_utils.c
```

## ⚙️ Commandes Makefile

| Commande | Description |
|---|---|
| `make` | Compile le projet (MiniLibX, libft, puis cub3D) |
| `make clean` | Supprime les fichiers objets |
| `make fclean` | Supprime les objets, l'exécutable, libft et MiniLibX |
| `make re` | Recompile entièrement le projet (fclean + all) |
| `make leak` | Compile puis lance le programme sous Valgrind pour détecter les fuites mémoire |

## 👥 Auteurs

Projet réalisé dans le cadre du cursus de l'école **42**.

- hmimouni
- pacda-si

---

N'hésitez pas à ouvrir une issue si vous rencontrez un problème de compilation ou d'exécution.

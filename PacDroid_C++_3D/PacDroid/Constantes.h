//constantes.h
#pragma once

// Chargement de l'application
/******************************/
#define LARGEUR_FENETRE_INIT 900
#define HAUTEUR_FENETER_INIT 400
#define EXTENSION ".xD"
#define NOM_APPLICATION "PacDroid"

// Etats du jeu
/***************/
#define START 1
#define PAUSE -1

// Directions
/*************/
#define HAUT 0
#define GAUCHE 90
#define BAS 180
#define DROITE 270

// Déplacement
/**************/
#define DIRECTION_INIT 270;
#define VITESSE 0.04f

// Constantes des display lists
/*******************************/
#define NB_DISPLAY_LIST (PACMAN_3D_LIST + 1 + NOMBRE_ANIMATION_PACMAN_3D)
// Décalages des display lists par rapport à la première générée via glGenList(...)
#define SURFACE_SOL_LIST 0
#define FANTOME_3D_LIST 1
#define FANTOME_2D_LIST 2
#define PASTILLE_3D_LIST 3
#define PASTILLE_2D_LIST 4
#define SUPER_PASTILLE_3D_LIST 5
#define SUPER_PASTILLE_2D_LIST 6
#define MUR_HAUT_3D_LIST 7
#define MUR_HAUT_2D_LIST 8
#define VIE_PACMAN 9
#define PACMAN_3D_LIST 10

// Paramètres du pacman
/***********************/
#define NB_VIES_DEBUT 3
// Fixe la taille de l'angle de la bouche de Pacman
#define ANGLE_BOUCHE 90 
// Temps de raffraichissement pour la bouche de pacman
#define TEMPS_BASE_BOUCHE 0.5f 
// Nombre de modèles de pacman 3D utilisés pour l'animation
#define NOMBRE_ANIMATION_PACMAN_3D 4
// Durée du mode super Pacman
#define DUREE_SUPER_PAC 10
#define VITESSE_PERTE_SUPER_PAC 0.04f

// Constantes concernant le contenu des cases du labyrinthe
/***********************************************************/
#define NB_ENTITE_MAX_PAR_CASE 3
// Codes des entités contenues dans une case du labyrinthe
#define SUPER_PASTILLE 32
#define PASTILLE 16
#define MUR_GAUCHE_INV 8
#define MUR_HAUT_INV 4
#define MUR_GAUCHE 2
#define MUR_HAUT 1
// Constantes des pastilles
#define NB_SLICES_QUADRIQUES 36
#define RAYON_PASTILLE 1.0/30
#define RAYON_SUPER_PASTILLE 1.0/10
#define COULEUR_PASTILLE (Couleur(1, 1, 1))
#define COULEUR_SUPER_PASTILLE (Couleur(0, 0, 1))
// Constantes des murs
#define COULEUR_MUR (Couleur(0.1, 0.1, 0.7))
#define COULEUR_MUR_INV (Couleur(0.2, 0.2, 0.4))
#define EPAISSEUR_MUR 0.06 
// Constante du sol
#define COULEUR_SOL (Couleur(0.1, 0.1, 0.3))

// Constantes concernant les niveaux du labyrinthe
/**************************************************/
#define NIVEAU_GAME_OVER 7

// Constantes de gestion du panel des boutons
/*********************************************/
#define NB_BOUTON 17
#define NB_LIGNE_BOUTON 7.0

// Paramètres du buffer pour le repérage du centre du labyrinthe
/****************************************************************/
#define TAILLE_SELECTION 64

// Constantes de paramétrage de la caméra
/*****************************************/
#define PAS_ZOOM_PARALLELE 1
#define MIN_ZOOM_PARALLELE 0
#define MAX_ZOOM_PARALLELE 10
#define PAS_ZOOM_PERSPECTIVE 5
#define MIN_ZOOM_PERSPECTIVE 45
#define MAX_ZOOM_PERSPECTIVE 90

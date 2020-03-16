/* ---------------------------
Laboratoire : 02
Fichier     : main.cpp
Auteur(s)   : Vallon Axel, Oliveira da Costa Dany, Allemano Enzo
Date        : 16.03.2020

But         : Ce programme permet de trouver toutes les solutions du puzzle
              décrit sur la page suivante : 
              https://asd1-heigvd.github.io/ASD1-Labs/puzzle/

Remarques   : Il est possible d'exploiter ce programme qui effectue des permutations
              afin de résoudre d'autres puzzles. Seulement, il faudra effectuer les 
              opérations suivantes:
                1) Dans le fichier d'entête, il faudra adapter les nouvelle figures 
                   de chaque pièces, et modifier le vecteur constant PIECES afin 
                   que chaque pièce du puzzle à résoudre soient disponibles. Il 
                   faudra aussi que ces pièces aient tous des côtés différents.
                2) Deuxièmement, il faudra modifier les valeurs des constantes dans
                   scruct parametres afin de connaitres les dimensions du puzzle. Il 
                   faut que le nombre de pièce du puzzle soit le même que la 
                   constante NB_PIECES.
   
--------------------------- */

#include "pieces.h"
#include <iostream>
#include <algorithm>

using namespace std;

//côtés d'une pièce
enum Position {
   HAUT, DROITE, BAS, GAUCHE
};

struct parametres {
   static const unsigned HAUTEUR_PUZZLE = 3;
   static const unsigned LARGEUR_PUZZLE = 3;   
   static const unsigned NB_PIECES = HAUTEUR_PUZZLE * LARGEUR_PUZZLE;
   static const unsigned NB_COTES_PAR_PIECE = 4;
};

/**
 * Fonction "maitre" appelant la fonction récursive "esclave" permettant de
 * résoudre le puzzle.
 * @param puzzle Puzzle à résoudre.
 */
void resoudrePuzzle(Pieces& puzzle);

/**
 * Surcharge de l'opérateur de flux permettant l'affichage des pièces des puzzles
 * une après les autres séparé par un espace. L'affichage d'un puzzle fonctionne en 
 * le comparant avec vecteur PIECES et affiche la position et la rotation des pièces 
 * par rapport à leur situation initiale.
 * @param lhs flux de sortie
 * @param rhs Pièces du puzzle à afficher.
 * @return le flux de sortie
 */
ostream& operator<<(ostream& lhs, const Pieces& rhs);

/**
 * Fonction résursive appelée par la fonction maitre pour résoudre le puzzle
 * @param puzzle puzzle à résoudre
 * @param niveau niveau de résolution du puzzle, de NB_PIECE à 1. Si 0, le puzzle est
 * résolu
 */
void resoudrePuzzleRecur(Pieces& puzzle, unsigned niveau);

/**
 * Compare si deux figure de pièces sont compatibles.
 * @param figure1 première figure à tester.
 * @param figure2 deuxième figure à tester.
 * @return la compabilité de deux figures de pièces.
 */
bool fit(AttachementType figure1, AttachementType figure2);

int main() {
   Pieces puzzle(PIECES);
   resoudrePuzzle(puzzle);
   system("PAUSE");
   return EXIT_SUCCESS;
}

ostream& operator<<(ostream& lhs, const Pieces& rhs) {
   string sortie;
   for (unsigned i = 0; i < rhs.size(); i++) {
      if (i)
         sortie += " ";
      for (unsigned j = 0; j < PIECES.size(); j++) {
         Piece tmp = PIECES[j];
         for (char k = 'a'; k <= 'a' + (int)parametres::NB_COTES_PAR_PIECE; ++k) {
            if (rhs[i] == tmp) {
               sortie += to_string(j + 1) + k;
               break;
            } else {
               rotate(tmp.begin(), tmp.begin() + 1, tmp.end());
            }
         }
      }
   }
   return lhs << sortie;
}

//effectue chaque appel récursif possible à partir de l'emplacement situé en bas à
//droite, avec toute les permutations et rotations possible pour cet emplacement.
void resoudrePuzzle(Pieces& puzzle) {
   const unsigned PROCHAIN_NIVEAU = parametres::NB_PIECES - 1;
   for (Piece& piece : puzzle) {
      resoudrePuzzleRecur(puzzle, PROCHAIN_NIVEAU);
      for (unsigned j = 0; j < parametres::NB_COTES_PAR_PIECE - 1; j++) {
         rotate(puzzle.back().begin(), puzzle.back().begin() + 1, 
                 puzzle.back().end());
         resoudrePuzzleRecur(puzzle, PROCHAIN_NIVEAU);
      }
      swap(piece, puzzle[PROCHAIN_NIVEAU]);
   }
}

//fonction récursive qui pour chacune des pièces disponibles restantes analyse si une
//pièce est compatible à l'emplacement ciblé et si oui, permutte la pièce, et 
//effectue un appel récursif plus bas. Si aucune pièce est compatible, cela quitte 
//la fonction.
void resoudrePuzzleRecur(Pieces& puzzle, unsigned niveau) {
   if (niveau && niveau < parametres::NB_PIECES) {
      bool pieceOK;
      for (unsigned i = 0; i < niveau; i++) {
         pieceOK = false;
         
         //cas où la pièce doit être compatible avec la pièce du bas et la pièce de 
         //droite.
         if (niveau % parametres::LARGEUR_PUZZLE && niveau <=
         parametres::NB_PIECES - parametres::HAUTEUR_PUZZLE) {
            
            for (unsigned j = 0; j < parametres::NB_COTES_PAR_PIECE; j++) {
               
               if (fit(puzzle[i][(DROITE + j) % parametres::NB_COTES_PAR_PIECE],
                       puzzle[niveau][GAUCHE]) && 
                       fit(puzzle[i][(BAS + j) % parametres::NB_COTES_PAR_PIECE], 
                       puzzle[niveau + parametres::LARGEUR_PUZZLE - 1][HAUT])) {
                  
                  if (j)
                     rotate(puzzle[i].begin(), puzzle[i].begin() + j, 
                             puzzle[i].end());
                  pieceOK = true;
                  break;
               }
            }
         //cas où la pièce doit être compatible avec la pièce de droite seulement.
         } else if (niveau % parametres::LARGEUR_PUZZLE) {
            
            for (unsigned j = 0; j < parametres::NB_COTES_PAR_PIECE; j++) {
               
               if (fit(puzzle[i][(DROITE + j) % parametres::NB_COTES_PAR_PIECE], 
                       puzzle[niveau][GAUCHE])) {
                  if (j)
                     rotate(puzzle[i].begin(), puzzle[i].begin() + j,
                          puzzle[i].end());
                  pieceOK = true;
                  break;
               }
            }
          //cas où la pièce doit être compatible avec la pièce du bas seulement.
         } else {
            for (unsigned j = 0; j < parametres::NB_COTES_PAR_PIECE; j++) {
               if (fit(puzzle[i][(BAS + j) % parametres::NB_COTES_PAR_PIECE], 
                       puzzle[niveau + parametres::LARGEUR_PUZZLE - 1][HAUT])) {
                  if (j)
                     rotate(puzzle[i].begin(), puzzle[i].begin() + j,
                          puzzle[i].end());
                  pieceOK = true;
                  break;
               }
            }
         }
         if (pieceOK) {
            swap(puzzle[i], puzzle[niveau - 1]);
            resoudrePuzzleRecur(puzzle, niveau - 1);
            swap(puzzle[i], puzzle[niveau - 1]);
         }
      }
   } else if (niveau == 0)
      cout << puzzle << endl;
}

bool fit(AttachementType figure1, AttachementType figure2) {
   switch (figure1) {
      case FILLE_HAUT: return figure2 == FILLE_BAS;
      case FILLE_BAS: return figure2 == FILLE_HAUT;
      case DAME_HAUT: return figure2 == DAME_BAS;
      case DAME_BAS: return figure2 == DAME_HAUT;
      case ARROSOIR_GAUCHE: return figure2 == ARROSOIR_DROIT;
      case ARROSOIR_DROIT: return figure2 == ARROSOIR_GAUCHE;
      case GATEAU_GAUCHE: return figure2 == GATEAU_DROIT;
      case GATEAU_DROIT: return figure2 == GATEAU_GAUCHE;
      case ARROSOIR_INVERSE: return false;
      case NONE: return false;
   }
   return false;
}
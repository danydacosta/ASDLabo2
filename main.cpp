/* ---------------------------
Laboratoire : 02
Fichier     : main.cpp
Auteur(s)   : Valon Axel, Oliveira da Costa Dany, Allemano Enzo
Date        : 16.03.2020

But         : Ce programme permet de trouver toutes les solutions du puzzle
 décrit sur la page suivante : https://asd1-heigvd.github.io/ASD1-Labs/puzzle/

Remarque(s) :
--------------------------- */

#include "pieces.h"
#include <iostream>
#include <algorithm>

using namespace std;

enum Position {
   HAUT, DROITE, BAS, GAUCHE
};

struct parametres {
   static const unsigned TAILLE_PUZZLE = 3;
   static const unsigned NB_PIECES = TAILLE_PUZZLE * TAILLE_PUZZLE;
   static const unsigned NB_COTES_PAR_PIECE = 4;
};

/**
 * Fonction "maitre" appelant la fonction récursive "esclave" permettant de
 * résoudre le puzzle
 */
void resoudrePuzzle(Pieces& puzzle);

/**
 * Surcharge de l'opérateur de flux permettant l'affichage des pièces des puzzles
 * une après les autres séparé par un espace
 */
ostream& operator<<(ostream& lhs, const Pieces& rhs);

/**
 * Fonction "esclave" réscursive
 */
void resoudrePuzzleRecur(Pieces& puzzle, unsigned niveau);

/**
 * Retourne si oui ou non deux figures sont compatibles (voir critères de
 * compatibilité dans la donnée du labo
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
         for (char k = 'a'; k <= 'a' + parametres::NB_COTES_PAR_PIECE; ++k) {
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

void resoudrePuzzle(Pieces& puzzle) {
   const unsigned PROCHAIN_NIVEAU = puzzle.size() - 1;
   const unsigned NB_ROTATION = 3; 
   for (Piece& piece : puzzle) {
      resoudrePuzzleRecur(puzzle, PROCHAIN_NIVEAU);
      for (unsigned j = 0; j < NB_ROTATION; j++) {
         rotate(puzzle.back().begin(), puzzle.back().begin() + 1, 
                 puzzle.back().end());
         resoudrePuzzleRecur(puzzle, PROCHAIN_NIVEAU);
      }
      swap(piece, puzzle[PROCHAIN_NIVEAU]);
   }
}

void resoudrePuzzleRecur(Pieces& puzzle, unsigned niveau) {
   if (niveau && niveau < parametres::NB_PIECES) {
      bool pieceOK;
      for (unsigned i = 0; i < niveau; i++) {
         pieceOK = false;
         if (niveau % parametres::TAILLE_PUZZLE && niveau <=
         parametres::NB_PIECES - parametres::TAILLE_PUZZLE) {
            for (unsigned j = 0; j < parametres::NB_COTES_PAR_PIECE; j++) {
               if (fit(puzzle[i][(DROITE + j) % parametres::NB_COTES_PAR_PIECE], puzzle[niveau][GAUCHE]) &&
                       fit(puzzle[i][(BAS + j) % parametres::NB_COTES_PAR_PIECE], puzzle[niveau + 2][HAUT])) {
                  if (j)
                     rotate(puzzle[i].begin(), puzzle[i].begin() + j, 
                             puzzle[i].end());
                  pieceOK = true;
                  break;
               }
            }

         } else if (niveau % parametres::TAILLE_PUZZLE) {
            for (unsigned j = 0; j < parametres::NB_COTES_PAR_PIECE; j++) {
               if (fit(puzzle[i][(DROITE + j) % parametres::NB_COTES_PAR_PIECE], puzzle[niveau][GAUCHE])) {
                  if (j)
                     rotate(puzzle[i].begin(), puzzle[i].begin() + j,
                          puzzle[i].end());
                  pieceOK = true;
                  break;
               }
            }
         } else {
            for (unsigned j = 0; j < parametres::NB_COTES_PAR_PIECE; j++) {
               if (fit(puzzle[i][(BAS + j) % parametres::NB_COTES_PAR_PIECE], puzzle[niveau + 2][HAUT])) {
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
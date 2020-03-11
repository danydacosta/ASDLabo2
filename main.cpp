#include "pieces.h"
#include <iostream>
#include <algorithm>

using namespace std;

enum Position {
   HAUT, DROITE, BAS, GAUCHE
};

// TODO: Le prof m'a montré ça mais je ne sais pas l'utiliser, qui peut regarder ?
/*struct parametres {
   int largeur = 3;
   int hauteur = 3;
   int nombreDePiece = largeur * hauteur;
   int nbCoteParPiece = 4;
};*/

void resoudrePuzzle(Pieces& puzzle);

ostream& operator<<(ostream& lhs, const Pieces& rhs);

void resoudrePuzzleRecur(Pieces& puzzle, size_t niveau);

bool fit(AttachementType figure1, AttachementType figure2);

int main() {
   Pieces puzzle(PIECES);
   resoudrePuzzle(puzzle);
   system("PAUSE");
   return EXIT_SUCCESS;
}

ostream& operator<<(ostream& lhs, const Pieces& rhs) {
   string sortie;
   for (size_t i = 0; i < rhs.size(); i++) {
      if (i)
         sortie += " ";
      for (size_t j = 0; j < PIECES.size(); j++) {
         Piece tmp = PIECES[j];
         for (char k = 'a'; k <= 'd'; ++k) {
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
   const size_t prochainNiveau = puzzle.size() - 1;
   const unsigned NB_ROTATION = 3; 
   for (Piece& piece : puzzle) {
      resoudrePuzzleRecur(puzzle, prochainNiveau);
      for (unsigned j = 0; j < NB_ROTATION; j++) {
         rotate(puzzle.back().begin(), puzzle.back().begin() + 1, 
                 puzzle.back().end());
         resoudrePuzzleRecur(puzzle, prochainNiveau);
      }
      swap(piece, puzzle[prochainNiveau]);
   }
}

void resoudrePuzzleRecur(Pieces& puzzle, size_t niveau) {
   if (niveau && niveau < 9) {
      bool pieceOK;
      for (size_t i = 0; i < niveau; i++) {
         pieceOK = false;
         if (niveau % 3 && niveau <= 6) {
            for (unsigned j = 0; j < 4; j++) {
               if (fit(puzzle[i][(DROITE + j) % 4], puzzle[niveau][GAUCHE]) &&
                       fit(puzzle[i][(BAS + j) % 4], puzzle[niveau + 2][HAUT])) {
                  if (j)
                     rotate(puzzle[i].begin(), puzzle[i].begin() + j, 
                             puzzle[i].end());
                  pieceOK = true;
                  break;
               }
            }

         } else if (niveau % 3) {
            for (unsigned j = 0; j < 4; j++) {
               if (fit(puzzle[i][(DROITE + j) % 4], puzzle[niveau][GAUCHE])) {
                  if (j)
                     rotate(puzzle[i].begin(), puzzle[i].begin() + j,
                          puzzle[i].end());
                  pieceOK = true;
                  break;
               }
            }
         } else {
            for (unsigned j = 0; j < 4; j++) {
               if (fit(puzzle[i][(BAS + j) % 4], puzzle[niveau + 2][HAUT])) {
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
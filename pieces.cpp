//
//  pieces.cpp
//  Puzzle récursif
//
//  Created by Olivier Cuisenaire on 06.11.18.
//  Copyright © 2018 Olivier Cuisenaire. All rights reserved.
//

#include <vector>
#include <algorithm>

#include "pieces.h"

using namespace std;

const Pieces PIECES = {
   { DAME_HAUT, GATEAU_DROIT, ARROSOIR_GAUCHE, FILLE_HAUT}, //0
   { DAME_BAS, ARROSOIR_GAUCHE, FILLE_HAUT, GATEAU_DROIT}, //1
   { FILLE_BAS, GATEAU_GAUCHE, DAME_HAUT, ARROSOIR_DROIT}, //2
   { ARROSOIR_DROIT, GATEAU_GAUCHE, DAME_HAUT, FILLE_HAUT}, //3
   { FILLE_BAS, DAME_HAUT, ARROSOIR_DROIT, GATEAU_DROIT}, //4
   { DAME_BAS, GATEAU_GAUCHE, FILLE_HAUT, ARROSOIR_DROIT}, //5
   { FILLE_BAS, ARROSOIR_GAUCHE, DAME_HAUT, GATEAU_DROIT}, //6
   { DAME_BAS, ARROSOIR_GAUCHE, GATEAU_DROIT, FILLE_HAUT}, //7
   { ARROSOIR_INVERSE, DAME_HAUT, GATEAU_DROIT, FILLE_BAS}, //8
};

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
   }
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

/*void rotation(Piece& piece){
   for (AttachementType& cote : piece){
      cote = AttachementType((cote + 1) % 4);
   }
}*/

void fRecur(Pieces& pieces, size_t niveau) {
   if (niveau > 1 && niveau < 9) {
      for (size_t i = 0; i < niveau; i++) {
         if (niveau % 3 && niveau <= 6) {
            for (unsigned j = 0; j < 4; j++) {
               if (fit(pieces[i][(DROITE + j) % 4], pieces[niveau][GAUCHE]) &&
                       fit(pieces[i][(BAS + j) % 4], pieces[niveau + 2][HAUT])) {
                  if (j)
                     rotate(pieces[i].begin(), pieces[i].begin() + j, pieces[i].end());
                  swap(pieces[i], pieces[niveau - 1]);
                  fRecur(pieces, niveau - 1);
                  swap(pieces[i], pieces[niveau - 1]);
                  break;
               }
            }

         } else if (niveau % 3) {
            for (unsigned j = 0; j < 4; j++) {
               if (fit(pieces[i][(DROITE + j) % 4], pieces[niveau][GAUCHE])) {
                  if (j)
                     rotate(pieces[i].begin(), pieces[i].begin() + j,
                          pieces[i].end());
                  swap(pieces[i], pieces[niveau - 1]);
                  fRecur(pieces, niveau - 1);
                  swap(pieces[i], pieces[niveau - 1]);
                  break;
               }
            }
         } else if (niveau <= 6) {
            for (unsigned j = 0; j < 4; j++) {
               if (fit(pieces[i][(BAS + j) % 4], pieces[niveau + 2][HAUT])) {
                  if (j)
                     rotate(pieces[i].begin(), pieces[i].begin() + j,
                          pieces[i].end());
                  swap(pieces[i], pieces[niveau - 1]);
                  fRecur(pieces, niveau - 1);
                  swap(pieces[i], pieces[niveau - 1]);
                  break;
               }
            }
         }
      }
   } else if (niveau == 1) {
      //la dernière pièce doit être compatible 
      for (unsigned i = 0; i < 4; i++) {
         if (fit(pieces[niveau - 1][(DROITE + i) % 4], pieces[niveau][GAUCHE]) &&
                 fit(pieces[niveau - 1][(BAS + i) % 4], pieces[niveau + 2][HAUT])) {
            //une solution du puzzle
            if (i)
               rotate(pieces[niveau - 1].begin(), pieces[niveau - 1].begin() + i,
                    pieces[niveau - 1].end());
            cout << pieces << endl;
            break;
         }
      }
   } else {
      for (unsigned i = 0; i < 9; i++) {
         fRecur(pieces, niveau - 1);
         for (int j = 0; j < 3; j++) {
            rotate(pieces[niveau - 1].begin(), pieces[niveau - 1].begin() + 1,
                    pieces[niveau - 1].end());
            fRecur(pieces, niveau - 1);
         }
         swap(pieces[i], pieces[niveau - 1]);
      }
   }
}
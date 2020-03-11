//
//  pieces.h
//  Puzzle récursif
//
//  Created by Olivier Cuisenaire on 06.11.18.
//  Copyright © 2018 Olivier Cuisenaire. All rights reserved.
//

#ifndef pieces_h
#define pieces_h

#include <array>
#include <vector>
#include <iostream>
//test 

enum AttachementType {
  FILLE_HAUT, FILLE_BAS, DAME_HAUT, DAME_BAS, ARROSOIR_GAUCHE, ARROSOIR_DROIT, 
  GATEAU_GAUCHE, GATEAU_DROIT,  ARROSOIR_INVERSE, NONE };
  
enum Position {
   HAUT, DROITE, BAS, GAUCHE
};

using Piece = std::array<AttachementType,4>;
using Pieces = std::vector<Piece>;

/**
 * Surchage de l'opérateur de flux sur les Pièces par rapport à l'ordre des pièces 
 * original.
 * @param lhs flux de sortie.
 * @param rhs les pièces à afficher.
 * @return Le flux de sortie
 */
std::ostream& operator<<(std::ostream& lhs, const Pieces& rhs);

/**
 * Affiche les solutions du puzzle
 * @param pieces Pieces du puzzle à résoudre
 * @param niveau Nombre de case du puzzle
 */
void fRecur(Pieces& pieces, size_t niveau);

/**
 * Test la compatibilité entre deux côtés de pièces différentes.
 * @param figure1 Figure de la première pièce.
 * @param figure2 Figure de la deuxième pièce.
 * @return La compatibilité entres les faces de deux pièces.
 */
bool fit(AttachementType figure1, AttachementType figure2);

extern const Pieces PIECES;

#endif /* pieces_h */

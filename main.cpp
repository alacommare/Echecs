/**
 * Programme test de Piece
 *
 * @file testPiece.cxx
 */

// Utile pour l'affichage
#include <iostream>
#include "Piece.h"
#include "Joueur.h"
#include "Echiquier.h"
#include "Partie.h"

// Pour utiliser les flux de iostream sans mettre "std::" tout le temps.
using namespace std;


bool compare(Piece &pa, Piece &pb)
{
  return ( (pa.x()== pb.x()) && (pa.y() == pb.y()) );
}



/**
 * Programme principal
 */
int main( int argc, char** argv )
{
    Partie p;
    p.jouerPartie();




/**
  //fb1.mouvementValide(e,9,7);   //faux
  e.enleverPiece(2,2);
  //fb1.mouvementValide(e,2,2);   //vrai

  e.enleverPiece(3,7);
  //cb1.mouvementValide(e,3,7);   //faux
  e.enleverPiece(4,2);
e.deplacer(&cb1, 4, 2);
  e.enleverPiece(5,3);
  e.enleverPiece(5,2);
  e.enleverPiece(1,2);
  e.enleverPiece(1,3);
e.deplacer(&pb1,1,4);


  e.affiche();

  //On a un pointeur sur une pièce et on veut un pointeur sur un roi
  Piece* ptr;
  ptr = &rb;
  Roi* rptr;
  //rptr=ptr impossible car pb de transtypage
  rptr=dynamic_cast<Roi*>(ptr);
  if (rptr==NULL)
    cout << "cast impossible" << endl;
  else
    cout << "cast reussi" << endl;

  // les objets definis dans cette fonction sont automatiquement détruits.
  // Ex : p1
  **/
}






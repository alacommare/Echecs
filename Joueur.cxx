#include <iostream>
#include "Joueur.h"

using namespace std;

Joueur::Joueur()
{
  cout << "Constructeur Joueur defaut" << endl;
}

Joueur::~Joueur()
{
  cout << "Destructeur Joueur" << endl;
}

Joueur::Joueur(bool white)
{
  int n = 0;
  int y = white ? 1 : 8;
  for ( int x = 1; x <= 8; ++x )
    m_pieces[ n++ ].init( x, y, white );
  y = white ? 2 : 7;
  for ( int x = 1; x <= 8; ++x )
    m_pieces[ n++ ].init( x, y, white );
  cout << "Constructeur Joueur specialise" << endl;
}

void 
Joueur::affiche()
{
  for (int i=0; i<16; i++)
    m_pieces[i].affiche();
}

/*
bool
Joueur::isWhite()
{
  return m_pieces[0].isWhite();
}
*/

bool
JoueurBlanc::isWhite()
{
  return true;
}

bool
JoueurNoir::isWhite()
{
  return false;
}

void
Joueur::placerPieces(Echiquier &e)
{
  for (int i=0; i<16; i++)
    e.placer(&(m_pieces[i])/*m_pieces+i*/);
}

JoueurBlanc::JoueurBlanc() : Joueur(true)
{
  cout << "Constructeur joueur blanc" << endl;
}

JoueurNoir::JoueurNoir() : Joueur(false)
{
  cout << "Constructeur joueur noir" << endl;
}

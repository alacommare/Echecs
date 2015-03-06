/**
 * Mise en oeuvre de Piece.h
 *
 * @file Piece.cxx
 */

// A besoin de la declaration de la classe
#include <iostream>
#include "Piece.h"
#include "Echiquier.h"
#include <cmath>

using namespace std;

Piece::Piece()
{
  cout << "Constructeur Piece defaut" << endl;
}

Piece::Piece(const Piece & autre)
{
  m_x = autre.m_x;
  m_y = autre.m_y;
  m_white = autre.m_white;
  cout << "Constructeur par copie" << endl;
}

Piece &
Piece::operator=(const Piece & autre)
{
  m_x = autre.m_x;
  m_y = autre.m_y;
  m_white = autre.m_white;
  cout << "Affectation Piece" << endl;
  return *this;
}

Piece::~Piece()
{
  cout << "Destructeur Piece" << endl;
}

Piece::Piece( int x, int y, bool white )
{
  m_x = x;
  m_y = y;
  m_white = white;
  cout << "Constructeur Piece specialise" << endl;
}

void
Piece::init( int x, int y, bool white )
{
  m_x = x;
  m_y = y;
  m_white = white;
}

void
Piece::move( int x, int y )
{
  m_x = x;
  m_y = y;
}

int
Piece::x()
{
  return m_x;
}

int
Piece::y()
{
  return m_y;
}

bool
Piece::isWhite()
{
  return m_white;
}


bool
Piece::isBlack()
{
  return !m_white;
}

void
Piece::affiche()
{
  cout << "Piece: x=" << m_x << " y=" << m_y << " "
       << ( m_white ? "blanche" : "noire" ) << endl;
}

bool
Piece::mouvementValide(Echiquier &e, int x, int y)
{
  cout << "mouvementValide Piece" << endl;
  return 0;
}

char
Piece::codePiece()
{
  return (m_white)? 'B' : 'N';
}

Roi::Roi(bool white)
{
  m_x = 5;
  m_y = white ? 1 : 8;
  m_white = white;
  cout << "Constructeur Roi" << endl;
}

bool
Roi::mouvementValide(Echiquier &e, int x, int y)
{
        bool estValide = false;

        if ((abs(x - m_x) <= 1) && (abs(y - m_y) <= 1))
        {
            //Vérifier si piece présente ou pas sur case d'arrivée
            if (e.getPiece(x,y) != NULL)
            {
                if (e.getPiece(x,y)->isWhite() != m_white)   //Si pièce couleur joueur adverse alors on l'enlève !
                {
                    e.enleverPiece(x,y);
                    cout << "Le mouvement du Roi est valide" << endl;
                    estValide = true;
                }
            }
            else
            {
                cout << "Le mouvement du Roi est valide" << endl;
                estValide = true;
            }
        }

    return estValide;
}

char
Roi::codePiece()
{
  return (m_white)? 'R' : 'r';
}

Reine::Reine(bool white) : Piece(4,white?1:8,white), Fou(white,true), Tour(white, true)
{

  cout << "Constructeur Reine" << endl;
}

bool
Reine::mouvementValide(Echiquier &e, int x, int y)
{
  bool mouvementOk = false;

  if (Tour::mouvementValide(e,x,y) || Fou::mouvementValide(e,x,y))
  {
      cout << "\nLe mouvement de la Reine est valide." << endl;
      mouvementOk = true;
  }

  return (mouvementOk);
}

char
Reine::codePiece()
{
  return (m_white)? 'Q' : 'q';
}

Fou::Fou(bool white, bool left) : Piece(left?3:6,white?1:8,white)
{
  cout << "Constructeur Fou" << endl;
}

bool
Fou::mouvementValide(Echiquier &e, int x, int y)
{
    int xDepart = this->x(); //Récupération du départ de la pièce
    int yDepart = this->y();
    bool estBlanche = this->isWhite();
    bool estValide = false;
    int ecartX = x - xDepart;
    int ecartY = y - yDepart;

    //vérifier si pièce sur chemin et vérifier si pièce sur case d'arrivée et sa couleur
    if (ecartX == ecartY || ecartX == -ecartY)   //pour aller en diagonale
    {
        if (ecartX > 0 && ecartY < 0)    //déplacement en haut à droite
        {
            while (xDepart != x && yDepart != y) //ET ou OU
            {
                yDepart++;
                yDepart--;

                if (e.getPiece(yDepart,yDepart) != NULL)
                {
                    if (xDepart == x && yDepart == y && e.getPiece(x,y)->isWhite() != estBlanche)   //Si pièce couleur joueur adverse alors on l'enlève !
                    {
                        e.enleverPiece(x,y);
                        cout << "Le mouvement du Fou est valide : déplacement Haut Droite" << endl;
                        estValide = true;
                    }
                }
                else
                {
                    if(xDepart == x && yDepart == y && estValide == false)
                    {
                        cout << "Le mouvement du Fou est valide : déplacement Haut Droite" << endl;
                        estValide = true;
                    }
                }
            }
        }
        else
        {
            if (ecartX < 0 && ecartY > 0)    //déplacement en bas à gauche
            {
                while (xDepart != x && yDepart != y) //ET ou OU
                {
                    xDepart--;
                    yDepart++;

                    if (e.getPiece(yDepart, yDepart) != NULL)
                    {
                        if (xDepart == x && yDepart == y && e.getPiece(x,y)->isWhite() != estBlanche)   //Si pièce couleur joueur adverse alors on l'enlève !
                        {
                            e.enleverPiece(x,y);
                            cout << "Le mouvement du Fou est valide : déplacement Bas Gauche" << endl;
                            estValide = true;
                        }
                    }
                    else
                    {
                        if(xDepart == x && yDepart == y && estValide == false)
                        {
                            cout << "Le mouvement du Fou est valide : déplacement Bas Gauche" << endl;
                            estValide = true;
                        }
                    }
                }
            }
            else
            {
                if(ecartX < 0 || ecartY < 0)    //déplacement haut gauche
                {
                    while (xDepart != x || yDepart != y) //ET ou OU
                    {
                        xDepart--;
                        yDepart--;

                        if (e.getPiece(xDepart, yDepart) != NULL)
                        {
                            if (xDepart == x && yDepart == y && e.getPiece(x,y)->isWhite() != estBlanche)   //Si pièce couleur joueur adverse alors on l'enlève !
                            {
                                e.enleverPiece(x,y);
                                cout << "Le mouvement du Fou est valide : déplacement Haut Gauche" << endl;
                                estValide = true;
                            }
                        }
                        else
                        {
                            if(xDepart == x && yDepart == y && estValide == false)
                            {
                                cout << "Le mouvement du Fou est valide : déplacement Haut Gauche" << endl;
                                estValide = true;
                            }
                        }
                    }
                }
                else            //déplacement bas droite
                {
                    while (ecartX != x && ecartY != y) //ET ou OU
                    {
                        xDepart++;
                        yDepart++;

                        if (e.getPiece(xDepart, yDepart) != NULL)
                        {
                            if (xDepart == x && yDepart == y && e.getPiece(x,y)->isWhite() != estBlanche)   //Si pièce couleur joueur adverse alors on l'enlève !
                            {
                                e.enleverPiece(x,y);
                                cout << "Le mouvement du Fou est valide : déplacement Bas Droite" << endl;
                                estValide = true;
                            }
                        }
                        else
                        {
                            if(xDepart == x && yDepart == y && estValide == false)
                            {
                                cout << "Le mouvement du Fou est valide : déplacement Bas Droite" << endl;
                                estValide = true;
                            }
                        }
                    }
                }
            }
        }
    }
  return estValide;
}

char
Fou::codePiece()
{
  return (m_white)? 'F' : 'f';
}

Tour::Tour(bool white, bool left) : Piece(left?1:8,white?1:8,white)
{

  cout << "Constructeur Tour" << endl;
}

bool
Tour::mouvementValide(Echiquier &e, int x, int y)
{
    bool estValide = false;
    int i = 0;  //pour indice de boucle

    //vérifier si pièce sur chemin et vérifier si pièce sur case d'arrivée et sa couleur
    if ((x == m_x && y>=1 && y <=8) || (y == m_y && x>=1 && x<=8))
    {
        if (m_x < x)    //déplacement vers droite
        {
            for (i = m_x; i <= x; i++)
            {
                if (e.getPiece(i,y) != NULL)
                {
                    if (i == x && e.getPiece(i,y)->isWhite() != m_white)   //Si pièce couleur joueur adverse alors on l'enlève !
                    {
                        e.enleverPiece(x,y);
                        cout << "Le mouvement de la Tour est valide : deplacement Droite" << endl;
                        estValide = true;
                    }
                }
                else
                {
                    if(i == x && estValide == false)
                    {
                        cout << "Le mouvement de la Tour est valide : deplacement Droite" << endl;
                        estValide = true;
                    }
                }
            }
        }
        else
        {
            if (m_x > x)    //déplacement vers gauche
            {
                for (i = m_x; i <= x; i--)
                {
                    if (e.getPiece(i,y) != NULL)
                    {
                        if (i == x && e.getPiece(i,y)->isWhite() != m_white)   //Si pièce couleur joueur adverse alors on l'enlève !
                        {
                            e.enleverPiece(x,y);
                            cout << "Le mouvement de la Tour est valide : deplacement Gauche" << endl;
                            estValide = true;
                        }
                    }
                    else
                    {
                        if(i == x && estValide == false)
                        {
                            cout << "Le mouvement de la Tour est valide : deplacement Gauche" << endl;
                            estValide = true;
                        }
                    }
                }
            }
            else
            {
                if(m_y < y)    //déplacement vers bas
                {
                    for (i = m_y; i <= y; i++)
                    {
                        if (e.getPiece(x,i) != NULL)
                        {
                            if (i == y && e.getPiece(x,i)->isWhite() != m_white)   //Si pièce couleur joueur adverse alors on l'enlève !
                            {
                                e.enleverPiece(x,y);
                                cout << "Le mouvement de la Tour est valide : deplacement Bas" << endl;
                                estValide = true;
                            }
                        }
                        else
                        {
                            if(i == y && estValide == false)
                            {
                                cout << "Le mouvement de la Tour est valide : deplacement Bas" << endl;
                                estValide = true;
                            }
                        }
                    }
                }
                else            //déplacement vers haut
                {
                    for (i = m_y; i <= y; i--)
                    {
                        if (e.getPiece(x,i) != NULL)
                        {
                            if (i == y && e.getPiece(x,i)->isWhite() != m_white)   //Si pièce couleur joueur adverse alors on l'enlève !
                            {
                                e.enleverPiece(x,y);
                                cout << "Le mouvement de la Tour est valide : deplacement Haut" << endl;
                                estValide = true;
                            }
                        }
                        else
                        {
                            if(i == y && estValide == false)
                            {
                                cout << "Le mouvement de la Tour est valide : deplacement Haut" << endl;
                                estValide = true;
                            }
                        }
                    }
                }
            }
        }
    }

  return estValide;
}

char
Tour::codePiece()
{
  return (m_white)? 'T' : 't';
}

Cavalier::Cavalier(bool white, bool left) : Piece(left?2:7,white?1:8,white)
{

  cout << "Constructeur Cavalier" << endl;
}

bool
Cavalier::mouvementValide(Echiquier &e, int x, int y)
{
    bool estValide = false;

    //Vérifier que la case d'arrivée est valide
    if ((abs(x-m_x) == 2 && abs(y-m_y) == 1) || (abs(x-m_x) == 1 && abs(y-m_y) == 2))
    {
        if (e.getPiece(x, y) != NULL)
        {
            if (e.getPiece(x, y)->isWhite() != m_white)
            {
                e.enleverPiece(x,y);
                cout << "Le mouvement du Cavalier est valide." << endl;
                estValide = true;
            }
        }
        else
        {
                cout << "Le mouvement du Cavalier est valide." << endl;
                estValide = true;
        }
    }

    return estValide;
}

char
Cavalier::codePiece()
{
  return (m_white)? 'C' : 'c';
}

Pion::Pion(int x, bool white) : Piece(x,white?2:7,white)
{
  cout << "Constructeur Pion" << endl;
}

bool
Pion::mouvementValide(Echiquier &e, int x, int y)
{
    bool estValide = false;

    if((m_y == 2 && m_white) || (m_y == 7 && !m_white))
    {
        //Le pion peut avancer de 1 ou 2 cases ou en diagonale si piece adverse
        if ((x == m_x && y == m_y+2 && m_white) || (x == m_x && y == m_y-2 && !m_white)) //cas avancer de 2 cases
        {
            if (m_white && e.getPiece(m_x, m_y+1) == NULL && e.getPiece(m_x, m_y+2) == NULL)
            {
                cout << "Le mouvement du Pion est valide." << endl;
                estValide = true;
            }
            else
            {
                if (!m_white && e.getPiece(m_x, m_y-1) == NULL && e.getPiece(m_x, m_y-2) == NULL)
                {
                    cout << "Le mouvement du Pion est valide." << endl;
                    estValide = true;
                }
            }
        }
        else
        {
            if ((x == m_x && y == m_y+1 && m_white) || (x == m_x && y == m_y-1 && !m_white))    //Cas avancer 1 case
            {
                if(e.getPiece(x,y) == NULL)
                {
                    cout << "Le mouvement du Pion est valide." << endl;
                    estValide = true;
                }
            }
            else
            {
                if((1 == abs(x-m_x) && y == m_y+1 && m_white) || (1 == abs(x-m_x) && y == m_y-1 && !m_white))
                {
                    if (e.getPiece(x,y) != NULL && e.getPiece(x, y)->isWhite() != m_white)
                    {
                        e.enleverPiece(x,y);
                        cout << "Le mouvement du Pion est valide." << endl;
                        estValide = true;
                    }
                }
            }
        }
    }
    else
    {
        if ((x == m_x && y == m_y+1 && m_white) || (x == m_x && y == m_y-1 && !m_white))
            {
                if(e.getPiece(x,y) == NULL)
                {
                    cout << "Le mouvement du Pion est valide." << endl;
                    estValide = true;
                }
            }
            else
            {
                if((1 == abs(x-m_x) && y == m_y+1 && m_white) || (1 == abs(x-m_x) && y == m_y-1 && !m_white))
                {
                    if (e.getPiece(x,y) != NULL && e.getPiece(x, y)->isWhite() != m_white)
                    {
                        e.enleverPiece(x,y);
                        cout << "Le mouvement du Pion est valide." << endl;
                        estValide = true;
                    }
                }
            }
    }

  return estValide;
}

char
Pion::codePiece()
{
  return (m_white)? 'P' : 'p';
}

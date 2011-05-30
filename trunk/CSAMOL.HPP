#ifndef _CSAMOL_HPP
  #define _CSAMOL_HPP


#include"clasdu.hpp"

struct pocis
{
 int xp,yp;
 int spx,spy;
 int licz_klat_p;
 int stan_p;
 int akt_klat_p;
 int czest,zeg;
 int dx,dy;
 pocis *nast, *pop;
};

class samol:public duszek

{
public:
    int tabl;
    samol();
    samol(int xa, int ya, int pr, int po, int cz);
   ~samol();
    pocis *p;
    void ruch();// ruch wroga
    void rys_p();
    void strzal();
    void przes_p();//przesun pocisk
    void wstaw();//do labiryntu
    void przesun(); // do labiryntu

};

#endif
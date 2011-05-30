  #include "paral.h"
  #include "clasdu.hpp"
  #include "csamol.hpp"

extern samol d1;
extern samol d2;
extern samol tor;
extern duszek pr;
////////////////////////////////////////////////////////////
void kon_pocis()
{
   pocis *h=d1.p,*d,*p1;
 if (d1.p==NULL) return;
  while (h->nast != NULL)
  {
   if( (h->xp>300) || ( h->yp<0) || ( h->yp>150 ))
     {
       d=h->pop;
       d->nast=h->nast;
       p1=h->nast;
       p1->pop=h->pop;
       if (h->pop==NULL) d1.p=h->nast;
       delete []h;
       h=p1->pop;

     }//kon if
     h=h->nast;
   }
   if( (h->xp>300) || ( h->yp<0) || ( h->yp>150 ))
     {
       if (h==d1.p) d1.p=NULL;// zle
	else
	 {
	   d=h->pop;
	   d->nast=NULL;
	 }
	 delete [] h;
     }

}
/////////////////////////////////////////////////
void kon_tor()
{
     pocis *h=tor.p,*d,*p1; //labirynt
   if (tor.p==NULL) return;
  while (h->nast != NULL)
  {
   if( h->xp<3)
     {
	     d=h->pop;
       d->nast=h->nast;
       p1=h->nast;
       p1->pop=h->pop;
       if (h->pop==NULL) tor.p=h->nast;
       delete []h;
       h=p1->pop;

     }//kon if
     h=h->nast;
   }
   if( h->xp<3)
     {
	if (h==tor.p) tor.p=NULL;// zle
	else
	 {
	   d=h->pop;
	   d->nast=NULL;
	 }
	 delete [] h;
     }
}

//////////////////////////////////////////////////////////////////////
void traf(samol &ob1, samol &ob2)// kolozaj pocisku z samolotem
{
 if ((ob1.p==NULL) || (ob2.stan== DEAD)) return;

  pocis *h=ob1.p,*d,*p1;

  while (h->nast != NULL)
  {
   if ((ob2.x < (h->xp+h->dx)) && ((ob2.x+20) > h->xp) &&
       (ob2.y < (h->yp+h->dy)) && ((ob2.y+20) > h->yp))
    {
       ob2.stan=DEAD;//zlikwidowanie samolotu
       d1.punkty+=15;//dodanie puktow

       d=h->pop;
       d->nast=h->nast;
       p1=h->nast;
       p1->pop=h->pop;
       if (h->pop==NULL) ob1.p=h->nast;
       delete []h;
       h=p1->pop;
    }//koniec if kolizji
   h=h->nast;
  }//koniec while

 if ((ob2.x < (h->xp+h->dx)) && ((ob2.x+20) > h->xp) &&
     (ob2.y < (h->yp+h->dy)) && ((ob2.y+20) > h->yp))

   {
     if (h==ob1.p) ob1.p=NULL;//
	else
	 {
	   d=h->pop;
	   d->nast=NULL;
	 }
	 delete [] h;
   }
}
//////////////////////////////////////////////////////////////////////
void punkty()
{
   if ((pr.x+5 < (d1.x+20)) && ((pr.x+10) > d1.x) &&
       (pr.y+5 < (d1.y+20)) && ((pr.y+10) > d1.y))
       {
	pr.stan=DEAD;
	pr.x=320;
	if (pr.akt_klat==0) d1.il_po+=10;
	if (pr.akt_klat==1) d1.il_en+=10;
	if (pr.akt_klat==2) d1.punkty+=15;
       }

}
///////////////////////////////////////////////////////////////
void kol(samol &ob1, samol &ob2)
{
   if ((ob2.x < (ob1.x+20)) && ((ob2.x+20) > ob1.x) &&
       (ob2.y < (ob1.y+20)) && ((ob2.y+20) > ob1.y))
       {
	ob1.il_en-=20;
	ob2.stan=DEAD;
       }

}

/////////////////////////////////////////////////////////////////
void premia()
{
  if (pr.x<0)
  {
   pr.x=300;
   pr.stan=DEAD;
  }
  if (pr.stan==DEAD)
    {
     pr.akt_klat=rand()%3;
     pr.y=rand()%130;
     pr.stan=LIVE;
    }
	pr.x--;
       if (pr.stan==LIVE)
       pr.rys();

}

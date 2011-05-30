
#include"csamol.hpp"
 int krzywa[3][30]={1,0,-1,
		    1,0,-1,
		    1,0,-1,
		   -1,1,0,
		   -1,1,0,
		   -1,-1,0,
		   -1,1,1,
		   -1,1,1,
		    0,1,1,
		    0,-1,0,
		    0,-1,-1,
		    0,1,1,
		    0,-1,-1,
		    0,1,0,
		    0,-1,0,
		    0,1,1,
		    0,0, -1,
		    1,0, 1,
		    1,0,0,
		    1,0,-1,
		    1,1,0,
		    1,1,0,
		   -1,1,1,
		   -1,-1,1,
		   -1,1,1 ,
		   -1,-1,1,
		    1,-1,-1,
		    1,-1,0,
		    1,-1,-1,
		    1,-1,1};


 int lab[55]={5,11,17,28,28,28,28,28,28,17,17,17,11,5,5,5,5,5,11,17,28,34,40,46,46,46,46,46,52,52,46,40,34,28,17,17,11,11,5,5,5};
 int w=0,q=0;
 int wa;
 extern  unsigned char far *MemBuf;

///////////////////////////////////////////////////////////////////////////
   samol::samol()
  {
	 x			=0;
	 y			=50;
	 x_old			=0;
	 y_old			=100;
	 wys			=WYS_DUSZKA;
	 szer           	=SZER_DUSZKA;
	 zeg_anim		=0;
	 pr_anim		=7;
	 zeg_por		=0;
	 pr_por			=3;
	 akt_klat		=0;
	 stan			=LIVE;
	 licz_klat		=0;
	 il_po			=20;
	 il_en			=50;
	 punkty			=0;
	 tlo_ptr		=NULL;
	 tlo_ptr		=new unsigned char far [WYS_DUSZKA*SZER_DUSZKA+1];//wys_duszka*szer_duszka+1
		for (int i=0; i<MAX_LICZBA_KLATEK; i++)
	 klatki[i]		=NULL;


	 p			=NULL;
	 p->akt_klat_p		=0;
	 p->stan_p		=LIVE;
	 p->licz_klat_p		=0;
	 p->zeg			=0;
	 p->czest		=2;

  }
  samol::samol(int xa,int ya,int pr, int po, int cz)
  {
	 p			=NULL;
	 p->akt_klat_p		=0;
	 p->stan_p		=LIVE;
	 p->licz_klat_p		=0;
	 p->czest		=cz;//czestotliwosc szczelania
	 x			=xa;
	 y			=ya;
	 x_old			=x;
	 y_old			=y;
	 wys			=WYS_DUSZKA;
	 szer           	=SZER_DUSZKA;
	 zeg_anim		=0;
	 pr_anim		=pr;//predkosc poruszania sie klatek
	 zeg_por		=0;
	 pr_por			=po;//predkosc poruszania
	 akt_klat		=0;
	 stan			=LIVE;
	 licz_klat		=0;
	 il_po			=20;
	 il_en			=50;
	 punkty			=0;
	 tlo_ptr		=NULL;
	 tlo_ptr		=new unsigned char far [WYS_DUSZKA*SZER_DUSZKA+1];//wys_duszka*szer_duszka+1
		for (int i=0; i<MAX_LICZBA_KLATEK; i++)
	 klatki[i]		=NULL;


  }

 samol::~samol()
 {
	  delete [] tlo_ptr;

	 for( int i=0; i<MAX_LICZBA_KLATEK; i++)
	    delete [] klatki[i];
	 pocis *d;
	 while (p)
	 {
	  d=p;
	  p=p->nast;
	  delete [] d;
	 }
}

//////////////////////////////////////////////////////////////////////////
void samol::rys_p()
{
     if (p==NULL) return;

	  char far * prac_duszka;
	  unsigned long work_offset, offset, a, b;
	  unsigned char data;
	  pocis *h=p;

   while (h->nast != NULL)
   {
	  work_offset=0;

	  prac_duszka =klatki[h->akt_klat_p];

	   offset = (h->yp<<8)+(h->yp<<6)+h->xp;
	   for (b=0; b<SZER_DUSZKA; b++)
	   {
	     for (a=0; a<WYS_DUSZKA; a++)
	      {
		 data=prac_duszka[work_offset+a];
		 if ( data )
			 MemBuf[offset+a]=data;
	      }

	     work_offset+=WYS_DUSZKA;
	     offset+=VIEW_WIDTH;

	   }

       h=h->nast;
   } //end while

       work_offset=0;
     {
	  prac_duszka =klatki[h->akt_klat_p];

	   offset = (h->yp<<8)+(h->yp<<6)+h->xp;
	   for (b=0; b<SZER_DUSZKA; b++)
	   {
	     for (a=0; a<WYS_DUSZKA; a++)
	      {
		 data=prac_duszka[work_offset+a];
		 if ( data )
			 MemBuf[offset+a]=data;
	      }

	     work_offset+=WYS_DUSZKA;
	     offset+=VIEW_WIDTH;

	   }
      }
 }

void samol::strzal()
 {

 if (il_po==0) return;
  il_po--;
  pocis *nowy = new pocis;

   if ((akt_klat==0) || (akt_klat==1))
   {
     nowy->dx=7;
     nowy->dy=4;
     nowy->xp=x+12;
     nowy->yp=y;
     nowy->spx=2;
     nowy->spy=0;
     nowy->akt_klat_p=6;
     nowy->nast=NULL; //ustawia na nowym elemencie adres nastepny NULL
   }
   if ((akt_klat==2) || (akt_klat==3))
   {
     nowy->dx=7;
     nowy->dy=7;
     nowy->xp=x+14;
     nowy->yp=y;
     nowy->spx=2;
     nowy->spy=2;
     nowy->akt_klat_p=7;
     nowy->nast=NULL; //ustawia na nowym elemencie adres nastepny NULL
   }
   if ((akt_klat==4) || (akt_klat==5))
   {
     nowy->dx=7;
     nowy->dy=7;
     nowy->xp=x+14;
     nowy->yp=y;
     nowy->spx=2;
     nowy->spy=-2;
     nowy->akt_klat_p=8;
     nowy->nast=NULL; //ustawia na nowym elemencie adres nastepny NULL
   }



   if (p == NULL)
    {
     nowy->pop=NULL;
     p=nowy;
    return;
    }

  pocis *tmp=p;
  while (tmp->nast!=NULL)//przesuwa do puki ostatni nie bedzie NULL
    tmp=tmp->nast;

     nowy->pop=tmp; //ustawia adres poprzedniego elementu
     tmp->nast=nowy;


 }

 void samol::przes_p()
{
  if (p==NULL) return;
  pocis *h=p;
 while (h->nast != NULL)
  {
      h->xp+=h->spx;
      h->yp+=h->spy;
      h=h->nast;
  }

      h->xp+=h->spx;
      h->yp+=h->spy;

}


void samol::wstaw()// wstawia element labiryntu
 {
      pocis *nowy = new pocis;

   nowy->xp=310;
   if (q>55)//ilosc elementow
    q=0;
   nowy->yp=lab[q++];
   nowy->akt_klat_p =0;
   nowy->nast=NULL;

   if (p == NULL)
    {
      nowy->pop=NULL;
      p=nowy;
      return;
    }

  pocis *tmp=p;
  while (tmp->nast!=NULL)//przesuwa do puki ostatni nie bedzie NULL
    tmp=tmp->nast;

     nowy->pop=tmp; //ustawia adres poprzedniego elementu
     tmp->nast=nowy;
 }

 void samol::przesun()
 {
  pocis *h=p;
  if (p==NULL) return;

  while (h->nast != NULL)
  {
    h->xp-=3;
    h=h->nast;
   }

   h->xp-=3;
 }

void samol::ruch()
{
 if (stan==DEAD) {return;}

  if (x==2) x=320;
  x--;
  y_old=y;

 if(w>29) w=0;

 if (++zeg_por>pr_por)
  {
    wa=krzywa[tabl][w++];
    zeg_por=0;
  }

   if (y>130) wa=-1;
     if (y<3) wa=1;
	y+=wa;

  if ( y_old == y)
     {
	if (++zeg_anim>pr_anim)
	  {
	    zeg_anim=0;
	    if (akt_klat!=0) akt_klat=0; else akt_klat=1;
	  }
      }

   if ( y_old<y)
    {
       if (++zeg_anim>pr_anim)
       {
	 zeg_anim=0;
	 if (akt_klat!=2) akt_klat=2; else akt_klat=3;
       }
     }

  if (y_old > y)
   {
      if (++zeg_anim>pr_anim)
	{
	   zeg_anim=0;
	   if (akt_klat!=4) akt_klat=4; else akt_klat=5;
	}
    }


}


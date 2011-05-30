    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <time.h>
    #include <dos.h>
    #include <math.h>
    #include "paral.h"
    #include "clasdu.hpp"
    #include "koliz.hpp"
    #include "csamol.hpp"



extern int frames;
extern int volatile KeyScan;
extern PcxFile pcx;
 extern  unsigned char far *MemBuf;
 extern unsigned char far* VideoRam;

PcxFile samo,pul;//definicja plikow 320x200
duszek pr; //premia

  samol d1,tor, d2(310,20,7,30,7);
     int b=0,kr=0;


void initdusz()// wczytywanie poszczegulnych klatek animacji
 {

    Load("samo.pcx",&samo);
    d1.zap_tabli(samo.pal);
    d1.czyt(samo.bitmap,0,0);
    d1.czyt(samo.bitmap,1,0);
    d1.czyt(samo.bitmap,2,0);
    d1.czyt(samo.bitmap,3,0);
    d1.czyt(samo.bitmap,4,0);
    d1.czyt(samo.bitmap,5,0);
    d1.czyt(samo.bitmap,0,2);
    d1.czyt(samo.bitmap,2,2);
    d1.czyt(samo.bitmap,1,2);
    d1.czyt(samo.bitmap,6,0);

    d2.czyt(samo.bitmap,0,1);
    d2.czyt(samo.bitmap,1,1);
    d2.czyt(samo.bitmap,2,1);
    d2.czyt(samo.bitmap,3,1);
    d2.czyt(samo.bitmap,4,1);
    d2.czyt(samo.bitmap,5,1);
    d2.czyt(samo.bitmap,6,1);

    pr.czyt(samo.bitmap,1,3);
    pr.czyt(samo.bitmap,2,3);
    pr.czyt(samo.bitmap,3,3);


    zamk(&samo);

 }

void sprawdz()
{
 kon_pocis();
 kon_tor();
 traf(d1,d2);// kolozaj ob1(pocisku) z ob2 samolotem
 punkty();// kolizja premi z samolotem
 kol(d1,d2);// kolizja dwuch samolotow
}

void punktacja()
 {
  int w,w1;

  if ((d1.il_po>0) && (d1.il_po<110))
  {
   w=(int)(d1.il_po/2);
  linia(10,10+50,165,BLACK);
  linia(10,10+50,166,BLACK);
  linia(10,10+50,167,BLACK);
  linia(10,10+w,165,WHITE);
  linia(10,10+w,166,WHITE);
  linia(10,10+w,167,WHITE);
  }

    if ((d1.il_en>0) && (d1.il_en<100))
  {
   w1=(int)(d1.il_en);
  linia(10,10+90,190,BLACK);
  linia(10,10+90,191,BLACK);
  linia(10,10+90,192,BLACK);
  linia(10,10+w1,190,WHITE);
  linia(10,10+w1,191,15);
  linia(10,10+w1,192,15);
  }

 }

void wrug()
 {
  if(d2.stan==DEAD)
   {
    d2.x=300;
    d2.y=rand()%130;
    d2.tabl=rand()%3;
    d2.stan=LIVE;
   }
 }

////////////////////////////////////////////////////////////////////////////
//
 int main()
   {
      InitVideo();// inicjacja trybu graficznego
      demo(); //czolowka
      Initialize(); //incjacja tla
      initdusz(); //incjacja wszystkich postaci
      Load("pulpit.pcx",&pul); //zaladowanie pulpitu
	rys(pul);
      zamk(&pul);

//////////////////////////////////////////////////////////////////////////
//////////////////////// petla glowna ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

      while((KeyScan != ESC_PRESSED) && (d1.il_en>3))
      {
	switch(KeyScan)
	{
	  case RIGHT_ARROW_PRESSED:
		d1.ruch_p();
		break;
	  case  DOWN_ARROW_PRESSED:
		d1.ruch_d();
		break;
	  case   UP_ARROW_PRESSED :
		d1.ruch_g();
		break;
	  case  LEFT_ARROW_PRESSED:
		if (++kr>6)
		 {
		   kr=0;
		   d1.strzal();
		  }
		 break;
	 default:
	       {
		 if (++d1.zeg_anim>d1.pr_anim)
		   {
		     d1.zeg_anim=0;
		     if (d1.akt_klat!=0) d1.akt_klat=0; else d1.akt_klat=1;
		    }
		 if (d1.x!=0)
		 d1.x--;
		}
	}// koniec swith

	sprawdz();//sprawdzanie wszystkich kolizji
	wrug();// inicjacja wroga
	AnimLoop(); //animacja tla
	punktacja();//wyswietlanie stanu punktow
	premia();//animacja premii

	d2.ruch();//ruch wroga wedlug wyznaczonej trasy
	d2.rys();// rysowanie wroga

	d1.rys();// rysowanie mnie
	d1.rys_p(); // rysowanie pociskow
	na_ekran(); // wyswietlanie wszystkiego na ekran
	d1.przes_p();// przesuniecie wszystkich pociskow


      }
     RestoreKeyboard();

      koniec();
      char pkt[6];
      sprintf(pkt,"%d",d1.punkty);
      GraphString(20,23,pkt,WHITE);
      GraphString(10,23,"ZDOBYLES  ",WHITE);
      GraphString(25,23," PUNKTOW ",WHITE);
      fflush(stdin);
      getch();
      getch();
      rozp();
      CleanUp();//
      printf("Dziekujemy za skorzystanie z naszej gry");
      return 0;
    }



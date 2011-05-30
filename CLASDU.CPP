#include"clasdu.hpp"

 extern unsigned char far* VideoRam;
 extern  unsigned char far *MemBuf;

   duszek::duszek()
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
	 il_en			=50;
	 il_po			=20;
	 punkty			=0;
	 tlo_ptr		=NULL;
	 tlo_ptr		=new unsigned char far [WYS_DUSZKA*SZER_DUSZKA+1];//wys_duszka*szer_duszka+1
		for (int i=0; i<MAX_LICZBA_KLATEK; i++)
	 klatki[i]		=NULL;

    }

    duszek::duszek(int xa, int ya, int z_anim, int p_anim, int z_por, int p_por)
    {
		x		=xa;
		y		=ya;
		x_old		=x;
		y_old		=y;
		wys		=WYS_DUSZKA;
		szer            =SZER_DUSZKA;
		zeg_anim	=z_anim;
		pr_anim		=p_anim;
		zeg_por		=z_por;
		pr_por		=p_por;
		akt_klat	=0;
		stan		=LIVE;
		licz_klat	=0;
		tlo_ptr		=NULL;
		tlo_ptr		=new unsigned char far [WYS_DUSZKA*SZER_DUSZKA+1];//wys_duszka*szer_duszka+1
	for (int i=0; i<MAX_LICZBA_KLATEK; i++)
		klatki[i]	=NULL;

    }
duszek::duszek(duszek &du)
   {
		x		=du.x;
		y		=du.y;
		x_old		=du.x_old;
		y_old		=du.y_old;
		wys		=du.wys;
		szer            =du.szer;
		zeg_anim	=du.zeg_anim;
		pr_anim		=du.pr_anim;
		zeg_por		=du.zeg_por;
		pr_por		=du.pr_por;
		akt_klat	=du.akt_klat;
		stan		=du.stan;
		licz_klat	=du.licz_klat;
		tlo_ptr		=du.tlo_ptr;
	for (int i=0; i<MAX_LICZBA_KLATEK; i++)
		klatki[i]	=du.klatki[i];
   }

duszek::~duszek()
      {
	  delete [] tlo_ptr;

	 for( int i=0; i<MAX_LICZBA_KLATEK; i++)
	    delete [] klatki[i];

      }
////////////////////////////////////////////////////////////////////////

void duszek::czyt(unsigned char far *bitmap, int grab_x, int grab_y)
  {

  unsigned long x_off,a,b,y_off;

   char far * duch_data;

    klatki[licz_klat]=NULL;
    klatki[licz_klat]= new char far [WYS_DUSZKA*SZER_DUSZKA];

    duch_data=klatki[licz_klat];

       x_off=25* grab_x+1;
       y_off=25* grab_y+1;

    y_off=(int)y_off*320;

    for ( b=0; b<SZER_DUSZKA; b++)
    {
     for ( a=0; a<WYS_DUSZKA; a++)
      {
	duch_data[24*b+a]= bitmap[y_off+x_off+a];
      }
      y_off+=320;
    }
    licz_klat++;

  }

void duszek::rys()
   {
       if ( stan== DEAD) { return; }

	  char far * prac_duszka;
	  unsigned long work_offset=0, offset, a, b;
	  unsigned char data;


	  prac_duszka = klatki[akt_klat];

	   offset = (y<<8)+(y<<6)+x;
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


void duszek::tlo()
  {

	  unsigned int tlo_offset=0, offset,ya;


	  offset = (y<<8)+(y<<6)+x;

	   for (ya=0; ya<SZER_DUSZKA; ya++)
	    {
	     _fmemcpy((unsigned char far *)tlo_ptr[tlo_offset], (unsigned char far* )VideoRam[offset],WYS_DUSZKA);
	   tlo_offset+=SZER_DUSZKA;
		    }

  }

void duszek::rys_tlo()
  {
      unsigned int tlo_offset=0, offset, ya;

	  offset =(y_old << 8) + (y_old<<6) +x_old;
	   for ( ya=0; ya<SZER_DUSZKA; ya++)
	    {
	      _fmemcpy((unsigned char far*) VideoRam[offset], (unsigned char far*) tlo_ptr[tlo_offset], WYS_DUSZKA);

	     offset +=VIEW_WIDTH;
	     tlo_offset+=WYS_DUSZKA;
	   }
  }

void duszek::scala_duszka(float scala)
 {
	  char far *prac_duszka;
	  int work_offset=0, offset, xa, ya;
	  unsigned char data;
	  float y_scala_index,x_scala_step,y_scala_step,x_scala_index;

      y_scala_index = 0;

    y_scala_step = SZER_DUSZKA/scala;
    x_scala_step = WYS_DUSZKA/scala;

  prac_duszka = klatki[akt_klat];

	 offset = (y<<8)+(y<<6)+x;
	 for (ya=0; ya<(int)(scala); ya++)
	   {
	    x_scala_index=0;
	     for(xa=0; xa<(int)(scala);xa++)
	      {
		if ((data=prac_duszka[work_offset+(int)x_scala_index]))
			VideoRam[offset+xa] = data;

			x_scala_index+=(x_scala_step);
	      }
	   y_scala_index+=y_scala_step;
	   offset +=VIEW_WIDTH;
   work_offset=WYS_DUSZKA*(int)(y_scala_index);
  }
}
void duszek::zap_tabli(char pale[3*256])
 {
   for (int i=0;i<(3*256);i++)
   pal[i]=pale[i];
 }

void duszek::tablica()
 {
      struct SREGS s;
      union REGS r;

      segread(&s);
      s.es=FP_SEG((void far*)pal);
      r.x.dx=FP_OFF((void far*)pal);
      r.x.ax=0x1012;
      r.x.bx=0;
      r.x.cx=256;
      int86x(0x10,&r,&r,&s);

  }

void duszek::ruch_p()
 {
  if (x<200)
  {  x_old=x; x++;}
  if (++zeg_anim>pr_anim)
  {
    zeg_anim=0;
    if (akt_klat!=0) akt_klat=0; else akt_klat=1;
  }
     dzwiek=32;
 }

 void duszek::ruch_d()
 {
   if (x<200)
   {
    if(y<130)
     {x_old=x; y_old=y; x++; y++; }

       if (++zeg_anim>pr_anim)
       {
	 zeg_anim=0;
	 if (akt_klat!=2) akt_klat=2; else akt_klat=3;
       }
       dzwiek=25;
    }
 }

 void duszek::ruch_g()
 {
   if (x<200)
  {
    if(y>1)
     {x_old=x; y_old=y; x++; y--; }
      if (++zeg_anim>pr_anim)
	{
	   zeg_anim=0;
	   if (akt_klat!=4) akt_klat=4; else akt_klat=5;
	}
      dzwiek=40;
  }
 }


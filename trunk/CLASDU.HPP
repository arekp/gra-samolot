#ifndef _CLASDU_HPP
  #define _CLASDU_HPP

#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mem.h>
#include <alloc.h>

 #define MAX_LICZBA_KLATEK 16
 #define MAX_LICZBA_POCISK 4
 #define DEAD  0
 #define LIVE  1
 #define WYS_DUSZKA 24
 #define SZER_DUSZKA 24

    #define VIEW_WIDTH    320
    #define VIEW_HEIGHT   150


  class duszek
 {
    public:

    int wys,szer ;
    int zeg_por;
    int pr_por;
    char far *klatki[MAX_LICZBA_KLATEK];
    int licz_klat;
    int stan;
    unsigned char far *tlo_ptr;
    char pal[768];
    int x,y;
    int akt_klat;
    int x_old,y_old;
    int zeg_anim;
    int pr_anim;
    int dzwiek;
    int il_en;
    int il_po;
    int punkty;


    duszek();
    duszek(int x, int y, int z_anim, int p_anim, int z_por, int p_por);
    duszek(duszek &du);
    ~duszek();

    void czyt(unsigned char far *bitmap, int grab_x, int grab_y);
    void rys();
    void tlo();
    void rys_tlo();
    void scala_duszka(float scala);
    void zap_tabli(char *pale);
    void tablica();
    void ruch_p();
    void ruch_g();
    void ruch_d();

 };


#endif

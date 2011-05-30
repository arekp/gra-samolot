    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <time.h>
    #include <dos.h>
    #include "paral.h"

  unsigned char far *MemBuf,            // wskaznik na bufor
	 *BackGroundBmp,     // wskaznik na  background bitmap data
	 *ForeGroundBmp,     // wskaznik na foreground bitmap data
	 *VideoRam;          // wskazni na ekran

    PcxFile pcx;             // otwieranie struktury PCX

    int volatile KeyScan;

    int frames=0,
	PrevMode;

    int background,
	foreground,
	position;

    void _interrupt (*OldInt9)(...);

/////////////////////////////////////////////////////////////////////////////
//  czytanie obrazka PCX w 256 kolorach
//////////////////////////////////////////////////////////////////
    int ReadPcxFile(char *filename,PcxFile *pcx)
    {
      long i;
      int mode=NORMAL,nbytes;
      char abyte,*p;
      FILE *f;

      f=fopen(filename,"rb");
      if(f==NULL)
	return PCX_NOFILE;
      fread(&pcx->hdr,sizeof(PcxHeader),1,f);
      pcx->width=1+pcx->hdr.xmax-pcx->hdr.xmin;
      pcx->height=1+pcx->hdr.ymax-pcx->hdr.ymin;
      pcx->imagebytes=(unsigned int)(pcx->width*pcx->height);
      if(pcx->imagebytes > PCX_MAX_SIZE)
	return PCX_TOOBIG;

      pcx->bitmap=(unsigned char*)malloc(pcx->imagebytes);
      if(pcx->bitmap == NULL)
	return PCX_NOMEM;

      p=pcx->bitmap;
      for(i=0;i<pcx->imagebytes;i++)
      {
	if(mode == NORMAL)
	{
	  abyte=fgetc(f);
	  if((unsigned char)abyte > 0xbf)
	  {
	    nbytes=abyte & 0x3f;
	    abyte=fgetc(f);
	    if(--nbytes > 0)
	      mode=RLE;
	  }
	}
	else if(--nbytes == 0)
	  mode=NORMAL;
	*p++=abyte;
      }

      fseek(f,-768L,SEEK_END);      // paleta
      fread(pcx->pal,768,1,f);
      p=pcx->pal;
      for(i=0;i<768;i++)
	*p++=*p >>2;
      fclose(f);
      return PCX_OK;
    }

/////////////////////////////////////////////////////////////////////////
//Nowe przerwanie klawiatury
    void _interrupt NewInt9(...)
    {
      register char x;

      KeyScan=inp(0x60);
      x=inp(0x61);
      outp(0x61,(x|0x80));
      outp(0x61,x);
      outp(0x20,0x20);
      if(KeyScan == RIGHT_ARROW_REL || KeyScan == LEFT_ARROW_REL || KeyScan==DOWN_ARROW_REL ||KeyScan == UP_ARROW_REL   )
	 KeyScan=0;
    }

//
///////////////////////////////////////////////////////////////////////////
//
    void RestoreKeyboard(void)
    {
      _dos_setvect(KEYBOARD,OldInt9);
    }


//////////////////////////////////////////////////////////////////////////
// inicjacja klawiatury
//
    void InitKeyboard(void)
    {
      OldInt9=_dos_getvect(KEYBOARD);
      _dos_setvect(KEYBOARD,NewInt9);
    }

////////////////////////////////////////////////////////////////////////////
// zapis palet kolorow
//
    void SetAllRgbPalette(char *pal)
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

///////////////////////////////////////////////////////////////////////////
// rozpoczecie trybu graficznego 13h
    void InitVideo()
    {
	union REGS regs;

	VideoRam = (unsigned char far *)MK_FP(0xA000, 0x0000);
	PrevMode = peekb(0x0040, 0x0049);

	regs.h.ah = 0x00;
	regs.h.al = 0x13;
	int86(0x10, &regs, &regs);
    }

//////////////////////////////////////////////////////////////////////
// Zamkniecie trybu 13h
    void RestoreVideo()
    {
      union REGS r;

      r.x.ax=PrevMode;
      int86(0x10,&r,&r);
    }

////////////////////////////////////////////////////////////////////////
//inicjacja bitmap
    int InitBitmaps()
    {
      int r;

      background=foreground=1;

      r=ReadPcxFile("foregrnd.pcx",&pcx);
      if(r != PCX_OK)
	return FALSE;
      ForeGroundBmp=pcx.bitmap;

      r=ReadPcxFile("backgrnd.pcx",&pcx);
      if(r != PCX_OK)
	return FALSE;
      BackGroundBmp=pcx.bitmap;
      SetAllRgbPalette(pcx.pal);



      MemBuf=(unsigned char*)malloc(MEMBLK);
      if(MemBuf == NULL)
	return FALSE;

      memset(MemBuf,0,MEMBLK);
      return TRUE;
    }

///////////////////////////////////////////////////////////////////////////
// zwalnianie pamieci
    void FreeMem()
    {
      free(MemBuf);
      free(BackGroundBmp);
      free(ForeGroundBmp);
    }

//////////////////////////////////////////////////////////////////////////
// rysowanie warstw
    void DrawLayers()
    {
      OpaqueBlt(BackGroundBmp,0,100,background);
      TransparentBlt(ForeGroundBmp,50,100,foreground);
    }

//////////////////////////////////////////////////////////////////////////
// funkcja animacji
    void AnimLoop()
    {
	  background-=1;
	  if(background < 1)
	    background+=VIEW_WIDTH;

	  foreground-=2;
	  if(foreground < 1)
	    foreground+=VIEW_WIDTH;

	DrawLayers();
  //	memcpy(VideoRam,MemBuf,MEMBLK);
	frames++;

    }

////////////////////////////////////////////////////////////////////////////
// inicjalizacja trybu graficznego, klawiatury, czytanie bitmap
    void Initialize()
    {
      position=0;
//      InitVideo();
      InitKeyboard();
      if(!InitBitmaps())
      {
	CleanUp();
	printf("\nniemozliwe odczytanie bitmapy\n");
	exit(1);
      }
    }

////////////////////////////////////////////////////////////////////////////
// czyszenie
    void CleanUp()
    {
      RestoreVideo();
//      RestoreKeyboard();
      FreeMem();
    }

///////////////////////////////////////////////////////////////////////////
 void na_ekran()
 {
	memcpy(VideoRam,MemBuf,MEMBLK);
 }

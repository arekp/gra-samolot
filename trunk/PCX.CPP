    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <time.h>
    #include <dos.h>
    #include <conio.h>
    #include "paral.h"

 extern unsigned char far* VideoRam;
PcxFile de;//definicja plikow 320x200

////////////////////////////////////////////////////////////////////////////
    int Load(char *filename,PcxFile *pcx)
    {
      long i;
      int mode=NORMAL,nbytes;
      char abyte;
      unsigned char far *p;
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


      pcx->bitmap= new unsigned char far [pcx->imagebytes];
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

      fseek(f,-768L,SEEK_END);
      fread(pcx->pal,768,1,f);
      p=pcx->pal;
      for(i=0;i<768;i++)
	*p++=*p >>2;
      fclose(f);
      return PCX_OK;
    }

//////////////////////////////////////////////////////////////////////////////

void rys(PcxFile &image)
{

   _fmemcpy((unsigned char far *)VideoRam, (unsigned char far *)image.bitmap, SCREEN_WIDTH*SCREEN_HEIGHT);

}
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////

void pixel(int x,int y, unsigned char color)
{
   VideoRam[((y<<8)+(y<<6))+x] = color;
}
////////////////////////////////////////////////////////////////////////////

void rozp()
{
 for (unsigned long index=0;index<=300000; index++,pixel(rand()%320,rand()%200,0));
}
//////////////////////////////////////////////////////////////////////////
void zamk(PcxFile *sam)
 {
  delete [] sam->bitmap;
 }
///////////////////////////////////////////////////////////////////////////
void linia(int x1, int x2,int y, unsigned int color)
{
_fmemset((void far*)(VideoRam+((y<<8)+(y<<6))+x1),color,x2-x1+1);
}

////////////////////////////////////////////////////
void Go2xy(int x,int y)
{
   union REGS regs;

   regs.h.ah = 0x02;
   regs.h.bh = 0;
   regs.h.dh = y;
   regs.h.dl = x;
   int86(0x10,&regs,&regs);
}
////////////////////////////////////////////////////////////////////
void GraphChar(unsigned char value, unsigned char color)
{
	union REGS regs;

	regs.h.ah = 0x0E;
	regs.h.al = value;
	regs.h.bh = 0;
	regs.h.bl = color;
	int86(0x10,&regs,&regs);
}
///////////////////////////////////////////////////////////////////
void GraphString(int x, int y, unsigned char *string, unsigned char color)
{
	int loop;

	Go2xy(x,y);
	for (loop = 0; loop < strlen(string); loop++)
		GraphChar(string[loop],color);
}

////////////////////////////////////////////////////////////////////////////
void demo()
 {
       Load("l1.pcx",&de);
     SetAllRgbPalette(de.pal);
	rys(de);
      zamk(&de);
	fflush(stdin);
      getch();
      getch();
	fflush(stdin);
       Load("l2.pcx",&de);
     SetAllRgbPalette(de.pal);
	rys(de);
      zamk(&de);
	fflush(stdin);
      getch();
      getch();
	  rozp();

  }
///////////////////////////////////////////////////////////////////////
void koniec()
 {
	 Load("l3.pcx",&de);
     SetAllRgbPalette(de.pal);
	rys(de);
      zamk(&de);
	fflush(stdin);
 }


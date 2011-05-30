    #define KEYBOARD 0x09
//

//
    #define RIGHT_ARROW_PRESSED   77
    #define RIGHT_ARROW_REL      205
    #define LEFT_ARROW_PRESSED    75
    #define LEFT_ARROW_REL       203
    #define ESC_PRESSED          129
    #define UP_ARROW_PRESSED      72
    #define UP_ARROW_REL         200
    #define DOWN_ARROW_PRESSED    80
    #define DOWN_ARROW_REL       208

    #define VIEW_WIDTH    320
    #define VIEW_HEIGHT   150
    #define SCREEN_WIDTH  320
    #define SCREEN_HEIGHT 200
    #define MEMBLK        VIEW_WIDTH*VIEW_HEIGHT
    #define TRANSPARENT   0
    #define TOTAL_SCROLL  320

    enum {NORMAL,RLE};
    enum {FALSE,TRUE};

    typedef struct
    {
      char manufacturer;    // ma zawsze wartosc 10
      char version;         /*2-2.8 z paleta, 2.8-3 nalezy uzyc palety
			     standardowj 3-5 lub nowsza */
      char encoding;        //ma zawsze wartosc 1 i oznacza kodowanie RLE
      char bits_per_pixel;  //ilosc bitow na piksel( u mnie 8)
      int  xmin,ymin;       // lewy gorny rog obrazu
      int  xmax,ymax;       // wysokosc i szerokosc obrazu
      int  hres;            // liczba pikseli w ppoziomie
      int  vres;            // liczba pikseli w pionie
      char palette16[48];
      char reserved;
      char color_planes;    // liczba planow w obrazie
      int  bytes_per_line;  //liczba bajtow na jedna pozioma linie
      int  palette_type;
      char filler[58];
    } PcxHeader;

    typedef struct
    {
      PcxHeader hdr;
     unsigned char far *bitmap;
      char pal[768];
      unsigned imagebytes,width,height;
    } PcxFile;


    #define PCX_MAX_SIZE 64000L
    enum {PCX_OK,PCX_NOMEM,PCX_TOOBIG,PCX_NOFILE};

#ifdef __cplusplus
extern "C" {
#endif
    int Load(char *filename,PcxFile *pcx); //drugi plik
    void rys(PcxFile &image);
    void pixel(int x,int y, unsigned char color);
    void rozp();// rozplywanie
    void zamk(PcxFile *sam);

    int ReadPcxFile(char *filename,PcxFile *pcx);
    void _interrupt NewInt9(void);
    void RestoreKeyboard(void);
    void InitKeyboard(void);
    void SetAllRgbPalette(char *pal);
    void InitVideo(void);
    void RestoreVideo(void);
    int InitBitmaps(void);
    void FreeMem(void);
    void DrawLayers(void);
    void AnimLoop(void);
    void Initialize(void);
    void CleanUp(void);
    void OpaqueBlt(char *,int,int,int);
    void TransparentBlt(char *,int,int,int);
    void na_ekran();
    void Go2xy(int x,int y);
    void GraphChar(unsigned char value, unsigned char color);
    void GraphString(int x, int y, unsigned char *string, unsigned char color);
    void demo();
    void koniec();
    void linia(int x1, int x2,int y, unsigned int color);
    #ifdef __cplusplus
  }
#endif

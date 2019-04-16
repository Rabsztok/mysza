#include <allegro.h>
#include <math.h>
#define max(a, b) (((a) > (b)) ? (a): (b))
#define min(a, b) (((a) < (b)) ? (a): (b))
volatile long speed = 0;
volatile long timer = 0;

void increment_speed() 
{ 
  speed++; 
} 

END_OF_FUNCTION(increment_speed);
LOCK_VARIABLE(speed); 
LOCK_FUNCTION(increment_speed);
void mytimer() {
    timer++;
}
int collide_detect(int xmin1, int ymin1, BITMAP *sprite1, int xmin2, int ymin2, BITMAP *sprite2) {
  int xmax1 = xmin1 + sprite1->w, ymax1 = ymin1 + sprite1->h;
  int xmax2 = xmin2 + sprite2->w, ymax2 = ymin2 + sprite2->h;
  int xmin = max(xmin1, xmin2);
  int ymin = max(ymin1, ymin2);
  int xmax = min(xmax1, xmax2);
  int ymax = min(ymax1, ymax2);
  if (xmax <= xmin || ymax <= ymin) { return 0; }
  int mask1 = bitmap_mask_color(sprite1);
  int mask2 = bitmap_mask_color(sprite2);
  for (int y = ymin; y < ymax; y++) {
    for (int x = xmin; x < xmax; x++) {
      int x1 = x - xmin1, y1 = y - ymin1;
      int x2 = x - xmin2, y2 = y - ymin2;
      int color1 = getpixel(sprite1, x1, y1);
      int color2 = getpixel(sprite2, x2, y2);
      if (color1 != mask1 && color2 != mask2) { return 1; }
    }
  }
  return 0;
}

int main() 
{ 
  allegro_init(); 
  install_keyboard();
  set_color_depth(16); 
  set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0);  
  clear_to_color(screen, makecol(200,200,128));


BITMAP *bufor = NULL;
BITMAP *ludek = NULL; 
BITMAP *ludekd1 = NULL; 
BITMAP *ludekr1 = NULL; 
BITMAP *ludekg1 = NULL; 
BITMAP *ludekl1 = NULL;
BITMAP *ludekd2 = NULL; 
BITMAP *ludekr2 = NULL; 
BITMAP *ludekg2 = NULL; 
BITMAP *ludekl2 = NULL;
BITMAP *wrog = NULL; 
BITMAP *wrogd1 = NULL; 
BITMAP *wrogr1 = NULL; 
BITMAP *wrogg1 = NULL; 
BITMAP *wrogl1 = NULL;
BITMAP *wrogd2 = NULL; 
BITMAP *wrogr2 = NULL; 
BITMAP *wrogg2 = NULL; 
BITMAP *wrogl2 = NULL;
BITMAP *ser = NULL;
BITMAP *wallu= NULL;
BITMAP *wallm= NULL;
BITMAP *walld= NULL;
BITMAP *floor= NULL;
BITMAP *credit= NULL;
BITMAP *menu= NULL;
BITMAP *resgame= NULL;
BITMAP *newgame= NULL;
BITMAP *exit= NULL;
BITMAP *credits= NULL;
BITMAP *hscore= NULL;
BITMAP *mark= NULL;
PALETTE palette;
FONT *cheese;
bufor = create_bitmap(800,600); 
if (!bufor) 
{ 
  set_gfx_mode(GFX_TEXT,0,0,0,0); 
  allegro_message("Nie mogê utworzyæ bufora !"); 
  allegro_exit(); 
  return 0; 
} 
cheese = load_font("cheese.pcx", palette, NULL);
ludek = load_bmp("myszr1.bmp",default_palette); 
ludekd1 = load_bmp("myszd1.bmp",default_palette); 
ludekr1 = load_bmp("myszr1.bmp",default_palette); 
ludekg1 = load_bmp("myszg1.bmp",default_palette); 
ludekl1 = load_bmp("myszl1.bmp",default_palette);
ludekd2 = load_bmp("myszd2.bmp",default_palette); 
ludekr2 = load_bmp("myszr2.bmp",default_palette); 
ludekg2 = load_bmp("myszg2.bmp",default_palette); 
ludekl2 = load_bmp("myszl2.bmp",default_palette);

wrog = load_bmp("kotr1.bmp",default_palette); 
wrogd1 = load_bmp("kotd1.bmp",default_palette); 
wrogr1 = load_bmp("kotr1.bmp",default_palette); 
wrogg1 = load_bmp("kotg1.bmp",default_palette); 
wrogl1 = load_bmp("kotl1.bmp",default_palette);
wrogd2 = load_bmp("kotd2.bmp",default_palette); 
wrogr2 = load_bmp("kotr2.bmp",default_palette); 
wrogg2 = load_bmp("kotg2.bmp",default_palette); 
wrogl2 = load_bmp("kotl2.bmp",default_palette);

ser     = load_bmp("ser.bmp",default_palette);
wallu   = load_bmp("wall1.bmp",default_palette);
wallm   = load_bmp("wall2.bmp",default_palette);
walld   = load_bmp("wall3.bmp",default_palette);
floor   = load_bmp("floor.bmp",default_palette);
credit   = load_bmp("credit.bmp",default_palette);
menu   = load_bmp("menu.bmp",default_palette);
resgame   = load_bmp("resgame.bmp",default_palette);
newgame   = load_bmp("newgame.bmp",default_palette);
exit  = load_bmp("exit.bmp",default_palette);
credits   = load_bmp("credits.bmp",default_palette);
hscore   = load_bmp("hscore.bmp",default_palette);
mark   = load_bmp("mark.bmp",default_palette);
int wrog_x = 400, wrog_y = 300; 
int ludek_x = 0, ludek_y = 250; 
int ser_x = 300, ser_y = 200;
int frame = 0;
int wynik = 0;
int zycia = 3;
int czas = timer/100;
int seccount=0;
int droga=0;
short int kierunek=0;
int los=0;
bool alarm;
int mark_y=250;
bool kb=false;
int k=0;
bool ok=false;
int gra=0;
int stan=0;
int akt_czas=0;
int gameover=0;
do{
while(!ok){
masked_blit( menu, bufor, 0,0,0,0, menu->w, menu->h);
if(gra==1)masked_blit( resgame, bufor, 0,0, 267, 250, resgame->w, resgame->h);
if(gra==0||gameover==1)masked_blit( newgame, bufor, 0,0, 267, 250, newgame->w, newgame->h);
masked_blit( credits, bufor, 0,0, 267, 320, credits->w, credits->h);
masked_blit( hscore, bufor, 0,0, 267, 390, credits->w, credits->h);
masked_blit( exit, bufor, 0,0, 267, 460, credits->w, credits->h);
masked_blit( mark, bufor, 0,0, 267, mark_y, mark->w, mark->h);
blit( bufor, screen, 0,0,0,0, 800,600);
if((key[KEY_DOWN])&&(mark_y!=460)){mark_y+=70;key[KEY_DOWN]=0;}
if((key[KEY_UP])&&(mark_y!=250)){mark_y-=70;key[KEY_UP]=0;}
if(key[KEY_ENTER]&&(mark_y==250)){stan=1;ok=true;
if(gameover==1){gameover=0;akt_czas=0;zycia=3;wynik=0;ludek_x = 0;ludek_y = 250;}}
if(key[KEY_ENTER]&&(mark_y==320))
while(!key[KEY_ESC])
{masked_blit( credit, bufor,0,0,0,0,credit->w,credit->h);
blit( bufor, screen, 0,0,0,0, 800,600);}
if(key[KEY_ENTER]&&(mark_y==460))
{remove_int( increment_speed);
destroy_bitmap(bufor); 
allegro_exit(); 
return 0;}
}

ok=false;
  install_timer();
  install_int_ex(increment_speed, BPS_TO_TIMER(100));
  install_int(mytimer, 1000);
  timer=akt_czas;
/*********************************___________________STEROWANIE_________________________*********************************/
/************************************************************************************************************************/
while(stan==1)
{
while( speed > 0) 
{ 
gra=1;
if(key[KEY_ESC])
{
akt_czas=timer;
remove_timer();
stan=0;
}

masked_blit( floor, bufor, 0,0,0,0, menu->w, menu->h);
masked_blit( wallu, bufor, 0,0, 45, 0, wallu->w, wallu->h);
masked_blit( wallm, bufor, 0,0, 45, 115, wallm->w, wallm->h);
masked_blit( walld, bufor, 0,0, 45, 545, walld->w, walld->h);
masked_blit( wallu, bufor, 0,0, 725, 0, wallu->w, wallu->h);
masked_blit( wallm, bufor, 0,0, 725, 115, wallm->w, wallm->h);
masked_blit( walld, bufor, 0,0, 725, 545, walld->w, walld->h);

if( key[KEY_LEFT]&&(gameover==0))
  {if( frame<50)ludek=ludekl1;
  else if( frame>=50)ludek=ludekl2;
  if(ludek_x>0)ludek_x--;} 
  if( key[KEY_RIGHT]&&(gameover==0))
  {if( frame<50)ludek=ludekr1;
  else if( frame>=50)ludek=ludekr2;
  if(ludek_x<750) ludek_x++; }
  if( key[KEY_UP]&&(gameover==0))
  {if( frame<50)ludek=ludekg1;
  else if( frame>=50)ludek=ludekg2;
  if(ludek_y>0)ludek_y--; }
  if( key[KEY_DOWN]&&(gameover==0))
  {if( frame<50)ludek=ludekd1;
  else if( frame>=50)ludek=ludekd2;
  if(ludek_y<550)ludek_y++; }
  if( key[KEY_LEFT]&&key[KEY_UP]&&(gameover==0)){ludek_x++;
  ludek_y++;}
  if( key[KEY_RIGHT]&&key[KEY_UP]&&(gameover==0)){ludek_x--;
  ludek_y++;}
  if( key[KEY_LEFT]&&key[KEY_DOWN]&&(gameover==0)){ludek_x++;
  ludek_y--;}
  if( key[KEY_RIGHT]&&key[KEY_DOWN]&&(gameover==0)){ludek_x--;
  ludek_y--;}
/********************************KOT AI********************************************/

srand(time(NULL));
if((ludek_x<=60||ludek_x>=690))
{
droga=1+rand()%20;
kierunek=1+rand()%4;
alarm=false;
}
if(((ludek_x<=wrog_x)&&kierunek==1)||((ludek_x>=wrog_x)&&kierunek==2)||((ludek_y<=wrog_y)&&kierunek==3)||((ludek_y>=wrog_y)&&kierunek==4))alarm=true;
if((ludek_x>60&&ludek_x<690)&&(alarm==true))
{
    textout_centre_ex(bufor, font, "miau! miau!",wrog_x,wrog_y-20, makecol(0,0,0), -1);
	los=rand()%2;
	if(los==0)
	{
	if(ludek_x<wrog_x)kierunek=1;droga=1;/*lewo*/
	if(wrog_x<=650)if(ludek_x>wrog_x)kierunek=2;droga=1;/*prawo*/
	if(ludek_y<wrog_y)kierunek=3;droga=1;/*gora*/
	if(wrog_y<=520)if(ludek_y>wrog_y)kierunek=4;droga=1;/*dol*/
	}else
	{
	if(ludek_y<wrog_y)kierunek=3;droga=1;
	if(wrog_y<=520)if(ludek_y>wrog_y)kierunek=4;droga=1;
	if(ludek_x<wrog_x)kierunek=1;droga=1;
	if(wrog_x<=650)if(ludek_x>wrog_x)kierunek=2;droga=1;
	}
	}
 
switch(kierunek)
{
 case 1:/*lewo*/
{if( frame<50)wrog=wrogl1;
else if( frame>=50)wrog=wrogl2;
if(wrog_x>=70)wrog_x--;
else kierunek=2;
break;}
 case 2:/*prawo*/
{if( frame<50)wrog=wrogr1;
else if( frame>=50)wrog=wrogr2;
if(wrog_x<=650)wrog_x++;
else kierunek=1;
break;}
 case 3:/*gora*/
{if( frame<50)wrog=wrogg1;
else if( frame>=50)wrog=wrogg2;
if(wrog_y>=0)wrog_y--;
else kierunek=4;
break;}
 case 4:/*dol*/
{if( frame<50)wrog=wrogd1;
else if( frame>=50)wrog=wrogd2;
if(wrog_y<=520)wrog_y++;
else kierunek=3;
break;}
droga--;
}
/**************************************************************KOLIZJE***************************************************/
if(collide_detect(int(ludek_x), int(ludek_y), ludek, int(wrog_x), int(wrog_y), wrog)==1){
zycia--;
if(zycia!=0)ludek_x =0, ludek_y =250;
else ludek_x=1000;
}
if(collide_detect(int(ludek_x), int(ludek_y), ludek, int(ser_x), int(ser_y), ser)==1){
wynik++;
ser_x =71+rand()%608, ser_y =rand()%550; }
/********************************ŒCIANY LEWE********************************************/
if((ludek_x>1)&&(ludek_x<60)&&(ludek_y<49))ludek_x--;  //lewo
if((ludek_x<70)&&(ludek_x>60)&&(ludek_y<49))ludek_x++;               //prawo
if((ludek_x>1)&&(ludek_x<70)&&(ludek_y==49))ludek_y++; //dó³

if((ludek_x>1)&&(ludek_x<70)&&(ludek_y==71))ludek_y--;    //góra
if((ludek_x>1)&&(ludek_x<60)&&(ludek_y>71)&&(ludek_y<478))ludek_x--;  //lewo
if((ludek_x<70)&&(ludek_x>60)&&(ludek_y>71)&&(ludek_y<478))ludek_x++;               //prawo
if((ludek_x>1)&&(ludek_x<70)&&(ludek_y==478))ludek_y++;                    //dó³

if((ludek_x>1)&&(ludek_x<60)&&(ludek_y>501))ludek_x--;  //lewo
if((ludek_x<70)&&(ludek_x>60)&&(ludek_y>501))ludek_x++;               //prawo
if((ludek_x>1)&&(ludek_x<70)&&(ludek_y==501))ludek_y--; //góra
/********************************ŒCIANY PRAWE********************************************/
if((ludek_x>680)&&(ludek_x<690)&&(ludek_y<49))ludek_x--;  //lewo
if((ludek_x<748)&&(ludek_x>730)&&(ludek_y<49))ludek_x++;               //prawo
if((ludek_x>680)&&(ludek_x<748)&&(ludek_y==49))ludek_y++; //dó³

if((ludek_x>680)&&(ludek_x<748)&&(ludek_y==71))ludek_y--;    //góra
if((ludek_x>680)&&(ludek_x<690)&&(ludek_y>71)&&(ludek_y<478))ludek_x--;  //lewo
if((ludek_x<748)&&(ludek_x>730)&&(ludek_y>71)&&(ludek_y<478))ludek_x++;               //prawo
if((ludek_x>680)&&(ludek_x<748)&&(ludek_y==478))ludek_y++;                    //dó³

if((ludek_x>680)&&(ludek_x<690)&&(ludek_y>501))ludek_x--;  //lewo
if((ludek_x<748)&&(ludek_x>730)&&(ludek_y>501))ludek_x++;               //prawo
if((ludek_x>680)&&(ludek_x<748)&&(ludek_y==501))ludek_y--; //góra


  mytimer();
  speed--; 
  frame++; 
  if( frame > 120) frame=0;
}
int czas;
if(gameover==0)czas = timer/100;
masked_blit( ser, bufor, 0,0, ser_x, ser_y, ser->w, ser->h);
masked_blit( ludek, bufor, 0,0, ludek_x, ludek_y, ludek->w, ludek->h);
masked_blit( wrog, bufor, 0,0, wrog_x, wrog_y, wrog->w, wrog->h);
textprintf_centre_ex(bufor, font, SCREEN_W / 2, 10, makecol( 0, 0, 255), -1, "time: %d",czas);
textprintf_centre_ex(bufor, font, SCREEN_W / 2, 20, makecol( 0, 0, 255), -1, "points: %d",wynik);
textprintf_centre_ex(bufor, font, SCREEN_W / 2, 30, makecol( 0, 0, 255), -1, "lives: %d",zycia);
if(zycia==0){textout_centre_ex(bufor, cheese, "GAME OVER",SCREEN_W / 2, SCREEN_H / 2, makecol(0,0,0), -1);gameover=1;
textout_centre_ex(bufor, font, "press escape",SCREEN_W / 2, (SCREEN_H / 2)+40, makecol(0,0,0), -1);}
blit( bufor, screen, 0,0,0,0, 800,600); 
}
}while(!key[KEY_Q]);
remove_int( increment_speed);
destroy_bitmap(bufor); 
allegro_exit(); 
return 0; 
}
END_OF_MAIN();
END_OF_FUNCTION(mytimer);

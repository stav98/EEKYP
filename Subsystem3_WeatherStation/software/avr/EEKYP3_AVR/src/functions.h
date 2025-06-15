//Κάνει software Reset τον AVR
void(* resetFunc)(void) = 0;

 float fmap(unsigned int x, unsigned int min, unsigned int max, unsigned int o_min, unsigned int o_max)
 {
  //if (x < min) x = min;
  float y = (float)(x - min) * (o_max - o_min) / (float)(max - min) + o_min;
  if (min > max)
     {
      if (x < max) x = max;
      y = (float)(min - x) * (o_max - o_min) / (float)(min - max) + o_min;
     }
  return y;
 }
 
//Θέση σε τροποποιημένο κώδικα Gray  
//                               0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15  Η τιμή 1 δείχνει στον βορά δηλ. 0 μοίρες
const int PROGMEM wind_dir[] = {-1,   0,  72,  12, 144, 132,  84, 120, 216, 348, 204,  24, 156, 168, 192, 180,
                               288, 300,  60,  48, 276, 312,  96, 108, 228, 336, 240,  36, 264, 324, 252, -1}; //Γωνίες σε βήματα 12 μοίρες / βήμα
//                              16   17   18   19   20   21   22   23   24   25   26   27   28   29   30  31   

 int readAirVane()
 {
  byte t = 0;
  t = digitalRead(AIR_DIR_B0) * 1 | digitalRead(AIR_DIR_B1) * 2 | digitalRead(AIR_DIR_B2) * 4 |
      digitalRead(AIR_DIR_B3) * 8 | digitalRead(AIR_DIR_B4) * 16;
  return pgm_read_word(wind_dir + t);
 }
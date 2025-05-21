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
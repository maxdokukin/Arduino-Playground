#define HUE_GAP 35000      // заброс по hue
#define FIRE_STEP 30    // шаг огня
#define HUE_START 25000     // начальный цвет огня (0 красный, 80 зелёный, 140 молния, 190 розовый)
#define MIN_BRIGHT 10   // мин. яркость огня
#define MAX_BRIGHT 1255  // макс. яркость огня
#define MIN_SAT 180     // мин. насыщенность
#define MAX_SAT 255     // макс. насыщенность


class Perlin{
    
  int counter = 0;  
  
  public: void tick(){
  
      for(int i = 0; i < NUM_LEDS; i++)
        strip.setPixelColor(i, getFireColor((inoise8(i * FIRE_STEP, counter))));
  
      counter += 5;      
  }
  
  
  
    long getFireColor(int val) {
  
    return strip.ColorHSV(
               HUE_START + map(val, 0, 255, 0, HUE_GAP),                    // H  
               constrain(map(val, 0, 255, MAX_SAT, MIN_SAT), 0, 255),       // S
               constrain(map(val, 0, 255, MIN_BRIGHT, MAX_BRIGHT), 0, 255)  // V   
             );
    }
  
    long getPerlinColor(){
  
      return getFireColor((inoise8(0, 0)));
    }
};


Perlin* perlinLink;

void perlin(){

  if(perlinLink == NULL)
    perlinLink = new Perlin();
    
  perlinLink->tick();
}

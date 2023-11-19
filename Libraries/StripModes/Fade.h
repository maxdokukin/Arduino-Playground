unsigned int fadeDelay = 3000;
boolean fadeIN = false;
long fadeCol1 = 0xff00ff;
long fadeCol2 = 0x00ffff;



class Fade{

  long startT;
  short colors[2][3];
  public: bool finished = false;

  public:  
    Fade(long col1, long col2){
      
      getColors(col1, col2);
      startT = millis();
    }

  void tick(){

    if(millis() - startT >= fadeDelay){
      
      finished = true;
      return;
    }

    if(colorChanged){

      finished = true;
      colorChanged = false;
    }
    
    float progress = (map(millis() - startT, 0, fadeDelay, 0, 1000) / (float) 1000);
    
    byte R = colors[0][0] + colors[1][0] * progress;
    byte G = colors[0][1] + colors[1][1] * progress;
    byte B = colors[0][2] + colors[1][2] * progress;

    for(int i = 0; i < NUM_LEDS; i++)      
      strip.setPixelColor(i, R, G, B);

  }

  void getColors(long col1, long col2){
      
    colors[0][0] = colCon(col1, 'R');
    colors[0][1] = colCon(col1, 'G');
    colors[0][2] = colCon(col1, 'B');
  
    colors[1][0] = (short) colCon(col2, 'R') - (short) colors[0][0];
    colors[1][1] = (short) colCon(col2, 'G') - (short) colors[0][1];
    colors[1][2] = (short) colCon(col2, 'B') - (short) colors[0][2]; 
  } 
};


Fade* fadeLink;

void fade(){

  if(fadeLink == NULL)
    fadeLink = new Fade(fadeCol1, fadeCol2);


  if(fadeLink->finished){
    
    delete fadeLink;
    
    if(fadeIN)
      fadeLink = new Fade(fadeCol1, fadeCol2);

    else
      fadeLink = new Fade(fadeCol2, fadeCol1);
    
    fadeIN = !fadeIN;
  }
    
  fadeLink->tick();
}

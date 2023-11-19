byte rainbowDelay = 10;

class Rainbow{

  long lastUPD;
  long firstPixelHue = 0;
  
  public:Rainbow(){

    lastUPD = 0;
    
  }
  
  void tick() {


    if(millis() - lastUPD < rainbowDelay)
      return;
      

    lastUPD = millis();

    if(firstPixelHue >= 327680)
      firstPixelHue = 0;

    for(int i = 0; i < NUM_LEDS; i++) { 

      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());

      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    
    firstPixelHue += 256;
  }
};



Rainbow *rainbowLink;


void rainbow(){

  if(rainbowLink == NULL)
    rainbowLink = new Rainbow();

  rainbowLink->tick();
}

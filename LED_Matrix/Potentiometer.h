#define AVERAGE_ARRAY_SIZE 10
#define dV 1

class Potentiometer{

  byte pin;
  long minVal = -1, maxVal = -1;

  float readings[AVERAGE_ARRAY_SIZE];
  int lastAverage = 0;

  public: Potentiometer(byte p, long min, long max){

    pin = p;
    minVal = min;
    maxVal = max;

    pinMode(pin, INPUT);
  }


  void update(){

    for(int i = AVERAGE_ARRAY_SIZE - 1; i > 0; i--)
      readings[i] = readings[i - 1];

    short currentReading = analogRead(pin);
    
    if(!(lastAverage - dV < currentReading && currentReading < lastAverage + dV))
      readings[0] = currentReading;
  }


  public: float getAverage(){

    float sum = 0;

    for(int i = 0; i < AVERAGE_ARRAY_SIZE; i++)
      sum += readings[i];

    return sum / AVERAGE_ARRAY_SIZE;
  }


  public: long getValue(){

    lastAverage = getAverage();

    return map(lastAverage, 0, 1023, minVal, maxVal);
  }

  public: int getMappedValue(int min, int max){
    
    lastAverage = getAverage();

    return map(lastAverage, 0, 1023, min, max);
  }
};
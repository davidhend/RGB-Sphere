#include <FastLED.h>

// Params for width and height
const uint8_t kMatrixWidth = 19;
const uint8_t kMatrixHeight = 16;

#define DATA_PIN    5
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS (kMatrixWidth * kMatrixHeight)

#define BRIGHTNESS          56 //56
#define FRAMES_PER_SECOND  120

uint16_t LEDChannels[19];

// Param for different pixel layouts
const bool    kMatrixSerpentineLayout = false;

//accelerometer variables
const int xInput = A0;
// initialize minimum and maximum Raw Ranges for each axis
int RawMin = 0;
int RawMax = 1023;
// Take multiple samples to reduce noise
const int sampleSize = 10;

uint16_t XY( uint8_t x, uint8_t y)
{
  uint16_t i;

  if ( kMatrixSerpentineLayout == false) {
    i = (y * kMatrixWidth) + x;
  }

  if ( kMatrixSerpentineLayout == true) {
    if ( y & 0x01) {
      // Odd rows run backwards
      uint8_t reverseX = (kMatrixWidth - 1) - x;
      i = (y * kMatrixWidth) + reverseX;
    } else {
      // Even rows run forwards
      i = (y * kMatrixWidth) + x;
    }
  }

  return i;
}

#define NUM_LEDS (kMatrixWidth * kMatrixHeight)
CRGB leds_plus_safety_pixel[ NUM_LEDS + 1];
CRGB* const leds( leds_plus_safety_pixel + 1);

uint16_t XYsafe( uint8_t x, uint8_t y)
{
  if ( x >= kMatrixWidth) return -1;
  if ( y >= kMatrixHeight) return -1;
  return XY(x, y);
}

uint8_t gHue = 0; // rotating "base color" used by many of the patterns

//used to increment Hue for LEDs (slowly cycle the "base color" through the rainbow)
long previousMillis2 = 0;
long interval2 = 20;

//used for NSL routines
unsigned int offset = 0;
float mil;

//used for bounching line routines
int ball_x;
int ball_y;
int travel_direction;

//triggered by button to change effects
const byte interruptPin = 2;
volatile int effectNum = 1;

//used to debounce button input
long debouncing_time = 50;
volatile unsigned long last_micros;

int exitloop = 0;

void setup() {
  Serial.begin(115200);

  //max 5v @ 700MA
  //FastLED.setMaxPowerInVoltsAndMilliamps(5,650);

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);

  randomSeed(analogRead(5));

  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), incrementEffectCount, FALLING);
  
}


void loop() {
  //used for bouncing ball effect
  ball_x = random(kMatrixWidth - 1);
  ball_y = random(kMatrixHeight - 1);
  travel_direction = random(3) + 1;

  switch(effectNum)
  {
    case 1:
      //Serial.println("DownDown");
      launch_effect(1, 1); 
      break;
    case 2:
      //Serial.println("Swirl");
      launch_effect(2, 1); 
      break;    
    case 3:
      //Serial.println("Swirl2");
      launch_effect(3, 16); 
      break;    
    case 4:
      //Serial.println("Spiral");
      launch_effect(4, 1);
      break;    
    case 5:
      //Serial.println("UpDown2");
      launch_effect(5, 1); 
      break;    
    case 6:
      //Serial.println("BouncingBall");
      launch_effect(6, 50); 
      break;    
    case 7:
      //Serial.println("RainEffect");
      launch_effect(7, 1);
      break;    
    case 8:
      //Serial.println("UpDown");
      launch_effect(8, 1);
      break;    
    case 9:
      //Serial.println("WholeSphereCylon");
      launch_effect(9, 1);
      break;    
    case 10:
      //Serial.println("Juggle");
      launch_effect(10, 100);
      break;    
    case 11:
      //Serial.println("Fading");
      launch_effect(11, 100);
      break;    
    case 12:
      FastLED.clear();
      //Serial.println("Fireworks");
      launch_effect(12, 1);
      break;    
    case 13:
      //Serial.println("Accelerometer Demo");
      launch_effect(13, 100);
      break;    
    default:
      break;  
  }


}

void incrementEffectCount() {
 if((long)(micros() - last_micros)>=debouncing_time*1000)
 {
   if (effectNum < 13){
     effectNum++;
   }else{
     effectNum = 1;
   }

   exitloop = 1;
   last_micros = micros();
 }
}

void launch_effect(int effect_number, int duration)
{
  for (int i = 0; i < duration; i++)
  {
    //necessary for a couple routines
    if(exitloop == 1){
      exitloop = 0;
      break;
    }
    
    switch (effect_number)
    {
      case 1:
        downDown();
        break;
      case 2:
        swirl();
        break;
      case 3:
        swirl2(i);
        break;
      case 4:
        spiral();
        break;
      case 5:
        upDown2();
        break;
      case 6:
        bouncingBall();
        break;
      case 7:
        rainEffect();
        break;
      case 8:
        upDown();
        break;
      case 9:
        wholeSphereCylon();
        break;
      case 10:
        juggle();
        break;
      case 11:
        fading();
        break;
      case 12:
        fireWorks();
        break;
      case 13:
        accel_demo();
        break;
      default:
        break;
    }
  }
}

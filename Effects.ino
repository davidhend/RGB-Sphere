void swirl()
{
  byte x1 = random(17) + 1;
  byte x2 = random(17) + 1;
  if (x1 == x2) {
    x2 = random(17) + 1;
  }

  byte y2 = 0;
  for (int itterations = 0; itterations < 5; itterations++) {
    for ( byte y1 = 0; y1 < kMatrixHeight; y1++) { //16
      fadeToBlackBy( leds, NUM_LEDS, 20); //was fadeToBlackBy( leds, NUM_LEDS, 5);
      leds[ XY(x1, y1)] = CHSV( gHue, 255, 192);
      y2 = abs(y1 - 15);
      leds[ XY(x2, y2)] = CHSV( gHue / 2, 255, 192);
      // send the 'leds' array out to the actual LED strip
      FastLED.show();
      // insert a delay to keep the framerate modest
      FastLED.delay(1000 / FRAMES_PER_SECOND);
      FastLED.delay(1000 / FRAMES_PER_SECOND);
      FastLED.delay(1000 / FRAMES_PER_SECOND);
      FastLED.delay(1000 / FRAMES_PER_SECOND);
      //FastLED.delay(1000/FRAMES_PER_SECOND);
      //FastLED.clear();

      //increment Hue every 20 ms, this can be adjusted in any pattern
      long currentMillis = millis();
      if (currentMillis - previousMillis2 >= interval2) {
        previousMillis2 = currentMillis;
        gHue++;
      }
    }
  }
}

int table[16][2] =
{
  0, 8,
  1, 9,
  2, 10,
  3, 11,
  4, 12,
  5, 13,
  6, 14,
  7, 15,
  8, 0,
  9, 1,
  10, 2,
  11, 3,
  12, 4,
  13, 5,
  14, 6,
  15, 7
};

boolean invert = false;
void swirl2(int i)
{
  for ( byte y = 0; y < 2; y++) {
    if (y == 0) {
      invert = false;
    } else if (y == 1) {
      invert = true;
    }
    byte y1 = table[i][y];
    for ( byte x = 0; x < kMatrixWidth; x++) { //19

      fadeToBlackBy( leds, NUM_LEDS, 20);
      //    0-19 0-15
      //    led# slice#

      if (invert == false) {
        leds[ XYsafe(x, y1)]  = CHSV( gHue, 255, 192);
      } else if (invert == true) {
        leds[ XYsafe(18 - x, y1)]  = CHSV( gHue, 255, 192);
      }

      // send the 'leds' array out to the actual LED strip
      FastLED.show();
      FastLED.delay(1000 / FRAMES_PER_SECOND);

      //increment Hue every 20 ms, this can be adjusted in any pattern
      long currentMillis = millis();
      if (currentMillis - previousMillis2 >= interval2) {
        previousMillis2 = currentMillis;
        gHue++;
      }
    }
  }
}


void fireWorks()
{
  int slice = random(15);

  //up
  for ( byte x = 0; x < kMatrixWidth; x++) { //19
    fadeToBlackBy( leds, NUM_LEDS, 5);

    leds[ XYsafe(x, slice)] = CRGB::White;

    // send the 'leds' array out to the actual LED strip
    FastLED.show();
    // insert a delay to keep the framerate modest
    FastLED.delay(1000 / FRAMES_PER_SECOND);
    FastLED.delay(1000 / FRAMES_PER_SECOND);
    FastLED.delay(1000 / FRAMES_PER_SECOND);
    FastLED.delay(1000 / FRAMES_PER_SECOND);
    FastLED.delay(1000 / FRAMES_PER_SECOND);
  }

  //down (explosion)
  for ( byte x = kMatrixWidth; x > 0; x--) { //19
    for ( byte y = 0; y < kMatrixHeight; y++) { //12
      fadeToBlackBy( leds, NUM_LEDS, 5);

      leds[ XYsafe(x, y)] = CHSV( gHue, 255, 192);

      addGlitter(60);

      //increment Hue every 20 ms, this can be adjusted in any pattern
      long currentMillis = millis();
      if (currentMillis - previousMillis2 >= interval2) {
        previousMillis2 = currentMillis;
        gHue++;
      }
    }
    // send the 'leds' array out to the actual LED strip
    FastLED.show();
    // insert a delay to keep the framerate modest
    FastLED.delay(1000 / FRAMES_PER_SECOND);
    FastLED.delay(1000 / FRAMES_PER_SECOND);
  }
  FastLED.clear();
}

void addGlitter( fract8 chanceOfGlitter)
{
  if ( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

int x1, x2, x3, x4, x5, x6;
void rainEffect()
{
  int number_of_drops = random(5)+1;
  
  int slice1 = random(15);
  int slice2 = random(15);
  int slice3 = random(15);
  int slice4 = random(15);
  int slice5 = random(15);
  int slice6 = random(15);

  int offset1 = random(9);
  int offset2 = random(9);
  int offset3 = random(9);
  int offset4 = random(9);
  int offset5 = random(9);
  int offset6 = random(9);

  x1 = kMatrixWidth + offset1;
  x2 = kMatrixWidth + offset2;
  x3 = kMatrixWidth + offset3;
  x4 = kMatrixWidth + offset4;
  x5 = kMatrixWidth + offset5;
  x6 = kMatrixWidth + offset6;

  //down
  while (x1 != -1 || x2 != -1 || x3 != -1 || x4 != -1 || x5 != -1 || x6 != -1) {
    FastLED.clear();

    switch(number_of_drops)
    {
      case 1:
        leds[ XYsafe(x1, slice1)] = CRGB::Blue;
        break;
      case 2:
        leds[ XYsafe(x1, slice1)] = CRGB::Blue;
        leds[ XYsafe(x2, slice2)] = CRGB::Blue;
        break;
      case 3:
        leds[ XYsafe(x1, slice1)] = CRGB::Blue;
        leds[ XYsafe(x2, slice2)] = CRGB::Blue;
        leds[ XYsafe(x3, slice3)] = CRGB::Blue;
        break;      
      case 4:
        leds[ XYsafe(x1, slice1)] = CRGB::Blue;
        leds[ XYsafe(x2, slice2)] = CRGB::Blue;
        leds[ XYsafe(x3, slice3)] = CRGB::Blue;
        leds[ XYsafe(x4, slice4)] = CRGB::Blue;      
        break;  
      case 5:
        leds[ XYsafe(x1, slice1)] = CRGB::Blue;
        leds[ XYsafe(x2, slice2)] = CRGB::Blue;
        leds[ XYsafe(x3, slice3)] = CRGB::Blue;
        leds[ XYsafe(x4, slice4)] = CRGB::Blue;
        leds[ XYsafe(x5, slice5)] = CRGB::Blue;      
        break;  
      case 6:
        leds[ XYsafe(x1, slice1)] = CRGB::Blue;
        leds[ XYsafe(x2, slice2)] = CRGB::Blue;
        leds[ XYsafe(x3, slice3)] = CRGB::Blue;
        leds[ XYsafe(x4, slice4)] = CRGB::Blue;
        leds[ XYsafe(x5, slice5)] = CRGB::Blue;
        leds[ XYsafe(x6, slice6)] = CRGB::Blue;      
        break;  
    }

    if (x1 >= 0)
      x1--;

    if (x2 >= 0)
      x2--;

    if (x3 >= 0)
      x3--;

    if (x4 >= 0)
      x4--;

    if (x5 >= 0)
      x5--;

    if (x6 >= 0)
      x6--;

    // send the 'leds' array out to the actual LED strip
    FastLED.show();
    
    FastLED.delay(1000 / FRAMES_PER_SECOND);
    FastLED.delay(1000 / FRAMES_PER_SECOND);
  }
}

void spiral()
{
  for (float i = 1; i < 5; i += .06) {
    offset = (int)((1.0f + sinf(i)) * 60.0f);
    LEDscan3(255, (offset * 2), 1); //Try LEDscan2 instead!
  }
}

void upDown2()
{
  for (int offset = 0; offset < 360; offset += 1) {
    //necessary for a couple routines (supdown2 / piral2 / whole sphere cylon)
    if(exitloop == 1){
      exitloop = 0;
      break;
    }
    LEDscan2(255, offset, 1);
  }
}

void upDownRandom()
{
  FastLED.setBrightness(56);
  mil = 50 + (rand() % 70);
  for (float i = 1; i < 10; i += .1) {
    offset = (int)((1.0f + sinf(i)) * mil);
    LEDscan2(4096, (offset * 2), 1);
    delay(i * 6);
  }
}

byte y = 0;
void LEDscan3(int red, float degreeoffset, unsigned int count)
{
  float brightnessfactor = 0.0f;
  float scanindex = (1.0f + sinf(degreeoffset * 3.14159f / 180.0f)) * ((float)(count * 19 ) / 2.0);

  for (unsigned int LEDindex = 0; LEDindex < (count  * 19); LEDindex++) {
    brightnessfactor = expf(0.0f - fabs(scanindex - ((float)LEDindex + 0.5f)) * 1.3f);
    LEDChannels[LEDindex] = red * brightnessfactor;
  }

  for ( byte x = 0; x < kMatrixWidth - 1; x++) {
    int value = LEDChannels[x];
    leds[ XYsafe(x, y)] = CHSV(value, 0, value); //G,R,B
  }

  // send the 'leds' array out to the actual LED strip
  FastLED.show();
  // insert a delay to keep the framerate modest
  FastLED.delay(1000 / FRAMES_PER_SECOND);
  FastLED.delay(1000 / FRAMES_PER_SECOND);

  fadeToBlackBy( leds, NUM_LEDS, 20);

  if (y < kMatrixHeight) {
    y++;
  } else {
    y = 0;
  }
}


void LEDscan2(int red, float degreeoffset, unsigned int count)
{
  float brightnessfactor = 0.0f;

  float scanindex = (1.0f + sinf(degreeoffset * 3.14159f / 180.0f)) * ((float)(count * 19 ) / 2.0);

  for (unsigned int LEDindex = 0; LEDindex < (count  * 19); LEDindex++) {
    brightnessfactor = expf(0.0f - fabs(scanindex - ((float)LEDindex + 0.5f)) * 1.3f);
    LEDChannels[LEDindex] = red * brightnessfactor;
  }

  for ( byte y = 0; y < kMatrixHeight; y++) {
    for ( byte x = 0; x < kMatrixWidth; x++) {
      int value = LEDChannels[x];
      leds[ XY(x, y)] = CRGB(value, 0, value); //G,R,B
    }
  }
  FastLED.show();
  // insert a delay to keep the framerate modest
  //FastLED.delay(1000/FRAMES_PER_SECOND);
  fadeToBlackBy( leds, NUM_LEDS, 20);
}


void juggle() 
{
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for ( int i = 0; i < 8; i++) {
    leds[beatsin16( i + 7, 0, NUM_LEDS - 1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
  // send the 'leds' array out to the actual LED strip
  FastLED.show();
  // insert a delay to keep the framerate modest
  FastLED.delay(1000 / FRAMES_PER_SECOND);
}

void wholeSphereCylon()
{
  for ( byte y = 0; y < kMatrixHeight; y++) {
    //necessary for a couple routines (spiral2 / whole sphere cylon)
    if(exitloop == 1){
      exitloop = 0;
      break;
    }
    for ( byte x = 0; x < kMatrixWidth; x++) {

      fadeToBlackBy( leds, NUM_LEDS, 20);
      //    0-19 0-15
      //    led# slice#
      leds[ XYsafe(x, y)]  = CHSV( gHue, 255, 192);

      // send the 'leds' array out to the actual LED strip
      FastLED.show();
      FastLED.delay(1000 / FRAMES_PER_SECOND);

      //increment Hue every 20 ms, this can be adjusted in any pattern
      long currentMillis = millis();
      if (currentMillis - previousMillis2 >= interval2) {
        previousMillis2 = currentMillis;
        gHue++;
      }
    }
  }
}


void upDown()
{
  //down
  for ( byte x = kMatrixWidth - 1; x > 0; x--) { //19
    for ( byte y = 0; y < kMatrixHeight; y++) { //16
      fadeToBlackBy( leds, NUM_LEDS, 5);

      leds[ XY(x, y)]  = CHSV( gHue, 255, 192);

      //increment Hue every 20 ms, this can be adjusted in any pattern
      long currentMillis = millis();
      if (currentMillis - previousMillis2 >= interval2) {
        previousMillis2 = currentMillis;
        gHue++;
      }
    }
    // send the 'leds' array out to the actual LED strip
    FastLED.show();
    // insert a delay to keep the framerate modest
    FastLED.delay(1000 / FRAMES_PER_SECOND);
    FastLED.delay(1000 / FRAMES_PER_SECOND);
    FastLED.delay(1000 / FRAMES_PER_SECOND);
    FastLED.delay(1000 / FRAMES_PER_SECOND);
  }

  //up
  for ( byte x = 0; x < kMatrixWidth - 1; x++) { //19
    for ( byte y = 0; y < kMatrixHeight; y++) { //16
      fadeToBlackBy( leds, NUM_LEDS, 5);

      leds[ XYsafe(x, y)]  = CHSV( gHue, 255, 192);

      //increment Hue every 20 ms, this can be adjusted in any pattern
      long currentMillis = millis();
      if (currentMillis - previousMillis2 >= interval2) {
        previousMillis2 = currentMillis;
        gHue++;
      }
    }
    // send the 'leds' array out to the actual LED strip
    FastLED.show();
    // insert a delay to keep the framerate modest
    FastLED.delay(1000 / FRAMES_PER_SECOND);
    FastLED.delay(1000 / FRAMES_PER_SECOND);
    FastLED.delay(1000 / FRAMES_PER_SECOND);
    FastLED.delay(1000 / FRAMES_PER_SECOND);
  }
}


void downDown()
{
  //down
  for ( byte x = kMatrixWidth; x > 0; x--) { //19
    for ( byte y = 0; y < kMatrixHeight; y++) { //12
      fadeToBlackBy( leds, NUM_LEDS, 5);

      leds[ XYsafe(x - 1, y)] = CHSV( gHue, 255, 192);

      //increment Hue every 20 ms, this can be adjusted in any pattern
      long currentMillis = millis();
      if (currentMillis - previousMillis2 >= interval2) {
        previousMillis2 = currentMillis;
        gHue++;
      }
    }
    // send the 'leds' array out to the actual LED strip
    FastLED.show();
    // insert a delay to keep the framerate modest
    FastLED.delay(1000 / FRAMES_PER_SECOND);
    FastLED.delay(1000 / FRAMES_PER_SECOND);
    //uncomment - to incease the speed of the color transition
    //long currentMillis = millis();
    //if (currentMillis - previousMillis2 >= interval2) {
    //  previousMillis2 = currentMillis;
    //  gHue++;
    //}
    FastLED.delay(1000 / FRAMES_PER_SECOND);
    FastLED.delay(1000 / FRAMES_PER_SECOND);
  }
}

void fading()
{
  //beatsin16 is a function on the FastLED library generating sinwave, (10) is bpm, (0,255) is value range.
  //value range will create the breathing effect

  interval2 = 80; //change hue timing for this animation
  int pos = beatsin16(10, 0, 192); // generating the sinwave
  fill_solid(leds, NUM_LEDS, CHSV( gHue, 255, pos)); // CHSV (hue, saturation, value);
  //EVERY_N_MILLISECONDS(100) {gHue++;}
  // send the 'leds' array out to the actual LED strip
  FastLED.show();
  // insert a delay to keep the framerate modest
  FastLED.delay(1000 / FRAMES_PER_SECOND);

  //increment Hue every 20 ms, this can be adjusted in any pattern
  long currentMillis = millis();
  if (currentMillis - previousMillis2 >= interval2) {
    previousMillis2 = currentMillis;
    gHue++;
  }
}


void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for ( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
  }
}

//int ball_x;
//int ball_y;
//int travel_direction;
void bouncingBall()
{
  if (travel_direction == 1) {
    ball_x = ball_x + 1;
    ball_y = ball_y + 1;
  }
  if (travel_direction == 2) {
    ball_x = ball_x + 1;
    ball_y = ball_y - 1;
  }
  if (travel_direction == 3) {
    ball_x = ball_x - 1;
    ball_y = ball_y + 1;
  }
  if (travel_direction == 4) {
    ball_x = ball_x - 1;
    ball_y = ball_y - 1;
  }


  if (travel_direction == 3 && ball_x <= 0)
    travel_direction = 1;

  if (travel_direction == 4 && ball_x <= 0)
    travel_direction = 2;

  if (travel_direction == 2 && ball_y <= 0)
    travel_direction = 1;

  if (travel_direction == 4 && ball_y <= 0)
    travel_direction = 3;

  if (travel_direction == 1 && ball_x >= kMatrixWidth)
    travel_direction = 3;

  if (travel_direction == 2 && ball_x >= kMatrixWidth)
    travel_direction = 4;

  if (travel_direction == 1 && ball_y >= kMatrixHeight)
    travel_direction = 2;

  if (travel_direction == 3 && ball_y >= kMatrixHeight)
    travel_direction = 4;

  fadeToBlackBy( leds, NUM_LEDS, 20);
  //FastLED.clear();

  leds[ XYsafe(ball_x, ball_y)] = CHSV( gHue, 255, 192);

  //increment Hue every 20 ms, this can be adjusted in any pattern
  long currentMillis = millis();
  if (currentMillis - previousMillis2 >= interval2) {
    previousMillis2 = currentMillis;
    gHue++;
  }

  // send the 'leds' array out to the actual LED strip
  FastLED.show();
  // insert a delay to keep the framerate modest
  FastLED.delay(1000 / FRAMES_PER_SECOND);
  FastLED.delay(1000 / FRAMES_PER_SECOND);
  FastLED.delay(1000 / FRAMES_PER_SECOND);
  FastLED.delay(1000 / FRAMES_PER_SECOND);
  FastLED.delay(1000 / FRAMES_PER_SECOND);
}



void accel_demo()
{
  fadeToBlackBy( leds, NUM_LEDS, 20);

  //Read raw values
  int xRaw = ReadAxis(xInput);
  int x = map(xRaw, 350, 372, 19, 0);

  //Serial.println(xRaw);

  for ( byte y = 0; y < kMatrixHeight; y++) {
    leds[ XYsafe(x, y)]  = CHSV( 125, 255, 255);
  }

  FastLED.show();
  FastLED.delay(1000 / FRAMES_PER_SECOND);
}

// Take samples and return the average
int ReadAxis(int axisPin)
{
  long reading = 0;
  analogRead(axisPin);
  delay(1);
  for (int i = 0; i < sampleSize; i++)
  {
    reading += analogRead(axisPin);
  }
  return reading / sampleSize;
}

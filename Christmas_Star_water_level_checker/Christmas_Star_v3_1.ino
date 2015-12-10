#define waterLevelHighPin 0
#define waterLevelLowPin  1

int ledsRed[] = {
  3, 5, 6, 9, 10, 11, 3
}; // added 3 at end to make rotation look smooth
int ledBlue = 13;
boolean latch = true; // for Blue LED on an doff state
unsigned long timer = 0; //get current time
int pause = 70; // delay speed

void setup()
{
  pinMode (ledBlue, OUTPUT);
  for (int x = 0; x < 6; x++)
  {
    pinMode (ledsRed[x], OUTPUT);
  }
  timer = millis();

  digitalWrite (ledBlue, HIGH);
  for (int x = 0; x < 256; x++) {
    for (int y = 0 ; y < 6; y++) {
      analogWrite (ledsRed[y], x);
    }

    delay(50);
  }

}

void loop() {

  checkWaterLevel(waterLevelLowPin);

  do {
    functionClockWiseAllOn();
  }
  while ((millis() - timer) < 10000);
  timer = millis();

  checkWaterLevel(waterLevelLowPin);
  do {
    functionAntiClockWiseAllOn();
  }
  while ((millis() - timer) < 10000);
  timer = millis();
  checkWaterLevel(waterLevelLowPin);
  do {
    functionChase();
  }
  while ((millis() - timer) < 10000);
  timer = millis();
  checkWaterLevel(waterLevelLowPin);
  do {
    functionFlashhAll();
  }
  while ((millis() - timer) < 10000);
  timer = millis();
  checkWaterLevel(waterLevelLowPin);
  do {
    functionWaveDown();
  }
  while ((millis() - timer) < 10000);
  timer = millis();
  checkWaterLevel(waterLevelLowPin);
  do {
    functionClockWiseAllOn();
    functionClockWiseAllOn();
  }
  while ((millis() - timer) < 10000);
  timer = millis();
  checkWaterLevel(waterLevelLowPin);
  do {
    functionChaseBackwards();
  }
  while ((millis() - timer) < 10000);
  timer = millis();
}

void functionClockWiseAllOn() {
  latch = false;
  for (int x = 0; x < 7; x++) {
    digitalWrite (ledsRed[x], HIGH);
    delay (pause);
  }
  for (int x = 0; x < 7; x++) {
    digitalWrite (ledsRed[x], LOW);
    delay (pause);
  }
  blueled();
}

void functionAntiClockWiseAllOn() {
  latch = false;
  for (int x = 7; x >= 0; x--) {
    digitalWrite (ledsRed[x], HIGH);
    delay (pause);
  }
  for (int x = 7; x >= 0; x--) {
    digitalWrite (ledsRed[x], LOW);
    delay (pause);
  }
  blueled();
}

void blueled () {
  if (latch) {
    digitalWrite (ledBlue, HIGH);
    latch = false;
  }
  else
  {
    digitalWrite (ledBlue, LOW);
    latch = true;
  }
}
void functionChase() {
  int direct = 1;
  int curled = 0;
  int lastled = 0;
  for (int x = 0; x < 7; x++) {
    if (curled == 7) {
      curled = 6;
      direct = -1;
    }
    if (curled == -1) {
      curled = 0;
      direct = 1;
    }
    digitalWrite(ledsRed[curled], HIGH);
    digitalWrite(ledsRed[lastled], LOW);
    lastled = curled;
    curled = curled + direct;
    delay(25);
    blueled();
    delay(25);
    blueled();
  }
}
void functionChaseBackwards() {
  int direct = -1;
  int curled = 7;
  int lastled = 0;
  for (int x = 0; x < 7; x++) {
    // Serial.println (x);

    // Serial.println (curled);
    if (curled == 7) {
      curled = 6;
      // Serial.println (curled);
      direct = -1;
      // Serial.println (direct);
    }
    if (curled == -1) {
      curled = 0;
      direct = 1;
    }
    // Serial.println (curled);
    // Serial.println (direct);
    digitalWrite(ledsRed[curled], HIGH);
    digitalWrite(ledsRed[lastled], LOW);
    lastled = curled;
    curled = curled + direct;
    delay(25);
    blueled();
    delay(25);
    blueled();
  }
}

void functionFlashhAll() {
  for (int x = 7; x >= 0; x--) {
    digitalWrite (ledsRed[x], HIGH);
    blueled();
  }
  delay (pause);
  for (int x = 7; x >= 0; x--) {
    digitalWrite (ledsRed[x], LOW);
    blueled();
  }
  delay (pause);
}

void functionWaveDown() {
  // start top to botton lights on
  digitalWrite (ledsRed[0], HIGH);
  delay (pause);
  digitalWrite (ledsRed[1], HIGH);
  digitalWrite (ledsRed[5], HIGH);
  delay (pause);
  digitalWrite (ledsRed[2], HIGH);
  digitalWrite (ledsRed[4], HIGH);
  delay (pause);
  digitalWrite (ledsRed[3], HIGH);
  delay (pause);
  // start to turn off lights bottom to top
  digitalWrite (ledsRed[3], LOW);
  delay (pause);
  digitalWrite (ledsRed[2], LOW);
  digitalWrite (ledsRed[4], LOW);
  delay (pause);
  digitalWrite (ledsRed[1], LOW);
  digitalWrite (ledsRed[5], LOW);
  delay (pause);
  digitalWrite (ledsRed[0], LOW);
  delay (pause);

}

void checkWaterLevel(int checkPin) {
  if (getWaterLevel(checkPin) < 400)
  {
    noWater();

  }

}

int getWaterLevel(int checkPin) {
  return analogRead(checkPin);
}

void noWater() {

  for (int y = 0 ; y < 6; y++) {
    digitalWrite (ledsRed[y], HIGH);
  }

  do {
    digitalWrite (ledBlue, HIGH);
    delay(1000);
    digitalWrite (ledBlue, LOW);
    delay(1000);
  }
  while (getWaterLevel(waterLevelHighPin) < 400);

}


// http://blog.riyas.org/2013/12/online-led-matrix-font-generator-with.html for Matrix Code
// https://www.sparkfun.com/products/12708 for RTC

unsigned char i;

/*Port Definitions*/
int Max7219_pinCLK = 10;
int Max7219_pinCS = 9;
int Max7219_pinDIN = 8;

//RTC
#include <Wire.h>
const int DS1307 = 0x68; // Address of DS1307 see data sheets
byte second = 0;
byte minute = 0;
byte hour = 0;
byte weekday = 0;
byte monthday = 0;
byte month = 0;
byte year = 0;
byte five_minutes = 0;
byte hour_selected = 0;

//Words for minutes past and to
unsigned char time_1ed[12][8]={
  { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 }  , //on the hour 
  { 0x00,0xd4,0x1e,0x00,0x00,0x00,0x00,0x00 }  ,//5 past
  { 0x2c,0x00,0x1e,0x00,0x00,0x00,0x00,0x00 }  ,//10 past
  { 0x00,0xef,0x1e,0x00,0x00,0x00,0x00,0x00 }  ,//15 past
  { 0x3f,0x00,0x1e,0x00,0x00,0x00,0x00,0x00 }  ,//20 past
  { 0x3f,0xd4,0x1e,0x00,0x00,0x00,0x00,0x00 }  ,//25 past
  { 0xc0,0x00,0xde,0x00,0x00,0x00,0x00,0x00 }  ,//half past
  { 0x3f,0xd4,0x03,0x00,0x00,0x00,0x00,0x00 }  ,//25 to
  { 0x3f,0x00,0x03,0x00,0x00,0x00,0x00,0x00 }  ,//20 to
  { 0x00,0xef,0x03,0x00,0x00,0x00,0x00,0x00 }  ,//15 to
  { 0x2c,0x00,0x03,0x00,0x00,0x00,0x00,0x00 }  ,//10 to
  { 0x00,0xd4,0x03,0x00,0x00,0x00,0x00,0x00 }   // 5 to

};

// Words for the HOUR
unsigned char hour_led[12][8]={
  { 0x00,0x00,0x00,0x00,0xe0,0x00,0x00,0x00 }  ,// one
  { 0x00,0x00,0x00,0x00,0x10,0x40,0x40,0x00 }  ,// two
  { 0x00,0x00,0x00,0x00,0x1f,0x00,0x00,0x00 }  ,// three
  { 0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0x00 }  ,// four
  { 0x00,0x00,0x00,0x00,0x00,0x00,0x0f,0x00 }  ,// five
  { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xe0 }  ,// six
  { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1f }  ,//seven
  { 0x00,0x00,0x00,0x1f,0x00,0x00,0x00,0x00 }  ,// eight
  { 0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00 }  , //nine
  { 0x00,0x00,0x00,0x01,0x01,0x01,0x00,0x00 }  , //ten
  { 0x00,0x00,0x00,0x00,0x00,0x3f,0x00,0x00 }  ,// eleven
  { 0x00,0x00,0x00,0x00,0x10,0x76,0x00,0x00 }   // twelve
};

void Write_Max7219_byte(unsigned char DATA) 
{   
  unsigned char i;
  digitalWrite(Max7219_pinCS,LOW);		
  for(i=8;i>=1;i--)
  {		  
    digitalWrite(Max7219_pinCLK,LOW);
    digitalWrite(Max7219_pinDIN,DATA&0x80);// Extracting a bit data
    DATA = DATA<<1;
    digitalWrite(Max7219_pinCLK,HIGH);
  }                                 
}

void Write_Max7219(unsigned char address,unsigned char dat)
{
  digitalWrite(Max7219_pinCS,LOW);
  Write_Max7219_byte(address);           //address，code of LED
  Write_Max7219_byte(dat);               //data，figure on LED 
  digitalWrite(Max7219_pinCS,HIGH);
}

void Init_MAX7219(void)
{
  Write_Max7219(0x09, 0x00);       //decoding ：BCD
  Write_Max7219(0x0a, 0x03);       //brightness 
  Write_Max7219(0x0b, 0x07);       //scanlimit；8 LEDs
  Write_Max7219(0x0c, 0x01);       //power-down mode：0，normal mode：1
  Write_Max7219(0x0f, 0x00);       //test display：1；EOT，display：0
}

void setup()
{
   Serial.begin(9600);
  // Start wire for RTL
  Wire.begin(); 

  // configure 8x8 led matrixusing MAX 7219
  pinMode(Max7219_pinCLK,OUTPUT);
  pinMode(Max7219_pinCS,OUTPUT);
  pinMode(Max7219_pinDIN,OUTPUT);
  delay(50);
  Init_MAX7219();
}

void loop()
{



  readTime(); //Read time from RTL

  if (minute > 34){ //Check if past 30 minutes to add 1 hour for TO
    hour++;
  }
    if (hour > 12) {
    hour -= 12;
  }
  // Convert 5 minutes increments to array number for each word
  if (minute >=0 && minute <5){
    five_minutes = 1;
  }
  else if (minute >=5 && minute <10){
    five_minutes = 2;
  }
  else if (minute >=10 && minute <15){
    five_minutes = 3;
  }
  else if (minute >=15 && minute <20){
    five_minutes = 4;
  }
  else if (minute >=20 && minute <25){
    five_minutes = 5;
  }
  else if (minute >=25 && minute <30){
    five_minutes = 6;
  }
  else if (minute >=30 && minute <35){
    five_minutes = 7;
  }
  else if (minute >=35 && minute <40){
    five_minutes = 8;
  }
  else if (minute >=40 && minute <45){
    five_minutes = 9;
  }
  else if (minute >=45 && minute <50){
    five_minutes = 10;
  }
  else if (minute >=50 && minute <55){
    five_minutes = 11;
  }
  else if (minute >=55 && minute <=59){
    five_minutes = 12;
  }

  //Display word on 8x8 LED matrix
  // Add together the top half of the matrix to the lower half
  for(i=1;i<9;i++)
    Write_Max7219(i,time_1ed[five_minutes-1][i-1]+ hour_led[hour-1][i-1]);
  delay(1000);
}


// Read time from RTL chip
void readTime() {
  Wire.beginTransmission(DS1307);
  Wire.write(byte(0));
  Wire.endTransmission();
  Wire.requestFrom(DS1307, 7);
  second = bcdToDec(Wire.read());
  minute = bcdToDec(Wire.read());
  hour = bcdToDec(Wire.read());
  weekday = bcdToDec(Wire.read());
  monthday = bcdToDec(Wire.read());
  month = bcdToDec(Wire.read());
  year = bcdToDec(Wire.read());
}

byte decToBcd(byte val) {
  return ((val/10*16) + (val%10));
}
byte bcdToDec(byte val) {
  return ((val/16*10) + (val%16));
}

// ---- END ----



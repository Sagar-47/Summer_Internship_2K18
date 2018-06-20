// include the library header
// no font headers have to be included
#include <openGLCD.h>

// initialize the library with the numbers of the interface pins
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


#define S2 2
#define S3 3
#define sensorOut 12
#define sensorOut_1 13
 double frequency = 0;
   double redavg     =0;
   double blueavg    =0;
   double greenavg   =0;
  double redavg_1   =0;
   double blueavg_1  =0;
   double greenavg_1 =0;
int s=0;
void setup() {
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  pinMode(sensorOut_1 , INPUT);
//  pinMode(led, OUTPUT);
  
  // Setting frequency-scaling to 20%

  Serial.begin(9600);

  // Initialize the GLCD 
  GLCD.Init();

 // Select the font for the default text area
  GLCD.SelectFont(System5x7);
  // Print a message to the LCD.
  
  
}
void loop() {
   s=s+1;
  // Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
 frequency = pulseIn(sensorOut, LOW);
 redavg = redavg + frequency;

  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  greenavg = greenavg + frequency;

// Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  blueavg = blueavg + frequency;

 // Setting red filtered photodiode_1 to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
 frequency = pulseIn(sensorOut_1, LOW);
 redavg_1 = redavg_1 + frequency;

  // Setting Green filtered photodiode_1 to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut_1, LOW);
  greenavg_1 = greenavg_1 + frequency;

// Setting Blue filtered photodiode_1 to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut_1, LOW);
  blueavg_1 = blueavg_1 + frequency;

 
  if(s == 100)
  {
    delay(10);
    Serial.print("R = ");
    Serial.print(" ");
    Serial.print(redavg/100);
    Serial.print(" ");
    Serial.print("G = ");
    Serial.print(" ");
    Serial.print(greenavg/100);
    GLCD.CursorTo(0, 0);
    GLCD.print("G = ");
    GLCD.print(greenavg/100);
    Serial.print(" ");
    Serial.print("B = ");
    Serial.print(blueavg/100);
    Serial.print(" ");
    Serial.println(" ");
    
    Serial.print("R_1 = ");
    Serial.print(" ");
    Serial.print(redavg_1/100);
    Serial.print(" ");
    Serial.print("G_1 = ");
    Serial.print(" ");
    Serial.print(greenavg_1/100);
    GLCD.CursorTo(0, 1);
    GLCD.print("G_1 = ");
    GLCD.print(greenavg_1/100);
    Serial.print(" ");
    Serial.print("B_1 = ");
    Serial.print(blueavg_1/100);
    Serial.print(" ");
    Serial.println(" ");
    Serial.println();
    s=0;   
   redavg =0;
   blueavg=0;
   greenavg =0;
   redavg_1 =0;
   blueavg_1=0;
   greenavg_1 =0;
     // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  }
  
}

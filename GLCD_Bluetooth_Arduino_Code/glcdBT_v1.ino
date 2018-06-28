#include <openGLCD.h>
#define sensorOut_1 12
#define sensorOut_2 13

 String ID="";
 String temp="";
 double greenavg_1 = 0;
 double greenavg_2 = 0;
 int i, c_1 =0, c_2=0;
 int a[100],b[100];
 double mean_1 = 0.0, mean_2 = 0.0, stddev_1 = 0.0 , stddev_2 = 0.0;


  void setup() {
  pinMode(sensorOut_1, INPUT);
  pinMode(sensorOut_2 , INPUT);
  Serial.begin(9600);
 GLCD.Init();

 // Select the font for the default text area
GLCD.SelectFont(System5x7);
  // Print a message to the LCD.
}
void loop()
{
//    while(Serial.available()==0)
//{
//
//}

//delay(500);


    for (i=0; i<100; i++){
        a[i] = pulseIn(sensorOut_1, LOW);
        b[i] = pulseIn(sensorOut_2, LOW);
        mean_1 += a[i];
        mean_2 += b[i];
    }
    mean_1 /= 100;
    mean_2 /= 100;
    
    for(i = 0; i < 100; i++)
    {
        stddev_1 += pow(a[i] - mean_1,2);
        stddev_2 += pow(b[i] - mean_2,2);
    }
    stddev_1 /= 100;
    stddev_2 /= 100;
    stddev_1 = pow(stddev_1,0.5);
    stddev_2 = pow(stddev_2,0.5);
    for (i=0; i<100; i++)
    {
        if (a[i]>=(mean_1-stddev_1) && a[i]<=(mean_1+stddev_1))
        {
        greenavg_1 += a[i]; 
        c_1++;
        }
        if (b[i]>=(mean_2 - stddev_2) && b[i]<=(mean_2 + stddev_2))
        {
        greenavg_2 += b[i]; 
        c_2++;
        }
    }
    delay(100);
    GLCD.ClearScreen();
    Serial.print(greenavg_1/c_1);
    Serial.print("|");
    Serial.print(greenavg_2/c_2);

  if (Serial.available() != 0){
  ID = Serial.readString();
    temp = ID;
  }

     GLCD.CursorTo(0, 0);
    GLCD.print("ID= ");
    GLCD.CursorTo(4, 0);
    GLCD.print(temp);
    GLCD.CursorTo(0, 1);
    GLCD.print("G_1 = ");
    GLCD.print(greenavg_1/c_1);    
    GLCD.CursorTo(0, 2);
    GLCD.print("G_2 = ");
    GLCD.print(greenavg_2/c_2);  
    
     
    c_1 = 0;
    c_2 = 0;
    greenavg_1 = 0;
    greenavg_2 = 0;
    mean_1 = 0.0;
    mean_2 = 0.0;
    stddev_1 = 0.0;
    stddev_2 = 0.0;
    
}

#include <openGLCD.h>
#define sensorOut_1 12
#define S2 2
#define S3 3
  int seconds = 0;
int minutes = 0;
 String rec = "";
 String disp[3];
 String temp[3];
 double greenavg_1 = 0;
 int i, c_1 =0;
 int c=0;
 int a[100];
 double mean_1 = 0.0, stddev_1 = 0.0;


  void setup() {
  pinMode(sensorOut_1, INPUT);
   pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);

  Serial.begin(9600);
 GLCD.Init();

 // Select the font for the default text area
GLCD.SelectFont(System5x7);
  // Print a message to the LCD.
}
void loop()
{
    for (i=0; i<100; i++){
        a[i] = pulseIn(sensorOut_1, LOW);
        mean_1 += a[i];
    }
    mean_1 /= 100;    
    for(i = 0; i < 100; i++)
    {
        stddev_1 += pow(a[i] - mean_1,2);
    }
    stddev_1 /= 100;
    stddev_1 = pow(stddev_1,0.5);
    for (i=0; i<100; i++)
    {
        if (a[i]>=(mean_1-stddev_1) && a[i]<=(mean_1+stddev_1))
        {
        greenavg_1 += a[i]; 
        c_1++;
        }
    }
    delay(1000);
    GLCD.ClearScreen();
    Serial.print(greenavg_1/c_1);
  if (Serial.available() != 0){
  rec = Serial.readString();
  for (int j=0; j<rec.length();j++)
  {
    if (rec.charAt(j)!= '|'){
      disp[c] = disp[c] + rec.charAt(j);
    }
    else{
      c++;
    }
  }
    temp[0] = disp[0];
    temp[1] = disp[1];
    temp[2] = disp[2];
    
  }

    GLCD.CursorTo(0, 0);
    GLCD.print("ID= ");
    GLCD.print(temp[0]);
    GLCD.CursorTo(0, 1);
    GLCD.print("NAME= ");
    GLCD.print(temp[1]);
    GLCD.CursorTo(0, 3);
    GLCD.print("OUTPUT = ");
    GLCD.print(greenavg_1/c_1);
    GLCD.CursorTo(0, 4);
    GLCD.print("TYPHOID : ");
     if (greenavg_1/c_1 > 4000)
     {
        GLCD.print("NO");
     }
     else if (greenavg_1/c_1 <= 4000)
     {
      GLCD.print("YES");
     }

     
    
    GLCD.CursorTo(9,6);
    GLCD.print(temp[2]); 
     
     GLCD.CursorTo(7, 7);
  seconds = millis()/1000 - 60*minutes;
  if (seconds > 59){
    minutes = minutes + 1;
    } 
  // print the number of seconds since reset:
  GLCD.print("RUN TIME=");
  if (minutes < 10){
   GLCD.print("0");
  GLCD.print(minutes);
    }
    else GLCD.print(minutes);
    GLCD.print(":");
  if (seconds < 10){
    GLCD.print("0");
  GLCD.print(seconds);
    }
    else GLCD.print(seconds);

   disp[0] ="";
   disp[1]="";
   disp[2]="";
    c=0;  
    c_1 = 0;
    greenavg_1 = 0;
    mean_1 = 0.0;
    stddev_1 = 0.0;
}

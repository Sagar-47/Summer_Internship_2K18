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
 double threshold = 2000;       // Default value of Threshold for declaration of Typhoid

  void setup() {
  pinMode(sensorOut_1, INPUT); // To receive data from detector
  pinMode(S2, OUTPUT);          
  pinMode(S3, OUTPUT);
  digitalWrite(S2,HIGH);      // To operate detector in Green Wavelength
  digitalWrite(S3,HIGH);      // To operate detector in Green Wavelength

  Serial.begin(9600);         // Setting BAUD Rate to communicate with GLCD and Bluetooth Module
 GLCD.Init();                 // To iniatialize Graphic LCD Screen
GLCD.SelectFont(System5x7);   // Setting Font style and size

}
void loop()
{
    for (i=0; i<100; i++){
        a[i] = pulseIn(sensorOut_1, LOW);
        mean_1 += a[i];
    }
    mean_1 /= 100;                      // To compute mean of 100 readings
    for(i = 0; i < 100; i++)
    {
        stddev_1 += pow(a[i] - mean_1,2);
    }
    stddev_1 /= 100;
    stddev_1 = pow(stddev_1,0.5);       // To compute standard deviation of 100 readings
    for (i=0; i<100; i++)
    {
        if (a[i]>=(mean_1-stddev_1) && a[i]<=(mean_1+stddev_1))
        {
        greenavg_1 += a[i];             // To skip values lying outside mean of 100 readings
        c_1++;
        }
    }
    delay(1000);
    GLCD.ClearScreen();                 // To Clear the Graphic LCD Screen
    
    Serial.print(greenavg_1/c_1);       // Send Output data to Bluetooth Module
    
  if (Serial.available() != 0){         // To check if an input is recieved from Bluetooth Module
  rec = Serial.readString();            // Collect the data received from Bluetooth Module and store it in rec
  if (rec.charAt(0)!= '{' && rec.charAt(1)!= '}' ){ // If the data starts with "{}" the value of threshold will be changed 
   threshold = (rec.substring(2)).toInt();   // To take string after "{}", convert to int and store in threshold
  }
  
  else{
    for (int j=0; j<rec.length();j++)
      {
         if (rec.charAt(j)!= '|'){           // Storing Name, ID, and Date separately, which arer separated by a Vertical Bar '|'
         disp[c] = disp[c] + rec.charAt(j);
      }
    else{
      c++;
    }
  }
  }
  
  
    temp[0] = disp[0];                    // Store ID
    temp[1] = disp[1];                    // Store Name
    temp[2] = disp[2];                    // Store Date
    
  }

    GLCD.CursorTo(0, 0);                  // Moving Cursor to required location on Graphic LCD
    GLCD.print("ID= ");                   // To print on Graphic LCD
    GLCD.print(temp[0]);                  
    GLCD.CursorTo(0, 1);
    GLCD.print("NAME= ");
    GLCD.print(temp[1]);
    GLCD.CursorTo(0, 3);
    GLCD.print("TYPHOID : ");
     if (greenavg_1/c_1 > threshold)           // To judge for presence of Typhoid, an output above 2000(Threshold) is declared to have no Typhi
     {
        GLCD.print("NO");
        Serial.print("|NO|");                  // Sending value of Threshold to Bluetooth Module
     }
     else if (greenavg_1/c_1 <= threshold)     // To judge for presence of Typhoid, an output below 2000(Threshold) is declared to have Typhi
     {
      GLCD.print("YES");
      Serial.print("|YES|");                   // Sending value of Threshold to Bluetooth Module
     }
    Serial.print(threshold);                   // Sending value of Threshold to Bluetooth Module
    
    GLCD.CursorTo(9,6);
    GLCD.print(temp[2]);                  // Print Date
     
     GLCD.CursorTo(7, 7);
  seconds = millis()/1000 - 60*minutes;
  if (seconds > 59){
    minutes = minutes + 1;
    }                          // To calculate number of minutes and seconds since reset
  GLCD.print("RUN TIME=");
  if (minutes < 10){
   GLCD.print("0");
  GLCD.print(minutes);
    }
    else GLCD.print(minutes);  // print the number of minutes since reset
    GLCD.print(":");
  if (seconds < 10){
    GLCD.print("0");
  GLCD.print(seconds);          // print the number of seconds since reset
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

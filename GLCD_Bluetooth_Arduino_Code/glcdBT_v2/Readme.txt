Working- 
Displays presence of Typhoid - Yes/No and Runtime from reset
Once connected to Bluetooth, GLCD displays Patient ID, Name and Date from data received from App
The Output of Device(used to check Typhoid) and Current Threshold value is sent to App alongwith data about presence of Typhoid
The Value of Threshold is changed from App if received, default value is 2000
App later stores the Output in a CSV file

Precautions - 
The Output of device(green_avg) is inverted, i.e. Higher concentration of green results in smaller value of output
The value of Threshold for declaration of presence or absence of Typhoid is Hardcoded at 2000, Can be Changed from App




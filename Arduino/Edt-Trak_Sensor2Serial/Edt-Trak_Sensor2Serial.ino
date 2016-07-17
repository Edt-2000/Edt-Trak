// Define analog pins + UTP colors + GameTrak internal wire colors
#define Left_X A2 // Blue / - yellow left
#define Left_Y A1 // Orange / - orange left
#define Left_Z A0 // Green / - red left

#define Right_X A5 // Brown / - yellow right
#define Right_Y A4 // Orange - orange right
#define Right_Z A3 // Green - red right

// Feedback LED
#define LED 13

// Define value variables initial values
int Left_X_Val = 0;
int Left_Y_Val = 0;
int Left_Z_Val = 0;

int Right_X_Val = 0;
int Right_Y_Val = 0;
int Right_Z_Val = 0;

// Minimal value for Z axis, otherwise send 0's or no values at all (if GameTrak is in resting position, don't send anything)
int gate = 100;
bool active = false;

// Values are divided with a -, instead of println's we give an endpoint :
String divider = "-";
String endPoint = ":";

// Start serial as fast as we can
void setup() {
  Serial.begin(1000000);
  pinMode(LED, OUTPUT);
}

void loop() {
  // Read the values of each pin
  Left_X_Val = analogRead(Left_X);
  Left_Y_Val = 1023 - analogRead(Left_Y);
  Left_Z_Val = analogRead(Left_Z);
  Right_X_Val = analogRead(Right_X);
  Right_Y_Val = analogRead(Right_Y);
  Right_Z_Val = analogRead(Right_Z);
  // Only send when one of the X values is higher than 100
  if(Left_Z_Val > gate || Right_Z_Val > gate) {
    active = true;
    // LED feedback
    digitalWrite(LED, HIGH);
    // When below gate, set to 0
    if(Left_Z_Val <= gate) {
      Left_X_Val = 0;
      Left_Y_Val = 0;
      Left_Z_Val = 0;
    }
    // When below 100, set to 0
    if(Right_Z_Val <= gate) {
      Right_X_Val = 0;
      Right_Y_Val = 0;
      Right_Z_Val = 0;
    }
    // Print to a line seperated by divider
    Serial.print(
      Left_X_Val + 
      divider + 
      Left_Y_Val + 
      divider + 
      Left_Z_Val + 
      divider + 
      Right_X_Val + 
      divider + 
      Right_Y_Val + 
      divider + 
      Right_Z_Val + 
      endPoint
    );
  } else {
    if(active) {
      // Send a last 0 0 0 0 0 0 message
      Serial.print(0 + divider + 0 + divider + 0 + divider + 0 + divider + 0 + divider + 0 + endPoint);
      active = false;
    }
    // Not sending, LED to LOW
    digitalWrite(LED, LOW);
  }
}

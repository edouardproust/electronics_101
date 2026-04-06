#include "colors.h"

#define ON 50          // LED intensity when ON
#define OFF 0          // LED intensity when OFF
#define DEBOUNCE_DELAY 50 // ms debounce delay

// Define buttons + LEDs
Color colors[] = {
  {5, 13, OFF, HIGH, HIGH, 0},   // red
  {19, 12, OFF, HIGH, HIGH, 0},  // yellow
  {22, 14, OFF, HIGH, HIGH, 0}   // blue
};

int n = sizeof(colors) / sizeof(colors[0]);

void setup() 
{
  for (int i = 0; i < n; ++i) {
    pinMode(colors[i].ledPin, OUTPUT);
    analogWrite(colors[i].ledPin, colors[i].ledIntensity);
    pinMode(colors[i].buttonPin, INPUT_PULLUP);

    // Initialize states
    colors[i].lastButtonState = HIGH; // raw state
    colors[i].stableState = HIGH;     // stable state for debounce
    colors[i].lastDebounceTime = 0;
  }
}

// Main loop
void loop() {
  for (int i = 0; i < n; ++i) {
    if (isButtonPressed(colors[i])) {
      toggleLed(colors[i]);
    }
  }
}

// Debounce function: returns true if button is pressed and stable
bool isButtonPressed(Color &c) {
  int reading = digitalRead(c.buttonPin);

  // If state changed → reset timer
  if (reading != c.lastButtonState) {
    c.lastDebounceTime = millis();
  }

  // If state stable long enough
  if ((millis() - c.lastDebounceTime) > DEBOUNCE_DELAY) {

    // Detect falling edge (button press)
    if (reading == LOW && c.stableState == HIGH) {
      c.stableState = LOW;           // update stable state
      c.lastButtonState = reading;   // update raw state
      return true;                   // stable press detected
    }

    // Detect rising edge (button release)
    else if (reading == HIGH && c.stableState == LOW) {
      c.stableState = HIGH;          // update stable state
    }
  }

  c.lastButtonState = reading;       // update raw state
  return false;                      // no stable press
}

// Toggle LED function
void toggleLed(Color &c) {
  c.ledIntensity = (c.ledIntensity == ON) ? OFF : ON;
  analogWrite(c.ledPin, c.ledIntensity);
}
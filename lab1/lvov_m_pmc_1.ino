const int buttonPin = 7;   // Button pin
const int ledPin1 = 8;     // First LED
const int ledPin2 = 9;     // Second LED

bool isBlinking = false;   // Blinking status
bool lastButtonState = LOW;
unsigned long previousMillis = 0;
const long interval = 500; // Blinking interval (500 ms)

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Configure the button with a pull-up resistor
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
}

void loop() {
  bool currentButtonState = digitalRead(buttonPin);

  // Button press handling (state change)
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    isBlinking = !isBlinking; // Toggle blinking state
    delay(50);               // Debounce delay
  }
  lastButtonState = currentButtonState;

  // Blinking logic
  if (isBlinking) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;

      // Alternate the state of LEDs
      if (digitalRead(ledPin1) == LOW) {
        digitalWrite(ledPin1, HIGH);
        digitalWrite(ledPin2, LOW);
      } else {
        digitalWrite(ledPin1, LOW);
        digitalWrite(ledPin2, HIGH);
      }
    }
  } else {
    // If blinking is off, turn off both LEDs
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
  }
}

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pushbutton pin
const int buttonPin = 6;

// Message to be scrolled
const char message[] = "Christmas is about this: JOHN 3:16.   "; // Add spaces for smoother wrap-around

// Interval for scrolling in milliseconds
const unsigned long scrollInterval = 700; // Fixed scrolling interval

// Length of the message
int messageLength;

// Current position of scrolling
int scrollPosition = 0;

void setup() {
  // Initialize the LCD
  lcd.init();
  
  // Turn on the backlight
  lcd.backlight();
  
  // Print a message to the LCD
  lcd.setCursor(0, 0);
  lcd.print(message);
  
  messageLength = strlen(message);
  
  // Initialize the button pin as input
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // Read the current state of the button
  int buttonState = digitalRead(buttonPin);

  // Check if the button is pressed
  if (buttonState == LOW) {
    static unsigned long lastScrollTime = 0;
    unsigned long currentMillis = millis();

    // Check if it's time to update the scroll position
    if (currentMillis - lastScrollTime >= scrollInterval) {
      lastScrollTime = currentMillis;

      // Clear the display
      lcd.clear();

      // Display the scrolling message
      for (int i = 0; i < 16; i++) {
        int charIndex = (scrollPosition + i) % messageLength;
        lcd.setCursor(i, 0);
        lcd.print(message[charIndex]);
      }

      // Increment the scroll position
      scrollPosition = (scrollPosition + 1) % messageLength;
    }
  }
}

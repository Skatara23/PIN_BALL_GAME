// Pin definitions using GPIO numbers directly for the first encoder
#define CLK_PIN 4  // GPIO4 (D2)
#define DT_PIN 0   // GPIO0 (D3)

// Pin definitions for the second encoder
#define CLK_PIN_2 5  // GPIO5 (D1)
#define DT_PIN_2 6   // GPIO6 (D6)

int encoderPos = 0;  // Variable to store the position of the first encoder
int encoderPos2 = 0;  // Variable to store the position of the second encoder

int lastCLKState = LOW;  // Last state of the CLK pin for the first encoder
int lastCLKState2 = LOW;  // Last state of the CLK pin for the second encoder
int currentCLKState;  // Current state of the CLK pin for the first encoder
int currentCLKState2;  // Current state of the CLK pin for the second encoder

// Timing variables
unsigned long previousMillis = 0;  // Store the last time a value was sent
const long interval = 16;  // Interval to send data (16 ms)

void setup() {
  // Start the serial monitor at 115200 baud rate
  Serial.begin(115200);

  // Set the encoder pins as input for the first encoder
  pinMode(CLK_PIN, INPUT);
  pinMode(DT_PIN, INPUT);

  // Set the encoder pins as input for the second encoder
  pinMode(CLK_PIN_2, INPUT);
  pinMode(DT_PIN_2, INPUT);

  // Initial reading to clear up any initial state
  lastCLKState = digitalRead(CLK_PIN);
  lastCLKState2 = digitalRead(CLK_PIN_2);

  Serial.println("Rotary Encoder Test");
}

void loop() {
  // Read the current state of the CLK pins for both encoders
  currentCLKState = digitalRead(CLK_PIN);
  currentCLKState2 = digitalRead(CLK_PIN_2);

  // Logic for the first encoder
  if (currentCLKState != lastCLKState) {
    if (digitalRead(DT_PIN) != currentCLKState) {
      encoderPos++;  // Clockwise rotation
    } else {
      encoderPos--;  // Counterclockwise rotation
    }
    lastCLKState = currentCLKState;  // Update last state
  }

  // Logic for the second encoder
  if (currentCLKState2 != lastCLKState2) {
    if (digitalRead(DT_PIN_2) != currentCLKState2) {
      encoderPos2++;  // Clockwise rotation
    } else {
      encoderPos2--;  // Counterclockwise rotation
    }
    lastCLKState2 = currentCLKState2;  // Update last state
  }

  // Check if 16 ms have passed to send the values to Serial Monitor
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // Save the last time a value was sent
    previousMillis = currentMillis;

    // Print the current positions of both encoders in the format (value1, value2)
    Serial.print("(");
    Serial.print(encoderPos);  // Value of the first encoder
    Serial.print(", ");
    Serial.print(encoderPos2);  // Value of the second encoder
    Serial.println(")");
  }
}

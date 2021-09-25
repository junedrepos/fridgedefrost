//1. When on load standy led and warmer
//2. When interrupt pressed, switch cook led and load heater element.
//3. When threshold temp crossed, off heater off cook led, load standby led and warmer
int intPin0 = 2;
int intPin1 = 3;
int opPin = 1;
int ledPina = 9;
int ledPinb = 10;
int ledPinc = 11;
int ledPind = 12;
int ledPine = 13;
int ledPinf = A0;
int ledPing = A1;
int speakerPin = A5;
int relayPin = A4;
int inPin = A4;
volatile unsigned long counter = 0;
volatile int defrostStatus = 0;
volatile int defrostMinute = 25; //defrost minute time
void setup() {
  pinMode(intPin0, INPUT_PULLUP);//interrupt defrost pin
  pinMode(intPin1, INPUT_PULLUP);//interrupt defrost pin
  attachInterrupt(digitalPinToInterrupt(intPin0), defrost, RISING);
  attachInterrupt(digitalPinToInterrupt(intPin1), defrost, RISING);
  pinMode(3, OUTPUT);
  pinMode(opPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(ledPina, OUTPUT);
  pinMode(ledPinb, OUTPUT);
  pinMode(ledPinc, OUTPUT);
  pinMode(ledPind, OUTPUT);
  pinMode(ledPine, OUTPUT);
  pinMode(ledPinf, OUTPUT);
  pinMode(ledPing, OUTPUT);
  pinMode(relayPin, OUTPUT);
}
void defrost() {
  if (isPressed()) {
    toggle();
  }
}
void doDefrost() {
  int toneCounter = 0;
  if (defrostStatus == 1) {
    allOn();
    while (counter < ((unsigned long)defrostMinute * 60UL * 100UL)) {
      if (toneCounter == 0) {
        tone(speakerPin, 5000, 500);
      }
      toneCounter++;
      if (toneCounter == 50) {
        noTone(speakerPin);
      }
      if (toneCounter > 3000) {
        toneCounter = 0;
      }
      delay(10);
      if (defrostStatus == 0) {
        break;
      }
      counter++;
    }
    counter=0;
    defrostStatus = 0;
    allOf();
  } else {
    allOf();
  }

}
void toggle() {
  counter=0;
  if (defrostStatus == 0) {
    defrostStatus = 1;
  } else {
    defrostStatus = 0;
  }
}
boolean isPressed() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > 500) {
    tone(speakerPin, 1000, 100);
    return true;
  }
  return false;
}
void loop() {
doDefrost();
}
void allOn() {
  boolean stat = true;
  digitalWrite(ledPina, stat);
  digitalWrite(ledPinb, stat);
  digitalWrite(ledPinc, stat);
  digitalWrite(ledPind, stat);
  digitalWrite(ledPine, stat);
  digitalWrite(ledPinf, stat);
  digitalWrite(ledPing, stat);
  digitalWrite(relayPin, stat);
}
void allOf() {
  boolean stat = false;
  digitalWrite(ledPina, stat);
  digitalWrite(ledPinb, stat);
  digitalWrite(ledPinc, stat);
  digitalWrite(ledPind, stat);
  digitalWrite(ledPine, stat);
  digitalWrite(ledPinf, stat);
  digitalWrite(ledPing, stat);
  digitalWrite(relayPin, stat);
}

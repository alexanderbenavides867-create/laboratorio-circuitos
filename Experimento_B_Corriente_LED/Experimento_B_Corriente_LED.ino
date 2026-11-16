/*
  Experimento_B_Corriente_LED.ino
  Experimento B: corriente en el LED.
  Mantiene encendido un LED rojo (con resistencia de 220 ohm a GND) con digitalWrite().
  Medir Vpin (pin-GND) y VR (extremos de la resistencia) con el multimetro.
  Para el Arduino UNO use el mismo programa cambiando PIN_LED a un pin digital (p. ej. 8).
*/

const uint8_t PIN_LED = 18;           // ESP32: GPIO 18

void setup() {
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, HIGH);
}

void loop() {
}

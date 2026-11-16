/*
  Experimento_C_V1_Delay.ino
  Experimento C, version V1: parpadeo con delay(500) y SIN antirrebote.
  Cuenta las pulsaciones detectadas (flanco 0 -> 1) y muestra el contador al aumentar.
  Boton: GPIO 4 con pull-down externa de 10 kohm. LED: GPIO 18..23.
  Monitor serie: 115200 baudios.
*/

const uint8_t LEDS[5] = {18, 19, 21, 22, 23};
const uint8_t PIN_BOTON = 4;

bool botonPrevio = false;
unsigned int contador = 0;

void todosLeds(bool nivel) {
  for (uint8_t i = 0; i < 5; i++) digitalWrite(LEDS[i], nivel);
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_BOTON, INPUT);
  for (uint8_t i = 0; i < 5; i++) pinMode(LEDS[i], OUTPUT);
}

void loop() {
  bool boton = digitalRead(PIN_BOTON);
  if (boton && !botonPrevio) {        // flanco ascendente, sin antirrebote
    contador++;
    Serial.print("Pulsaciones: ");
    Serial.println(contador);
  }
  botonPrevio = boton;

  todosLeds(HIGH);
  delay(250);                          // funcion bloqueante: el boton no se lee
  todosLeds(LOW);
  delay(250);                          // ciclo completo = 500 ms
}

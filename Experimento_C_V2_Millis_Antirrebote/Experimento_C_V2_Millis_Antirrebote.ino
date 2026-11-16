/*
  Experimento_C_V2_Millis_Antirrebote.ino
  Experimento C, version V2: parpadeo de 500 ms con millis() y antirrebote de 50 ms.
  Cuenta las pulsaciones detectadas y muestra el contador al aumentar.
  Boton: GPIO 4 con pull-down externa de 10 kohm. LED: GPIO 18..23.
  Monitor serie: 115200 baudios.
*/

const uint8_t LEDS[5] = {18, 19, 21, 22, 23};
const uint8_t PIN_BOTON = 4;
const unsigned long INTERVALO = 500;       // ms
const unsigned long T_ANTIRREBOTE = 50;    // ms

bool botonPrevio = false;
bool ledsEncendidos = false;
unsigned int contador = 0;
unsigned long tAnterior = 0;
unsigned long tUltimaPulsacion = 0;

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
  if (boton && !botonPrevio && (millis() - tUltimaPulsacion >= T_ANTIRREBOTE)) {
    tUltimaPulsacion = millis();
    contador++;
    Serial.print("Pulsaciones: ");
    Serial.println(contador);
  }
  botonPrevio = boton;

  if (millis() - tAnterior >= INTERVALO) {
    tAnterior = millis();
    ledsEncendidos = !ledsEncendidos;
    todosLeds(ledsEncendidos);
  }
}

/*
  Luces_Navidad.ino
  Laboratorio: Luces de Navidad con ESP32 (ESP32 DevKit V1)
  Maquina de estados finitos de Moore, 5 estados, sin delay().

  Conexiones:
    LED 1..5 -> GPIO 18, 19, 21, 22, 23 (cada uno con 220 ohm a GND)
    Pulsador -> 3V3 y GPIO 4; resistencia pull-down externa de 10 kohm a GND

  Monitor serie: 115200 baudios.
*/

const uint8_t LEDS[5] = {18, 19, 21, 22, 23};
const uint8_t NUM_LEDS = 5;
const uint8_t PIN_BOTON = 4;

const unsigned long T_ANTIRREBOTE = 50;  // ms
const unsigned long T_E1 = 500;          // Parpadeo
const unsigned long T_E2 = 150;          // Carrera
const unsigned long T_E3 = 300;          // Alternado
const unsigned long T_E4 = 80;           // Vaiven (coche fantastico)

enum Estado { E0_APAGADAS, E1_PARPADEO, E2_CARRERA, E3_ALTERNADO, E4_VAIVEN };
Estado estado = E0_APAGADAS;             // estado inicial

bool botonPrevio = false;                // lectura anterior del pulsador
unsigned long tUltimaPulsacion = 0;      // ultima pulsacion aceptada
unsigned long tPaso = 0;                 // instante del ultimo paso de la secuencia
uint8_t paso = 0;                        // paso actual del patron
bool entrando = true;                    // true al entrar a un estado

// Enciende los LED cuyo bit esta en 1 en la mascara (bit 0 = LED 1).
void escribirLeds(uint8_t mascara) {
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    digitalWrite(LEDS[i], (mascara >> i) & 1);
  }
}

void PrintStates() {
  Serial.print("Estado: ");
  switch (estado) {
    case E0_APAGADAS:  Serial.println("E0 - Apagadas"); break;
    case E1_PARPADEO:  Serial.println("E1 - Parpadeo"); break;
    case E2_CARRERA:   Serial.println("E2 - Carrera"); break;
    case E3_ALTERNADO: Serial.println("E3 - Alternado"); break;
    case E4_VAIVEN:    Serial.println("E4 - Vaiven (coche fantastico)"); break;
  }
}

void cambiarEstado() {
  estado = (Estado)((estado + 1) % 5);   // desde E4 vuelve a E0
  paso = 0;                              // la secuencia empieza desde su primer paso
  entrando = true;
  escribirLeds(0);
  PrintStates();
}

// Devuelve true si ya paso 'intervalo' ms (o si se acaba de entrar al estado).
bool pasoListo(unsigned long intervalo) {
  if (entrando || (millis() - tPaso >= intervalo)) {
    entrando = false;
    tPaso = millis();
    return true;
  }
  return false;
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_BOTON, INPUT);             // pull-down externa: sin resistencias internas
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    pinMode(LEDS[i], OUTPUT);
  }
  escribirLeds(0);
  PrintStates();
}

void loop() {
  // ---- Entrada: flanco ascendente (0 -> 1) con antirrebote por millis() ----
  bool boton = digitalRead(PIN_BOTON);
  if (boton && !botonPrevio && (millis() - tUltimaPulsacion >= T_ANTIRREBOTE)) {
    tUltimaPulsacion = millis();
    cambiarEstado();
  }
  botonPrevio = boton;

  // ---- Salidas segun el estado (Moore) ----
  switch (estado) {
    case E0_APAGADAS:
      escribirLeds(0);
      break;

    case E1_PARPADEO:                    // todos encienden y apagan a la vez
      if (pasoListo(T_E1)) {
        escribirLeds((paso % 2 == 0) ? 0b11111 : 0);
        paso++;
      }
      break;

    case E2_CARRERA:                     // un LED a la vez, izquierda a derecha
      if (pasoListo(T_E2)) {
        escribirLeds(1 << (paso % NUM_LEDS));
        paso++;
      }
      break;

    case E3_ALTERNADO:                   // pares e impares se turnan
      if (pasoListo(T_E3)) {
        escribirLeds((paso % 2 == 0) ? 0b10101 : 0b01010);
        paso++;
      }
      break;

    case E4_VAIVEN:                      // barrido de ida y vuelta (0,1,2,3,4,3,2,1)
      if (pasoListo(T_E4)) {
        uint8_t p = paso % 8;
        uint8_t indice = (p < NUM_LEDS) ? p : (8 - p);
        escribirLeds(1 << indice);
        paso++;
      }
      break;
  }
}

const int pinesLeds[] = {18, 19, 21, 22, 23};
const int numLeds = 5;
const int pinBoton = 4;

enum EstadoFSM { E0_APAGADAS, E1_PARPADEO, E2_CARRERA, E3_ALTERNADO, E4_VAIVEN };
EstadoFSM estadoActual = E0_APAGADAS;

unsigned long tAnteriorPatron = 0;
unsigned long tUltimaPulsacion = 0;
const unsigned long debounceDelay = 50;
bool estadoAnteriorBoton = LOW;

int pasoSecuencia = 0;
bool direccionVaiven = true;

void setup() {
  Serial.begin(115200);
  pinMode(pinBoton, INPUT);
  for (int i = 0; i < numLeds; i++) {
    pinMode(pinesLeds[i], OUTPUT);
    digitalWrite(pinesLeds[i], LOW);
  }
  Serial.println("Estado E0 - Apagadas");
}

void loop() {
  unsigned long tiempoActual = millis();

  bool lecturaBoton = digitalRead(pinBoton);
  if (lecturaBoton == HIGH && estadoAnteriorBoton == LOW) {
    if (tiempoActual - tUltimaPulsacion > debounceDelay) {
      tUltimaPulsacion = tiempoActual;
      
      switch (estadoActual) {
        case E0_APAGADAS:
          estadoActual = E1_PARPADEO;
          Serial.println("Cambio a Estado E1: Parpadeo");
          break;
        case E1_PARPADEO:
          estadoActual = E2_CARRERA;
          Serial.println("Cambio a Estado E2: Carrera");
          break;
        case E2_CARRERA:
          estadoActual = E3_ALTERNADO;
          Serial.println("Cambio a Estado E3: Alternado");
          break;
        case E3_ALTERNADO:
          estadoActual = E4_VAIVEN;
          Serial.println("Cambio a Estado E4: Vaivén");
          break;
        case E4_VAIVEN:
          estadoActual = E0_APAGADAS;
          Serial.println("Cambio a Estado E0: Apagadas");
          break;
      }
      pasoSecuencia = 0;
      tAnteriorPatron = tiempoActual;
    }
  }
  estadoAnteriorBoton = lecturaBoton;

  switch (estadoActual) {
    case E0_APAGADAS:
      for (int i = 0; i < numLeds; i++) digitalWrite(pinesLeds[i], LOW);
      break;

    case E1_PARPADEO:
      if (tiempoActual - tAnteriorPatron >= 500) {
        tAnteriorPatron = tiempoActual;
        pasoSecuencia = !pasoSecuencia;
        for (int i = 0; i < numLeds; i++) digitalWrite(pinesLeds[i], pasoSecuencia);
      }
      break;

    case E2_CARRERA:
      if (tiempoActual - tAnteriorPatron >= 150) {
        tAnteriorPatron = tiempoActual;
        for (int i = 0; i < numLeds; i++) {
          digitalWrite(pinesLeds[i], (i == pasoSecuencia) ? HIGH : LOW);
        }
        pasoSecuencia = (pasoSecuencia + 1) % numLeds;
      }
      break;

    case E3_ALTERNADO:
      if (tiempoActual - tAnteriorPatron >= 300) {
        tAnteriorPatron = tiempoActual;
        pasoSecuencia = !pasoSecuencia;
        for (int i = 0; i < numLeds; i++) {
          if (pasoSecuencia) digitalWrite(pinesLeds[i], (i % 2 == 0) ? HIGH : LOW);
          else digitalWrite(pinesLeds[i], (i % 2 != 0) ? HIGH : LOW);
        }
      }
      break;

    case E4_VAIVEN:
      if (tiempoActual - tAnteriorPatron >= 80) {
        tAnteriorPatron = tiempoActual;
        for (int i = 0; i < numLeds; i++) {
          digitalWrite(pinesLeds[i], (i == pasoSecuencia) ? HIGH : LOW);
        }
        if (direccionVaiven) {
          pasoSecuencia++;
          if (pasoSecuencia >= numLeds - 1) direccionVaiven = false;
        } else {
          pasoSecuencia--;
          if (pasoSecuencia <= 0) direccionVaiven = true;
        }
      }
      break;
  }
}
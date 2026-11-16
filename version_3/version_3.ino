const int leds = 18;
const int boton = 4;

int contador = 0;
bool estadoLed = LOW;
unsigned long tAnteriorLed = 0;
const unsigned long intervaloLed = 500;

bool estadoAnteriorBoton = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(boton, INPUT);
  pinMode(leds, OUTPUT);
  Serial.println("VERSION 3");
}

void loop() {
  unsigned long tiempoActual = millis();

  if (tiempoActual - tAnteriorLed >= intervaloLed) {
    tAnteriorLed = tiempoActual;
    estadoLed = !estadoLed;
    digitalWrite(leds, estadoLed);
  }

  bool lecturaBoton = digitalRead(boton);
  if (lecturaBoton == HIGH && estadoAnteriorBoton == LOW) {
    contador++;
    Serial.print("Contador con rebotes: ");
    Serial.println(contador);
  }
  estadoAnteriorBoton = lecturaBoton;
}
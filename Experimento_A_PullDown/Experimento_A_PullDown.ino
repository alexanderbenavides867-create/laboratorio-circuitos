/*
  Experimento_A_PullDown.ino
  Experimento A: entrada con resistencia pull-down.
  Hace 20 lecturas de digitalRead() en el GPIO 4, separadas 100 ms, y muestra
  cuantas valieron 1. Medir con el multimetro (punta negra a GND, roja al GPIO 4).
  Para repetir la prueba, presione el boton EN de la placa.
  Monitor serie: 115200 baudios.
*/

const uint8_t PIN_BOTON = 4;
const uint8_t NUM_LECTURAS = 20;
const unsigned long INTERVALO = 100;  // ms

void setup() {
  Serial.begin(115200);
  pinMode(PIN_BOTON, INPUT);          // sin resistencias internas
  delay(2000);                        // tiempo para colocar las puntas / el boton
  Serial.println("Experimento A: 20 lecturas del GPIO 4");

  uint8_t unos = 0;
  for (uint8_t i = 1; i <= NUM_LECTURAS; i++) {
    int lectura = digitalRead(PIN_BOTON);
    if (lectura == HIGH) unos++;
    Serial.print("Lectura ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(lectura);
    delay(INTERVALO);
  }

  Serial.print("RESULTADO: De ");
  Serial.print(NUM_LECTURAS);
  Serial.print(" lecturas, ");
  Serial.print(unos);
  Serial.println(" valieron 1 (HIGH)");
}

void loop() {
  // Sin accion: la prueba se ejecuta una vez en setup().
}

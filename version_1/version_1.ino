const int leds = 18;
const int boton = 4;
int contador = 0;

void setup() {
  Serial.begin(115200);
  pinMode(boton, INPUT);
  pinMode(leds, OUTPUT);
  Serial.println("VERSION 1 - DELAY");
  Serial.println("Contador: 0");
}

void loop() {
  bool lectura = digitalRead(boton);
  if (lectura) {
    contador++;
    Serial.println(contador);
  }
  digitalWrite(leds, HIGH);
  delay(250);
  digitalWrite(leds, LOW);
  delay(250);
}
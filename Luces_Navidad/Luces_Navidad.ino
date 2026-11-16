/*
  Luces_Navidad.ino
  Laboratorio: Luces de Navidad con ESP32 (ESP32 DevKit V1)
  Maquina de estados finitos de Moore, 5 estados, sin delay().
  Monitor serie: 115200 baudios.
*/

const uint8_t LEDS[5] = {18, 19, 21, 22, 23};
const uint8_t NUM_LEDS = 5;
const uint8_t PIN_BOTON = 4;

const unsigned long T_ANTIRREBOTE = 50;  
const unsigned long T_E1 = 500;          
const unsigned long T_E2 = 150;          
const unsigned long T_E3 = 300;          
const unsigned long T_E4 = 80;           
const uint8_t PASOS_E4 = 8;              

enum Estado { E0_APAGADAS, E1_PARPADEO, E2_CARRERA, E3_ALTERNADO, E4_VAIVEN };
Estado estado = E0_APAGADAS;             

bool botonPrevio = false;                
unsigned long tUltimaPulsacion = 0;      
unsigned long tPaso = 0;                 
uint8_t paso = 0;                        
bool entrando = true;                    

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
  estado = (Estado)((estado + 1) % 5);  
  paso = 0;                              
  entrando = true;
  escribirLeds(0);
  PrintStates();
}


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
  pinMode(PIN_BOTON, INPUT);             
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    pinMode(LEDS[i], OUTPUT);
  }
  escribirLeds(0);
  PrintStates();
}

void loop() {
 
  bool boton = digitalRead(PIN_BOTON);
  if (boton && !botonPrevio && (millis() - tUltimaPulsacion >= T_ANTIRREBOTE)) {
    tUltimaPulsacion = millis();
    cambiarEstado();
  }
  botonPrevio = boton;


  switch (estado) {
    case E0_APAGADAS:
      escribirLeds(0);
      break;

    case E1_PARPADEO:                    // todos encienden y apagan a la vez
      if (pasoListo(T_E1)) {
        escribirLeds((paso == 0) ? 0b11111 : 0);
        paso = (paso + 1) % 2;
      }
      break;

    case E2_CARRERA:                     // un LED a la vez, izquierda a derecha
      if (pasoListo(T_E2)) {
        escribirLeds(1 << paso);
        paso = (paso + 1) % NUM_LEDS;
      }
      break;

    case E3_ALTERNADO:                   // pares e impares se turnan
      if (pasoListo(T_E3)) {
        escribirLeds((paso == 0) ? 0b10101 : 0b01010);
        paso = (paso + 1) % 2;
      }
      break;

    case E4_VAIVEN:                      // barrido de ida y vuelta 
      if (pasoListo(T_E4)) {
        uint8_t indice = (paso < NUM_LEDS) ? paso : (PASOS_E4 - paso);
        escribirLeds(1 << indice);
        paso = (paso + 1) % PASOS_E4;
      }
      break;
  }
}

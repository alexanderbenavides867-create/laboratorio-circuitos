# Laboratorio de Circuitos Digitales

Repositorio de la práctica de laboratorio de Circuitos Digitales, Universidad de San Buenaventura, sede Bogotá.

## Descripción del proyecto

Este proyecto implementa y evalúa un sistema embebido con la tarjeta **ESP32 DevKit V1**. La práctica comprende:

* La caracterización de una entrada digital con resistencia **pull-down** externa (Experimento A).
* La comparación de la corriente en un LED entre la ESP32 (3.3 V) y el Arduino UNO (5 V) (Experimento B).
* El efecto de `delay()` frente a `millis()` y al antirrebote en la detección de un pulsador (Experimento C).
* Un juego de luces de navidad organizado como una **máquina de estados finitos (FSM) de Moore** de cinco estados, sin `delay()`.

Pregunta orientadora: ¿cómo se organiza un programa que debe atender un botón en todo momento mientras ejecuta secuencias de luces temporizadas, y qué diferencias entre la ESP32 y el Arduino UNO hay que tener en cuenta al pasar de una placa a la otra?

---

## Estructura del repositorio

Cada programa está en una carpeta con el mismo nombre del archivo `.ino`, como exige el Arduino IDE.

```text
├── Luces_Navidad/
│   └── Luces_Navidad.ino                        # FSM de Moore, 5 estados (millis() + antirrebote)
├── Experimento_A_PullDown/
│   └── Experimento_A_PullDown.ino               # 20 lecturas del GPIO 4
├── Experimento_B_Corriente_LED/
│   └── Experimento_B_Corriente_LED.ino          # LED encendido fijo para medir corriente
├── Experimento_C_V1_Delay/
│   └── Experimento_C_V1_Delay.ino               # delay() sin antirrebote
├── Experimento_C_V2_Millis_Antirrebote/
│   └── Experimento_C_V2_Millis_Antirrebote.ino  # millis() con antirrebote de 50 ms
├── Experimento_C_V3_Millis_SinAntirrebote/
│   └── Experimento_C_V3_Millis_SinAntirrebote.ino  # millis() sin antirrebote
└── README.md
```

---

## Montaje

Componentes: ESP32 DevKit V1, 5 LED, 5 resistencias de 220 Ω, 1 pulsador, 1 resistencia de 10 kΩ y cable USB de datos.

| Elemento | Pin ESP32 | Conexión |
|---|---|---|
| LED 1 a LED 5 | GPIO 18, 19, 21, 22 y 23 | Cada LED en serie con una resistencia de 220 Ω hacia GND |
| Pulsador | GPIO 4 | Un terminal a 3V3; el otro al GPIO 4 y, mediante la resistencia de 10 kΩ, a GND (pull-down externa) |

---


## Programa principal: máquina de estados de Moore


### Tabla de transiciones y salidas

| Estado actual | Nombre | Salidas (LED) | Período (ms) | Con flanco ↑ | Sin flanco |
|---|---|---|---|---|---|
| E0 (inicial) | Apagadas | Todos apagados | — | E1 | E0 |
| E1 | Parpadeo | Todos encienden y apagan a la vez | 500 | E2 | E1 |
| E2 | Carrera | Un LED a la vez, de izquierda a derecha | 150 | E3 | E2 |
| E3 | Alternado | Pares e impares se turnan | 300 | E4 | E3 |
| E4 | Vaivén (coche fantástico) | Barrido de ida y vuelta (LED 1 → 5 → 1) | 80 | E0 | E4 |

### Características del firmware

* Estado actual en una variable `enum` y comportamiento de cada estado dentro de un `switch`.
* Sin `delay()`: todos los tiempos se controlan con `millis()`, y cada patrón recuerda su paso en la variable `paso`.
* Cambio de estado solo en el **flanco ascendente** del pulsador, no mientras permanece presionado.
* Antirrebote con `millis()`: se ignoran las pulsaciones que llegan menos de 50 ms después de la última aceptada.
* Al cambiar de estado, el nuevo patrón empieza desde su primer paso.
* Cada cambio de estado se imprime en el monitor serie con el nombre del nuevo estado.

---

## Programas de los experimentos

| Archivo | Experimento | Descripción |
|---|---|---|
| `Experimento_A_PullDown.ino` | A | Hace 20 lecturas de `digitalRead()` en el GPIO 4, separadas 100 ms, y muestra cuántas valieron 1. Se mide el voltaje del pin con el multímetro. |
| `Experimento_B_Corriente_LED.ino` | B | Mantiene encendido un LED con su resistencia de 220 Ω para medir Vpin y VR. Para el Arduino UNO se usa el mismo programa cambiando `PIN_LED` a un pin digital. |
| `Experimento_C_V1_Delay.ino` | C, V1 | Parpadeo de 500 ms con `delay(250)` + `delay(250)` y sin antirrebote. Cuenta las pulsaciones detectadas. |
| `Experimento_C_V2_Millis_Antirrebote.ino` | C, V2 | Parpadeo de 500 ms con `millis()` y antirrebote de 50 ms. |
| `Experimento_C_V3_Millis_SinAntirrebote.ino` | C, V3 | Parpadeo de 500 ms con `millis()` y sin antirrebote. |

---

## Resultados principales

**Experimento A: entrada pull-down (GPIO 4, 20 lecturas)**

| Resistencia de 10 kΩ | Botón | Voltaje en GPIO 4 (V) | Lecturas en 1 (de 20) |
|---|---|---|---|
| Conectada | Suelto | 0.000 | 0 |
| Conectada | Presionado | 3.261 | 20 |

**Experimento B: corriente en el LED (R = 220 Ω, VF = 2.0 V)**

| Placa | Imedida (mA) | Iteórica (mA) | Error (%) |
|---|---|---|---|
| ESP32 | 5.24 | 5.91 | 11.3 |
| Arduino UNO | 11.52 | 13.64 | 15.5 |

**Experimento C: pulsaciones detectadas (3 intentos de 20 pulsaciones)**

| Versión | Intento 1 | Intento 2 | Intento 3 | Promedio | Detectado (%) |
|---|---|---|---|---|---|
| V1 (`delay()`) | 7 | 6 | 8 | 7.0 | 35.0 |
| V2 (`millis()` + antirrebote) | 20 | 20 | 20 | 20.0 | 100.0 |
| V3 (`millis()` sin antirrebote) | 36 | 34 | 39 | 36.3 | 181.7 |

Un porcentaje mayor que 100 indica que el programa contó pulsaciones que no ocurrieron (rebotes mecánicos).

---

## Autores

Facultad de Ingeniería, Programa de Ingeniería Multimedia, Universidad de San Buenaventura, sede Bogotá:

* Jimena Bedoya Huertas
* María Paula Erazo Criollo
* Yesid Santiago Quintero Gómez
* Daniel Alexander Benavides Silva

**Docente:** Ing. Sergio Alberto Reyes Gómez
**Asignatura:** Circuitos Digitales

**Docente:** Ing. Sergio Alberto Reyes Gómez  
**Asignatura:** Circuitos Digitales

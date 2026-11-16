# Laboratorio de Circuitos Digitales: Control de Entradas Digitales y Máquina de Estados en ESP32

Repositorio oficial para la práctica de laboratorio de Circuitos Digitales de la Universidad de San Buenaventura, sede Bogotá.

## Descripción del Proyecto
Este proyecto implementa y evalúa un sistema embebido utilizando la tarjeta de desarrollo **ESP32 DevKit V1**. La práctica comprende la caracterización de entradas digitales con resistencias de pull-down externas, la comparación de consumo y caídas de voltaje frente a microcontroladores de 5 V (como Arduino UNO), el análisis del impacto de funciones bloqueantes (`delay()`) frente a temporización no bloqueante con `millis()` y antirrebote, y finalmente el desarrollo de un sistema organizado mediante una **Máquina de Estados Finitos (FSM) de Moore** con cinco estados.

---

## Estructura del Repositorio

El repositorio está organizado con los códigos fuente correspondientes a las diferentes etapas de experimentación y al proyecto integrador:

```text
├── proyecto_principal/
│   └── fsm_luces_navidad.ino         # Código principal de la FSM (5 estados con millis() y antirrebote)
├── version_1/
│   └── version1_delay.ino            # Versión experimental con delay() (Bloqueante)
├── version_2/
│   └── version2_millis_antirrebote.ino # Versión experimental con millis() y filtro de 50 ms (100% lecturas)
├── version_3/
│   └── version3_millis_sin_filtro.ino  # Versión experimental con millis() sin filtro (Registro de rebotes)
└── README.md                         # Documentación técnica del repositorio
```

---

## Descripción de los Programas

1. **`proyecto_principal.ino`**:
   Implementa la máquina de estados finitos de Moore de cinco estados ($E_0$ a $E_4$):
   * **$E_0$ (Apagadas):** Todos los LEDs apagados.
   * **$E_1$ (Parpadeo):** Todos los LEDs conmutan simultáneamente cada 500 ms.
   * **$E_2$ (Carrera):** Secuencia de encendido secuencial de izquierda a derecha cada 150 ms.
   * **$E_3$ (Alternado):** Conmutación entre LEDs pares e impares cada 300 ms.
   * **$E_4$ (Vaivén):** Barrido dinámico de ida y vuelta cada 80 ms.
   * *Características:* No bloqueante mediante `millis()`, control por flanco ascendente del pulsador en el GPIO 4 y antirrebote de 50 ms.

2. **`version_1.ino`**:
   Programa del Experimento C (Versión 1) que utiliza `delay(250)` para el parpadeo del LED. Demuestra cómo la CPU se bloquea durante los retardos, provocando la pérdida de pulsaciones del botón (rendimiento aproximado del 35%).

3. **`version_2.ino`**:
   Programa del Experimento C (Versión 2) que utiliza temporización no bloqueante con `millis()` combinada con un filtro de antirrebote de 50 ms, logrando una detección exitosa del 100% de las pulsaciones.

4. **`version_3.ino`**:
   Programa del Experimento C (Versión 3) que utiliza `millis()` para el parpadeo pero sin filtro de antirrebote, registrando el ruido mecánico de los contactos y superando el 180% de conteo debido a los múltiples flancos falsos.

---

## Autores
Facultad de Ingeniería — Programa de Ingeniería Multimedia / Sistemas, Universidad de San Buenaventura, sede Bogotá:
* Jimena Bedoya Huertas
* María Paula Erazo Criollo
* Yesid Santiago Quintero Gómez
* Daniel Alexander Benavides Silva

**Docente:** Ing. Sergio Alberto Reyes Gómez  
**Asignatura:** Circuitos Digitales

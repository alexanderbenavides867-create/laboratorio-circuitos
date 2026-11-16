# Laboratorio: Luces de Navidad con ESP32

Repositorio para la práctica de Circuitos Digitales de la Universidad de San Buenaventura.

## Contenido del Repositorio
- `fsm_luces_navidad.ino`: Código principal implementando la Máquina de Estados Finitos (FSM) de 5 estados (Apagadas, Parpadeo, Carrera, Alternado, Vaivén) con temporización no bloqueante mediante `millis()` y antirrebote por flanco ascendente.
- `version1_delay.ino`: Versión experimental 1 utilizando la función bloqueante `delay()`.
- `version2_millis_antirrebote.ino`: Versión experimental 2 utilizando `millis()` con filtro de antirrebote de 50 ms.
- `version3_millis_sin_filtro.ino`: Versión experimental 3 utilizando `millis()` sin filtro de antirrebote para registrar rebotes mecánicos.

## Autores
- Jimena Bedoya-Huertas
- María Paula Erazo-Criollo
- Yesid Santiago Quintero-Gómez
- Daniel Alexander Benavides-Silva

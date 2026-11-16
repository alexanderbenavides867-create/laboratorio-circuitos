# Laboratorio: Luces de Navidad con ESP32

Repositorio para la práctica de Circuitos Digitales de la Universidad de San Buenaventura.

## Contenido del Repositorio
- `proyecto_principal.ino`: Código principal implementando la Máquina de Estados Finitos (FSM) de 5 estados (Apagadas, Parpadeo, Carrera, Alternado, Vaivén) con temporización no bloqueante mediante `millis()` y antirrebote por flanco ascendente.
- `version_1.ino`: Versión experimental 1 utilizando la función bloqueante `delay()`.
- `version_2.ino`: Versión experimental 2 utilizando `millis()` con filtro de antirrebote de 50 ms.
- `version_3.ino`: Versión experimental 3 utilizando `millis()` sin filtro de antirrebote para registrar rebotes mecánicos.

## Autores
- Jimena Bedoya-Huertas
- María Paula Erazo-Criollo
- Yesid Santiago Quintero-Gómez
- Daniel Alexander Benavides-Silva

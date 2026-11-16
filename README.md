# Sistema Embebido de Contenedor Inteligente y FSM — USB Bogotá

Sistema embebido implementado sobre microcontrolador e integrado en una maqueta a escala para atender la problemática de higiene, contacto físico con tapas de residuos y trazabilidad de uso en los puntos ecológicos de la Universidad de San Buenaventura, sede Bogotá.

## Problemática Abordada
En la Universidad de San Buenaventura, sede Bogotá, es común observar restos de alimentos y otros desechos arrojados directamente en el suelo alrededor de las zonas de consumo. Una de las causas principales es el rechazo de los usuarios a tocar manualmente las tapas de las canecas por percepción de suciedad y temor a la propagación de gérmenes. Este proyecto atiende el problema automatizando la apertura de la tapa cuando la persona acerca el residuo frente al sensor del contenedor, eliminando el contacto físico y fomentando la correcta disposición de la basura.

## Características del Sistema
- **Apertura automática sin contacto:** Detección de proximidad mediante sensor ultrasónico y accionamiento mecánico con control de estados y retardos temporizados.
- **Entrada manual de mantenimiento:** Conexión digital con resistencia pull-down externa y filtro antirrebote por software para fijar la tapa abierta durante labores de mantenimiento o cambio de bolsa.
- **Arquitectura no bloqueante:** Temporización basada en `millis()` para evitar congelamientos del sistema y permitir una respuesta fluida.
- **Comunicación serial UART bidireccional:** Envío periódico de telemetría y recepción de comandos de control desde el monitor serie o PC.

## Lista de Componentes
| Componente | Especificación | Función en el sistema |
| :--- | :--- | :--- |
| **Microcontrolador** | Placa de desarrollo / SoC | Procesamiento, control PWM, lectura digital y UART |
| **Sensor de entorno** | Módulo ultrasónico HC-SR04 | Medición de distancia de proximidad de residuos |
| **Entrada manual** | Microinterruptor SPDT | Activación/desactivación de modo manual de mantenimiento |
| **Resistencia externa** | Resistencia de carbón 10 kΩ (1/4 W) | Configuración pull-down externa |
| **Actuador mecánico** | Servomotor / Sistema de LEDs | Accionamiento mecánico o visualización de estados |
| **Cableado** | Cables Dupont M-H y M-M | Interconexión integrada dentro de la maqueta |

## Diagrama de Conexiones
| Componente / Terminal | Pin de Conexión | Observaciones |
| :--- | :--- | :--- |
| **Sensor / Módulo VCC** | 5V / 3.3V | Alimentación regulada |
| **Sensor / Módulo GND** | GND | Referencia común |
| **Señal de Control / Actuador** | Pines digitales / PWM | Control de salidas y actuadores |
| **Pulsador / Microswitch** | Pin digital con Pull-Down | Lectura de eventos de usuario con antirrebote |

## Instrucciones de Uso
1. Seleccionar el directorio de código correspondiente según la versión o prueba a realizar en el repositorio.
2. Abrir el archivo `.ino` deseado en Arduino IDE.
3. Seleccionar la placa correspondiente y el puerto COM adecuado, y cargar el programa.
4. Abrir el Monitor Serial a 115200 baudios para visualizar la telemetría y los estados del sistema.
5. Interactuar mediante el pulsador o el sensor de proximidad según la prueba seleccionada.

## Estructura del Repositorio
```text
├── proyecto_principal/
│   └── fsm_luces_navidad.ino         # Código principal del sistema embebido (FSM y control general)
├── version_1/
│   └── version1_delay.ino            # Versión experimental 1 (control básico / delay)
├── version_2/
│   └── version2_millis_antirrebote.ino # Versión experimental 2 (control no bloqueante con millis y antirrebote)
├── version_3/
│   └── version3_millis_sin_filtro.ino  # Versión experimental 3 (control no bloqueante sin filtro)
└── README.md                         # Documentación técnica completa del proyecto
```

## Autores
Ingeniería Multimedia — Universidad de San Buenaventura, sede Bogotá
- Jimena Bedoya Huertas
- Daniel Benavides Silva
- Yesid Santiago Quintero
- Maria Paula Erazo

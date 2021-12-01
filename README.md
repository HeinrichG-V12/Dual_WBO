# Dual_WBO

### Dual WBO controller based on: ### 
- Microchip AT90CAN128
- 2x Bosch CJ125 wideband lambda controller
- NXP TJA1051T can transceiver
- Analog Devices LT2633 dual channel 10-bit I²C DAC
- TI REF5050-Q1 reference for analog part
- ...

### Features: ### 
- supports LSU4.9 probes only
- dual analog output, either as 0..5V for AFR 10..20 OR narrow band emulation
- CAN output (AEM X-Series protocol) for both channels

Suitable Bosch lambda probe: 0 258 017 025<br/>

Probe pinout:<br/>
|Pin#|Color|Description|Symbol|
|----|-----|--------|-----------|
|1|red|Pump current APE|IP|
|2|yellow|Virtual ground IPN|VM|
|3|white|Heater voltage H-|Uh-|
|4|grey|Heater voltaget H+|Uh+|
|5|green|Trim Resistor RT|IA|
|6|black|Nernst voltage UN|RE|
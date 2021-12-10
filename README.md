# Dual_WBO

### Dual WBO controller based on: ### 
- Microchip AT90CAN128
- 2x Bosch CJ125 wideband lambda controller
- NXP TJA1051T can transceiver
- Analog Devices LT2633 dual channel 10-bit I²C DAC
- TI REF5050-Q1 precision reference (0.05%) for analog part
- Infineon TLS115B0EJXUMA1 voltage tracker
- Molex MX150 20-pin connector (348302001)
- ...

### Features: ### 
- supports **LSU4.9** probes only
- dual analog output, either as 0..5V for AFR 10..20 OR narrow band emulation
- CAN output (AEM X-Series protocol) for both channels

### Suitable Bosch lambda probes: ###
|Bosch number  |Length overall|Comment|
|--------------|--------------|-------|
|0 258 017 025 |1000mm|Bosch motorsport part|
|0 258 017 012 |1060mm||
|0 281 004 184 |1000mm||
|0 281 004 150 |1215mm||
|0 258 017 126 |680mm|black, used by BMW after 09/2006 (1178 7561410)|
|0 258 017 029 |620mm|grey, used by BMW after 09/2006 (1178 7539124)|
|0 258 017 092 |950mm|black, used by BMW (1178 7540167)|
|0 258 017 038 |340mm|grey, used by BMW (11787537984)|
|...|||

### LSU4.9 probe pinout: ###
|Pin#|Color|Description|Symbol|
|----|-----|--------|-----------|
|1|red|Pump current APE|IP|
|2|yellow|Virtual ground IPN|VM|
|3|white|Heater voltage H-|Uh-|
|4|grey|Heater voltaget H+|Uh+|
|5|green|Trim Resistor RT|IA|
|6|black|Nernst voltage UN|RE|

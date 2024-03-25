# Workflow for running CJ125

## How CJ125 runs

### Running phases

#### Phase 1, startup

- startup the MCU
- init GPIO, registers, PWM, ADC, DAC, SPI, CAN...

#### Phase 2, calibration

- read diag register of CJ125
- put CJ125 into calibration mode
- read Ua (ADC value for λ=1), store them (Ua_calibration)
- read Ur (ADC value for optimal heater power and heater temperature), store them (Ur_calibration)

#### Phase 3, condensation

- put CJ125 into measurement mode, amplification 17 (VL=1, λ = 0.75...∞)
- drive heater with 1.5V for 5 seconds

#### Phase 4, heat up

- drive heater with 8.5V to 13V (not UBat!), with 0.4V/s

#### Phase 5, running

- PID heater control (read Ur)
- read Ua
- calculate Ip (pump current)

### Ip calculation

#### Ip(A) = (Ua - Ua_calibration) / (amplification * Rshunt)

- Ua: actual Ua value
- Ua_calibration: stored value from calibration step (approx. 1.5V)
- amplification: amplification factor, 8 (rich applications, λ < 1) or 17 (lean applications, λ > 1)
- Rshunt: resistance of shunt resistor between IA and IP for pump current sensing, always 61.9 Ohm for LSU4.2 and LSU4.9

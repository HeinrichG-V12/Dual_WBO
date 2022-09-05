# Startup procedure

## Initialization the hardware

- lowlevel init hardware
  - adc
  - spi
  - can network init
  - board init
  - sensor init
  - board read inputs (measure vBat, offset (shunt) and set board status ok/nok)

## Calibration

- bring cj125 into calibration mode
  - wait 500ms
  - check cj125 status
- read calibration values
  - Ua (lambda value)
  - Ur (reference heater value, lower values means hoter heater)

## Running

- bring cj125 into running mode, amplifacation 8
  - wait 500ms
  - check cj125 status
  - set *sensor status* to *evap startup* (pre heating at 1.5v for some time)
- init timer with 1ms

## From now on the while loop is running and scheduler is active

### 10ms task

- if *sensor status* is *running*
  - read Ua, calculate the whole stuff (lambda, O2, ...)
- if *sensor status* is *evap startup*
  - NOP
- always
  - send CAN message with actual values (check DBC file)

### 25ms task

- nothing to do

### 50ms task

- nothing to do

### 100ms task

- if *sensor status* is *running*
  - read Ur
  - adjust pid
- if *sensor status* is *warm up*
  - increase the heater voltage

## Status transitions and actions

- *reset* --> *evap startup*
  - set heater voltage to 1.5v
- *evap startup* --> *warming up*
  - set heater voltage to 8.5v
  - ramp up heater voltage from 8.5v to 13v with maximum ramp up rate of 0.4v/s
- *warming up* --> *running*
  - activate heater pid control
- *running* --> *error*
  - shutdown heater

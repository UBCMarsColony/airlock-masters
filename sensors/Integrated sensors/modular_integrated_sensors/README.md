The modular_integrated_sensors software uses a bitmask to determine indicate valid data for the pi.

The format of the bitmask is as indicated below, starting from the leftmost (high) bit.

bit 0 (0b**0**0000000): O2 (Percent)

bit 1 (0b0**0**000000): Humidity (Percent)

bit 2 (0b00**0**00000): Temperature (degrees Celsius)

bit 3 (0b000**0**0000): Pressure (dekaPascals, Barometric)

bit 4 (0b0000**0**000): CO2 (Parts per Million)
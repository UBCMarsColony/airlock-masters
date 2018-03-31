#initialization
TAG = "pi-main_primary"

import sys
import importlib
import time
import RPi.GPIO as gpio
    
print("STARTING SYSTEM")

# Begin systems get
sys.path.insert(0, '../pi-systems/')

# Import the pool
ss_pool = importlib.import_module('pi-systems_subsystem-pool')

sensor_ss = importlib.import_module('pi-systems_sensor-reader')
light_ss = importlib.import_module('pi-systems_lighting_lights-manager')
input_ss = importlib.import_module('pi-systems_lighting_input-manager')
valve_ss = importlib.import_module('pi-systems_valve-manager')

print("SYSTEM READY\n-------------\n-------------\n\n")


# MAIN SYSTEM FUNCTIONS
# Based on the Arduino setup

def begin(config_data_dict):
    
    #Set GPIO mode to Broadcom SOC Channel
    gpio.setmode(gpio.bcm)
    
    #Initialize various systems
    
    sensors = sensor_ss.SensorSubsystem(gpio, "Sensors_Subsystem", 3)
    sensor.start()
    
    lights = light_ss.LightingSubsystem(gpio, "Lights_Subsystem", 4)
    lights.start() 
    
    input = input_ss.InputManager(gpio, "Input_Subsystem", 5)
    input.start()
    
    valves = valve_ss.ValveManager(gpio, "Valve_Subsystem", 6)
    
    try:
        loop(config_data_dict)
    except KeyboardInterrupt:
        input = input("Shut down colony? (y/n)\n")
        if input == "y" or input == "Y":
            ss_pool.stop_all()
            exit(0)
        else:
            print("Airlock shutdown cancelled")

        
def loop(config_data):
    while True:
        data = sensors.get_data()
        

        time.sleep(config_data["loop_delay"])

"""
NORMAL PROCESS
--------------
Get sensors, doors
    Check safety, handle issues

Check user input    
    Handle any input

Update:
    Lights
    UI

    
OPEN DOOR
---------
Get sensors, doors
    Check safety

Check user input

Run door, valves, pressure

Update:
    Lights
    UI

EMERGENCY
--------
Lights Full
Update UI wth warning

Close doors

Run valve, pressure
    Safety checks always
    
"""
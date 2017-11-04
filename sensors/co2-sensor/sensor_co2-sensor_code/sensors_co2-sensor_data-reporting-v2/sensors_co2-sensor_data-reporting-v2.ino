/*
 * Author: Thomas Richmond
 * Written in: Sept 2017
 */

#define MIN_VOLTAGE 400
#define ERROR_CODE -555

//INCREASE VALUES BELOW TO DECREASE PRINT FREQUENCY, AND VICE VERSA
#define PREHEAT_PRINT_COUNTER_MOD 1
#define DATA_PRINT_COUNTER_MOD 1

//A variable that stores sensor integrity. Uses values of enumerated AV
short integrityAlertLevel = 0;
long loopCounter = 0;

struct Datasheet{
  double voltage;
  double concentration;
};

struct Datasheet getCo2Values(int sensorIn){
  //Prepare a structure for use.
  struct Datasheet data;
  
  //Read sensor report.
  short sensorValue = analogRead(sensorIn); 

  // Convert analog signal to voltage.
  data.voltage = sensorValue*(5000/1024.0); 

  //Choose action to perform given the voltage.
  if(data.voltage < MIN_VOLTAGE)
  {
    //PREHEATING
    if(loopCounter%PREHEAT_PRINT_COUNTER_MOD == 0){ //Controls data printing per loop set.
      Serial.print("Preheating. Current voltage: ");
      Serial.print(data.voltage);
      Serial.println("mv");
    }
  } 
  else
  {
    //DATA REPORT
    if(loopCounter % DATA_PRINT_COUNTER_MOD == 0){ //Controls data printing per loop set.

      //Calculate the voltage difference and, by extension, the CO2 concentration.
      short voltage_diference = data.voltage - MIN_VOLTAGE;
      data.concentration = voltage_diference*50.0/16.0;
      
      // Print Voltage
      Serial.print("voltage: ");
      Serial.print(data.voltage);
      Serial.println("mv");
      
      //Print CO2 concentration.
      Serial.print("Concentation: ");
      Serial.print(data.concentration);
      Serial.println("ppm");
    }
  }  
  
  //Increment the print controlling counter.
  //REMOVE BELOW LINE IF NECESSARY
  loopCounter++;

  return data;
}

/*THE FUNCTIONS setup() AND loop() SHOULD NOT BE INCLUDED IN THE UPLOAD CODE
* They are here so that the code can run independantly of the main system for debug & development purposes.*/
void setup(){  
  Serial.begin(9600);  
  // Set the default voltage of the reference voltage
  analogReference(DEFAULT); 
}

void loop(){
  getCo2Values(A0);
  delay(100); 
}


/***************************************************
 * Infrared CO2 Sensor0-5000ppm 
 * ****************************************************
 * This example The sensors detect CO2
 * 
 * @author lg.gang(lg.gang@qq.com)
 * @version  V1.0
 * @date  2016-7-6
 * 
 * GNU Lesser General Public License.
 * See <http://www.gnu.org/licenses/> for details.
 * All above must be included in any redistribution
 * ****************************************************/
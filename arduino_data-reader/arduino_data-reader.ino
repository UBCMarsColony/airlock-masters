//constants and libs
#include <SoftwareSerial.h>
#include <SPI.h>
#define pin_RX 10
#define pin_TX 11
SoftwareSerial COML0 (pin_RX,pin_TX,false);

void setup(){
    SoftwareSerial(pin_RX,pin_TX,false);
    Serial.begin(9600);// begin physical uart comms via USB
    COML0.begin(9600);//begin COML0, which is the software UART on pins 10 and 11
    Serial.println("Begin logical serial COM0");
    Serial.println("Begin hardware serial at USB");
    delay(5000);
}

void loop(){
    //conditioning string for the cJSON parser
    //stringLength_required=stringReader(serialInput_raw[]);
    char readChar_TEST="k";//ISSUE: sample character "k" isn't being read as "k" in the Pi
    Serial.print("Sample char: ");
    Serial.println(readChar_TEST);
    // set vars
    // int stringLength_index=0;
    // int stringLength_required; //beware of global variables
    // char serialInput_raw[1024]="{\"title\":\"Person\",\"type\":\"object\",\"properties\":{\"firstName\":{\"type\":\"string\"},\"lastName\":{\"type\":\"string\"},\"age\":{\"description\":\"Age in years\",\"type\":\"integer\",\"minimum\": 0}},\"required\":[\"firstName\", \"lastName\"]}";

    // Serial.print("JSON string to be decoded is: ");
    // Serial.println(serialInput_raw);
    readChar_TEST=COML0.read();//ISSUE: Not reading properly
    Serial.print("COML0 byte read: ");
    Serial.println(readChar_TEST);

    // stringLength_required=strlen(serialInput_raw);

    // char serialInput_forParser[stringLength_required+1];

    // for(stringLength_index=0;stringLength_index<stringLength_required;stringLength_index++){ //copy string char by char
    //     serialInput_forParser[stringLength_index]=serialInput_raw[stringLength_index];
    // }
    // serialInput_forParser[stringLength_index+1]='\0'; //string terminator with null
    
    // Serial.print("JSON string on smaller array is: ");
    // Serial.println("serialInput_forParser");
    
    // delay(1000);

}

//self-defined functions

/* void stringReader(void)
    TAKES: reference to string stringInput of predetermined length
    RETURNS: number of bytes written to stringInput
    FUNCTION: reads a single data frame from serial, enclosed by start character frame_start and end character frame_end
*/
int stringReader(char stringInput[]){

    char COM_readChar;
    char frame_start="\a";
    char frame_end="\n";
    
    int readLength=0;
    int TRIGGER=0;//fuse function (?)
    
    //does blank reads from strim until alert character \a is found. fused so it runs at most once
    while(COM_readChar!=frame_start && TRIGGER!=1){
        COM_readChar=Serial.read(); //run continuously to discard from strim
        if(COM_readChar==frame_start){
            TRIGGER=1; //fuse if frame_start detected
            break;
        }
    }

    //read until end of frame
    while(COM_readChar!=frame_end){
        COM_readChar=Serial.read();
        stringInput[readLength]=COM_readChar;
        readLength++;
    }

    return readLength;
}


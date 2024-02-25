#include <SPI.h>
#include <mcp2515.h>

#define MQ2pin A2 //MQ2
#define MQ4pin A3 //MQ4
#define MQ7pin A4 // MQ7
#define MQ135 A5 //MQ135
#define LDRled A1 //LDR
#define FC_28 A0 //FC-28 

const int FCdigital = 8;
const int DSdigital = 7;

struct can_frame canMsg1;
struct can_frame canMsg2;
struct can_frame canMsg3;
struct can_frame canMsg4;
struct can_frame canMsg5;
struct can_frame canMsg6;
struct can_frame canMsg7;

MCP2515 mcp2515(10);

void setup() {

  Serial.begin(115200); // sets the serial port to 9600

  Serial.println("Gas sensor warming up!");
  delay(1000); // allow the MQ's to warm up
  
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_1000KBPS);
  mcp2515.setNormalMode();
  
  Serial.println("Example: Write to CAN");
}

void loop() {
  uint32_t MQ2sensorValue = analogRead(MQ2pin);
  uint32_t MQ4sensorValue = analogRead(MQ4pin); 
  uint32_t MQ7SensorValueppm = analogRead(MQ7pin);
  uint32_t MQ135sensorValue = analogRead(MQ135); 
  uint32_t LDRsensorValue = analogRead(A1);
  uint32_t FCHumiditysensorValue = analogRead(A0);
//  uint32_t FCHumiditySensorValueDigital = digitalRead(FCdigital); 
  uint32_t DSdigitalSensorValue = digitalRead(DSdigital); 
  
  canMsg1.can_id  = 50; //MQ2 Gas Sensor
  canMsg1.can_dlc = 4;
  canMsg1.data[0] = (MQ2sensorValue >> 24) & 0x000000FF;
  canMsg1.data[1] = (MQ2sensorValue >> 16) & 0x000000FF;
  canMsg1.data[2] = (MQ2sensorValue >> 8) & 0x000000FF;
  canMsg1.data[3] = MQ2sensorValue & 0x000000FF;

  canMsg2.can_id  = 51; //MQ4 Methane Gas Sensor
  canMsg2.can_dlc = 4;
  canMsg2.data[0] = (MQ4sensorValue >> 24) & 0x000000FF;
  canMsg2.data[1] = (MQ4sensorValue >> 16) & 0x000000FF;
  canMsg2.data[2] = (MQ4sensorValue >> 8) & 0x000000FF;
  canMsg2.data[3] = MQ4sensorValue & 0x000000FF;

  canMsg3.can_id  = 52; //MQ7 (Carbon Monoxide Sensor)
  canMsg3.can_dlc = 4;
  canMsg3.data[0] = (MQ7SensorValueppm >> 24) & 0x000000FF;
  canMsg3.data[1] = (MQ7SensorValueppm >> 16) & 0x000000FF;
  canMsg3.data[2] = (MQ7SensorValueppm >> 8) & 0x000000FF;
  canMsg3.data[3] = MQ7SensorValueppm & 0x000000FF;

  canMsg4.can_id  = 53; //MQ135 (Air Quality Sensor)
  canMsg4.can_dlc = 4;
  canMsg4.data[0] = (MQ135sensorValue >> 24) & 0x000000FF;
  canMsg4.data[1] = (MQ135sensorValue >> 16) & 0x000000FF;
  canMsg4.data[2] = (MQ135sensorValue >> 8) & 0x000000FF;
  canMsg4.data[3] = MQ135sensorValue & 0x000000FF;

  canMsg5.can_id  = 54; //LDR (Light Detector)
  canMsg5.can_dlc = 4;
  canMsg5.data[0] = (LDRsensorValue >> 24) & 0x000000FF;
  canMsg5.data[1] = (LDRsensorValue >> 16) & 0x000000FF;
  canMsg5.data[2] = (LDRsensorValue >> 8) & 0x000000FF;
  canMsg5.data[3] = LDRsensorValue & 0x000000FF;

  canMsg6.can_id  = 55; //DS (Termometer digital)
  canMsg6.can_dlc = 4;
  canMsg6.data[0] = (DSdigitalSensorValue >> 24) & 0x000000FF;
  canMsg6.data[1] = (DSdigitalSensorValue >> 16) & 0x000000FF;
  canMsg6.data[2] = (DSdigitalSensorValue >> 8) & 0x000000FF;
  canMsg6.data[3] = DSdigitalSensorValue & 0x000000FF;

  canMsg7.can_id  = 56; //FC-28 (Humidity Sensor)
  canMsg7.can_dlc = 4;
  canMsg7.data[0] = (FCHumiditysensorValue >> 24) & 0x000000FF;
  canMsg7.data[1] = (FCHumiditysensorValue >> 16) & 0x000000FF;
  canMsg7.data[2] = (FCHumiditysensorValue >> 8) & 0x000000FF;
  canMsg7.data[3] = FCHumiditysensorValue & 0x000000FF;

  Serial.print(" MQ2 Sensor Value: ");
  Serial.println(MQ2sensorValue);

  Serial.print(" MQ4 Sensor Value: ");
  Serial.println(MQ4sensorValue);

  Serial.print(" MQ7 Sensor Value: ");
  Serial.println(MQ7SensorValueppm);

  Serial.print(" MQ135 Sensor Value: ");
  Serial.println(MQ135sensorValue);

  Serial.print(" LDR Sensor Value: ");
  Serial.println(LDRsensorValue);

  Serial.print(" FC-28 Humidity Sensor Value: ");
  Serial.println(FCHumiditysensorValue);

  Serial.print(" DS Termometer Sensor Value Digital: ");
  Serial.println(DSdigitalSensorValue);

  /* Serial.print(" FC-28 Humidity Sensor Value Digital: ");
  Serial.println(FCHumiditySensorValueDigital);
  */

  mcp2515.sendMessage(&canMsg1);
  mcp2515.sendMessage(&canMsg2);
  mcp2515.sendMessage(&canMsg3);
  mcp2515.sendMessage(&canMsg4);
  mcp2515.sendMessage(&canMsg5);
  mcp2515.sendMessage(&canMsg6);
  mcp2515.sendMessage(&canMsg7);

  // Serial.println("Messages sent");
  
  delay(1000);
}

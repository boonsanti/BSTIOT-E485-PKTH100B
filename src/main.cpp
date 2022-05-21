
#include <ModbusMaster.h>

#define RXD2 16
#define TXD2 17

// instantiate ModbusMaster object
ModbusMaster node;

bool state = true;

void setup()
{

  // Modbus communication runs at 115200 baud
  Serial.begin(115200);

  Serial2.begin(4800, SERIAL_8N1, RXD2, TXD2);
  // Modbus slave ID 2
  node.begin(2, Serial2);

}

void loop()
{
  uint8_t result;
  uint16_t data[6];
  
  // Toggle the coil at address 0x0002 (Manual Load Control)
//   result = node.writeSingleCoil(0x0002, state);
//   state = !state;

  // Read 16 registers starting at 0x3100)
  result = node.readHoldingRegisters(0x0000, 2);
  if (result == node.ku8MBSuccess)
  {
    Serial.print("TEMP: ");
    Serial.print(node.getResponseBuffer(0x00)/10.0f);
    Serial.print(" , HUMI: ");
    Serial.println(node.getResponseBuffer(0x01)/10.0f);
  }

  delay(2000);
}

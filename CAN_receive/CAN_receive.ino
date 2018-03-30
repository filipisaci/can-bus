#include <mcp_can.h>
#include <SPI.h>

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[1];
char msgString[128];
int LED = 10;
byte LedApagado[1] = {0x00};
byte LedAceso[1]  = {0x01};

//Pinagem
#define CAN0_INT 48
MCP_CAN CAN0(53);


void setup()
{
  Serial.begin(115200);
  pinMode(LED, OUTPUT);

  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK)
    Serial.println("Shild MCP2515 Inicializada com sucesso!");
  else
    Serial.println("Erro ao inicializar a shild MCP2515...");

  CAN0.setMode(MCP_NORMAL);                     // Set operation mode to normal so the MCP2515 sends acks to received data.

  pinMode(CAN0_INT, INPUT);                            // Configuring pin for /INT input
}

void loop()
{
  if (!digitalRead(CAN0_INT))                        // If CAN0_INT pin is low, read receive buffer
  {
    CAN0.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
    if ((rxId & 0x40000000) == 0x40000000) {  // Determine if message is a remote request frame.
      sprintf(msgString, " REMOTE REQUEST FRAME");
      Serial.print(msgString);
    } else {
      for (byte i = 0; i < len; i++) {
        sprintf(msgString, " 0x%.2X", rxBuf[i]);
        if (rxBuf[i] == *LedAceso) {
          digitalWrite(LED, LOW);
          delay(10);
        } else {
          digitalWrite(LED, HIGH);
          delay(10);
        }
      }
    }
 }
}

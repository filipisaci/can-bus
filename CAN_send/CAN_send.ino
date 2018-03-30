// CAN Send Example
//

#include <mcp_can.h>
#include <SPI.h>

MCP_CAN CAN0(53);     // Set CS to pin 53
int LDR = A7;

void setup()
{
  Serial.begin(115200);

  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK) Serial.println("Shild MCP2515 Inicializada com sucesso!");
  else Serial.println("Erro ao inicializar a shild MCP2515...");

  CAN0.setMode(MCP_NORMAL);   // Change to normal mode to allow messages to be transmitted
}

byte dataPowerOff[1] = {0x00};
byte dataPowerOn[1]  = {0x01};

void loop()
{
  if (analogRead(LDR) > 800)
  {
    // send data:  ID = 0x100, Standard CAN Frame, Data length = 8 bytes, 'data' = array of data bytes to send
    byte sndStat = CAN0.sendMsgBuf(0x100, 0, 1, dataPowerOff);
    if (sndStat == CAN_OK) {
      Serial.println("Mensagem enviada com sucesso!");
    } else {
      Serial.println("Erro ao enviar mensagem...");
    }
    delay(100);
  }
  else  //Caso contrário, apaga o led
  {
    byte sndStat = CAN0.sendMsgBuf(0x100, 0, 1, dataPowerOn);
    if (sndStat == CAN_OK) {
      Serial.println("Mensagem enviada com sucesso!");
    } else {
      Serial.println("Erro ao enviar mensagem...");
    }
    delay(100);
  }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

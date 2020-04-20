#include "wibrick.h"
#include <Ticker.h>
#include "../lxlib/wifi.h"

// ESP mode
#include "WiFiUdp.h"
#define UDP_PORT 2112
#define udpPacketSize 10

WiFiUDP Udp;
char packetBuffer[udpPacketSize];
IPAddress controllerAddr;
uint16_t controllerPort;
//

void _onWiWireMessage(WiWirePacket p) {
  Udp.beginPacket(controllerAddr, controllerPort);
  char buff[udpPacketSize] = {
    0x1A,
    p.addr,
    p.cmd,
    p.data[0],
    p.data[1],
    p.data[2],
    p.data[3],
    p.data[4],
    p.data[5],
    0x2A
  };
  Udp.write(buff);
  Udp.endPacket();
}

WiWireMaster wiMaster;

void wibrickSetup() {
  Udp.begin(UDP_PORT);
  wiMaster.onReceive(_onWiWireMessage);
}

void wibrickLoop() {
  // wiMaster.update();
  // Direct control
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    // read the packet into packetBufffer
    Udp.read(packetBuffer, udpPacketSize);
    // Set controller address
    if (packetBuffer[0] == 0xDD) {
      controllerAddr = Udp.remoteIP();
      controllerPort = Udp.remotePort();
    }
    // Bridge send
    if (packetBuffer[0] == 0x0A) {
      WiWirePacket p;
      p.addr = packetBuffer[1];
      p.cmd = (WiCmd)packetBuffer[2];
      p.data[0] = packetBuffer[3];
      p.data[1] = packetBuffer[4];
      p.data[2] = packetBuffer[5];
      p.data[3] = packetBuffer[6];
      p.data[4] = packetBuffer[7];
      p.data[5] = packetBuffer[8];
      // wiMaster.send(p);
      wiMaster.write((uint8_t *) &p);
    }
  }
}

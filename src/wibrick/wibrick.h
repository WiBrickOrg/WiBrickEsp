#ifndef __WIBRICK_SERVO_H__
#define __WIBRICK_SERVO_H__

#include <Arduino.h>
#include "../../lib/wibrick-wire/master/wiwire-master.h"

void wibrickSetup();
void wibrickLoop();
void resetSleep();

void _onWiWireMessage(WiWirePacket p);

#endif

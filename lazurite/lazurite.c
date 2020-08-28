// D9:IM920_RX ← 1:TX
// D8:IM920_TX → 0:RX
#include "lazurite_ide.h"
#include <stdio.h>
#include <string.h>

#define IM920_BAUD 19200UL
#define IM920_MAX_BUFFER_SIZE 64
#define SW_REED 5
#define SW_OPEN 0
#define SW_CLOSE 1

int preStatus = SW_CLOSE;
int status = SW_CLOSE;
char buf[IM920_MAX_BUFFER_SIZE];

void setup() {
	pinMode(SW_REED, INPUT_PULLUP);
	Serial.begin(IM920_BAUD);
	Serial.println("DSRX");		// スリープ開始
	sleep(100);					// スリープ状態待ち
}

void loop() {
	status = SW_CLOSE;
	if (digitalRead(SW_REED) == LOW) {
		status = SW_OPEN;
		sleep(100);					// 省電力用待機
	}
	
	if(status != preStatus) {
		Serial.println("ENRX");		// スリープ解除
		sleep(100);					// スリープ解除待ち
		sprintf(buf,"TXDA %02d", status);
		Serial.println(buf);
		Serial.println("DSRX");		// スリープ開始
		sleep(100);					// スリープ状態待ち
	}
	preStatus = status;
	sleep(100);						// 省電力用待機
}

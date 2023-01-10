#include <TinyWireM.h>
#include <Tiny4kOLED.h>

#include "TinyOLED4kfont6x8Decimal.h"
#include "TinyDS18B20.h"

OneWire ds(4); // pin - 4

TinyDS18B20 sensor(&ds);

void setup(void)
{
    //    oled.begin(128, 32, sizeof(tiny4koled_init_128x32), tiny4koled_init_128x32);
    oled.begin();

    oled.setFont(FONT6X8DECIMAL);
    oled.on();

    sensor.find_address();
}

static int device_address_index = 0;

void loop(void)
{
    // Clear the half of memory not currently being displayed.
    oled.clear();

    device_address_index = (device_address_index + 1) % 8;

    oled.print(sensor[device_address_index]);

    oled.switchFrame();
    delay(2000);
}

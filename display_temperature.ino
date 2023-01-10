#include <TinyWireM.h>
#include <Tiny4kOLED.h>

#include "TinyOLED4kfont6x8Decimal.h"

#define TinyDS18B20_I_HAVE_AN_ADDRESS
#include "TinyDS18B20.h"

OneWire ds(4); // pin - 4

// Sensor address
// 40 170 239 246 55 20 1 109
uint8_t DeviceAddress[8] = {0x28, 0xAA, 0xEF, 0xF6, 0x37, 0x14, 0x01, 0x6D};

TinyDS18B20 sensor(&ds, DeviceAddress);

void setup(void)
{
    //    oled.begin(128, 32, sizeof(tiny4koled_init_128x32), tiny4koled_init_128x32);
    oled.begin();

    oled.setFont(FONT6X8DECIMAL);
    oled.on();

    pinMode(1, OUTPUT); // initialize digital pin LED_BUILTIN as an output.
}

void loop(void)
{
    digitalWrite(1, HIGH);

    // Clear the half of memory not currently being displayed.
    oled.clear();

    sensor.request_temperatures();
    // while (!sensor.is_conversion_complete())
    //     ;

    oled.print((float)sensor.get_temp_C(), 2);

    digitalWrite(1, LOW);
    oled.switchFrame();
    delay(2000);
}

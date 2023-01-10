/*
TinyDS18B20(OneWire *ow):
    Constructs a new TinyDS18B20 object and initializes it with a
    pointer to an OneWire object. The OneWire object represents
    the 1-Wire bus and provides methods for interacting with 1-Wire devices.

void getAddress(uint8_t retries = 3);
    Searches the 1-Wire bus for a DS18B20 device and stores the device's
    address in the m_device_address member variable. The search will be
    retried up to 'retries' times if no device is found.

bool is_conversion_complete(void);
    Returns true if a temperature conversion is in progress, and false otherwise.

void request_temperatures(void);
    Sends a command to the DS18B20 to start a temperature conversion.

float get_temp_C(void);
    Reads the temperature value from the DS18B20 and returns it in degrees Celsius.
*/

#pragma once

#include <OneWire.h>

// You can save some space by predefining the address of the
// sensor in your arduino code
// #define TinyDS18B20_I_HAVE_AN_ADDRESS

class TinyDS18B20
{
private:
    OneWire *m_onewire;
#ifdef TinyDS18B20_I_HAVE_AN_ADDRESS
    uint8_t *m_device_address;

public:
    explicit TinyDS18B20(OneWire *ow, uint8_t *device_address)
        : m_onewire(ow), m_device_address(device_address){
                             // memcpy(m_device_address, device_address, 9);
                         };
#else
    uint8_t m_device_address[8];

public:
    explicit TinyDS18B20(OneWire *ow)
        : m_onewire(ow){};

    void find_address(uint8_t retries = 3)
    {
        m_onewire->reset();
        for (; (retries > 0); retries--)
        {
            m_onewire->reset_search();
            m_device_address[0] = 0x00;
            m_onewire->search(m_device_address);
        }
    }

    const float &operator[](const int i) const
    {
        return m_device_address[i];
    }
#endif

    bool is_conversion_complete(void) const
    {
        return (m_onewire->read_bit() == 1);
    }

    void request_temperatures(void)
    {
        m_onewire->reset();
        m_onewire->skip();
        m_onewire->write(0x44, 0);
    }

    float get_temp_C(void)
    {
        uint8_t data[2] = {0};

        m_onewire->reset();
        m_onewire->select(m_device_address);
        m_onewire->write(0xBE); // Read Scratchpad

        data[0] = m_onewire->read();
        data[1] = m_onewire->read();

        const float temp = (float)((data[1] << 8) + data[0]) * 0.0625f;
        return (temp < -55.0f) ? -127.0f : temp;
    }
};

//  -- END OF FILE --

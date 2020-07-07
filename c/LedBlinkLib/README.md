# LedBlink

LedBlinkLib is a c library for led blink task.

## How to use

```cpp
#include "LedBlinkLib.h"

#define SCAN_CYCLE_MS       100

LedBlinkStruct led;

int main(void)
{
    LedBlinkInit(&led, gpio_led_low, gpio_led_high);
    
    LedBlinkAdd(&led);
    
    LedBlinkConfig(&led, 10, 10);
    
    for(;;)
    {
        delay_ms(SCAN_CYCLE_MS);
        
        LedBlink();
    }
}

```

# KeyScan

KeyScanLib is a c library for key scan task.

## How to use

```cpp
#include "KeyScanLib.h"

#define SCAN_CYCLE_MS       40

KeyStruct mkey;

int main(void)
{
    KeyInit(&mkey);
    KeySetInput(&mkey, gpio_key, 0);      // gpio_key() is a function to get key status
    KeyScanAddKey(&mkey);
    // enable long press fuction, 30 means long presssed more than 30*SCAN_CYCLE_MS works
    KeyEnableLong(&mkey, 30);
    // enable double click fuction, 4 means less than 4*SCAN_CYCLE_MS between two clcik as double_click
    KeyEnableDouble(&mkey, 4);
    
    for(;;)
    {
        delay_ms(SCAN_CYCLE_MS);
        KeyScan();
        
        if(mkey.key_signal == KEY_CLICKED)
        {
            dosomething();
        }
        
        if(mkey.key_signal == KEY_DOUBLE_CLICKED)
        {
            dothisthing();
        }
        
        if(mkey.key_signal == KEY_LONG_PRESSED)
        {
            dothatthing();
        }
    }
}

```

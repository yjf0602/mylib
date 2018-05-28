/*
 * KeyScanLib.h
 *
 *  Created on: 2018-5-28
 *      Author: Nick
 */

#ifndef KEYSCANLIB_H_
#define KEYSCANLIB_H_

typedef enum
{
    KEY_NO_SIGNAL = 0,
    KEY_CLICKED,
    KEY_DOUBLE_CLICKED,
    KEY_LONG_PRESSED,
}KeySignalEnum;

typedef enum
{
    KEY_PRESSED,
    KEY_RELEASED,
}KeyStateEnum;

typedef unsigned char (* key_state_input)(void);


typedef enum
{
    KSM_NONE,
    KSM_1_PRESSED,
    KSM_1_LONG_PRESSED,
    KSM_1_RELEASED,
    KSM_2_PRESSED,
    KSM_2_RELEASED,
}KSM_EMUN;


typedef struct
{
    KeyStateEnum key_state;                 // pressed or released
    KeySignalEnum key_signal;               // 按键的信号

    key_state_input state_input;            // 按键状态更新函数
    unsigned char input_toggle;           // 输入是否进行反转

    unsigned char enable_long;            // 是否使能长按功能
    int long_cnt;                          // 长按时长

    unsigned char enable_double;          // 是否使能双击功能
    int double_delay_cnt;                  // 双击间隔

    unsigned char ignore_next_signal;     // 忽略下次信号，主要用于组合键功能

    // KeyScan 内部用于记录状态的成员
    KeyStateEnum key_last_state;

    KSM_EMUN ksm_state;         // 状态机状态
    int ksm_cnt;                // 状态停留时间计数

}KeyStruct;

void KeyScan(void);

void KeyInit(KeyStruct *key);
void KeySetInput(KeyStruct *key, key_state_input input, unsigned char toggle);
void KeyEnableLong(KeyStruct *key, int cnt);
void KeyDisableLong(KeyStruct *key);
void KeyEnableDouble(KeyStruct *key, int cnt);
void KeyDisableDouble(KeyStruct *key);

void KeyIgnoreNextSignal(KeyStruct *key);

void KeyScanAddKey(KeyStruct *key);

#endif /* KEYSCANLIB_H_ */

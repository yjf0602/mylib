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
    KeySignalEnum key_signal;               // �������ź�

    key_state_input state_input;            // ����״̬���º���
    unsigned char input_toggle;           // �����Ƿ���з�ת

    unsigned char enable_long;            // �Ƿ�ʹ�ܳ�������
    int long_cnt;                          // ����ʱ��

    unsigned char enable_double;          // �Ƿ�ʹ��˫������
    int double_delay_cnt;                  // ˫�����

    unsigned char ignore_next_signal;     // �����´��źţ���Ҫ������ϼ�����

    // KeyScan �ڲ����ڼ�¼״̬�ĳ�Ա
    KeyStateEnum key_last_state;

    KSM_EMUN ksm_state;         // ״̬��״̬
    int ksm_cnt;                // ״̬ͣ��ʱ�����

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

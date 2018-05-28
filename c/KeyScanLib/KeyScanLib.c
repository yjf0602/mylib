/*
 * KeyScanLib.c
 *
 *  Created on: 2018-5-28
 *      Author: Nick
 */

#include "KeyScanLib.h"

#define KEY_MAX_NUM     16

KeyStruct *g_keys[KEY_MAX_NUM];
int g_keys_num = 0;

void update_key_input(KeyStruct *key)
{
    if(key->input_toggle)
    {
        if(key->state_input())
            key->key_state = KEY_RELEASED;
        else
            key->key_state = KEY_PRESSED;
    }
    else
    {
        if(key->state_input())
            key->key_state = KEY_PRESSED;
        else
            key->key_state = KEY_RELEASED;
    }
}

void key_delay(void)
{
    int cnt = 2000;
    while(cnt--);
}

void KeyScan(void)
{
    int i;
    for(i=0; i<g_keys_num; i++)
    {
        KeyStruct *key = g_keys[i];

        // ����״̬����
        update_key_input(key);

        key->ksm_cnt ++;

        // �ָ� KEY_NO_SIGNAL��ȷ�������� signal ֻ����һ��
        key->key_signal = KEY_NO_SIGNAL;

        // �߼�����, ͨ��״̬��ʵ��
        if(key->ksm_state == KSM_NONE)
        {
            if(key->key_state == KEY_PRESSED)
            {
                key_delay();        // ���ڷ���
                update_key_input(key);
                if(key->key_state == KEY_PRESSED)
                {
                    key->ksm_cnt = 0;
                    key->ksm_state = KSM_1_PRESSED;
                }
            }
        }
        else if(key->ksm_state == KSM_1_PRESSED)
        {
            if(key->key_state == KEY_RELEASED)
            {
                key_delay();        // ���ڷ���
                update_key_input(key);
                if(key->key_state == KEY_RELEASED)      // ������һ���ɿ�
                {
                    if(key->enable_double)      // ʹ��˫���Ļ����Ƚ����¸�״̬
                    {
                        key->ksm_cnt = 0;
                        key->ksm_state = KSM_1_RELEASED;
                    }
                    else                        // û��ʹ��˫���Ļ������������ź�
                    {
                        key->ksm_cnt = 0;
                        key->ksm_state = KSM_NONE;
                        key->key_signal = KEY_CLICKED;
                    }
                }
            }
            else if(key->enable_long && key->ksm_cnt >= key->long_cnt) // ����
            {
                key->ksm_cnt = 0;
                key->ksm_state = KSM_1_LONG_PRESSED;
                key->key_signal = KEY_LONG_PRESSED;
            }
        }
        else if(key->ksm_state == KSM_1_LONG_PRESSED)
        {
            if(key->key_state == KEY_RELEASED)          // �����ɿ�������KSM_NONE
            {
                key_delay();        // ���ڷ���
                update_key_input(key);
                if(key->key_state == KEY_RELEASED)
                {
                    key->ksm_cnt = 0;
                    key->ksm_state = KSM_NONE;
                }
            }
        }
        else if(key->ksm_state == KSM_1_RELEASED)       // �������״̬�Ļ�˵��ʹ��˫��
        {
            if(key->key_state == KEY_PRESSED)   // �жϰ����Ƿ��ٴΰ���
            {
                key_delay();        // ���ڷ���
                update_key_input(key);
                if(key->key_state == KEY_PRESSED)
                {
                    key->ksm_cnt = 0;
                    key->ksm_state = KSM_2_PRESSED;
                }
            }
            if(key->ksm_cnt >= key->double_delay_cnt)    // �ȴ�˫����ʱ�����������ź�
            {
                key->ksm_cnt = 0;
                key->ksm_state = KSM_NONE;
                key->key_signal = KEY_CLICKED;
            }
        }
        else if(key->ksm_state == KSM_2_PRESSED)
        {
            if(key->key_state == KEY_RELEASED)      // �����ٴ��ɿ�������˫���ź�
            {
                key_delay();        // ���ڷ���
                update_key_input(key);
                if(key->key_state == KEY_RELEASED)
                {
                    key->ksm_cnt = 0;
                    key->ksm_state = KSM_NONE;
                    key->key_signal = KEY_DOUBLE_CLICKED;
                }
            }
        }

        // �Ƿ���Դ˴ε��ź�
        if(key->key_signal != KEY_NO_SIGNAL)
        {
            if(key->ignore_next_signal)
            {
                key->ignore_next_signal = 0;
                key->key_signal = KEY_NO_SIGNAL;
            }
        }

        // ��¼�ϴΰ���״̬
        key->key_last_state = key->key_state;
    }
}



void KeyInit(KeyStruct *key)
{
    key->key_state = KEY_RELEASED;
    key->key_signal = KEY_NO_SIGNAL;

    key->state_input = 0;
    key->input_toggle = 0;

    key->enable_long = 0;
    key->enable_double = 0;

    key->key_last_state = KEY_RELEASED;

    key->ksm_state = KSM_NONE;
    key->ksm_cnt = 0;

    key->ignore_next_signal = 0;
}

void KeySetInput(KeyStruct *key, key_state_input input, unsigned char toggle)
{
    key->state_input = input;
    key->input_toggle = toggle;
}

void KeyEnableLong(KeyStruct *key, int cnt)
{
    key->enable_long = 1;
    key->long_cnt = cnt;
}

void KeyDisableLong(KeyStruct *key)
{
    key->enable_long = 0;
}

void KeyEnableDouble(KeyStruct *key, int cnt)
{
    key->enable_double = 1;
    key->double_delay_cnt = cnt;
}

void KeyDisableDouble(KeyStruct *key)
{
    key->enable_double = 0;
}

void KeyIgnoreNextSignal(KeyStruct *key)
{
    key->ignore_next_signal = 1;
}


void KeyScanAddKey(KeyStruct *key)
{
    g_keys[g_keys_num] = key;
    g_keys_num ++;
}














/*
 * gpio_i2c.c
 *
 */

#include "gpio_i2c.h"

void gpio_i2c_delay_us(int us)
{
	int i;
	for(i=0; i<us*6; i++);
}

void gpio_i2c_start(gpio_i2c_t *i2c)
{
	gpio_i2c_delay_us(20);
    i2c->sda_high();
    i2c->sda_out();
    i2c->sclk_high();
    gpio_i2c_delay_us(5);
    i2c->sda_low();
    gpio_i2c_delay_us(5);
    i2c->sclk_low();
}

void gpio_i2c_stop(gpio_i2c_t *i2c)
{
    i2c->sclk_low();
    i2c->sda_low();
    i2c->sda_out();
    gpio_i2c_delay_us(5);
    i2c->sclk_high();
    gpio_i2c_delay_us(5);
    i2c->sda_high();
    gpio_i2c_delay_us(20);
}

/*
 * 0:ACK GOOD; 1:ACK FAILED
 */
unsigned char gpio_i2c_wait_ack(gpio_i2c_t *i2c)
{
    int time_cnt = 0;

    i2c->sda_in();
//    gpio_i2c_delay_us(5);
    i2c->sclk_high();
    gpio_i2c_delay_us(5);
    while(i2c->sda_read())
    {
        time_cnt ++;
        if(time_cnt >= 500)
        {
            gpio_i2c_stop(i2c);
            return 1;
        }
    }
    i2c->sclk_low();

    gpio_i2c_delay_us(15);

    return 0;
}

void gpio_i2c_ack(gpio_i2c_t *i2c)
{
    i2c->sclk_low();
    i2c->sda_low();
    i2c->sda_out();
    gpio_i2c_delay_us(5);
    i2c->sclk_high();
    gpio_i2c_delay_us(5);
    i2c->sclk_low();
    gpio_i2c_delay_us(10);
}

void gpio_i2c_nack(gpio_i2c_t *i2c)
{
    i2c->sclk_low();
    i2c->sda_high();
    i2c->sda_out();
    gpio_i2c_delay_us(5);
    i2c->sclk_high();
    gpio_i2c_delay_us(5);
    i2c->sclk_low();
    gpio_i2c_delay_us(10);
}

void gpio_i2c_write_byte(gpio_i2c_t *i2c, unsigned char byte)
{
    unsigned char i;
    i2c->sclk_low();
    for(i=0; i<8; i++)
    {
        if(byte & 0x80)
            i2c->sda_high();
        else
            i2c->sda_low();
        i2c->sda_out();
        byte <<= 1;
        gpio_i2c_delay_us(5);
        i2c->sclk_high();
        gpio_i2c_delay_us(5);
        i2c->sclk_low();
    }
    gpio_i2c_delay_us(5);
}

unsigned char gpio_i2c_read_byte(gpio_i2c_t *i2c)
{
    unsigned char byte = 0;
    unsigned char i;

    i2c->sda_in();
    for(i=0; i<8; i++)
    {
        gpio_i2c_delay_us(5);
        i2c->sclk_high();
        byte <<= 1;
        if(i2c->sda_read())
            byte ++;
        gpio_i2c_delay_us(5);
        i2c->sclk_low();
    }

    return byte;
}



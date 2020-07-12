/*
 * gpio_i2c.h
 */

#ifndef GPIO_I2C_H_
#define GPIO_I2C_H_

typedef void (*void_func_void) (void);
typedef unsigned char (*u8_func_void) (void);

typedef struct
{
    void_func_void sclk_high;
    void_func_void sclk_low;

    void_func_void sda_in;
    void_func_void sda_out;
    void_func_void sda_high;
    void_func_void sda_low;
    u8_func_void sda_read;

}gpio_i2c_t;

void gpio_i2c_start(gpio_i2c_t *i2c);
void gpio_i2c_stop(gpio_i2c_t *i2c);
unsigned char gpio_i2c_wait_ack(gpio_i2c_t *i2c);
void gpio_i2c_ack(gpio_i2c_t *i2c);
void gpio_i2c_nack(gpio_i2c_t *i2c);
void gpio_i2c_write_byte(gpio_i2c_t *i2c, unsigned char byte);
unsigned char gpio_i2c_read_byte(gpio_i2c_t *i2c);

#endif /* GPIO_I2C_H_ */

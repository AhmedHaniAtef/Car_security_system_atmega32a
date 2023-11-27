/**
 * @file     hal_gpio.h
 * @author   Ahmed Hani Atef
 * @brief    contains the new data user types
 * @version  0.1
 * @date     2023-08-30
 */


#ifndef HAL_GPIO_H
#define	HAL_GPIO_H


/*****************************************************
*           Start of Section :    includes           *
******************************************************/

#include "../compiler.h"
#include "../device_config/device_config.h"
#include "../mcal_std_types/mcal_std_types.h"

/*****************************************************
*             End of Section :    includes           *
******************************************************/



/*****************************************************
*           Start of Section :    Data Types         *
******************************************************/
/**
 * @brief   new data type to get the configuration of a gpio pin 
 * @param pin       : this is a reference to @ref pin_index_t data type defined at @headerfile : mcal_std_types.h  
 * @param port      : this is a reference to @ref port_index_t data type defined at @headerfile : mcal_std_types.h  
 * @param direction : this is a reference to @ref direction_t data type defined at @headerfile : mcal_std_types.h  
 * @param logic     : this is a reference to @ref logic_t data type defined at @headerfile : mcal_std_types.h  
 */
typedef struct {
    uint8_t pin : 3;
    uint8_t port : 3;
    uint8_t direction : 1;
    uint8_t logic : 1;
}pin_cofig_t;

/*****************************************************
*             End of Section :    Data Types         *
******************************************************/

/*****************************************************
*         Start of Section :    Function declaration  *
******************************************************/

std_returntype gpio_pin_direction_initialize (const pin_cofig_t *__pin, gpio_direction_t __direction);
std_returntype gpio_pin_direction_status (const pin_cofig_t *__pin, gpio_direction_t *__direction);
std_returntype gpio_pin_read (const pin_cofig_t *__pin, gpio_logic_t *__logic);
std_returntype gpio_pin_write (const pin_cofig_t *__pin, gpio_logic_t __logic);
std_returntype gpio_pin_toggle (const pin_cofig_t *__pin);
std_returntype gpio_pin_initialize (const pin_cofig_t *__pin, gpio_direction_t __direction, gpio_logic_t __logic);


std_returntype gpio_port_direction_initialize (const port_index_t __port, uint8_t __direction);
std_returntype gpio_port_direction_status (const port_index_t __port, uint8_t *__direction);
std_returntype gpio_port_read (const port_index_t __port, gpio_logic_t *__logic);
std_returntype gpio_port_write (const port_index_t __port, gpio_logic_t __logic);
std_returntype gpio_port_toggle (const port_index_t __port);
std_returntype gpio_port_initialize (const port_index_t __port, uint8_t __direction, gpio_logic_t __logic);

/*****************************************************
*             End of Section :    Function declaration  *
******************************************************/






#endif // HAL_GPIO_H
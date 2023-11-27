/**
 * @file     mcal_std_types.h
 * @author   Ahmed Hani Atef
 * @brief    contains the new data user types
 * @version  0.1
 * @date     2023-08-30
 */


#ifndef MCAL_STD_TYPES_H
#define MCAL_STD_TYPES_H

/*****************************************************
*           Start of Section :    includes           *
******************************************************/

/*****************************************************
*             End of Section :    includes           *
******************************************************/



/*****************************************************
*           Start of Section :    defines            *
******************************************************/
#define EXIT_STATUS_SUCCESS (0)
#define EXIT_STATUS_FAILED  (1)

#define STD_OK      ((std_returntype) 0)
#define STD_NOT_OK  ((std_returntype) 1)

#define __8_BIT_ARC_MICROCONTROLLER_
/*****************************************************
*             End of Section :    defines            *
******************************************************/



/*****************************************************
*           Start of Section :    typedef            *
******************************************************/
#ifdef __8_BIT_ARC_MICROCONTROLLER_ 

typedef unsigned char   boolean;
typedef unsigned char   uint8_t;
typedef unsigned int    uint16_t;
typedef unsigned long   uint32_t;
typedef signed char     sint8_t;
typedef signed int      sint16_t;
typedef signed long     sint32_t;
typedef float           float32_t;

#elif  __16_BIT_ARC_MICROCONTROLLER_ 

#elif  __32_BIT_ARC_MICROCONTROLLER_ 

#else 

#endif

typedef uint8_t std_returntype;

typedef enum {
    GPIO_LOW = 0,   
    GPIO_HIGH
}gpio_logic_t;

typedef enum {
    PIN0_I = 0,   
    PIN1_I,
    PIN2_I,
    PIN3_I,
    PIN4_I,
    PIN5_I,
    PIN6_I,
    PIN7_I,
}pin_index_t;

typedef enum {
    GPIO_INPUT = 0,   
    GPIO_OUTPUT
}gpio_direction_t;

typedef enum {
    PORTA_I = 0,
    PORTB_I,
    PORTC_I,
    PORTD_I,
}port_index_t;

typedef enum {
    IDLE = 0,
    ACTIVE
}status_t;

typedef gpio_logic_t logic_t;


/*****************************************************
*             End of Section :    typedef            *
******************************************************/


#endif //MCAL_STD_TYPES_H


/******************************************************************************************************************************
    Log 
    ---------------------------------------------------------------------------------------------------------------------------          
    author              date                        details
    ***************************************************************************************************************************
    Ahmed Hani Atef     2023-08-30                  - create the file
                                                    - create the new types of 8 bit architecture microcontroller

    Ahmed Hani Atef     2023-09-01                  - create enums to ease accessing the microcontroller pins
 */
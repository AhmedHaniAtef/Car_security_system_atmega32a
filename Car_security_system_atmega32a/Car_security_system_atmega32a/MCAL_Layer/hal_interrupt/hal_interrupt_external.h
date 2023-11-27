/**
 * @file hal_interrupt_external.h
 * @author Ahmed Hani Atef
 * @date 2023-10-12
 */


#ifndef HAL_INTERRUPT_EXTERNAL_H
#define	HAL_INTERRUPT_EXTERNAL_H


/*****************************************************
*           Start of Section :    includes           *
******************************************************/

#include "hal_interrupt_config.h"

/*****************************************************
*             End of Section :    includes           *
******************************************************/


/*****************************************************
*           Start of Section :    Macro defines      *
******************************************************/
#define INT0_PIN    (2)
#define INT1_PIN    (3)
#define INT2_PIN    (2)


// ----------------- INT1 all bits ------------------- 

#define ISC10_BIT   (2)  // they are used 
#define ISC11_BIT   (3)  // to control INT1

#define INT1_BIT    (7)

#define INTF1_BIT   (7)

//----------------------------------------------------


// ----------------- INT0 all bits -------------------

#define ISC00_BIT   (0) // they are used 
#define ISC01_BIT   (1) // to control INT0

#define INT0_BIT    (6)

#define INTF0_BIT   (6)

//----------------------------------------------------


// ----------------- INT2 all bits -------------------

#define ISC2_BIT    (6)  

#define INT2_BIT    (5)

#define INTF2_BIT   (5)

//----------------------------------------------------

/*****************************************************
*             End of Section :    Macro defines      *
******************************************************/


/*****************************************************
*           Start of Section :    Macro functions    *
******************************************************/

#define INTERRUPT_EX_INT1_ENABLE()              (SET_BIT(GICR_REGISTER , INT1_BIT))
#define INTERRUPT_EX_INT0_ENABLE()              (SET_BIT(GICR_REGISTER , INT0_BIT))
#define INTERRUPT_EX_INT2_ENABLE()              (SET_BIT(GICR_REGISTER , INT2_BIT))
#define INTERRUPT_EX_INT1_DISABLE()             (CLEAR_BIT(GICR_REGISTER , INT1_BIT))
#define INTERRUPT_EX_INT0_DISABLE()             (CLEAR_BIT(GICR_REGISTER , INT0_BIT))
#define INTERRUPT_EX_INT2_DISABLE()             (CLEAR_BIT(GICR_REGISTER , INT2_BIT))
#define INTERRUPT_EX_INT1_FLAG_CLEAR()          (HWREG(GIFR_REGISTER) = ((~(HWREG(GIFR_REGISTER))) | (1 << INTF1_BIT)) & 0xE0)
#define INTERRUPT_EX_INT0_FLAG_CLEAR()          (HWREG(GIFR_REGISTER) = ((~(HWREG(GIFR_REGISTER))) | (1 << INTF0_BIT)) & 0xE0)
#define INTERRUPT_EX_INT2_FLAG_CLEAR()          (HWREG(GIFR_REGISTER) = ((~(HWREG(GIFR_REGISTER))) | (1 << INTF2_BIT)) & 0xE0)
#define INTERRUPT_EX_INT1_LOW_LEVEL_TRIG()      ((CLEAR_BIT(MCUCR_REGISTER , ISC10_BIT))); (CLEAR_BIT(MCUCR_REGISTER , ISC11_BIT))
#define INTERRUPT_EX_INT1_CHANGE_TRIG()         ((SET_BIT(MCUCR_REGISTER , ISC10_BIT))); (CLEAR_BIT(MCUCR_REGISTER , ISC11_BIT))
#define INTERRUPT_EX_INT1_FALLING_EDGE_TRIG()   ((CLEAR_BIT(MCUCR_REGISTER , ISC10_BIT))); (SET_BIT(MCUCR_REGISTER , ISC11_BIT))
#define INTERRUPT_EX_INT1_RISING_EDGE_TRIG()    ((SET_BIT(MCUCR_REGISTER , ISC10_BIT))); (SET_BIT(MCUCR_REGISTER , ISC11_BIT))
#define INTERRUPT_EX_INT0_LOW_LEVEL_TRIG()      ((CLEAR_BIT(MCUCR_REGISTER , ISC00_BIT))); (CLEAR_BIT(MCUCR_REGISTER , ISC01_BIT))
#define INTERRUPT_EX_INT0_CHANGE_TRIG()         ((SET_BIT(MCUCR_REGISTER , ISC00_BIT))); (CLEAR_BIT(MCUCR_REGISTER , ISC01_BIT))
#define INTERRUPT_EX_INT0_FALLING_EDGE_TRIG()   ((CLEAR_BIT(MCUCR_REGISTER , ISC00_BIT))); (SET_BIT(MCUCR_REGISTER , ISC01_BIT))
#define INTERRUPT_EX_INT0_RISING_EDGE_TRIG()    ((SET_BIT(MCUCR_REGISTER , ISC00_BIT))); (SET_BIT(MCUCR_REGISTER , ISC01_BIT))
#define INTERRUPT_EX_INT2_FALLING_EDGE_TRIG()   (CLEAR_BIT(MCUCSR_REGISTER , ISC2_BIT))
#define INTERRUPT_EX_INT2_RISING_EDGE_TRIG()    (SET_BIT(MCUCSR_REGISTER , ISC2_BIT))

/*****************************************************
*             End of Section :    Macro functions    *
******************************************************/


/*****************************************************
*           Start of Section :    Data Types         *
******************************************************/



typedef struct 
{
    pin_cofig_t pin;
    union 
    {
        ISR_Handler EXT_InterruptHandler;
        struct 
        {
            ISR_Handler EXT_InterruptHandler_High;
            ISR_Handler EXT_InterruptHandler_Low;
        }logical_change;
    }handler;
    uint8_t trigger_case : 2;
    uint8_t source : 2;
}interrupt_external_cfg_t;

typedef enum
{
    LOW_LEVEL_TRIGGER = 0,
    LOGICAL_CHANGE_TRIGGER,
    FALLING_EDGE_TRIGGER,
    RISING_EDGE_TRIGGER,
}interrupt_external_trig_t;

typedef enum
{
    INT0_INTERRUPT = 0,
    INT1_INTERRUPT,
    INT2_INTERRUPT,
}interrupt_external_src_t;

/* NOTE: find a good implementation for the logical_change to handle in case of 
high and case of low so that each one executes a different ISR 
HINT: use union to solve it this will be in line 102 */

/*****************************************************
*             End of Section :    Data Types         *
******************************************************/



/*****************************************************
*         Start of Section :    Function declaration  *
******************************************************/
std_returntype interrupt_ex_INTx_enable(interrupt_external_cfg_t *__interrupt);
std_returntype interrupt_ex_INTx_disable(interrupt_external_cfg_t *__interrupt);
/*****************************************************
*             End of Section :    Function declaration  *
******************************************************/






#endif // HAL_INTERRUPT_EXTERNAL_H
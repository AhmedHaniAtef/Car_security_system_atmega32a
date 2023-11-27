/**
 * @file hal_interrupt_config.h
 * @author Ahmed Hani Atef
 * @date 2023-10-12
 */


#ifndef HAL_INTERRUPT_CONFIG_H
#define	HAL_INTERRUPT_CONFIG_H


/*****************************************************
*           Start of Section :    includes           *
******************************************************/

#include "..\atmega32a_register.h"
#include "..\compiler.h"
#include "..\hal_gpio\hal_gpio.h"
#include "hal_interrupt_gen_cfg.h"

/*****************************************************
*             End of Section :    includes           *
******************************************************/


/*****************************************************
*           Start of Section :    Macro defines      *
******************************************************/
#define INTERRUPT_ENABLED   (1)
#define INTERRUPT_DISABLED  (0)
#define INTERRUPT_OCCUR     (1)
#define INTERRUPT_NOT_OCCUR (0)

// ------------ Global Interrupt Enable bit ----------

#define  I_BIT		(7)

//----------------------------------------------------


// ------------ Interrupt Vector Select bit ----------

#define IVCE_BIT    (0)
#define IVSEL_BIT   (1)

//----------------------------------------------------

/*****************************************************
*             End of Section :    Macro defines      *
******************************************************/


/*****************************************************
*           Start of Section :    Macro functions    *
******************************************************/

//#define INTERRUPT_GLOBAL_ENABLE()   sei()
//#define INTERRUPT_GLOBAL_DISABLE()  cli()

#define INTERRUPT_GLOBAL_ENABLE()   (SET_BIT(STATUS_REGISTER, I_BIT))
#define INTERRUPT_GLOBAL_DISABLE()  (CLEAR_BIT(STATUS_REGISTER, I_BIT))


/*****************************************************
*             End of Section :    Macro functions    *
******************************************************/


/*****************************************************
*           Start of Section :    Data Types         *
******************************************************/
typedef void (* ISR_Handler)(void);
/*****************************************************
*             End of Section :    Data Types         *
******************************************************/



/*****************************************************
*         Start of Section :    Function declaration  *
******************************************************/

/*****************************************************
*             End of Section :    Function declaration  *
******************************************************/






#endif // HAL_INTERRUPT_CONFIG_H
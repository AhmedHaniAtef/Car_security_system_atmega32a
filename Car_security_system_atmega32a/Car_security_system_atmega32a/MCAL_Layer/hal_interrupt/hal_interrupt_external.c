/**
 * @file hal_interrupt_external.c
 * @author Ahmed Hani Atef
 * @date 2023-10-12
 */



/*****************************************************
*           Start of Section :    includes           *
******************************************************/
#include "hal_interrupt_external.h"
/*****************************************************
*             End of Section :    includes           *
******************************************************/


/*****************************************************
*         Start of Section :    Function definition  *
******************************************************/

static std_returntype interrupt_global_enable(interrupt_external_cfg_t *__interrupt);
static std_returntype interrupt_global_disable(interrupt_external_cfg_t *__interrupt);
static std_returntype interrupt_external_enable(interrupt_external_cfg_t *__interrupt);
static std_returntype interrupt_external_disable(interrupt_external_cfg_t *__interrupt);
static std_returntype interrupt_pin_initialize(interrupt_external_cfg_t *__interrupt);
static std_returntype interrupt_set_trigger_case(interrupt_external_cfg_t *__interrupt);
static std_returntype interrupt_set_handler(interrupt_external_cfg_t *__interrupt);
static std_returntype interrupt_free_handler(interrupt_external_cfg_t *__interrupt);
/*****************************************************
*             End of Section : Function definition  *
******************************************************/



/*****************************************************
*       Start of Section : Variable declaration      *
******************************************************/
ISR_Handler EXT_InterruptHandler_INT0 = NULL;
ISR_Handler EXT_InterruptHandler_INT1 = NULL;
ISR_Handler EXT_InterruptHandler_INT2 = NULL;
ISR_Handler EXT_InterruptHandler_INT0_High = NULL;
ISR_Handler EXT_InterruptHandler_INT1_High = NULL;
ISR_Handler EXT_InterruptHandler_INT0_Low = NULL;
ISR_Handler EXT_InterruptHandler_INT1_Low = NULL;


/*****************************************************
*        End of Section : Variable declaration       *
******************************************************/



/*****************************************************
*         Start of Section :    Function declaration  *
******************************************************/

std_returntype interrupt_ex_INTx_enable(interrupt_external_cfg_t *__interrupt)
{
    std_returntype ret = STD_OK;
    if (NULL == __interrupt)
    {
        ret = STD_NOT_OK;
    }
    else
    {
        // Global Interrupt Disable
        interrupt_global_disable(__interrupt);
        // External Interrupt Enable
        interrupt_external_enable(__interrupt);
        // Pin Initialize
        interrupt_pin_initialize(__interrupt);
        // Set Trigger case
        interrupt_set_trigger_case(__interrupt);
        // Handler Initialization
        interrupt_set_handler(__interrupt);
        // Global Interrupt Enable
        interrupt_global_enable(__interrupt);
    }
    return ret;
}

std_returntype interrupt_ex_INTx_disable(interrupt_external_cfg_t *__interrupt)
{
    std_returntype ret = STD_OK;
    if (NULL == __interrupt)
    {
        ret = STD_NOT_OK;
    }
    else
    {
        // External Interrupt Disable
        interrupt_external_disable(__interrupt);
        // Handler DeInitialization
        interrupt_free_handler(__interrupt);
    }
    return ret;
}

/*****************************************************
*             End of Section : Function declaration  *
******************************************************/



/*****************************************************
*   Start of Section :  Helper Function declaration  *
******************************************************/

static std_returntype interrupt_global_enable(interrupt_external_cfg_t *__interrupt)
{
    std_returntype ret = STD_OK;
    if (NULL == __interrupt)
    {
        ret = STD_NOT_OK;
    }
    else
    {
        INTERRUPT_GLOBAL_ENABLE();
    }
    return ret;
}
static std_returntype interrupt_global_disable(interrupt_external_cfg_t *__interrupt)
{
    std_returntype ret = STD_OK;
    if (NULL == __interrupt)
    {
        ret = STD_NOT_OK;
    }
    else
    {
        INTERRUPT_GLOBAL_DISABLE();
    }
    return ret;
}
static std_returntype interrupt_external_enable(interrupt_external_cfg_t *__interrupt)
{
    std_returntype ret = STD_OK;
    if (NULL == __interrupt)
    {
        ret = STD_NOT_OK;
    }
    else
    {
        switch (__interrupt->source)
        {
        case INT0_INTERRUPT:
            INTERRUPT_EX_INT0_ENABLE();
            break;

        case INT1_INTERRUPT:
            INTERRUPT_EX_INT1_ENABLE();
            break;

        case INT2_INTERRUPT:
            INTERRUPT_EX_INT2_ENABLE();
            break;

        default:
            ret = STD_NOT_OK;
            break;
        }
    }
    return ret;
}
static std_returntype interrupt_external_disable(interrupt_external_cfg_t *__interrupt)
{
    std_returntype ret = STD_OK;
    if (NULL == __interrupt)
    {
        ret = STD_NOT_OK;
    }
    else
    {
        switch (__interrupt->source)
        {
        case INT0_INTERRUPT:
            INTERRUPT_EX_INT0_DISABLE();
            break;

        case INT1_INTERRUPT:
            INTERRUPT_EX_INT1_DISABLE();
            break;

        case INT2_INTERRUPT:
            INTERRUPT_EX_INT2_DISABLE();
            break;

        default:
            ret = STD_NOT_OK;
            break;
        }
    }
    return ret;
}
static std_returntype interrupt_pin_initialize(interrupt_external_cfg_t *__interrupt)
{
    std_returntype ret = STD_OK;
    if (NULL == __interrupt)
    {
        ret = STD_NOT_OK;
    }
    else
    {
        ret |= gpio_pin_initialize((&(__interrupt->pin)), (__interrupt->pin.direction), (__interrupt->pin.logic));
    }
    return ret;
}
static std_returntype interrupt_set_trigger_case(interrupt_external_cfg_t *__interrupt)
{
    std_returntype ret = STD_OK;
    if (NULL == __interrupt)
    {
        ret = STD_NOT_OK;
    }
    else
    {
        switch (__interrupt->source)
        {
        case INT0_INTERRUPT:
            switch (__interrupt->trigger_case)
            {
            case LOW_LEVEL_TRIGGER:
                INTERRUPT_EX_INT0_LOW_LEVEL_TRIG();
                break;

            case LOGICAL_CHANGE_TRIGGER:
                INTERRUPT_EX_INT0_CHANGE_TRIG();
                break;

            case FALLING_EDGE_TRIGGER:
                INTERRUPT_EX_INT0_FALLING_EDGE_TRIG();
                break;

            case RISING_EDGE_TRIGGER:
                INTERRUPT_EX_INT0_RISING_EDGE_TRIG();
                break;

            default:
                ret = STD_NOT_OK;
                break;
            }
            break;

        case INT1_INTERRUPT:
            switch (__interrupt->trigger_case)
            {
            case LOW_LEVEL_TRIGGER:
                INTERRUPT_EX_INT1_LOW_LEVEL_TRIG();
                break;

            case LOGICAL_CHANGE_TRIGGER:
                INTERRUPT_EX_INT1_CHANGE_TRIG();
                break;

            case FALLING_EDGE_TRIGGER:
                INTERRUPT_EX_INT1_FALLING_EDGE_TRIG();
                break;

            case RISING_EDGE_TRIGGER:
                INTERRUPT_EX_INT1_RISING_EDGE_TRIG();
                break;

            default:
                ret = STD_NOT_OK;
                break;
            }
            break;

        case INT2_INTERRUPT:
            switch (__interrupt->trigger_case)
            {
            case FALLING_EDGE_TRIGGER:
                INTERRUPT_EX_INT2_FALLING_EDGE_TRIG();
                break;

            case RISING_EDGE_TRIGGER:
                INTERRUPT_EX_INT2_RISING_EDGE_TRIG();
                break;

            default:
                ret = STD_NOT_OK;
                break;
            }
            break;

        default:
            ret = STD_NOT_OK;
            break;
        }
    }
    return ret;
}
static std_returntype interrupt_set_handler(interrupt_external_cfg_t *__interrupt)
{
    std_returntype ret = STD_OK;
    if (NULL == __interrupt)
    {
        ret = STD_NOT_OK;
    }
    else
    {
        switch (__interrupt->source)
        {
        case INT0_INTERRUPT:
            if(LOGICAL_CHANGE_TRIGGER == __interrupt->trigger_case)
            {
                EXT_InterruptHandler_INT0_Low  = __interrupt->handler.logical_change.EXT_InterruptHandler_Low;
                EXT_InterruptHandler_INT0_High = __interrupt->handler.logical_change.EXT_InterruptHandler_High;
            }
            else
            {
                EXT_InterruptHandler_INT0 = __interrupt->handler.EXT_InterruptHandler;
            }
            break;

        case INT1_INTERRUPT:
            if(LOGICAL_CHANGE_TRIGGER == __interrupt->trigger_case)
            {
                EXT_InterruptHandler_INT1_Low  = __interrupt->handler.logical_change.EXT_InterruptHandler_Low;
                EXT_InterruptHandler_INT1_High = __interrupt->handler.logical_change.EXT_InterruptHandler_High;
            }
            else
            {
                EXT_InterruptHandler_INT1 = __interrupt->handler.EXT_InterruptHandler;
            }
            break;

        case INT2_INTERRUPT:
            EXT_InterruptHandler_INT2 = __interrupt->handler.EXT_InterruptHandler;
            break;

        default:
            ret = STD_NOT_OK;
            break;
        }
    }
    return ret;
}
static std_returntype interrupt_free_handler(interrupt_external_cfg_t *__interrupt)
{
    std_returntype ret = STD_OK;
    if (NULL == __interrupt)
    {
        ret = STD_NOT_OK;
    }
    else
    {
        switch (__interrupt->source)
        {
        case INT0_INTERRUPT:
            if(LOGICAL_CHANGE_TRIGGER == __interrupt->trigger_case)
            {
                EXT_InterruptHandler_INT0_Low  = NULL;
                EXT_InterruptHandler_INT0_High = NULL;
            }
            else
            {
                EXT_InterruptHandler_INT0 = NULL;
            }
            break;

        case INT1_INTERRUPT:
            if(LOGICAL_CHANGE_TRIGGER == __interrupt->trigger_case)
            {
                EXT_InterruptHandler_INT1_Low  = NULL;
                EXT_InterruptHandler_INT1_High = NULL;
            }
            else
            {
                EXT_InterruptHandler_INT1 = NULL;
            }
            break;

        case INT2_INTERRUPT:
            EXT_InterruptHandler_INT2 = NULL;
            break;

        default:
            ret = STD_NOT_OK;
            break;
        }
    }
    return ret;
}

/*****************************************************
*    End of Section :  Helper Function declaration   *
******************************************************/



/*****************************************************
*         Start of Section :  ISR declaration        *
******************************************************/

ISR(INT0_vect)
{
    // store status register to restore it at end of ISR
    uint8_t status_reg = (HWREG(STATUS_REGISTER));
    // clear flag to make sure the interrupt won't occur multiple times
    INTERRUPT_EX_INT0_FLAG_CLEAR();
    // enable interrupt by enabling global interrupt enable
#ifdef  INTERRUPT_NESTING_ENABLE
    INTERRUPT_GLOBAL_ENABLE();
#endif
    // call the routine for INT0 depending on the trigger case 
    if(EXT_InterruptHandler_INT0)
    {
        EXT_InterruptHandler_INT0();
    }
    else if((EXT_InterruptHandler_INT0_High) && 
            (EXT_InterruptHandler_INT0_Low))
    {
        if (READ_BIT(PIND_REGISTER, INT0_PIN))
        {
            EXT_InterruptHandler_INT0_High();
        }
        else
        {
            EXT_InterruptHandler_INT0_Low();
        }
    }
	// solution for debouncing
#ifdef	INT0_DEBOUNCE_CASE
	_delay_ms(100);
#endif
    // restore status register 
    HWREG(STATUS_REGISTER) = status_reg;
}

ISR(INT1_vect)
{
    // store status register to restore it at end of ISR
    uint8_t status_reg = (HWREG(STATUS_REGISTER));
    // clear flag to make sure the interrupt won't occur multiple times
    INTERRUPT_EX_INT1_FLAG_CLEAR();
    // enable interrupt by enabling global interrupt enable
#ifdef  INTERRUPT_NESTING_ENABLE
    INTERRUPT_GLOBAL_ENABLE();
#endif
    // call the routine for INT1 depending on the trigger case 
    if(EXT_InterruptHandler_INT1)
    {
        EXT_InterruptHandler_INT1();
    }
    else if((EXT_InterruptHandler_INT1_High) && 
            (EXT_InterruptHandler_INT1_Low))
    {
        if (READ_BIT(PIND_REGISTER, INT1_PIN))
        {
            EXT_InterruptHandler_INT1_High();
        }
        else
        {
            EXT_InterruptHandler_INT1_Low();
        }
    }
	// solution for debouncing
#ifdef	INT1_DEBOUNCE_CASE
	_delay_ms(100);
#endif
    // restore status register 
    HWREG(STATUS_REGISTER) = status_reg;
}

ISR(INT2_vect)
{
    // store status register to restore it at end of ISR
    uint8_t status_reg = (HWREG(STATUS_REGISTER));
	// clear flag to make sure the interrupt won't occur multiple times
    INTERRUPT_EX_INT2_FLAG_CLEAR();
    // enable interrupt by enabling global interrupt enable
#ifdef  INTERRUPT_NESTING_ENABLE
    INTERRUPT_GLOBAL_ENABLE();
#endif
    // call the routine for INT2
    if(EXT_InterruptHandler_INT2)
    {
        EXT_InterruptHandler_INT2();
    }
	// solution for debouncing
#ifdef	INT2_DEBOUNCE_CASE
	_delay_ms(100);
#endif
    // restore status register 
    HWREG(STATUS_REGISTER) = status_reg;
}

/*****************************************************
*          End of Section :  ISR declaration         *
******************************************************/



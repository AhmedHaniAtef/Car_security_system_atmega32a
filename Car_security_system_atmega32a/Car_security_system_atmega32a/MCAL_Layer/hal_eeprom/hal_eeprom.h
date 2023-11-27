/**
 * @file hal_eeprom.h
 * @author Ahmed Hani Atef
 * @date 2023-10-22
 */

#ifndef HAL_EEPROM_H
#define HAL_EEPROM_H


/*****************************************************
*           Start of Section :    includes           *
******************************************************/
#include "../atmega32a_register.h"
#include "../compiler.h"
#include "../device_config/device_config.h"
#include "../mcal_std_types/mcal_std_types.h"
/*****************************************************
*             End of Section :    includes           *
******************************************************/



/*****************************************************
*           Start of Section :    Macro Defines      *
******************************************************/
// ----------------------- EECR BITS --------------------------
#define EERIE_BIT   (3)
#define EEMWE_BIT   (2)
#define EEWE_BIT    (1)
#define EERE_BIT    (0)
//-------------------------------------------------------------

// ------------------- EEPROM Access Registers ----------------
#define EEPROM_ADDRESS_LOWER_ACCESS     (HWREG(EEARL_REGISTER))
#define EEPROM_ADDRESS_HIGHER_ACCESS    (HWREG(EEARH_REGISTER))
#define EEPROM_DATA_ACCESS              (HWREG(EEDR_REGISTER))
// ------------------------------------------------------------

#define ZERO_BYTE_MASK  (0)
#define ONE_BYTE_MASK   (8)
#define TWO_BYTE_MASK   (16)
#define THREE_BYTE_MASK (24)
#define FOUR_BYTE_MASK  (32)
/*****************************************************
*             End of Section :    Macro Defines      *
******************************************************/


/*****************************************************
*           Start of Section :    Macro Functions    *
******************************************************/
#define EEPROM_READY_INTERRUPT_ENABLE()     (SET_BIT(EECR_REGISTER, EERIE_BIT))
#define EEPROM_READY_INTERRUPT_DISABLE()    (CLEAR_BIT(EECR_REGISTER, EERIE_BIT))
#define EEPROM_MASTER_WRITE_ENABLE()        (SET_BIT(EECR_REGISTER, EEMWE_BIT))
#define EEPROM_MASTER_WRITE_DISABLE()       (CLEAR_BIT(EECR_REGISTER, EEMWE_BIT))
#define EEPROM_WRITE_ENABLE()               (SET_BIT(EECR_REGISTER, EEWE_BIT))
#define EEPROM_WRITE_DISABLE()              (CLEAR_BIT(EECR_REGISTER, EEWE_BIT))
#define EEPROM_WRITE_READ()                 (READ_BIT(EECR_REGISTER, EEWE_BIT))
#define EEPROM_READ_ENABLE()                (SET_BIT(EECR_REGISTER, EERE_BIT))
#define EEPROM_READ_DISABLE()               (CLEAR_BIT(EECR_REGISTER, EERE_BIT))
/*****************************************************
*             End of Section :    Macro Functions    *
******************************************************/


/*****************************************************
*         Start of Section :    Function declaration  *
******************************************************/
std_returntype EEPROM_write_byte (uint16_t __address, uint8_t __data);
std_returntype EEPROM_read_byte (uint16_t __address, uint8_t *__data);
std_returntype EEPROM_write_uint16 (uint16_t __address, uint16_t __data);
std_returntype EEPROM_read_uint16 (uint16_t __address, uint16_t *__data);
std_returntype EEPROM_write_uint32 (uint16_t __address, uint32_t __data);
std_returntype EEPROM_read_uint32 (uint16_t __address, uint32_t *__data);
std_returntype EEPROM_write_sint8 (uint16_t __address, sint8_t __data);
std_returntype EEPROM_read_sint8 (uint16_t __address, sint8_t *__data);
std_returntype EEPROM_write_sint16 (uint16_t __address, sint16_t __data);
std_returntype EEPROM_read_sint16 (uint16_t __address, sint16_t *__data);
std_returntype EEPROM_write_sint32 (uint16_t __address, sint32_t __data);
std_returntype EEPROM_read_sint32 (uint16_t __address, sint32_t *__data);
std_returntype EEPROM_write_float32 (uint16_t __address, float32_t __data);
std_returntype EEPROM_read_float32 (uint16_t __address, float32_t *__data);
std_returntype EEPROM_write_string (uint16_t __address, uint8_t *str);
std_returntype EEPROM_read_string (uint16_t __address, uint8_t *str);
std_returntype EEPROM_write_string_dynamic_mem (uint16_t __address, uint8_t *__str);
std_returntype EEPROM_read_string_dynamic_mem (uint16_t __address, uint8_t **__str);
/*****************************************************
*             End of Section :    Function declaration*
******************************************************/



#endif // HAL_EEPROM_H
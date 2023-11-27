/**
 * @file hal_eeprom.c
 * @author Ahmed Hani Atef
 * @date 2023-10-22
 */



/*****************************************************
*           Start of Section :    includes           *
******************************************************/
#include "hal_eeprom.h"
/*****************************************************
*             End of Section :    includes           *
******************************************************/


/*****************************************************
*         Start of Section :    Function declaration  *
******************************************************/
std_returntype EEPROM_write_byte (uint16_t __address, uint8_t __data)
{
    std_returntype ret = STD_OK;
    if (__address >1023)
    {
        ret = STD_NOT_OK;
    }
    else
    {
        // Wait for completion of previous write
        while (EEPROM_WRITE_READ());
        // Set up address and data registers
        EEPROM_ADDRESS_LOWER_ACCESS  = (uint8_t)(__address & 0x00FF);
        EEPROM_ADDRESS_HIGHER_ACCESS = (uint8_t)((__address & 0xFF00) >> ONE_BYTE_MASK);
        EEPROM_DATA_ACCESS           = (uint8_t)(__data);
        // Write logical one to EEMWE
        EEPROM_MASTER_WRITE_ENABLE();
        // Start eeprom write by setting EEWE
        EEPROM_WRITE_ENABLE();
    }
    return ret;
}

std_returntype EEPROM_read_byte (uint16_t __address, uint8_t *__data)
{
    std_returntype ret = STD_OK;
    if ((NULL == __data) || (__address >1023))
    {
        ret = STD_NOT_OK;
    }
    else
    {
        // Wait for completion of previous write
        while (EEPROM_WRITE_READ());
        // Set up address and data registers
        EEPROM_ADDRESS_LOWER_ACCESS  = (uint8_t)(__address & 0x00FF);
        EEPROM_ADDRESS_HIGHER_ACCESS = (uint8_t)((__address & 0xFF00) >> ONE_BYTE_MASK);
        // Start eeprom read by setting EERE
        EEPROM_READ_ENABLE();
        // Return data from data register
        *__data = EEPROM_DATA_ACCESS;
    }
    return ret;
}

std_returntype EEPROM_write_uint16 (uint16_t __address, uint16_t __data)
{
    std_returntype ret = STD_OK;
    if (__address >1023)
    {
        ret = STD_NOT_OK;
    }
    else
    {
        ret |= EEPROM_write_byte((__address++), (uint8_t)((__data & 0xFF00) >> ONE_BYTE_MASK));
        ret |= EEPROM_write_byte((__address++), (uint8_t)((__data & 0x00FF) >> ZERO_BYTE_MASK));
    }
    return ret;
}

std_returntype EEPROM_read_uint16 (uint16_t __address, uint16_t *__data)
{
    std_returntype ret = STD_OK;
    uint8_t temp_data = 0;
    if ((NULL == __data) || (__address >1023))
    {
        ret = STD_NOT_OK;
    }
    else
    {
        *__data = 0;

        ret |= EEPROM_read_byte(__address++, &temp_data);
        *__data |= (uint16_t)((uint16_t)temp_data << ONE_BYTE_MASK);
        ret |= EEPROM_read_byte(__address++, &temp_data);
        *__data |= (uint16_t)((uint16_t)temp_data << ZERO_BYTE_MASK);
    }
    return ret;
}

std_returntype EEPROM_write_uint32 (uint16_t __address, uint32_t __data)
{
    std_returntype ret = STD_OK;
    if (__address >1023)
    {
        ret = STD_NOT_OK;
    }
    else
    {
        ret |= EEPROM_write_byte((__address++), (uint8_t)((__data & 0xFF000000) >> THREE_BYTE_MASK));
        ret |= EEPROM_write_byte((__address++), (uint8_t)((__data & 0x00FF0000) >> TWO_BYTE_MASK));
        ret |= EEPROM_write_byte((__address++), (uint8_t)((__data & 0x0000FF00) >> ONE_BYTE_MASK));
        ret |= EEPROM_write_byte((__address++), (uint8_t)((__data & 0x000000FF) >> ZERO_BYTE_MASK));
    }
    return ret;
}

std_returntype EEPROM_read_uint32 (uint16_t __address, uint32_t *__data)
{
    std_returntype ret = STD_OK;
    uint8_t temp_data = 0;
    if ((NULL == __data) || (__address >1023))
    {
        ret = STD_NOT_OK;
    }
    else
    {
        *__data = 0;

        ret |= EEPROM_read_byte(__address++, &temp_data);
        *__data |= (uint32_t)((uint32_t)temp_data << THREE_BYTE_MASK);
        ret |= EEPROM_read_byte(__address++, &temp_data);
        *__data |= (uint32_t)((uint32_t)temp_data << TWO_BYTE_MASK);
        ret |= EEPROM_read_byte(__address++, &temp_data);
        *__data |= (uint32_t)((uint32_t)temp_data << ONE_BYTE_MASK);
        ret |= EEPROM_read_byte(__address++, &temp_data);
        *__data |= (uint32_t)((uint32_t)temp_data << ZERO_BYTE_MASK);
    }
    return ret;
}

std_returntype EEPROM_write_sint8 (uint16_t __address, sint8_t __data)
{
    std_returntype ret = STD_OK;
    if (__address >1023)
    {
        ret = STD_NOT_OK;
    }
    else
    {
        ret |= EEPROM_write_byte(__address, (uint8_t)__data);
    }
    return ret;
}

std_returntype EEPROM_read_sint8 (uint16_t __address, sint8_t *__data)
{
    std_returntype ret = STD_OK;
    uint8_t temp_data = 0;
    if ((NULL == __data) || (__address >1023))
    {
        ret = STD_NOT_OK;
    }
    else
    {
        ret |= EEPROM_read_byte(__address, &temp_data);
        *__data = (sint8_t)temp_data;
    }
    return ret;
}

std_returntype EEPROM_write_sint16 (uint16_t __address, sint16_t __data)
{
    std_returntype ret = STD_OK;
    if (__address >1023)
    {
        ret = STD_NOT_OK;
    }
    else
    {
        ret |= EEPROM_write_byte((__address++), (uint8_t)((__data & 0xFF00) >> ONE_BYTE_MASK));
        ret |= EEPROM_write_byte((__address++), (uint8_t)((__data & 0x00FF) >> ZERO_BYTE_MASK));
    }
    return ret;
}

std_returntype EEPROM_read_sint16 (uint16_t __address, sint16_t *__data)
{
    std_returntype ret = STD_OK;
    uint8_t temp_data = 0;
    if ((NULL == __data) || (__address >1023))
    {
        ret = STD_NOT_OK;
    }
    else
    {
        *__data = 0;

        ret |= EEPROM_read_byte(__address++, &temp_data);
        *__data |= (sint16_t)((sint16_t)temp_data << ONE_BYTE_MASK);
        ret |= EEPROM_read_byte(__address++, &temp_data);
        *__data |= (sint16_t)((sint16_t)temp_data << ZERO_BYTE_MASK);
    }
    return ret;
}

std_returntype EEPROM_write_sint32 (uint16_t __address, sint32_t __data)
{
    std_returntype ret = STD_OK;
    if (__address >1023)
    {
        ret = STD_NOT_OK;
    }
    else
    {
        ret |= EEPROM_write_byte((__address++), (uint8_t)((__data & 0xFF000000) >> THREE_BYTE_MASK));
        ret |= EEPROM_write_byte((__address++), (uint8_t)((__data & 0x00FF0000) >> TWO_BYTE_MASK));
        ret |= EEPROM_write_byte((__address++), (uint8_t)((__data & 0x0000FF00) >> ONE_BYTE_MASK));
        ret |= EEPROM_write_byte((__address++), (uint8_t)((__data & 0x000000FF) >> ZERO_BYTE_MASK));
    }
    return ret;
}

std_returntype EEPROM_read_sint32 (uint16_t __address, sint32_t *__data)
{
    std_returntype ret = STD_OK;
    uint8_t temp_data = 0;
    if ((NULL == __data) || (__address >1023))
    {
        ret = STD_NOT_OK;
    }
    else
    {
        *__data = 0;

        ret |= EEPROM_read_byte(__address++, &temp_data);
        *__data |= (sint32_t)((sint32_t)temp_data << THREE_BYTE_MASK);
        ret |= EEPROM_read_byte(__address++, &temp_data);
        *__data |= (sint32_t)((sint32_t)temp_data << TWO_BYTE_MASK);
        ret |= EEPROM_read_byte(__address++, &temp_data);
        *__data |= (sint32_t)((sint32_t)temp_data << ONE_BYTE_MASK);
        ret |= EEPROM_read_byte(__address++, &temp_data);
        *__data |= (sint32_t)((sint32_t)temp_data << ZERO_BYTE_MASK);
    }
    return ret;
}

std_returntype EEPROM_write_float32 (uint16_t __address, float32_t __data)
{
    std_returntype ret = STD_OK;
    uint32_t *temp_convertion = NULL;
	uint8_t data_sent = 0;
    if (__address > 1023)
    {
        ret = STD_NOT_OK;
    }
    else
    {
		
        temp_convertion = (uint32_t *)(& __data);
		
		data_sent = (((uint32_t)(*temp_convertion) & 0xFF000000) >> THREE_BYTE_MASK);
        ret |= EEPROM_write_byte((__address++), (uint8_t)data_sent);
		data_sent = (((uint32_t)(*temp_convertion) & 0x00FF0000) >> TWO_BYTE_MASK);
        ret |= EEPROM_write_byte((__address++), (uint8_t)data_sent);
		data_sent = (((uint32_t)(*temp_convertion) & 0x0000FF00) >> ONE_BYTE_MASK);
        ret |= EEPROM_write_byte((__address++), (uint8_t)data_sent);
		data_sent = (((uint32_t)(*temp_convertion) & 0x000000FF) >> ZERO_BYTE_MASK);
        ret |= EEPROM_write_byte((__address++), (uint8_t)data_sent);
		while (EEPROM_WRITE_READ());
    }
    return ret;
}

std_returntype EEPROM_read_float32 (uint16_t __address, float32_t *__data)
{
    std_returntype ret = STD_OK;
    uint8_t temp_data = 0;
    uint32_t final_unconverted_data = 0;
    float32_t *temp_conversion = NULL;
    if ((NULL == __data) || (__address >1023))
    {
        ret = STD_NOT_OK;
    }
    else
    {
       


        final_unconverted_data = 0;

        ret |= EEPROM_read_byte(__address++, &temp_data);
        final_unconverted_data = (uint32_t)(((uint32_t)temp_data << THREE_BYTE_MASK) | (uint32_t)(final_unconverted_data));
        ret |= EEPROM_read_byte(__address++, &temp_data);
        final_unconverted_data = (uint32_t)(((uint32_t)temp_data << TWO_BYTE_MASK) | (uint32_t)(final_unconverted_data));
        ret |= EEPROM_read_byte(__address++, &temp_data);
        final_unconverted_data = (uint32_t)(((uint32_t)temp_data << ONE_BYTE_MASK) | (uint32_t)(final_unconverted_data));
        ret |= EEPROM_read_byte(__address++, &temp_data);
        final_unconverted_data = (uint32_t)(((uint32_t)temp_data << ZERO_BYTE_MASK) | (uint32_t)(final_unconverted_data));

        temp_conversion = (float32_t *)(&final_unconverted_data);
        *__data = *temp_conversion;
    }
    return ret;
}

std_returntype EEPROM_write_string (uint16_t __address, uint8_t *__str)
{
    std_returntype ret = STD_OK;
    uint8_t counter = 0;
    if ((NULL == __str) || (__address >1023))
    {
        ret = STD_NOT_OK;
    }
    else
    {
        while (*(__str + counter) != '\0')
        {
            ret |= EEPROM_write_byte((__address++), (uint8_t)(*(__str + counter)));
            counter++;
        }
        ret |= EEPROM_write_byte((__address++), (uint8_t)(*(__str + counter)));
    }
    return ret;
}

std_returntype EEPROM_read_string (uint16_t __address, uint8_t *__str)
{
    std_returntype ret = STD_OK;
    uint8_t temp_char = '\0';
    uint8_t counter = 0;
    if ((NULL == __str) || (__address >1023))
    {
        ret = STD_NOT_OK;
    }
    else
    {
        do
        {
            ret |= EEPROM_read_byte(__address++, &temp_char);
            *(__str + counter) = temp_char;
            counter++;
        } while (temp_char != '\0');
    }
    return ret;
}


std_returntype EEPROM_write_string_dynamic_mem (uint16_t __address, uint8_t *__str)
{
    std_returntype ret = STD_OK;
    uint8_t counter = 0;
    uint8_t *temp_str = NULL;
    if ((NULL == __str) || (__address >1023))
    {
        ret = STD_NOT_OK;
    }
    else
    {
        temp_str = (uint8_t *)calloc(strlen((const char *)__str), sizeof(uint8_t));
        strcpy((char *)temp_str, (const char *)__str);
        while (*(temp_str + counter) != '\0')
        {
            ret |= EEPROM_write_byte((__address++), (uint8_t)(*(temp_str + counter)));
            counter++;
        }
        ret |= EEPROM_write_byte((__address++), (uint8_t)(*(temp_str + counter)));
    }
    return ret;
}

uint8_t temp_char = '\0';
uint8_t *temp_str = NULL;
uint8_t counter = 0;

std_returntype EEPROM_read_string_dynamic_mem (uint16_t __address, uint8_t **__str)
{
    std_returntype ret = STD_OK;
	
    if ((NULL == __str) || (__address >1023))
    {
        ret = STD_NOT_OK;
    }
    else
    {
        temp_str = (uint8_t *)calloc((1), sizeof(uint8_t));
        do
        {
            ret |= EEPROM_read_byte(__address++, &temp_char);
            temp_str = (uint8_t *)realloc(temp_str, (counter + 1) * sizeof(uint8_t));
            *(temp_str + counter) = temp_char;
            counter++;
        } while (temp_char != '\0');
        *(temp_str + counter) = temp_char;
        *__str = temp_str;
    }
    return ret;
}
/*****************************************************
*             End of Section :  Function declaration *
******************************************************/
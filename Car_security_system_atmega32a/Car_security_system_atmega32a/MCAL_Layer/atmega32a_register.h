/**
 * @file    atmega32a_register.h
 * @author  Ahmed Hani Atef
 * @brief 
 * @version 0.1
 * @date    2023-09-01
 */

#ifndef ATMEGA32A_REGISTER_H
#define	ATMEGA32A_REGISTER_H


/*****************************************************
*           Start of Section :    Macro Fuction      *
******************************************************/

#define HWREG(reg)  (*((volatile unsigned char *)reg)) // access a 8-bit register

#define READ_BIT(reg, bit_position)     (((HWREG(reg) & (1 << bit_position)) >> bit_position)) // read a bit
#define SET_BIT(reg, bit_position)      (HWREG(reg) |= (1 << bit_position))      // sets a bit
#define TOGGLE_BIT(reg, bit_position)   (HWREG(reg) ^= (1 << bit_position))      // toggle a bit
#define CLEAR_BIT(reg, bit_position)    (HWREG(reg) &= ~(1 << bit_position))     // clears a bit
#define WRITE_BITS_IN_REGISTER(reg, start, val, mask)    (HWREG(reg) = ((HWREG(reg) & mask) | ((val << start) & (~mask))))


/*****************************************************
*             End of Section :    Macro Fuction      *
******************************************************/


/*****************************************************
*           Start of Section :    Defines            *
******************************************************/
#define MAX_PIN     (8)
#define MAX_PORT    (4)
#define REG_MASK    (0xFF)


// ----------------- GPIO registers----------------------
#define	DDRA_REGISTER   ((volatile unsigned char *) 0x3A)
#define	DDRB_REGISTER   ((volatile unsigned char *) 0x37)
#define	DDRC_REGISTER   ((volatile unsigned char *) 0x34)
#define	DDRD_REGISTER   ((volatile unsigned char *) 0x31)

#define	PINA_REGISTER   ((volatile unsigned char *) 0x39)
#define	PINB_REGISTER   ((volatile unsigned char *) 0x36)
#define	PINC_REGISTER   ((volatile unsigned char *) 0x33)
#define	PIND_REGISTER   ((volatile unsigned char *) 0x30)

#define	PORTA_REGISTER  ((volatile unsigned char *) 0x3B)
#define	PORTB_REGISTER  ((volatile unsigned char *) 0x38)
#define	PORTC_REGISTER  ((volatile unsigned char *) 0x35)
#define	PORTD_REGISTER  ((volatile unsigned char *) 0x32)
//-------------------------------------------------------


// ------------------- Status registers------------------
#define	STATUS_REGISTER ((volatile unsigned char *) 0x5F)
//-------------------------------------------------------


// ------------ External Interrupt registers-------------
#define	GICR_REGISTER   ((volatile unsigned char *) 0x5B)
#define	MCUCR_REGISTER  ((volatile unsigned char *) 0x55)
#define	MCUCSR_REGISTER ((volatile unsigned char *) 0x54)
#define	GIFR_REGISTER   ((volatile unsigned char *) 0x5A)
//-------------------------------------------------------


// ------------------ EEPROM registers-------------------
#define	EEARL_REGISTER  ((volatile unsigned char *) 0x3E)
#define	EEARH_REGISTER  ((volatile unsigned char *) 0x3F)
#define	EEDR_REGISTER   ((volatile unsigned char *) 0x3D)
#define	EECR_REGISTER   ((volatile unsigned char *) 0x3C)
//-------------------------------------------------------


// ------------------ ADC registers ---------------------
#define SFIOR_REGISTER  ((volatile unsigned char *) 0X50)
#define ADMUX_REGISTER  ((volatile unsigned char *) 0X27)
#define ADCSRA_REGISTER ((volatile unsigned char *) 0X26)
#define ADCH_REGISTER   ((volatile unsigned char *) 0X25)
#define ADCL_REGISTER   ((volatile unsigned char *) 0X24)
// ------------------------------------------------------
/*****************************************************
*             End of Section :    Defines            *
******************************************************/

#endif	/* ATMEGA32A_REGISTER_H */


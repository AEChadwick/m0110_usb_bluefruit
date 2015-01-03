/*
Copyright 2011,2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CONFIG_H
#define CONFIG_H


#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0110
#define DEVICE_VER      0x0101
#define MANUFACTURER    t.m.k.
#define PRODUCT         M0110 keyboard converter
#define DESCRIPTION     convert M0110 keyboard to USB


/* matrix size */
#define MATRIX_ROWS 14
#define MATRIX_COLS 8


/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE


/* USART configuration
 *     asynchronous, 9600baud, 8-data bit, non parity, 1-stop bit, no flow control
 */
#ifdef __AVR_ATmega32U4__
    #define SERIAL_UART_BAUD       9600
    #define SERIAL_UART_DATA       UDR1
    #define SERIAL_UART_UBRR       ((F_CPU/(16UL*SERIAL_UART_BAUD))-1)
    #define SERIAL_UART_RXD_VECT   USART1_RX_vect
    #define SERIAL_UART_TXD_READY  (UCSR1A&(1<<UDRE1))
    #define SERIAL_UART_INIT()     do { \
        UBRR1L = (uint8_t) SERIAL_UART_UBRR;       /* baud rate */ \
        UBRR1H = (uint8_t) (SERIAL_UART_UBRR>>8);  /* baud rate */ \
        UCSR1B = (1<<TXEN1);                /* TX: enable */ \
        UCSR1C = (0<<UPM11) | (0<<UPM10) | /* parity: none(00), even(01), odd(11) */ \
                 (0<<UCSZ12) | (1<<UCSZ11) | (1<<UCSZ10); /* data-8bit(011) */ \
        sei(); \
    } while(0)
#else
#   error "USART configuration is needed."
#endif


/* magic key */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LGUI)) || \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LCTL)) \
)

/* boot magic key */
#define BOOTMAGIC_KEY_SALT                      KC_FN0
#define BOOTMAGIC_KEY_CAPSLOCK_TO_CONTROL       KC_LCAP


/* ports */
#define M0110_CLOCK_PORT        PORTD
#define M0110_CLOCK_PIN         PIND
#define M0110_CLOCK_DDR         DDRD
#define M0110_CLOCK_BIT         1
#define M0110_DATA_PORT         PORTD
#define M0110_DATA_PIN          PIND
#define M0110_DATA_DDR          DDRD
#define M0110_DATA_BIT          0

#endif

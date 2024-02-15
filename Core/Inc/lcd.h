#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>
#include "i2c.h"

// Configuration macros
#define BL_PIN_ON              // Enable Blue Light. Comment out this line to disable the backlight.
#define HI2C_DEF hi2c1         // Default I2C instance. Change to hi2c2 or hi2c3 as needed.

// LCD I2C address and basic commands
#define LCD_I2C_ADDR 0x27      // I2C address of the PCF8574 expander used by the LCD.
#define LINE_ADDRESS 0x80      // Base address for line positioning commands.
#define LCD_LINE1 0x00         // Address offset for the first line.
#define LCD_LINE2 0x40         // Address offset for the second line.
#define LCD_LINE3 0x14         // Address offset for the third line (if applicable).
#define LCD_LINE4 0x54         // Address offset for the fourth line (if applicable).
#define LCD_CLR 0x01           // Command to clear the display.
#define LCD_HOME 0x02          // Command to return the cursor to the home position.

// LCD function set commands
#define LCD_FUNC 0x20
#define LCD_FUNC5x10 0x04      // Use 5x10 dots for character font.
#define LCD_FUNC5x7 0x00       // Use 5x7 dots for character font.
#define LCD_FUNC2LINE 0x08     // Set for 2-line display.
#define LCD_FUNC1LINE 0x00     // Set for 1-line display.
#define LCD_FUNC8BIT 0x10      // Set for 8-bit data interface.
#define LCD_FUNC4BIT 0x00      // Set for 4-bit data interface.

// LCD dimensions
#define LCD_ROWS 4             // Number of display rows.
#define LCD_COLS 20            // Number of display columns.

// Pin configuration for PCF8574
#define RS_PIN 0x01            // Register Select pin.
#define RW_PIN 0x02            // Read/Write pin (not used in this setup).
#define EN_PIN 0x04            // Enable pin.
#define BL_PIN 0x08            // Backlight control pin.
#define D4_PIN 0x10            // Data pin 4.
#define D5_PIN 0x20            // Data pin 5.
#define D6_PIN 0x40            // Data pin 6.
#define D7_PIN 0x80            // Data pin 7.

// Display control commands
#define DISPLAY_ON_CURSOR_OFF_BLINK_OFF 0x0C    // Display ON, Cursor OFF, Blink OFF.
#define DISPLAY_ON_CURSOR_OFF_BLINK_ON 0x0D     // Display ON, Cursor OFF, Blink ON.
#define DISPLAY_ON_CURSOR_ON_BLINK_OFF 0x0E     // Display ON, Cursor ON, Blink OFF.
#define DISPLAY_ON_CURSOR_ON_BLINK_ON 0x0F      // Display ON, Cursor ON, Blink ON.

// Function prototypes
void LCD_Write(uint8_t data, uint8_t rs);       // Write data/command to LCD.
void LCD_Init(void);                            // Initialize the LCD.
void LCD_String(char *str);                     // Display a string on the LCD.
void LCD_SetLocation(uint8_t row, uint8_t col); // Set cursor position.
void LCD_Clear(void);                           // Clear the LCD display.
void LCD_Home(void);                            // Return cursor to home position.

#endif /* LCD_H_ */

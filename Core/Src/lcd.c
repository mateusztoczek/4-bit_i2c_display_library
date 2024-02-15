#include "lcd.h"
#include "tim.h"

TIM_HandleTypeDef *timer = &htim3;	// Default timer set to TIM3. Replace '&htim3' with your own timer instance if necessary.



// Cut byte and send into display
void LCD_Write(uint8_t data, uint8_t rs) {
    uint8_t tx_data[4];
    uint8_t control = (rs ? RS_PIN : 0);

	#ifdef BL_PIN_ON
    	control |= BL_PIN;
	#endif

    tx_data[0] = (data & 0xF0) | EN_PIN | control;
    tx_data[1] = (data & 0xF0) | control;
    tx_data[2] = (data << 4) | EN_PIN | control;
    tx_data[3] = (data << 4) | control;

    HAL_I2C_Master_Transmit(&HI2C_DEF, LCD_I2C_ADDR<<1, tx_data, 4, 100);
}


// Display init
void LCD_Init() {
	LCD_Delay_ms(timer, 50);
	LCD_Write(0x03, 0);	//write 0011XXXX
	LCD_Delay_ms(timer, 50);
	LCD_Write(0x03, 0);	//write 0011XXXX
	LCD_Delay_us(timer, 100);
	LCD_Write(0x03, 0);	//write 0011XXXX
	LCD_Write(0x02, 0); //write 0010XXXX

	LCD_Write(LCD_FUNC|LCD_FUNC4BIT|LCD_FUNC2LINE|LCD_FUNC5x7,0);
	LCD_Write(DISPLAY_ON_CURSOR_OFF_BLINK_OFF,0);
	LCD_Write(LCD_ENTRY|LCD_ENTRYRIGHT,0);

	LCD_Clear();
	LCD_SetLocation(0,0);
}


// Print string on display
void LCD_String(char *str) {
  while (*str) {
	LCD_Write(*str++,1);
  }
}



// Set cursor at any line
void LCD_SetLocation(uint8_t x, uint8_t y) {
    uint8_t line_offset[] = {LCD_LINE1, LCD_LINE2, LCD_LINE3, LCD_LINE4};

    if (y < LCD_ROWS && x < LCD_COLS) {
        uint8_t target_line = line_offset[y];
        LCD_Write((0x80 + target_line + x), 0);
    }
}


// Clear display
void LCD_Clear(void) {
	LCD_Write(LCD_CLR,0);
	LCD_Delay_ms(timer,2);
}


// Set cursor to home position
void LCD_Home(void) {
	LCD_Write(LCD_HOME,0);
	LCD_Delay_ms(timer,2);
}


// Delay in us
void LCD_Delay_us(TIM_HandleTypeDef *htim, uint16_t us) {
    htim->Instance->CNT = 0;
    while (htim->Instance->CNT <= us);
}


// Delay in ms
void LCD_Delay_ms(TIM_HandleTypeDef *htim, uint16_t ms) {
    htim->Instance->CNT = 0;
    while (htim->Instance->CNT <= (ms * 1000)) {
    }
}

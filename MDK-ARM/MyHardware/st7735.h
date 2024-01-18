#ifndef ST7735_H
#define ST7735_H

#include "main.h"
#include "spi.h"

#define ST7735_RST_Pin SPI1_RST_Pin
#define ST7735_RST_GPIO_Port SPI1_RST_GPIO_Port
#define ST7735_DC_Pin SPI1_DC_Pin
#define ST7735_DC_GPIO_Port SPI1_DC_GPIO_Port
#define ST7735_CS_Pin SPI1_CS_Pin
#define ST7735_CS_GPIO_Port SPI1_CS_GPIO_Port

#define ST7735_SPI_INSTANCE hspi1

#define ST7735_XSTART 1
#define ST7735_YSTART 2
//#define ST7735_WIDTH 161
//#define ST7735_HEIGHT 129
#define ST7735_WIDTH 160
#define ST7735_HEIGHT 120

#define ST7735_ROTATION 3

// Color definitions
#define ST7735_BLACK 0x0000
#define ST7735_BLUE 0x001F
#define ST7735_RED 0xF800
#define ST7735_GREEN 0x07E0
#define ST7735_CYAN 0x07FF
#define ST7735_MAGENTA 0xF81F
#define ST7735_YELLOW 0xFFE0
#define ST7735_WHITE 0xFFFF
#define ST7735_COLOR565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))

void ST7735_Init(void);
void ST7735_WriteAll(void);
void ST7735_WriteAll_withbackground(const unsigned char* gImage);
void ST7735_DrawPoint(uint16_t x, uint16_t y, uint16_t color);
void ST7735_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void ST7735_DrawRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
void ST7735_DrawCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color);
void ST7735_FillScreen(uint16_t color);
void ST7735_Draw_16x8_SingleColorImage(uint16_t x, uint16_t y, const uint8_t *image, uint16_t color);
void ST7735_ShowChar(uint16_t x, uint16_t y, uint8_t data, uint16_t color);
void ST7735_ShowString(uint16_t x, uint16_t y, char *String, uint16_t color);
void ST7735_ShowNum(uint16_t x, uint16_t y, uint32_t data, uint8_t size, uint16_t color);
void ST7735_DrawImage(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const unsigned char* gImage);
void ST7735_Clip(uint16_t x_start, uint16_t y_start, uint16_t x_to, uint16_t y_to, uint16_t width, uint16_t height);
void ST7735_Test(void);
#endif

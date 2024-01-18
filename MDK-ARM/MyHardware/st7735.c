#include "st7735.h"
#include "font.h"
#include <math.h>

#define ST7735_SLPOUT 0x11
#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR 0xB4
#define ST7735_PWCTR1 0xC0
#define ST7735_PWCTR2 0xC1
#define ST7735_PWCTR3 0xC2
#define ST7735_PWCTR4 0xC3
#define ST7735_PWCTR5 0xC4
#define ST7735_VMCTR1 0xC5
#define ST7735_COLMOD 0x3A
#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1
#define ST7735_NORON 0x13
#define ST7735_DISPON 0x29
#define ST7735_CASET 0x2A
#define ST7735_RASET 0x2B
#define ST7735_RAMWR 0x2C
#define ST7735_INVOFF 0x20

#define ST7735_MADCTL 0x36
#define ST7735_MADCTL_MX 0x40
#define ST7735_MADCTL_MY 0x80
#define ST7735_MADCTL_MV 0x20
#define ST7735_MADCTL_RGB 0x00

uint8_t SCREEN[ST7735_WIDTH * ST7735_HEIGHT * 2] = {0};

void ST7735_Reset(void)
{
  HAL_GPIO_WritePin(ST7735_RST_GPIO_Port, ST7735_RST_Pin, GPIO_PIN_RESET);
  HAL_Delay(100);
  HAL_GPIO_WritePin(ST7735_RST_GPIO_Port, ST7735_RST_Pin, GPIO_PIN_SET);
  HAL_Delay(100);
}

void ST7735_WriteCommand(uint8_t cmd)
{
  HAL_GPIO_WritePin(ST7735_DC_GPIO_Port, ST7735_DC_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(ST7735_CS_GPIO_Port, ST7735_CS_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&ST7735_SPI_INSTANCE, &cmd, 1, 100);
  // HAL_SPI_Transmit_DMA(&ST7735_SPI_INSTANCE, &cmd, 1);
  HAL_GPIO_WritePin(ST7735_CS_GPIO_Port, ST7735_CS_Pin, GPIO_PIN_SET);
}

void ST7735_WriteData(uint8_t data)
{
  HAL_GPIO_WritePin(ST7735_DC_GPIO_Port, ST7735_DC_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(ST7735_CS_GPIO_Port, ST7735_CS_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&ST7735_SPI_INSTANCE, &data, 1, 100);
  // HAL_SPI_Transmit_DMA(&ST7735_SPI_INSTANCE, &data, 1);
  HAL_GPIO_WritePin(ST7735_CS_GPIO_Port, ST7735_CS_Pin, GPIO_PIN_SET);
}

void ST7735_SetRotation(uint8_t rotation)
{
  uint8_t madctl = 0;

  switch (rotation)
  {
  case 0:
    madctl = ST7735_MADCTL_MX | ST7735_MADCTL_MY | ST7735_MADCTL_RGB;
    break;
  case 1:
    madctl = ST7735_MADCTL_MY | ST7735_MADCTL_MV | ST7735_MADCTL_RGB;
    break;
  case 2:
    madctl = ST7735_MADCTL_RGB;
    break;
  case 3:
    madctl = ST7735_MADCTL_MX | ST7735_MADCTL_MV | ST7735_MADCTL_RGB;
    break;
  }

  ST7735_WriteCommand(ST7735_MADCTL);
  ST7735_WriteData(madctl);
}

void ST7735_Init(void)
{
  // Initialize the display
  ST7735_Reset();
  ST7735_WriteCommand(ST7735_SLPOUT);
  HAL_Delay(120);
  ST7735_WriteCommand(ST7735_FRMCTR1);
  ST7735_WriteData(0x01);
  ST7735_WriteData(0x2C);
  ST7735_WriteData(0x2D);
  ST7735_WriteCommand(ST7735_FRMCTR2);
  ST7735_WriteData(0x01);
  ST7735_WriteData(0x2C);
  ST7735_WriteData(0x2D);
  ST7735_WriteCommand(ST7735_FRMCTR3);
  ST7735_WriteData(0x01);
  ST7735_WriteData(0x2C);
  ST7735_WriteData(0x2D);
  ST7735_WriteData(0x01);
  ST7735_WriteData(0x2C);
  ST7735_WriteData(0x2D);
  ST7735_WriteCommand(ST7735_INVCTR);
  ST7735_WriteData(0x07);
  ST7735_WriteCommand(ST7735_PWCTR1);
  ST7735_WriteData(0xA2);
  ST7735_WriteData(0x02);
  ST7735_WriteData(0x84);
  ST7735_WriteCommand(ST7735_PWCTR2);
  ST7735_WriteData(0xC5);
  ST7735_WriteCommand(ST7735_PWCTR3);
  ST7735_WriteData(0x0A);
  ST7735_WriteData(0x00);
  ST7735_WriteCommand(ST7735_PWCTR4);
  ST7735_WriteData(0x8A);
  ST7735_WriteData(0x2A);
  ST7735_WriteCommand(ST7735_PWCTR5);
  ST7735_WriteData(0x8A);
  ST7735_WriteData(0xEE);
  ST7735_WriteCommand(ST7735_VMCTR1);
  ST7735_WriteData(0x0E);
  ST7735_WriteCommand(ST7735_INVOFF);
  ST7735_WriteCommand(ST7735_COLMOD);
  ST7735_WriteData(0x05);
  ST7735_WriteCommand(ST7735_CASET);
  ST7735_WriteData(0x00);
  ST7735_WriteData(0x00);
  ST7735_WriteData(0x00);
  ST7735_WriteData(0x7F);
  ST7735_WriteCommand(ST7735_RASET);
  ST7735_WriteData(0x00);
  ST7735_WriteData(0x00);
  ST7735_WriteData(0x00);
  ST7735_WriteData(0x9F);
  ST7735_WriteCommand(ST7735_GMCTRP1);
  ST7735_WriteData(0x02);
  ST7735_WriteData(0x1C);
  ST7735_WriteData(0x07);
  ST7735_WriteData(0x12);
  ST7735_WriteData(0x37);
  ST7735_WriteData(0x32);
  ST7735_WriteData(0x29);
  ST7735_WriteData(0x2D);
  ST7735_WriteData(0x29);
  ST7735_WriteData(0x25);
  ST7735_WriteData(0x2B);
  ST7735_WriteData(0x39);
  ST7735_WriteData(0x00);
  ST7735_WriteData(0x01);
  ST7735_WriteData(0x03);
  ST7735_WriteData(0x10);
  ST7735_WriteCommand(ST7735_GMCTRN1);
  ST7735_WriteData(0x03);
  ST7735_WriteData(0x1D);
  ST7735_WriteData(0x07);
  ST7735_WriteData(0x06);
  ST7735_WriteData(0x2E);
  ST7735_WriteData(0x2C);
  ST7735_WriteData(0x29);
  ST7735_WriteData(0x2D);
  ST7735_WriteData(0x2E);
  ST7735_WriteData(0x2E);
  ST7735_WriteData(0x37);
  ST7735_WriteData(0x3F);
  ST7735_WriteData(0x00);
  ST7735_WriteData(0x00);
  ST7735_WriteData(0x02);
  ST7735_WriteData(0x10);
  ST7735_WriteCommand(ST7735_NORON);
  HAL_Delay(10);
  ST7735_WriteCommand(ST7735_DISPON);
  HAL_Delay(10);

  ST7735_SetRotation(ST7735_ROTATION);
  ST7735_FillScreen(ST7735_BLACK);
}

/************************************************
这份代码驱动屏幕的原理是这样的，先用这个函数设置一个window，然后两个ST7735_WriteData填充一个像素，会自动在window里面顺序填充
画图是有一个起始点偏移的设置的，在.h里面，默认是0
************************************************/
void ST7735_SetAddressWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
  x0 += ST7735_XSTART;
  y0 += ST7735_YSTART;

  x1 += ST7735_XSTART;
  y1 += ST7735_YSTART;

  ST7735_WriteCommand(ST7735_CASET);
  ST7735_WriteData(0x00);
  ST7735_WriteData(x0);
  ST7735_WriteData(0x00);
  ST7735_WriteData(x1);

  ST7735_WriteCommand(ST7735_RASET);
  ST7735_WriteData(0x00);
  ST7735_WriteData(y0);
  ST7735_WriteData(0x00);
  ST7735_WriteData(y1);
}

// 把整个screen数组写进屏幕
void ST7735_WriteAll()
{
  ST7735_SetAddressWindow(0, 0, ST7735_WIDTH - 1, ST7735_HEIGHT - 1);
  ST7735_WriteCommand(ST7735_RAMWR);
  HAL_GPIO_WritePin(ST7735_DC_GPIO_Port, ST7735_DC_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(ST7735_CS_GPIO_Port, ST7735_CS_Pin, GPIO_PIN_RESET);

  // 去看https://blog.csdn.net/qq_30267617/article/details/118877845
  HAL_SPI_Transmit(&ST7735_SPI_INSTANCE, SCREEN, ST7735_WIDTH * ST7735_HEIGHT * 2, 100);

  HAL_GPIO_WritePin(ST7735_CS_GPIO_Port, ST7735_CS_Pin, GPIO_PIN_SET);
}
void ST7735_WriteAll_withbackground(const unsigned char *gImage)
{
  for (uint16_t i = 0; i < ST7735_WIDTH; i++)
  {
    for (uint16_t j = 0; j < ST7735_HEIGHT; j++)
    {
      if (SCREEN[(j * ST7735_WIDTH + i) * 2] == 0X00)
        SCREEN[(j * ST7735_WIDTH + i) * 2] = gImage[(j * ST7735_WIDTH + i) * 2];
      if (SCREEN[(j * ST7735_WIDTH + i) * 2 + 1] == 0X00)
        SCREEN[(j * ST7735_WIDTH + i) * 2 + 1] = gImage[(j * ST7735_WIDTH + i) * 2 + 1];
    }
  }
  ST7735_SetAddressWindow(0, 0, ST7735_WIDTH - 1, ST7735_HEIGHT - 1);
  ST7735_WriteCommand(ST7735_RAMWR);
  HAL_GPIO_WritePin(ST7735_DC_GPIO_Port, ST7735_DC_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(ST7735_CS_GPIO_Port, ST7735_CS_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&ST7735_SPI_INSTANCE, SCREEN, ST7735_WIDTH * ST7735_HEIGHT * 2, 100);
  HAL_GPIO_WritePin(ST7735_CS_GPIO_Port, ST7735_CS_Pin, GPIO_PIN_SET);
}

// 画点
void ST7735_DrawPoint(uint16_t x, uint16_t y, uint16_t color)
{
  // if ((x <= ST7735_WIDTH) & (y <= ST7735_HEIGHT))
  // {
  SCREEN[(y * ST7735_WIDTH + x) * 2] = color >> 8;
  SCREEN[(y * ST7735_WIDTH + x) * 2 + 1] = color & 0xFF;
  // }
}

// 画直线
void ST7735_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{

  uint8_t x_flag = 0;   // x1>x2为1
  uint8_t y_flag = 0;   // y1>y2为1
  uint8_t x_y_flag = 0; // x1-x2>y1-y2为1
  if (x1 > x2)
  {
    x_flag = 1;
  }
  if (y1 > y2)
  {
    y_flag = 1;
  }

  if (abs(x2 - x1) > abs(y2 - y1))
  {
    x_y_flag = 1;
  }
  if (x_y_flag)
  {
    if (x_flag)
    {
      for (uint8_t i = x2; i <= x1; i++)
      {
        float y = ((y2 - y1) / (float)(x2 - x1)) * (i - x2) + y2;
        y = (((int)(y + 1) - y) < (y - (int)y)) ? (int)(y + 1) : (int)y;
        ST7735_DrawPoint(i, y, color);
      }
    }
    else
    {
      for (uint8_t i = x1; i <= x2; i++)
      {
        float y = ((y2 - y1) / (float)(x2 - x1)) * (i - x2) + y2;
        y = (((int)(y + 1) - y) < (y - (int)y)) ? (int)(y + 1) : (int)y;
        ST7735_DrawPoint(i, y, color);
      }
    }
  }
  else
  {
    if (y_flag)
    {
      for (uint8_t i = y2; i <= y1; i++)
      {
        float x = ((float)(x2 - x1) / (y2 - y1)) * (i - y2) + x2;
        x = (((int)(x + 1) - x) < (x - (int)x)) ? (int)(x + 1) : (int)x;
        ST7735_DrawPoint(x, i, color);
      }
    }
    else
    {
      for (uint8_t i = y1; i <= y2; i++)
      {
        float x = ((float)(x2 - x1) / (y2 - y1)) * (i - y2) + x2;
        x = (((int)(x + 1) - x) < (x - (int)x)) ? (int)(x + 1) : (int)x;
        ST7735_DrawPoint(x, i, color);
      }
    }
  }
}

// 画填充的矩形
void ST7735_DrawRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color)
{
  if ((x <= ST7735_WIDTH) & (y <= ST7735_HEIGHT))
  {
    uint16_t width_correct = ((x + width) > ST7735_WIDTH) ? (ST7735_WIDTH - x) : (width);
    uint16_t height_correct = ((y + height) > ST7735_HEIGHT) ? (ST7735_HEIGHT - y) : (height);
    for (uint16_t j = 0; j < height_correct; j++)
    {
      for (uint16_t i = 0; i < width_correct; i++)
      {
        SCREEN[((y + j) * ST7735_WIDTH + x + i) * 2] = color >> 8;
        SCREEN[((y + j) * ST7735_WIDTH + x + i) * 2 + 1] = color & 0xFF;
      }
    }
  }
  /*
  if ((x <= ST7735_WIDTH) & (y <= ST7735_HEIGHT))
  {
    for (uint16_t i = 0; i < ((x + width) > ST7735_WIDTH) ? (ST7735_WIDTH - x) : (width); i++)
    {
      for (uint16_t j = 0; j < ((y + height) > ST7735_HEIGHT) ? (ST7735_HEIGHT - y) : (height); j++)
      {
        SCREEN[((y + j) * ST7735_WIDTH + x + i) * 2] = color >> 8;
        SCREEN[((y + j) * ST7735_WIDTH + x + i) * 2 + 1] = color & 0xFF;
      }
    }
  }*/
}

// 画空心圆
void ST7735_DrawCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color)
{
  float sqrt_r = r / 1.414;
  for (uint8_t i = (int)(x0 - sqrt_r); i <= (int)(x0 + sqrt_r) + 1; i++)
  {
    float y_cal = sqrt(r * r - (i - x0) * (i - x0));
    float y = (((int)(y_cal + 1) - y_cal) < (y_cal - (int)y_cal)) ? (int)(y_cal + 1) : (int)y_cal;
    ST7735_DrawPoint(i, y0 + y, color);
    ST7735_DrawPoint(i, y0 - y, color);
  }
  for (uint8_t i = (int)(y0 - sqrt_r); i <= (int)(y0 + sqrt_r) + 1; i++)
  {
    float x_cal = sqrt(r * r - (i - y0) * (i - y0));
    float x = (((int)(x_cal + 1) - x_cal) < (x_cal - (int)x_cal)) ? (int)(x_cal + 1) : (int)x_cal;
    ST7735_DrawPoint(x0 + x, i, color);
    ST7735_DrawPoint(x0 - x, i, color);
  }
}

// 本质上是画矩形，界面长宽在.h里面设
void ST7735_FillScreen(uint16_t color)
{
  ST7735_DrawRectangle(0, 0, ST7735_WIDTH, ST7735_HEIGHT, color);
}

// 把一个uint_8大小（8位）的16进制数转换为二进制，放在一个8位char中，最低位存在char[0]
// 返回char的指针
char *h_to_b(int h)
{
  static char b[8];
  uint16_t j = 1;
  for (uint8_t i = 0; i < 8; i++)
  {
    b[i] = (h & j) ? 1 : 0;
    j <<= 1;
  }
  return b;
}

// 画单色的图形，即取模软件取出来的，仅支持8*8为最小单元的，*image是字模数组的首地址
void ST7735_Draw_16x8_SingleColorImage(uint16_t x, uint16_t y, const uint8_t *image, uint16_t color)
{
  /*
  0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x33,0x30,0x00,0x00,0x00,//!
  */
  for (int j = 0; j < 8; j++) // 先显示上面8*8的方块
  {
    for (int i = 0; i < 8; i++) // 先遍历每个u_int8的第一个bit，再遍历每个u_int8的第二个bit。。。直到第八个bit
                                // （第一个bit是最小的一位）（所以每个u_int8写成2进制和h_to_b[]里面存的是镜像了）
    {
      if (h_to_b(image[i])[j])
      {
        SCREEN[((y + j) * ST7735_WIDTH + (x + i)) * 2] = color >> 8;
        SCREEN[((y + j) * ST7735_WIDTH + (x + i)) * 2 + 1] = color & 0xFF;
      }
      else
      {
        SCREEN[((y + j) * ST7735_WIDTH + (x + i)) * 2] = 0;
        SCREEN[((y + j) * ST7735_WIDTH + (x + i)) * 2 + 1] = 0;
      }
    }
  }
  for (int j = 0; j < 8; j++) // 再显示下面8*8的方块，i+8就是从第二行开始了
  {
    for (int i = 0; i < 8; i++)
    {
      if (h_to_b(image[i + 8])[j])
      {
        SCREEN[((y + 8 + j) * ST7735_WIDTH + (x + i)) * 2] = color >> 8;
        SCREEN[((y + 8 + j) * ST7735_WIDTH + (x + i)) * 2 + 1] = color & 0xFF;
      }
      else
      {
        SCREEN[((y + 8 + j) * ST7735_WIDTH + (x + i)) * 2] = 0;
        SCREEN[((y + 8 + j) * ST7735_WIDTH + (x + i)) * 2 + 1] = 0;
      }
    }
  }
}

/************************************************
 这里目前只能显示8*16的ASCII码
************************************************/
void ST7735_ShowChar(uint16_t x, uint16_t y, uint8_t data, uint16_t color)
{
  ST7735_Draw_16x8_SingleColorImage(x, y, LCD_F8x16[data - (uint8_t)' '], color);
  // ST7735_DrawSingleColorImage(x, y, 8, 16, LCD_F8x16[1], color);
}

void ST7735_ShowString(uint16_t x, uint16_t y, char *String, uint16_t color)
{
  for (uint8_t i = 0; String[i] != '\0'; i++)
  {
    ST7735_ShowChar(x + (i * 8), y, String[i], color);
  }
}

// 原理是%10和/10
void ST7735_ShowNum(uint16_t x, uint16_t y, uint32_t data, uint8_t size, uint16_t color)
{
  uint32_t data_copy = data;
  for (uint8_t i = size; i > 0; i--)
  {
    ST7735_ShowChar(x + (8 * (i - 1)), y, data_copy % 10 + '0', color);
    data_copy /= 10;
  }
}

// 使用Img2Lcd取模
void ST7735_DrawImage(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const unsigned char *gImage)
{
  if ((x <= ST7735_WIDTH) & (y <= ST7735_HEIGHT))
  {
    uint16_t width_correct = ((x + width) > ST7735_WIDTH) ? (ST7735_WIDTH - x) : (width);
    uint16_t height_correct = ((y + height) > ST7735_HEIGHT) ? (ST7735_HEIGHT - y) : (height);
    for (uint16_t j = 0; j < height_correct; j++)
    {
      for (uint16_t i = 0; i < width_correct; i++)
      {
        SCREEN[((y + j) * ST7735_WIDTH + (x + i)) * 2] = gImage[(j * width + i) * 2];
        SCREEN[((y + j) * ST7735_WIDTH + (x + i)) * 2 + 1] = gImage[(j * width + i) * 2 + 1];
      }
    }
  }
  /*
  if ((x <= ST7735_WIDTH) & (y <= ST7735_HEIGHT))
  {
    for (uint16_t i = 0; i < ((x + width) > ST7735_WIDTH) ? (ST7735_WIDTH - x) : (width); i++)
    {
      for (uint16_t j = 0; j < ((y + height) > ST7735_HEIGHT) ? (ST7735_HEIGHT - y) : (height); j++)
      {
        SCREEN[((y + j) * ST7735_WIDTH + (x + i)) * 2] = gImage[(j * width + i) * 2];
        SCREEN[((y + j) * ST7735_WIDTH + (x + i)) * 2 + 1] = gImage[(j * width + i) * 2 + 1];
      }
    }
  }*/
}

// 剪贴，传左上角的起始，终止位置，以及区域长宽
void ST7735_Clip(uint16_t x_start, uint16_t y_start, uint16_t x_to, uint16_t y_to, uint16_t width, uint16_t height)
{
  for (uint16_t j = 0; j < height; j++)
  {
    for (uint16_t i = 0; i < width; i++)
    {
      SCREEN[((y_to + j) * ST7735_WIDTH + (x_to + i)) * 2] = SCREEN[((y_start + j) * ST7735_WIDTH + (x_start + i)) * 2];
      SCREEN[((y_start + j) * ST7735_WIDTH + (x_start + i)) * 2] = 0;
      SCREEN[((y_to + j) * ST7735_WIDTH + (x_to + i)) * 2 + 1] = SCREEN[((y_start + j) * ST7735_WIDTH + (x_start + i)) * 2 + 1];
      SCREEN[((y_start + j) * ST7735_WIDTH + (x_start + i)) * 2 + 1] = 0;
    }
  }
}

// 打印测试图形
void ST7735_Test(void)
{
  ST7735_DrawRectangle(40, 20, 80, 40, ST7735_BLUE);
  ST7735_ShowChar(5, 5, '2', ST7735_YELLOW);
  ST7735_DrawLine(5, 10, 50, 100, ST7735_CYAN);
  ST7735_DrawCircle(40, 80, 50, ST7735_YELLOW);
  ST7735_ShowChar(108, 100, '!', ST7735_MAGENTA);
  ST7735_ShowNum(0, 0, 114514, 6, ST7735_GREEN);
  ST7735_DrawPoint(10, 10, ST7735_BLUE);
  ST7735_DrawPoint(100, 100, ST7735_BLUE);
  ST7735_DrawRectangle(0, 0, 2, 2, ST7735_WHITE);
  ST7735_ShowNum(0, 50, 12, 2, ST7735_WHITE);
  ST7735_WriteAll();
}

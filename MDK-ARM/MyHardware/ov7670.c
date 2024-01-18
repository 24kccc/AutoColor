#include "ov7670.h"

#define OV7670_ADDRESS 0x42
uint16_t CAMERA[160 * 120] = {0};

void WrCmos7670(uint8_t regID, uint8_t regDat)
{
	HAL_I2C_Mem_Write(&hi2c1, OV7670_ADDRESS, regID, I2C_MEMADD_SIZE_8BIT, &regDat, 1, 0x100);
}
void set_Cmos7670reg(void)
{
	// AGC 0x00
	// 自动增益控制 默认00
	WrCmos7670(0x00, 0x00);

	// BLUE 0x01
	// AWB-蓝色通道增益 [00]~[FF]
	WrCmos7670(0x01, 0x80);

	// RED 0x02
	// AWB-红色通道增益 [00]~[FF]
	WrCmos7670(0x02, 0x80);//这两个改了都没啥反应

	WrCmos7670(0x8c, 0x00);

	WrCmos7670(0x3a, 0x04);
	WrCmos7670(0x40, 0xd0);

	// COM7 0x12
	// 位[7]:	SCCB寄存器复位
	// 			0：不复位
	// 			1：复位
	// 位[6]:	保留
	// 位[5]:	输出格式-CIF
	// 位[4]:	输出格式-QVGA
	// 位[3]:	输出格式-QCIF
	// 位[2]:	输出格式-RGB(见下面）
	// 位[1]:	彩色条
	// 			0:非使能
	// 			1:使能
	// 位[0]:	输出格式-Raw RGB（见以下）
	// 						COM7[2] 	COM7[0]
	// YUV 					0 			0
	// RGB 					1 			0
	// Bayer RAW 			0 			1
	// Processed Bayer RAW 	1 			1
	WrCmos7670(0x12, 0x14);//0x14 0001 0100

	WrCmos7670(0x32, 0x80);
	WrCmos7670(0x17, 0x16);
	WrCmos7670(0x18, 0x04);
	WrCmos7670(0x19, 0x02);
	WrCmos7670(0x1a, 0x7b);
	WrCmos7670(0x03, 0x06);
	WrCmos7670(0x0c, 0x00);
	WrCmos7670(0x3e, 0x00);
	WrCmos7670(0x70, 0x3a);
	WrCmos7670(0x71, 0x35); // 如果调整为WrCmos7670(0x71, 0x80);会显示8条彩色竖条，调试用WrCmos7670(0x71, 0x35);
	WrCmos7670(0x72, 0x11);
	WrCmos7670(0x73, 0x00);
	WrCmos7670(0xa2, 0x02);
	WrCmos7670(0x11, 0x81);

	WrCmos7670(0x7a, 0x20);
	WrCmos7670(0x7b, 0x1c);
	WrCmos7670(0x7c, 0x28);
	WrCmos7670(0x7d, 0x3c);
	WrCmos7670(0x7e, 0x55);
	WrCmos7670(0x7f, 0x68);
	WrCmos7670(0x80, 0x76);
	WrCmos7670(0x81, 0x80);
	WrCmos7670(0x82, 0x88);
	WrCmos7670(0x83, 0x8f);
	WrCmos7670(0x84, 0x96);
	WrCmos7670(0x85, 0xa3);
	WrCmos7670(0x86, 0xaf);
	WrCmos7670(0x87, 0xc4);
	WrCmos7670(0x88, 0xd7);
	WrCmos7670(0x89, 0xe8);

	WrCmos7670(0x13, 0xe0);

	WrCmos7670(0x10, 0x40);// 曝光值，默认40	改了没反应
	WrCmos7670(0x0d, 0x00);
	WrCmos7670(0x14, 0x28);
	WrCmos7670(0xa5, 0x05);
	WrCmos7670(0xab, 0x07);
	WrCmos7670(0x24, 0x75);
	WrCmos7670(0x25, 0x63);
	WrCmos7670(0x26, 0xA5);
	WrCmos7670(0x9f, 0x78);
	WrCmos7670(0xa0, 0x68);
	WrCmos7670(0xa1, 0x03);
	WrCmos7670(0xa6, 0xdf);
	WrCmos7670(0xa7, 0xdf);
	WrCmos7670(0xa8, 0xf0);
	WrCmos7670(0xa9, 0x90);
	WrCmos7670(0xaa, 0x94);
	WrCmos7670(0x13, 0xe5);

	WrCmos7670(0x0e, 0x61);
	WrCmos7670(0x0f, 0x4b);
	WrCmos7670(0x16, 0x02);
	WrCmos7670(0x1e, 0x37);
	WrCmos7670(0x21, 0x02);
	WrCmos7670(0x22, 0x91);
	WrCmos7670(0x29, 0x07);
	WrCmos7670(0x33, 0x0b);
	WrCmos7670(0x35, 0x0b);
	WrCmos7670(0x37, 0x1d);
	WrCmos7670(0x38, 0x71);
	WrCmos7670(0x39, 0x2a);
	WrCmos7670(0x3c, 0x78);
	WrCmos7670(0x4d, 0x40);
	WrCmos7670(0x4e, 0x20);
	WrCmos7670(0x69, 0x00);
	WrCmos7670(0x6b, 0x60);
	WrCmos7670(0x74, 0x19);
	WrCmos7670(0x8d, 0x4f);
	WrCmos7670(0x8e, 0x00);
	WrCmos7670(0x8f, 0x00);
	WrCmos7670(0x90, 0x00);
	WrCmos7670(0x91, 0x00);
	WrCmos7670(0x92, 0x00);
	WrCmos7670(0x96, 0x00);
	WrCmos7670(0x9a, 0x80);
	WrCmos7670(0xb0, 0x84);
	WrCmos7670(0xb1, 0x0c);
	WrCmos7670(0xb2, 0x0e);
	WrCmos7670(0xb3, 0x82);
	WrCmos7670(0xb8, 0x0a);

	WrCmos7670(0x43, 0x14);
	WrCmos7670(0x44, 0xf0);
	WrCmos7670(0x45, 0x34);
	WrCmos7670(0x46, 0x58);
	WrCmos7670(0x47, 0x28);
	WrCmos7670(0x48, 0x3a);
	WrCmos7670(0x59, 0x88);
	WrCmos7670(0x5a, 0x88);
	WrCmos7670(0x5b, 0x44);
	WrCmos7670(0x5c, 0x67);
	WrCmos7670(0x5d, 0x49);
	WrCmos7670(0x5e, 0x0e);
	WrCmos7670(0x64, 0x04);
	WrCmos7670(0x65, 0x20);
	WrCmos7670(0x66, 0x05);
	WrCmos7670(0x94, 0x04);
	WrCmos7670(0x95, 0x08);
	WrCmos7670(0x6c, 0x0a);
	WrCmos7670(0x6d, 0x55);
	WrCmos7670(0x6e, 0x11);
	WrCmos7670(0x6f, 0x9f);
	WrCmos7670(0x6a, 0x40);
	WrCmos7670(0x13, 0xe7);
	WrCmos7670(0x15, 0x00);

	WrCmos7670(0x4f, 0x80);
	WrCmos7670(0x50, 0x80);
	WrCmos7670(0x51, 0x00);
	WrCmos7670(0x52, 0x22);
	WrCmos7670(0x53, 0x5e);
	WrCmos7670(0x54, 0x80);
	WrCmos7670(0x58, 0x9e);

	WrCmos7670(0x41, 0x08);
	WrCmos7670(0x3f, 0x00);
	WrCmos7670(0x75, 0x05);
	WrCmos7670(0x76, 0xe1);
	WrCmos7670(0x4c, 0x00);
	WrCmos7670(0x77, 0x01);
	WrCmos7670(0x3d, 0xc2);
	WrCmos7670(0x4b, 0x09);
	WrCmos7670(0xc9, 0x60);
	WrCmos7670(0x41, 0x38);
	WrCmos7670(0x56, 0x40);

	WrCmos7670(0x34, 0x11);
	WrCmos7670(0x3b, 0x02);

	WrCmos7670(0xa4, 0x89);
	WrCmos7670(0x96, 0x00);
	WrCmos7670(0x97, 0x30);
	WrCmos7670(0x98, 0x20);
	WrCmos7670(0x99, 0x30);
	WrCmos7670(0x9a, 0x84);
	WrCmos7670(0x9b, 0x29);
	WrCmos7670(0x9c, 0x03);
	WrCmos7670(0x9d, 0x4c);
	WrCmos7670(0x9e, 0x3f);
	WrCmos7670(0x78, 0x04);

	WrCmos7670(0x79, 0x01);
	WrCmos7670(0xc8, 0xf0);
	WrCmos7670(0x79, 0x0f);
	WrCmos7670(0xc8, 0x00);
	WrCmos7670(0x79, 0x10);
	WrCmos7670(0xc8, 0x7e);
	WrCmos7670(0x79, 0x0a);
	WrCmos7670(0xc8, 0x80);
	WrCmos7670(0x79, 0x0b);
	WrCmos7670(0xc8, 0x01);
	WrCmos7670(0x79, 0x0c);
	WrCmos7670(0xc8, 0x0f);
	WrCmos7670(0x79, 0x0d);
	WrCmos7670(0xc8, 0x20);
	WrCmos7670(0x79, 0x09);
	WrCmos7670(0xc8, 0x80);
	WrCmos7670(0x79, 0x02);
	WrCmos7670(0xc8, 0xc0);
	WrCmos7670(0x79, 0x03);
	WrCmos7670(0xc8, 0x40);
	WrCmos7670(0x79, 0x05);
	WrCmos7670(0xc8, 0x30);
	WrCmos7670(0x79, 0x26);
	WrCmos7670(0x09, 0x00);
}

void ov7670_init(void)
{
	HAL_GPIO_WritePin(CAM_RST_GPIO_Port, CAM_RST_Pin, GPIO_PIN_RESET); // reset low
	HAL_Delay(20);
	HAL_GPIO_WritePin(CAM_RST_GPIO_Port, CAM_RST_Pin, GPIO_PIN_SET); // reset high
	uint8_t mmm;
	mmm = 0x80;
	WrCmos7670(0x12, mmm);
	HAL_Delay(20);
	set_Cmos7670reg();
}
uint8_t take_photo_flag = 0; // 0空闲，1准备拍照，2拍照中

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == CAM_VSYNC_Pin) // 摄像头帧同步的中断
	{
		if (take_photo_flag == 1)
		{
			take_photo_flag = 2;
			HAL_GPIO_WritePin(CAM_WRST_GPIO_Port, CAM_WRST_Pin, GPIO_PIN_RESET); // OV7670_WRST = 0;  复位写指针
			HAL_GPIO_WritePin(CAM_WRST_GPIO_Port, CAM_WRST_Pin, GPIO_PIN_SET);	 // OV7670_WRST = 1;
			HAL_GPIO_WritePin(CAM_WEN_GPIO_Port, CAM_WEN_Pin, GPIO_PIN_SET);	 // OV7670_WREN = 1;  允许写入FIFO
		}
		else if (take_photo_flag == 2)
		{
			take_photo_flag = 0;
			HAL_GPIO_WritePin(CAM_WRST_GPIO_Port, CAM_WRST_Pin, GPIO_PIN_RESET); // OV7670_WRST = 0;  复位写指针
			HAL_GPIO_WritePin(CAM_WRST_GPIO_Port, CAM_WRST_Pin, GPIO_PIN_SET);	 // OV7670_WRST = 1;
			HAL_GPIO_WritePin(CAM_WEN_GPIO_Port, CAM_WEN_Pin, GPIO_PIN_RESET);	 // OV7670_WREN = 0;  禁止写入FIFO
		}
		else
		{
			// take_photo_flag == 0,直接跳过
		}
	}
}
extern uint8_t SCREEN[ST7735_WIDTH * ST7735_HEIGHT * 2];
void camera_refresh(void)
{

	HAL_GPIO_WritePin(CAM_RRST_GPIO_Port, CAM_RRST_Pin, GPIO_PIN_RESET); // OV7670_RRST = 0; // 开始复位读指针
	HAL_GPIO_WritePin(CAM_RCLK_GPIO_Port, CAM_RCLK_Pin, GPIO_PIN_RESET); // OV7670_RCK_L;
	HAL_GPIO_WritePin(CAM_RCLK_GPIO_Port, CAM_RCLK_Pin, GPIO_PIN_SET);	 // OV7670_RCK_H;
	HAL_GPIO_WritePin(CAM_RCLK_GPIO_Port, CAM_RCLK_Pin, GPIO_PIN_RESET); // OV7670_RCK_L;
	HAL_GPIO_WritePin(CAM_RRST_GPIO_Port, CAM_RRST_Pin, GPIO_PIN_SET);	 // OV7670_RRST = 1; // 复位读指针结束
	HAL_GPIO_WritePin(CAM_RCLK_GPIO_Port, CAM_RCLK_Pin, GPIO_PIN_SET);	 // OV7670_RCK_H;
	for (uint16_t i = 0; i < 120; i++)	// 对每一行
	{
		for (uint16_t j = 0; j < 160; j++){	// 对每一行的每一个像素
			HAL_GPIO_WritePin(CAM_RCLK_GPIO_Port, CAM_RCLK_Pin, GPIO_PIN_RESET); // OV7670_RCK_L;
			SCREEN[(i*160+j)*2] = GPIOF->IDR & 0XFF;										 // 读数据
			HAL_GPIO_WritePin(CAM_RCLK_GPIO_Port, CAM_RCLK_Pin, GPIO_PIN_SET);	 // OV7670_RCK_H;
			HAL_GPIO_WritePin(CAM_RCLK_GPIO_Port, CAM_RCLK_Pin, GPIO_PIN_RESET); // OV7670_RCK_L;
			SCREEN[(i*160+j)*2+1] = GPIOF->IDR & 0XFF;									 // 读数据
			HAL_GPIO_WritePin(CAM_RCLK_GPIO_Port, CAM_RCLK_Pin, GPIO_PIN_SET);	 // OV7670_RCK_H;
			// 跳过一个
			HAL_GPIO_WritePin(CAM_RCLK_GPIO_Port, CAM_RCLK_Pin, GPIO_PIN_RESET); // OV7670_RCK_L;
			HAL_GPIO_WritePin(CAM_RCLK_GPIO_Port, CAM_RCLK_Pin, GPIO_PIN_SET);	 // OV7670_RCK_H;
			HAL_GPIO_WritePin(CAM_RCLK_GPIO_Port, CAM_RCLK_Pin, GPIO_PIN_RESET); // OV7670_RCK_L;
			HAL_GPIO_WritePin(CAM_RCLK_GPIO_Port, CAM_RCLK_Pin, GPIO_PIN_SET);	 // OV7670_RCK_H;
		}
		for (uint16_t j = 0; j < 320; j++){	// 跳过一行
			HAL_GPIO_WritePin(CAM_RCLK_GPIO_Port, CAM_RCLK_Pin, GPIO_PIN_RESET); // OV7670_RCK_L;
			HAL_GPIO_WritePin(CAM_RCLK_GPIO_Port, CAM_RCLK_Pin, GPIO_PIN_SET);	 // OV7670_RCK_H;
			HAL_GPIO_WritePin(CAM_RCLK_GPIO_Port, CAM_RCLK_Pin, GPIO_PIN_RESET); // OV7670_RCK_L;
			HAL_GPIO_WritePin(CAM_RCLK_GPIO_Port, CAM_RCLK_Pin, GPIO_PIN_SET);	 // OV7670_RCK_H;
		}
	}

	// for (uint16_t i = 0; i < 240; i++) // 此种方式需清楚TFT内部显示方向控制寄存器值 速度较快
	// {
	// 	for (uint16_t j = 0; j < 320; j++)
	// 	{
	// 		if ((i % 2) & (j % 2))
	// 		{
	// 			HAL_GPIO_WritePin(CAM_RCLK_GPIO_Port, CAM_RCLK_Pin, GPIO_PIN_RESET); // OV7670_RCK_L;
	// 			SCREEN[(i / 2) * 160 + (j / 2)] = GPIOF->IDR & 0XFF;			   // 读数据
	// 			HAL_GPIO_WritePin(CAM_RCLK_GPIO_Port, CAM_RCLK_Pin, GPIO_PIN_SET); // OV7670_RCK_H;
	// 			// SCREEN[i] <<= 8;
	// 			HAL_GPIO_WritePin(CAM_RCLK_GPIO_Port, CAM_RCLK_Pin, GPIO_PIN_RESET); // OV7670_RCK_L;
	// 			// SCREEN[i] |= GPIOF->IDR & 0XFF;
	// 			SCREEN[(i / 2) * 160 + (j / 2) + 1] = GPIOF->IDR & 0XFF; // 读数据
	// 			HAL_GPIO_WritePin(CAM_RCLK_GPIO_Port, CAM_RCLK_Pin, GPIO_PIN_SET); // OV7670_RCK_H;
	// 		}
	// 	}
	// }
	// ST7735_ShowNum(10, 10, SCREEN[5000], 4, ST7735_WHITE);
	ST7735_WriteAll();
}

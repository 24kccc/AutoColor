#ifndef OV7670_H
#define OV7670_H

#include "main.h"
#include "i2c.h"
#include "st7735.h"

extern uint8_t take_photo_flag;
void camera_refresh(void);
void ov7670_init(void);
#endif

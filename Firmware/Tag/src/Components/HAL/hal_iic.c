#include "hal_iic.h"
#include "OLED_I2C.h"

int Hal_I2C_LCD_Init(void)
{
	I2C_InitTypeDef  I2C_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure; 

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	/*STM32F103C8T6芯片的硬件I2C: PB6 -- SCL; PB7 -- SDA */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;//I2C必须开漏输出
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	I2C_DeInit(I2C1);//使用I2C1
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = 0x30;//主机的I2C地址,随便写的
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = 400000;//400K

	I2C_Cmd(I2C1, ENABLE);
	I2C_Init(I2C1, &I2C_InitStructure);

	OLED_Init();

	OLED_Fill(0xFF);//全屏点亮
	return 0;
}

void HalI2cInit( void )
{
#ifdef	HAL_I2C_LCD
	Hal_I2C_LCD_Init();
	//OLED_ShowCN(16,1,0);
	//OLED_ShowCN(32,1,2);
	//OLED_ShowCN(48,1,1);
	//OLED_ShowCN(64,1,3);	
	//OLED_ShowStr(81, 1, "-AoA-", 2);	
	OLED_ShowStr(6, 1, "Makerfabs-AoA-", 2);
	OLED_ShowStr(42, 3, "-Tag-", 2);
	
#endif
}

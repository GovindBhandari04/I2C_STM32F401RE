#include <stm32f4xx.h>

void I2C_config()
{
	RCC -> AHB1ENR |= (1U<<0);
	RCC -> APB1ENR |= (1U<<21);
	GPIOA -> MODER |= (2U<<16)|(2U<<18);
	GPIOA -> OTYPER |= (1U<<8)|(1U<<9);
	GPIOA -> OSPEEDR |= (3U<<16)|(3U<<18);
	GPIOA -> PUPDR |= (1U<<16)|(1U<<18);
	GPIOA -> AFR[1] |= (4U<<0)|(4U<<4);

	I2C1  -> CCR &= ~(1U<<15);
	I2C1 -> CR2 |= (45<<0);
	I2C1 -> CCR = (225<<0);
	I2C1 -> TRISE = 46;
	I2C1 -> CR1 |= (1U<<0);
}

void I2C_start()
{
	I2C1 -> CR1 |= (1U<<8);
	while(!(I2C1 -> SR1 & (1U<<0)));
}

void I2C_write(unsigned char data)
{
	I2C1 -> SR1 |= (1U<<7);
	I2C1 -> DR = data;
	while(!(I2C1 -> SR1 & (1U<<2)));
}

void I2C_address(unsigned char addr)
{
	I2C1 -> DR = addr;
	while(!(I2C1 -> SR1 & (1U<<1)));
	uint8_t temp = I2C1 -> SR1 | I2C1 -> SR2;
}

void I2C_stop()
{
	I2C1 -> CR1 |= (1U<<9);
}

void I2C_write_multi(char *data,char size)
{
	while(!(I2C1 -> SR1 & (1U<<7)));
	while(size)
	{
		while(!(I2C1 -> SR1 & (1U<<7)))*data++;
		size--;
	}
	while(I2C1 -> SR1 & (1U<<2));
}

int main()
{
	I2C_config();
	while(1)
	{
	   for(int i=0;i<7;i++)
	   {

		   	I2C_start();
		   	I2C_address(0X4E);
		   	I2C_write(1<<i);
		   	for(int i=0 ;i<10000;i++)
		   	{}
		   	I2C_stop();
	   }

	}
}

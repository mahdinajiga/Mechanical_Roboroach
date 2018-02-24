/*****************************************************
This program was produced by the
CodeWizardAVR V2.05.3 Standard
Automatic Program Generator
© Copyright 1998-2011 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : RoborochTest01
Version : 
Date    : 8/20/2017
Author  : 
Company : 
Comments: 


Chip type               : ATmega328
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*****************************************************/

#include <mega328.h>

#include <delay.h>
#include <MPU_lib.h>
#include <math.h>
#include <i2c_lib.h>

// Declare your global variables here

unsigned char str[15];
float gyro_xrs,gyro_yrs,gyro_zrs,accel_xg,accel_yg,accel_zg;
signed int gyro_x,gyro_y,gyro_z,accel_x,accel_y,accel_z;
float roll,pitch;


#define MPU6050_GXOFFSET -27
#define MPU6050_GYOFFSET -2
#define MPU6050_GZOFFSET 22


void main(void)
{

#pragma optsize-
CLKPR=0x80;
CLKPR=0x00;
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif

PORTB=0x00;
DDRB=0x00;

PORTC=0x00;
DDRC=0x00;

PORTD=0x00;
DDRD=0x00;

TCCR0A=0x00;
TCCR0B=0x00;
TCNT0=0x00;
OCR0A=0x00;
OCR0B=0x00;

TCCR1A=0x00;
TCCR1B=0x00;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

ASSR=0x00;
TCCR2A=0x00;
TCCR2B=0x00;
TCNT2=0x00;
OCR2A=0x00;
OCR2B=0x00;

EICRA=0x00;
EIMSK=0x00;
PCICR=0x00;

TIMSK0=0x00;

TIMSK1=0x00;

TIMSK2=0x00;

UCSR0B=0x00;

ACSR=0x80;
ADCSRB=0x00;
DIDR1=0x00;

ADCSRA=0x00;

SPCR=0x00;

TWCR=0x00;


mpu_Initialize();

while (1)
      {
      // Place your code here
                  
          mpu_BurstRead(MPU6050_REG_ACCEL_XOUT_H,14,str);

    accel_x=(str[0]<<8)|str[1];      
    accel_y=(str[2]<<8)|str[3];      
    accel_z=(str[4]<<8)|str[5];       

    accel_xg=accel_x/2048.0;                              // convert to g (m/s*2)
    accel_yg=accel_y/2048.0;
    accel_zg=accel_z/2048.0;
    
    gyro_x=(str[8]<<8)|str[9];
    gyro_y=(str[10]<<8)|str[11];      
    gyro_z=(str[12]<<8)|str[13];

    gyro_xrs= (gyro_x-(MPU6050_GXOFFSET))/16.4;           // convert to (deg / sec)
    gyro_yrs= (gyro_y-(MPU6050_GYOFFSET))/16.4;
    gyro_zrs= (gyro_z-(MPU6050_GZOFFSET))/16.4;


    roll=atan2(accel_yg,accel_zg);
    roll=roll*57.32;                                      

    pitch=atan2(accel_xg,accel_zg);
    pitch=pitch*57.32;    


    delay_ms(100);
      }
}

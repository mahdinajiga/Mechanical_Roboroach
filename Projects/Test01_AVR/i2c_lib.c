#include <mega328.h>
#include <i2c_lib.h>
#include <math.h>
#define F_CPU 8000000UL

void  i2c_Initialize(unsigned long int bitrate,unsigned char prescale){
prescale &= 0x03; // Get 2 Least significant bits
TWSR |= prescale;
TWBR = (unsigned char)((F_CPU-(16*bitrate))/(2*bitrate*pow(4,prescale)));
}
void  i2c_Start(){
TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN); // send start condition
while (!(TWCR & (1 << TWINT)));
//while( TW_STATUS != TW_START); // Check for the acknowledgment
}
void  i2c_ReStart(){
TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN); // send start condition
while(!(TWCR & (1 << TWINT)));
//while( TW_STATUS != TW_REP_START); // Check for the acknowledgment
}
void  i2c_Stop(){
TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN); // send stop condition
//while(!(TWCR & (1<<TWSTO))); // Wait till stop condition is transmitted
}

void  i2c_WriteDeviceAddress(unsigned char address,unsigned char instruction){
address = (address<<1) | (instruction & TW_INSTRUCTION_BIT); // put instruction bit at least significant bit of address byte ( Address + Instruction )
TWDR = address; // Address and write instruction
TWCR = (1<<TWINT) | (1<<TWEN); // Clear TWI interrupt flag,Enable TWI

while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte transmitted

//if ((instruction & TW_INSTRUCTION_BIT) == TW_WRITE )
//{
////while(TW_STATUS != TW_MT_SLA_ACK); // Check for Address + W acknowledgment
//}
//
//else
//{
////while(TW_STATUS != TW_MR_SLA_ACK); // Check for Address + R acknowledgment
//}
//

}
void  i2c_WriteByte(unsigned char data){
TWDR=data; // put data in TWDR

TWCR=(1<<TWINT)|(1<<TWEN); // Clear TWI interrupt flag,Enable TWI
while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte transmitted

//while(TW_STATUS != TW_MT_DATA_ACK); // Check for the acknowledgment
}
unsigned char  i2c_ReadByte(){
TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN); // Clear TWI interrupt flag,Enable TWI
while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte received
//while(TW_STATUS != TW_MR_DATA_NACK); // Check for the acknowledgment
return TWDR;
}
unsigned char  i2c_ReadLastByte(){
TWCR = (1 << TWINT) | (1 << TWEN); // Clear TWI interrupt flag,Enable TWI
while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte received
//while(TW_STATUS != TW_MR_DATA_NACK); // Check for the acknowledgment
return TWDR;
}
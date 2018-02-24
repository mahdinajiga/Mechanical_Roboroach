#define TW_INSTRUCTION_BIT (0x01)
 #define TW_READ 1
 #define TW_WRITE 0 
void  i2c_Initialize(unsigned long int bitrate,unsigned char prescale);
void  i2c_Start();
void  i2c_ReStart();
void  i2c_Stop();
unsigned char i2c_ReadByte();
unsigned char  i2c_ReadLastByte();
void  i2c_WriteByte(unsigned char data);
void  i2c_WriteDeviceAddress(unsigned char address,unsigned char instruction);

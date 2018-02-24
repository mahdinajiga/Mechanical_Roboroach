#include "MPU_lib.h"
#include "i2c_lib.h"

void mpu_Initialize(){
i2c_Initialize(400000,0);
mpu_WriteByte(MPU6050_REG_PWR_MGMT_1,0);
mpu_WriteByte(MPU6050_REG_SMPLRT_DIV,0); // Set Sample Rate To 8kHz
mpu_WriteByte(MPU6050_REG_CONFIG,0); // FSYNC = OFF , DLPF = OFF
mpu_WriteByte(MPU6050_REG_GYRO_CONFIG,(MPU6050_GYRO_FULL_SCALE_RANGE_2000<<3)); // = 000 11 XXX Set Gyro Full Scale Range to 2000 , Self Test Disabled
mpu_WriteByte(MPU6050_REG_ACCEL_CONFIG,(MPU6050_ACCEL_FULL_SCALE_RANGE_16G<<3)); // = 000 11 XXX Set Accelerometer Full Scale Range to 16g , Self Test Disabled
}
unsigned char mpu_GetByte(unsigned char reg){
unsigned char temp = i2c_ReadLastByte();
i2c_Start();
i2c_WriteDeviceAddress(MPU6050_DEVICE_ADRESS,TW_WRITE); // Device address
i2c_WriteByte(reg); // Reg address
i2c_ReStart();
i2c_WriteDeviceAddress(MPU6050_DEVICE_ADRESS,TW_READ); // Device address
temp = i2c_ReadLastByte();
i2c_Stop();
return temp;
}
void mpu_WriteByte(unsigned char reg,unsigned char value){
i2c_Start();
i2c_WriteDeviceAddress(MPU6050_DEVICE_ADRESS,TW_WRITE); // Device address
i2c_WriteByte(reg); // Register address
i2c_WriteByte(value);
i2c_Stop();
}

void mpu_BurstRead(unsigned char startRegAddress,unsigned char count, unsigned char * buffer){
unsigned char i;
if (count<=0)
{
return;
}
i2c_Start();
i2c_WriteDeviceAddress(MPU6050_DEVICE_ADRESS,TW_WRITE); // Device address
i2c_WriteByte(startRegAddress); // REg address
i2c_ReStart();
i2c_WriteDeviceAddress(MPU6050_DEVICE_ADRESS,TW_READ); // Device address
for ( i=0; i<count-1; i++)
{
buffer[i] = i2c_ReadByte();
}
buffer[count-1] = i2c_ReadLastByte();
i2c_Stop();
}
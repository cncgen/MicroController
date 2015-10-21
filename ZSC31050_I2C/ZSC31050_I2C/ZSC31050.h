/*
 * ZSC31050.h
 *
 * Created: 21.01.2014 10:13:56
 *  Author: Rouven
 */ 


#ifndef ZSC31050_H_
#define ZSC31050_H_

#define SIGNATURE_EEP                       0x01
#define SIGNATURE_RAM                       0x00

#define ZSC31050_ADDRESS                    0xF0

#define ZSC31050_CM_COMMAND                 0x72

#define ZSC31050_EEP_READ_MESS_COMMAND      0x30
#define ZSC31050_EEP_READ_LIMIT_COMMAND     0x38
#define ZSC31050_EEP_READ_TEMP_COMMAND      0x3A
#define ZSC31050_EEP_READ_CONFIG_COMMAND    0x46

#define ZSC31050_RAM_READ_MESS_COMMAND      0x10
#define ZSC31050_RAM_READ_LIMIT_COMMAND     0x18
#define ZSC31050_RAM_READ_TEMP_COMMAND      0x1A
#define ZSC31050_RAM_READ_CONFIG_COMMAND    0x26

#define ZSC31050_EEP_WRITE_MESS_COMMAND     0xA0
#define ZSC31050_EEP_WRITE_LIMIT_COMMAND    0xA8
#define ZSC31050_EEP_WRITE_TEMP_COMMAND     0xAA
#define ZSC31050_EEP_WRITE_CONFIG_COMMAND   0xB6

#define ZSC31050_RAM_WRITE_MESS_COMMAND     0x80
#define ZSC31050_RAM_WRITE_LIMIT_COMMAND    0x88
#define ZSC31050_RAM_WRITE_TEMP_COMMAND     0x8A
#define ZSC31050_RAM_WRITE_CONFIG_COMMAND   0x96

#define ZSC31050_EEP_READ_ID_COMMAND        0x4E
#define ZSC31050_EEP_WRITE_ID_COMMAND       0x9E

#define EEP_READ_ALL_COMMAND                0x1A

#define EEP_READ_MESS_COMMAND               0x11
#define EEP_READ_LIMIT_COMMAND              0x12
#define EEP_READ_TEMP_COMMAND               0x13
#define EEP_READ_CONFIG_COMMAND             0x14

#define RAM_READ_ALL_COMMAND                0x19

#define RAM_READ_MESS_COMMAND               0x15
#define RAM_READ_LIMIT_COMMAND              0x16
#define RAM_READ_TEMP_COMMAND               0x17
#define RAM_READ_CONFIG_COMMAND             0x18

#define EEP_READ_ID_COMMAND                 0x1B

#define EEP_WRITE_ALL_COMMAND               0x2A

#define EEP_WRITE_MESS_COMMAND              0x21
#define EEP_WRITE_LIMIT_COMMAND             0x22
#define EEP_WRITE_TEMP_COMMAND              0x23
#define EEP_WRITE_CONFIG_COMMAND            0x24

#define RAM_WRITE_ALL_COMMAND               0x29

#define RAM_WRITE_MESS_COMMAND              0x25
#define RAM_WRITE_LIMIT_COMMAND             0x26
#define RAM_WRITE_TEMP_COMMAND              0x27
#define RAM_WRITE_CONFIG_COMMAND            0x28

#define EEP_WRITE_ID_COMMAND                0x2B

#define COPY_RAM2EEP                        0x31
#define COPY_EEP2RAM                        0x32

#define ZSC31050_COPY_RAM2EEP               0xC3
#define ZSC31050_COPY_EEP2RAM               0xC0

#define ZSC31050_START_P                    0xD0
#define ZSC31050_START_T1                   0xD1
#define ZSC31050_START_PAZ                  0xD4
#define ZSC31050_START_TAZ1                 0xD5
#define ZSC31050_START_PAZC                 0xD8
#define ZSC31050_START_T1AZC                0xD9
#define ZSC31050_START_CMV_AZC              0xDB
#define ZSC31050_START_MESS                 0x02

#define START_P                             0x40
#define START_T1                            0x41
#define START_PAZ                           0x42
#define START_TAZ1                          0x43
#define START_PAZC                          0x44
#define START_T1AZC                         0x45
#define START_CMV_AZC                       0x46
#define START_MESS                          0x47

void Read_ZSC31050 (volatile unsigned char[]);

unsigned char Write_ZSC31050 (volatile unsigned char[],volatile unsigned char);

void Command_mode(void);

void Signature_write(unsigned char);

void Copy(volatile unsigned char[]);

void Output(volatile unsigned char[]);

#endif /* ZSC31050_H_ */
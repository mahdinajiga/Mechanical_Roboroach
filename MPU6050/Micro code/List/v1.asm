
;CodeVisionAVR C Compiler V3.12 Advanced
;(C) Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
;http://www.hpinfotech.com

;Build configuration    : Release
;Chip type              : ATmega328
;Program type           : Application
;Clock frequency        : 8.000000 MHz
;Memory model           : Small
;Optimize for           : Size
;(s)printf features     : float, width, precision
;(s)scanf features      : int, width
;External RAM size      : 0
;Data Stack size        : 512 byte(s)
;Heap size              : 0 byte(s)
;Promote 'char' to 'int': Yes
;'char' is unsigned     : Yes
;8 bit enums            : Yes
;Global 'const' stored in FLASH: No
;Enhanced function parameter passing: Yes
;Enhanced core instructions: On
;Automatic register allocation for global variables: On
;Smart register allocation: On

	#define _MODEL_SMALL_

	#pragma AVRPART ADMIN PART_NAME ATmega328
	#pragma AVRPART MEMORY PROG_FLASH 32768
	#pragma AVRPART MEMORY EEPROM 1024
	#pragma AVRPART MEMORY INT_SRAM SIZE 2048
	#pragma AVRPART MEMORY INT_SRAM START_ADDR 0x100

	#define CALL_SUPPORTED 1

	.LISTMAC
	.EQU EERE=0x0
	.EQU EEWE=0x1
	.EQU EEMWE=0x2
	.EQU UDRE=0x5
	.EQU RXC=0x7
	.EQU EECR=0x1F
	.EQU EEDR=0x20
	.EQU EEARL=0x21
	.EQU EEARH=0x22
	.EQU SPSR=0x2D
	.EQU SPDR=0x2E
	.EQU SMCR=0x33
	.EQU MCUSR=0x34
	.EQU MCUCR=0x35
	.EQU WDTCSR=0x60
	.EQU UCSR0A=0xC0
	.EQU UDR0=0xC6
	.EQU SPL=0x3D
	.EQU SPH=0x3E
	.EQU SREG=0x3F
	.EQU GPIOR0=0x1E

	.DEF R0X0=R0
	.DEF R0X1=R1
	.DEF R0X2=R2
	.DEF R0X3=R3
	.DEF R0X4=R4
	.DEF R0X5=R5
	.DEF R0X6=R6
	.DEF R0X7=R7
	.DEF R0X8=R8
	.DEF R0X9=R9
	.DEF R0XA=R10
	.DEF R0XB=R11
	.DEF R0XC=R12
	.DEF R0XD=R13
	.DEF R0XE=R14
	.DEF R0XF=R15
	.DEF R0X10=R16
	.DEF R0X11=R17
	.DEF R0X12=R18
	.DEF R0X13=R19
	.DEF R0X14=R20
	.DEF R0X15=R21
	.DEF R0X16=R22
	.DEF R0X17=R23
	.DEF R0X18=R24
	.DEF R0X19=R25
	.DEF R0X1A=R26
	.DEF R0X1B=R27
	.DEF R0X1C=R28
	.DEF R0X1D=R29
	.DEF R0X1E=R30
	.DEF R0X1F=R31

	.EQU __SRAM_START=0x0100
	.EQU __SRAM_END=0x08FF
	.EQU __DSTACK_SIZE=0x0200
	.EQU __HEAP_SIZE=0x0000
	.EQU __CLEAR_SRAM_SIZE=__SRAM_END-__SRAM_START+1

	.MACRO __CPD1N
	CPI  R30,LOW(@0)
	LDI  R26,HIGH(@0)
	CPC  R31,R26
	LDI  R26,BYTE3(@0)
	CPC  R22,R26
	LDI  R26,BYTE4(@0)
	CPC  R23,R26
	.ENDM

	.MACRO __CPD2N
	CPI  R26,LOW(@0)
	LDI  R30,HIGH(@0)
	CPC  R27,R30
	LDI  R30,BYTE3(@0)
	CPC  R24,R30
	LDI  R30,BYTE4(@0)
	CPC  R25,R30
	.ENDM

	.MACRO __CPWRR
	CP   R@0,R@2
	CPC  R@1,R@3
	.ENDM

	.MACRO __CPWRN
	CPI  R@0,LOW(@2)
	LDI  R30,HIGH(@2)
	CPC  R@1,R30
	.ENDM

	.MACRO __ADDB1MN
	SUBI R30,LOW(-@0-(@1))
	.ENDM

	.MACRO __ADDB2MN
	SUBI R26,LOW(-@0-(@1))
	.ENDM

	.MACRO __ADDW1MN
	SUBI R30,LOW(-@0-(@1))
	SBCI R31,HIGH(-@0-(@1))
	.ENDM

	.MACRO __ADDW2MN
	SUBI R26,LOW(-@0-(@1))
	SBCI R27,HIGH(-@0-(@1))
	.ENDM

	.MACRO __ADDW1FN
	SUBI R30,LOW(-2*@0-(@1))
	SBCI R31,HIGH(-2*@0-(@1))
	.ENDM

	.MACRO __ADDD1FN
	SUBI R30,LOW(-2*@0-(@1))
	SBCI R31,HIGH(-2*@0-(@1))
	SBCI R22,BYTE3(-2*@0-(@1))
	.ENDM

	.MACRO __ADDD1N
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	SBCI R22,BYTE3(-@0)
	SBCI R23,BYTE4(-@0)
	.ENDM

	.MACRO __ADDD2N
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	SBCI R24,BYTE3(-@0)
	SBCI R25,BYTE4(-@0)
	.ENDM

	.MACRO __SUBD1N
	SUBI R30,LOW(@0)
	SBCI R31,HIGH(@0)
	SBCI R22,BYTE3(@0)
	SBCI R23,BYTE4(@0)
	.ENDM

	.MACRO __SUBD2N
	SUBI R26,LOW(@0)
	SBCI R27,HIGH(@0)
	SBCI R24,BYTE3(@0)
	SBCI R25,BYTE4(@0)
	.ENDM

	.MACRO __ANDBMNN
	LDS  R30,@0+(@1)
	ANDI R30,LOW(@2)
	STS  @0+(@1),R30
	.ENDM

	.MACRO __ANDWMNN
	LDS  R30,@0+(@1)
	ANDI R30,LOW(@2)
	STS  @0+(@1),R30
	LDS  R30,@0+(@1)+1
	ANDI R30,HIGH(@2)
	STS  @0+(@1)+1,R30
	.ENDM

	.MACRO __ANDD1N
	ANDI R30,LOW(@0)
	ANDI R31,HIGH(@0)
	ANDI R22,BYTE3(@0)
	ANDI R23,BYTE4(@0)
	.ENDM

	.MACRO __ANDD2N
	ANDI R26,LOW(@0)
	ANDI R27,HIGH(@0)
	ANDI R24,BYTE3(@0)
	ANDI R25,BYTE4(@0)
	.ENDM

	.MACRO __ORBMNN
	LDS  R30,@0+(@1)
	ORI  R30,LOW(@2)
	STS  @0+(@1),R30
	.ENDM

	.MACRO __ORWMNN
	LDS  R30,@0+(@1)
	ORI  R30,LOW(@2)
	STS  @0+(@1),R30
	LDS  R30,@0+(@1)+1
	ORI  R30,HIGH(@2)
	STS  @0+(@1)+1,R30
	.ENDM

	.MACRO __ORD1N
	ORI  R30,LOW(@0)
	ORI  R31,HIGH(@0)
	ORI  R22,BYTE3(@0)
	ORI  R23,BYTE4(@0)
	.ENDM

	.MACRO __ORD2N
	ORI  R26,LOW(@0)
	ORI  R27,HIGH(@0)
	ORI  R24,BYTE3(@0)
	ORI  R25,BYTE4(@0)
	.ENDM

	.MACRO __DELAY_USB
	LDI  R24,LOW(@0)
__DELAY_USB_LOOP:
	DEC  R24
	BRNE __DELAY_USB_LOOP
	.ENDM

	.MACRO __DELAY_USW
	LDI  R24,LOW(@0)
	LDI  R25,HIGH(@0)
__DELAY_USW_LOOP:
	SBIW R24,1
	BRNE __DELAY_USW_LOOP
	.ENDM

	.MACRO __GETD1S
	LDD  R30,Y+@0
	LDD  R31,Y+@0+1
	LDD  R22,Y+@0+2
	LDD  R23,Y+@0+3
	.ENDM

	.MACRO __GETD2S
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	LDD  R24,Y+@0+2
	LDD  R25,Y+@0+3
	.ENDM

	.MACRO __PUTD1S
	STD  Y+@0,R30
	STD  Y+@0+1,R31
	STD  Y+@0+2,R22
	STD  Y+@0+3,R23
	.ENDM

	.MACRO __PUTD2S
	STD  Y+@0,R26
	STD  Y+@0+1,R27
	STD  Y+@0+2,R24
	STD  Y+@0+3,R25
	.ENDM

	.MACRO __PUTDZ2
	STD  Z+@0,R26
	STD  Z+@0+1,R27
	STD  Z+@0+2,R24
	STD  Z+@0+3,R25
	.ENDM

	.MACRO __CLRD1S
	STD  Y+@0,R30
	STD  Y+@0+1,R30
	STD  Y+@0+2,R30
	STD  Y+@0+3,R30
	.ENDM

	.MACRO __POINTB1MN
	LDI  R30,LOW(@0+(@1))
	.ENDM

	.MACRO __POINTW1MN
	LDI  R30,LOW(@0+(@1))
	LDI  R31,HIGH(@0+(@1))
	.ENDM

	.MACRO __POINTD1M
	LDI  R30,LOW(@0)
	LDI  R31,HIGH(@0)
	LDI  R22,BYTE3(@0)
	LDI  R23,BYTE4(@0)
	.ENDM

	.MACRO __POINTW1FN
	LDI  R30,LOW(2*@0+(@1))
	LDI  R31,HIGH(2*@0+(@1))
	.ENDM

	.MACRO __POINTD1FN
	LDI  R30,LOW(2*@0+(@1))
	LDI  R31,HIGH(2*@0+(@1))
	LDI  R22,BYTE3(2*@0+(@1))
	LDI  R23,BYTE4(2*@0+(@1))
	.ENDM

	.MACRO __POINTB2MN
	LDI  R26,LOW(@0+(@1))
	.ENDM

	.MACRO __POINTW2MN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	.ENDM

	.MACRO __POINTW2FN
	LDI  R26,LOW(2*@0+(@1))
	LDI  R27,HIGH(2*@0+(@1))
	.ENDM

	.MACRO __POINTD2FN
	LDI  R26,LOW(2*@0+(@1))
	LDI  R27,HIGH(2*@0+(@1))
	LDI  R24,BYTE3(2*@0+(@1))
	LDI  R25,BYTE4(2*@0+(@1))
	.ENDM

	.MACRO __POINTBRM
	LDI  R@0,LOW(@1)
	.ENDM

	.MACRO __POINTWRM
	LDI  R@0,LOW(@2)
	LDI  R@1,HIGH(@2)
	.ENDM

	.MACRO __POINTBRMN
	LDI  R@0,LOW(@1+(@2))
	.ENDM

	.MACRO __POINTWRMN
	LDI  R@0,LOW(@2+(@3))
	LDI  R@1,HIGH(@2+(@3))
	.ENDM

	.MACRO __POINTWRFN
	LDI  R@0,LOW(@2*2+(@3))
	LDI  R@1,HIGH(@2*2+(@3))
	.ENDM

	.MACRO __GETD1N
	LDI  R30,LOW(@0)
	LDI  R31,HIGH(@0)
	LDI  R22,BYTE3(@0)
	LDI  R23,BYTE4(@0)
	.ENDM

	.MACRO __GETD2N
	LDI  R26,LOW(@0)
	LDI  R27,HIGH(@0)
	LDI  R24,BYTE3(@0)
	LDI  R25,BYTE4(@0)
	.ENDM

	.MACRO __GETB1MN
	LDS  R30,@0+(@1)
	.ENDM

	.MACRO __GETB1HMN
	LDS  R31,@0+(@1)
	.ENDM

	.MACRO __GETW1MN
	LDS  R30,@0+(@1)
	LDS  R31,@0+(@1)+1
	.ENDM

	.MACRO __GETD1MN
	LDS  R30,@0+(@1)
	LDS  R31,@0+(@1)+1
	LDS  R22,@0+(@1)+2
	LDS  R23,@0+(@1)+3
	.ENDM

	.MACRO __GETBRMN
	LDS  R@0,@1+(@2)
	.ENDM

	.MACRO __GETWRMN
	LDS  R@0,@2+(@3)
	LDS  R@1,@2+(@3)+1
	.ENDM

	.MACRO __GETWRZ
	LDD  R@0,Z+@2
	LDD  R@1,Z+@2+1
	.ENDM

	.MACRO __GETD2Z
	LDD  R26,Z+@0
	LDD  R27,Z+@0+1
	LDD  R24,Z+@0+2
	LDD  R25,Z+@0+3
	.ENDM

	.MACRO __GETB2MN
	LDS  R26,@0+(@1)
	.ENDM

	.MACRO __GETW2MN
	LDS  R26,@0+(@1)
	LDS  R27,@0+(@1)+1
	.ENDM

	.MACRO __GETD2MN
	LDS  R26,@0+(@1)
	LDS  R27,@0+(@1)+1
	LDS  R24,@0+(@1)+2
	LDS  R25,@0+(@1)+3
	.ENDM

	.MACRO __PUTB1MN
	STS  @0+(@1),R30
	.ENDM

	.MACRO __PUTW1MN
	STS  @0+(@1),R30
	STS  @0+(@1)+1,R31
	.ENDM

	.MACRO __PUTD1MN
	STS  @0+(@1),R30
	STS  @0+(@1)+1,R31
	STS  @0+(@1)+2,R22
	STS  @0+(@1)+3,R23
	.ENDM

	.MACRO __PUTB1EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMWRB
	.ENDM

	.MACRO __PUTW1EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMWRW
	.ENDM

	.MACRO __PUTD1EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMWRD
	.ENDM

	.MACRO __PUTBR0MN
	STS  @0+(@1),R0
	.ENDM

	.MACRO __PUTBMRN
	STS  @0+(@1),R@2
	.ENDM

	.MACRO __PUTWMRN
	STS  @0+(@1),R@2
	STS  @0+(@1)+1,R@3
	.ENDM

	.MACRO __PUTBZR
	STD  Z+@1,R@0
	.ENDM

	.MACRO __PUTWZR
	STD  Z+@2,R@0
	STD  Z+@2+1,R@1
	.ENDM

	.MACRO __GETW1R
	MOV  R30,R@0
	MOV  R31,R@1
	.ENDM

	.MACRO __GETW2R
	MOV  R26,R@0
	MOV  R27,R@1
	.ENDM

	.MACRO __GETWRN
	LDI  R@0,LOW(@2)
	LDI  R@1,HIGH(@2)
	.ENDM

	.MACRO __PUTW1R
	MOV  R@0,R30
	MOV  R@1,R31
	.ENDM

	.MACRO __PUTW2R
	MOV  R@0,R26
	MOV  R@1,R27
	.ENDM

	.MACRO __ADDWRN
	SUBI R@0,LOW(-@2)
	SBCI R@1,HIGH(-@2)
	.ENDM

	.MACRO __ADDWRR
	ADD  R@0,R@2
	ADC  R@1,R@3
	.ENDM

	.MACRO __SUBWRN
	SUBI R@0,LOW(@2)
	SBCI R@1,HIGH(@2)
	.ENDM

	.MACRO __SUBWRR
	SUB  R@0,R@2
	SBC  R@1,R@3
	.ENDM

	.MACRO __ANDWRN
	ANDI R@0,LOW(@2)
	ANDI R@1,HIGH(@2)
	.ENDM

	.MACRO __ANDWRR
	AND  R@0,R@2
	AND  R@1,R@3
	.ENDM

	.MACRO __ORWRN
	ORI  R@0,LOW(@2)
	ORI  R@1,HIGH(@2)
	.ENDM

	.MACRO __ORWRR
	OR   R@0,R@2
	OR   R@1,R@3
	.ENDM

	.MACRO __EORWRR
	EOR  R@0,R@2
	EOR  R@1,R@3
	.ENDM

	.MACRO __GETWRS
	LDD  R@0,Y+@2
	LDD  R@1,Y+@2+1
	.ENDM

	.MACRO __PUTBSR
	STD  Y+@1,R@0
	.ENDM

	.MACRO __PUTWSR
	STD  Y+@2,R@0
	STD  Y+@2+1,R@1
	.ENDM

	.MACRO __MOVEWRR
	MOV  R@0,R@2
	MOV  R@1,R@3
	.ENDM

	.MACRO __INWR
	IN   R@0,@2
	IN   R@1,@2+1
	.ENDM

	.MACRO __OUTWR
	OUT  @2+1,R@1
	OUT  @2,R@0
	.ENDM

	.MACRO __CALL1MN
	LDS  R30,@0+(@1)
	LDS  R31,@0+(@1)+1
	ICALL
	.ENDM

	.MACRO __CALL1FN
	LDI  R30,LOW(2*@0+(@1))
	LDI  R31,HIGH(2*@0+(@1))
	CALL __GETW1PF
	ICALL
	.ENDM

	.MACRO __CALL2EN
	PUSH R26
	PUSH R27
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMRDW
	POP  R27
	POP  R26
	ICALL
	.ENDM

	.MACRO __CALL2EX
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	CALL __EEPROMRDD
	ICALL
	.ENDM

	.MACRO __GETW1STACK
	IN   R30,SPL
	IN   R31,SPH
	ADIW R30,@0+1
	LD   R0,Z+
	LD   R31,Z
	MOV  R30,R0
	.ENDM

	.MACRO __GETD1STACK
	IN   R30,SPL
	IN   R31,SPH
	ADIW R30,@0+1
	LD   R0,Z+
	LD   R1,Z+
	LD   R22,Z
	MOVW R30,R0
	.ENDM

	.MACRO __NBST
	BST  R@0,@1
	IN   R30,SREG
	LDI  R31,0x40
	EOR  R30,R31
	OUT  SREG,R30
	.ENDM


	.MACRO __PUTB1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RNS
	MOVW R26,R@0
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RNS
	MOVW R26,R@0
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RNS
	MOVW R26,R@0
	ADIW R26,@1
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	CALL __PUTDP1
	.ENDM


	.MACRO __GETB1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R30,Z
	.ENDM

	.MACRO __GETB1HSX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R31,Z
	.ENDM

	.MACRO __GETW1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R0,Z+
	LD   R31,Z
	MOV  R30,R0
	.ENDM

	.MACRO __GETD1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R0,Z+
	LD   R1,Z+
	LD   R22,Z+
	LD   R23,Z
	MOVW R30,R0
	.ENDM

	.MACRO __GETB2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R26,X
	.ENDM

	.MACRO __GETW2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	.ENDM

	.MACRO __GETD2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R1,X+
	LD   R24,X+
	LD   R25,X
	MOVW R26,R0
	.ENDM

	.MACRO __GETBRSX
	MOVW R30,R28
	SUBI R30,LOW(-@1)
	SBCI R31,HIGH(-@1)
	LD   R@0,Z
	.ENDM

	.MACRO __GETWRSX
	MOVW R30,R28
	SUBI R30,LOW(-@2)
	SBCI R31,HIGH(-@2)
	LD   R@0,Z+
	LD   R@1,Z
	.ENDM

	.MACRO __GETBRSX2
	MOVW R26,R28
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	LD   R@0,X
	.ENDM

	.MACRO __GETWRSX2
	MOVW R26,R28
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	LD   R@0,X+
	LD   R@1,X
	.ENDM

	.MACRO __LSLW8SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R31,Z
	CLR  R30
	.ENDM

	.MACRO __PUTB1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	.ENDM

	.MACRO __CLRW1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X,R30
	.ENDM

	.MACRO __CLRD1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X+,R30
	ST   X+,R30
	ST   X,R30
	.ENDM

	.MACRO __PUTB2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z,R26
	.ENDM

	.MACRO __PUTW2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z+,R26
	ST   Z,R27
	.ENDM

	.MACRO __PUTD2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z+,R26
	ST   Z+,R27
	ST   Z+,R24
	ST   Z,R25
	.ENDM

	.MACRO __PUTBSRX
	MOVW R30,R28
	SUBI R30,LOW(-@1)
	SBCI R31,HIGH(-@1)
	ST   Z,R@0
	.ENDM

	.MACRO __PUTWSRX
	MOVW R30,R28
	SUBI R30,LOW(-@2)
	SBCI R31,HIGH(-@2)
	ST   Z+,R@0
	ST   Z,R@1
	.ENDM

	.MACRO __PUTB1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	.ENDM

	.MACRO __MULBRR
	MULS R@0,R@1
	MOVW R30,R0
	.ENDM

	.MACRO __MULBRRU
	MUL  R@0,R@1
	MOVW R30,R0
	.ENDM

	.MACRO __MULBRR0
	MULS R@0,R@1
	.ENDM

	.MACRO __MULBRRU0
	MUL  R@0,R@1
	.ENDM

	.MACRO __MULBNWRU
	LDI  R26,@2
	MUL  R26,R@0
	MOVW R30,R0
	MUL  R26,R@1
	ADD  R31,R0
	.ENDM

;NAME DEFINITIONS FOR GLOBAL VARIABLES ALLOCATED TO REGISTERS
	.DEF _gyro_x=R3
	.DEF _gyro_x_msb=R4
	.DEF _gyro_y=R5
	.DEF _gyro_y_msb=R6
	.DEF _gyro_z=R7
	.DEF _gyro_z_msb=R8
	.DEF _accel_x=R9
	.DEF _accel_x_msb=R10
	.DEF _accel_y=R11
	.DEF _accel_y_msb=R12
	.DEF _accel_z=R13
	.DEF _accel_z_msb=R14

;GPIOR0 INITIALIZATION VALUE
	.EQU __GPIOR0_INIT=0x00

	.CSEG
	.ORG 0x00

;START OF CODE MARKER
__START_OF_CODE:

;INTERRUPT VECTORS
	JMP  __RESET
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00

_0x2020060:
	.DB  0x1
_0x2020000:
	.DB  0x2D,0x4E,0x41,0x4E,0x0,0x49,0x4E,0x46
	.DB  0x0

__GLOBAL_INI_TBL:
	.DW  0x01
	.DW  __seed_G101
	.DW  _0x2020060*2

_0xFFFFFFFF:
	.DW  0

#define __GLOBAL_INI_TBL_PRESENT 1

__RESET:
	CLI
	CLR  R30
	OUT  EECR,R30

;INTERRUPT VECTORS ARE PLACED
;AT THE START OF FLASH
	LDI  R31,1
	OUT  MCUCR,R31
	OUT  MCUCR,R30

;DISABLE WATCHDOG
	LDI  R31,0x18
	WDR
	IN   R26,MCUSR
	CBR  R26,8
	OUT  MCUSR,R26
	STS  WDTCSR,R31
	STS  WDTCSR,R30

;CLEAR R2-R14
	LDI  R24,(14-2)+1
	LDI  R26,2
	CLR  R27
__CLEAR_REG:
	ST   X+,R30
	DEC  R24
	BRNE __CLEAR_REG

;CLEAR SRAM
	LDI  R24,LOW(__CLEAR_SRAM_SIZE)
	LDI  R25,HIGH(__CLEAR_SRAM_SIZE)
	LDI  R26,LOW(__SRAM_START)
	LDI  R27,HIGH(__SRAM_START)
__CLEAR_SRAM:
	ST   X+,R30
	SBIW R24,1
	BRNE __CLEAR_SRAM

;GLOBAL VARIABLES INITIALIZATION
	LDI  R30,LOW(__GLOBAL_INI_TBL*2)
	LDI  R31,HIGH(__GLOBAL_INI_TBL*2)
__GLOBAL_INI_NEXT:
	LPM  R24,Z+
	LPM  R25,Z+
	SBIW R24,0
	BREQ __GLOBAL_INI_END
	LPM  R26,Z+
	LPM  R27,Z+
	LPM  R0,Z+
	LPM  R1,Z+
	MOVW R22,R30
	MOVW R30,R0
__GLOBAL_INI_LOOP:
	LPM  R0,Z+
	ST   X+,R0
	SBIW R24,1
	BRNE __GLOBAL_INI_LOOP
	MOVW R30,R22
	RJMP __GLOBAL_INI_NEXT
__GLOBAL_INI_END:

;GPIOR0 INITIALIZATION
	LDI  R30,__GPIOR0_INIT
	OUT  GPIOR0,R30

;HARDWARE STACK POINTER INITIALIZATION
	LDI  R30,LOW(__SRAM_END-__HEAP_SIZE)
	OUT  SPL,R30
	LDI  R30,HIGH(__SRAM_END-__HEAP_SIZE)
	OUT  SPH,R30

;DATA STACK POINTER INITIALIZATION
	LDI  R28,LOW(__SRAM_START+__DSTACK_SIZE)
	LDI  R29,HIGH(__SRAM_START+__DSTACK_SIZE)

	JMP  _main

	.ESEG
	.ORG 0

	.DSEG
	.ORG 0x300

	.CSEG
;/*****************************************************
;This program was produced by the
;CodeWizardAVR V2.05.3 Standard
;Automatic Program Generator
;© Copyright 1998-2011 Pavel Haiduc, HP InfoTech s.r.l.
;http://www.hpinfotech.com
;
;Project :
;Version :
;Date    : 7/27/2017
;Author  : Admin
;Company :
;Comments:
;
;
;Chip type               : ATmega8
;Program type            : Application
;AVR Core Clock frequency: 8.000000 MHz
;Memory model            : Small
;External RAM size       : 0
;Data Stack size         : 512
;*****************************************************/
;
;#include <mega8.h>
	#ifndef __SLEEP_DEFINED__
	#define __SLEEP_DEFINED__
	.EQU __se_bit=0x80
	.EQU __sm_mask=0x70
	.EQU __sm_powerdown=0x20
	.EQU __sm_powersave=0x30
	.EQU __sm_standby=0x60
	.EQU __sm_ext_standby=0x70
	.EQU __sm_adc_noise_red=0x10
	.SET power_ctrl_reg=mcucr
	#endif
;
;#include <delay.h>
;#include <MPU_lib.h>
;#include <math.h>
;#include <i2c_lib.h>
;
;
;
;// Declare your global variables here
;unsigned char str[15];
;float gyro_xrs,gyro_yrs,gyro_zrs,accel_xg,accel_yg,accel_zg;
;signed int gyro_x,gyro_y,gyro_z,accel_x,accel_y,accel_z;
;float roll,pitch;
;
;#define MPU6050_GXOFFSET -27
;#define MPU6050_GYOFFSET -2
;#define MPU6050_GZOFFSET 22
;
;
;void main(void)
; 0000 002D {

	.CSEG
_main:
; .FSTART _main
; 0000 002E // Declare your local variables here
; 0000 002F 
; 0000 0030 // Input/Output Ports initialization
; 0000 0031 // Port B initialization
; 0000 0032 // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=Out Func1=Out Func0=In
; 0000 0033 // State7=T State6=T State5=T State4=T State3=T State2=0 State1=0 State0=T
; 0000 0034 PORTB=0x00;
	LDI  R30,LOW(0)
	OUT  0x18,R30
; 0000 0035 DDRB=0x00;
	OUT  0x17,R30
; 0000 0036 
; 0000 0037 // Port C initialization
; 0000 0038 // Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
; 0000 0039 // State6=T State5=T State4=T State3=T State2=T State1=T State0=T
; 0000 003A PORTC=0x00;
	OUT  0x15,R30
; 0000 003B DDRC=0x00;
	OUT  0x14,R30
; 0000 003C 
; 0000 003D // Port D initialization
; 0000 003E // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
; 0000 003F // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
; 0000 0040 PORTD=0x00;
	OUT  0x12,R30
; 0000 0041 DDRD=0x00;
	OUT  0x11,R30
; 0000 0042 
; 0000 0043 // Timer/Counter 0 initialization
; 0000 0044 // Clock source: System Clock
; 0000 0045 // Clock value: Timer 0 Stopped
; 0000 0046 TCCR0=0x00;
	OUT  0x33,R30
; 0000 0047 TCNT0=0x00;
	OUT  0x32,R30
; 0000 0048 
; 0000 0049 // Timer/Counter 1 initialization
; 0000 004A // Clock source: System Clock
; 0000 004B // Clock value: 125.000 kHz
; 0000 004C // Mode: Fast PWM top=0x03FF
; 0000 004D // OC1A output: Non-Inv.
; 0000 004E // OC1B output: Non-Inv.
; 0000 004F // Noise Canceler: Off
; 0000 0050 // Input Capture on Falling Edge
; 0000 0051 // Timer1 Overflow Interrupt: Off
; 0000 0052 // Input Capture Interrupt: Off
; 0000 0053 // Compare A Match Interrupt: Off
; 0000 0054 // Compare B Match Interrupt: Off
; 0000 0055 TCCR1A=0x00;
	OUT  0x2F,R30
; 0000 0056 TCCR1B=0x00;
	OUT  0x2E,R30
; 0000 0057 TCNT1H=0x00;
	OUT  0x2D,R30
; 0000 0058 TCNT1L=0x00;
	OUT  0x2C,R30
; 0000 0059 ICR1H=0x00;
	OUT  0x27,R30
; 0000 005A ICR1L=0x00;
	OUT  0x26,R30
; 0000 005B OCR1AH=0x00;
	OUT  0x2B,R30
; 0000 005C OCR1AL=0x00;
	OUT  0x2A,R30
; 0000 005D OCR1BH=0x00;
	OUT  0x29,R30
; 0000 005E OCR1BL=0x00;
	OUT  0x28,R30
; 0000 005F 
; 0000 0060 // Timer/Counter 2 initialization
; 0000 0061 // Clock source: System Clock
; 0000 0062 // Clock value: Timer2 Stopped
; 0000 0063 // Mode: Normal top=0xFF
; 0000 0064 // OC2 output: Disconnected
; 0000 0065 ASSR=0x00;
	OUT  0x22,R30
; 0000 0066 TCCR2=0x00;
	OUT  0x25,R30
; 0000 0067 TCNT2=0x00;
	OUT  0x24,R30
; 0000 0068 OCR2=0x00;
	OUT  0x23,R30
; 0000 0069 
; 0000 006A 
; 0000 006B // External Interrupt(s) initialization
; 0000 006C // INT0: Off
; 0000 006D // INT1: Off
; 0000 006E MCUCR=0x00;
	OUT  0x35,R30
; 0000 006F 
; 0000 0070 // Timer(s)/Counter(s) Interrupt(s) initialization
; 0000 0071 TIMSK=0x00;
	OUT  0x39,R30
; 0000 0072 
; 0000 0073 
; 0000 0074 // USART initialization
; 0000 0075 // Communication Parameters: 8 Data, 1 Stop, No Parity
; 0000 0076 // USART Receiver: On
; 0000 0077 // USART Transmitter: On
; 0000 0078 // USART Mode: Asynchronous
; 0000 0079 // USART Baud Rate: 9600
; 0000 007A UCSRA=0x00;
	OUT  0xB,R30
; 0000 007B UCSRB=0x18;
	LDI  R30,LOW(24)
	OUT  0xA,R30
; 0000 007C UCSRC=0x86;
	LDI  R30,LOW(134)
	OUT  0x20,R30
; 0000 007D UBRRH=0x00;
	LDI  R30,LOW(0)
	OUT  0x20,R30
; 0000 007E UBRRL=0x33;
	LDI  R30,LOW(51)
	OUT  0x9,R30
; 0000 007F 
; 0000 0080 // Analog Comparator Input Capture by Timer/Counter 1: Off
; 0000 0081 ACSR=0x80;
	LDI  R30,LOW(128)
	OUT  0x8,R30
; 0000 0082 SFIOR=0x00;
	LDI  R30,LOW(0)
	OUT  0x30,R30
; 0000 0083 
; 0000 0084 
; 0000 0085 
; 0000 0086 // SPI initialization
; 0000 0087 // SPI disabled
; 0000 0088 SPCR=0x00;
	OUT  0xD,R30
; 0000 0089 
; 0000 008A // TWI initialization
; 0000 008B // TWI disabled
; 0000 008C TWCR=0x00;
	OUT  0x36,R30
; 0000 008D 
; 0000 008E // Global enable interrupts
; 0000 008F 
; 0000 0090 
; 0000 0091 mpu_Initialize();
	RCALL _mpu_Initialize
; 0000 0092 
; 0000 0093 
; 0000 0094 while (1)
_0x3:
; 0000 0095       {
; 0000 0096     mpu_BurstRead(MPU6050_REG_ACCEL_XOUT_H,14,str);
	LDI  R30,LOW(59)
	ST   -Y,R30
	LDI  R30,LOW(14)
	ST   -Y,R30
	LDI  R26,LOW(_str)
	LDI  R27,HIGH(_str)
	RCALL _mpu_BurstRead
; 0000 0097 
; 0000 0098     accel_x=(str[0]<<8)|str[1];
	LDS  R27,_str
	LDI  R26,LOW(0)
	__GETB1MN _str,1
	LDI  R31,0
	OR   R30,R26
	OR   R31,R27
	__PUTW1R 9,10
; 0000 0099     accel_y=(str[2]<<8)|str[3];
	__GETBRMN 27,_str,2
	LDI  R26,LOW(0)
	__GETB1MN _str,3
	LDI  R31,0
	OR   R30,R26
	OR   R31,R27
	__PUTW1R 11,12
; 0000 009A     accel_z=(str[4]<<8)|str[5];
	__GETBRMN 27,_str,4
	LDI  R26,LOW(0)
	__GETB1MN _str,5
	LDI  R31,0
	OR   R30,R26
	OR   R31,R27
	__PUTW1R 13,14
; 0000 009B 
; 0000 009C     accel_xg=accel_x/2048.0;                              // convert to g (m/s*2)
	__GETW1R 9,10
	CALL SUBOPT_0x0
	STS  _accel_xg,R30
	STS  _accel_xg+1,R31
	STS  _accel_xg+2,R22
	STS  _accel_xg+3,R23
; 0000 009D     accel_yg=accel_y/2048.0;
	__GETW1R 11,12
	CALL SUBOPT_0x0
	STS  _accel_yg,R30
	STS  _accel_yg+1,R31
	STS  _accel_yg+2,R22
	STS  _accel_yg+3,R23
; 0000 009E     accel_zg=accel_z/2048.0;
	__GETW1R 13,14
	CALL SUBOPT_0x0
	STS  _accel_zg,R30
	STS  _accel_zg+1,R31
	STS  _accel_zg+2,R22
	STS  _accel_zg+3,R23
; 0000 009F 
; 0000 00A0     gyro_x=(str[8]<<8)|str[9];
	__GETBRMN 27,_str,8
	LDI  R26,LOW(0)
	__GETB1MN _str,9
	LDI  R31,0
	OR   R30,R26
	OR   R31,R27
	__PUTW1R 3,4
; 0000 00A1     gyro_y=(str[10]<<8)|str[11];
	__GETBRMN 27,_str,10
	LDI  R26,LOW(0)
	__GETB1MN _str,11
	LDI  R31,0
	OR   R30,R26
	OR   R31,R27
	__PUTW1R 5,6
; 0000 00A2     gyro_z=(str[12]<<8)|str[13];
	__GETBRMN 27,_str,12
	LDI  R26,LOW(0)
	__GETB1MN _str,13
	LDI  R31,0
	OR   R30,R26
	OR   R31,R27
	__PUTW1R 7,8
; 0000 00A3 
; 0000 00A4     gyro_xrs= (gyro_x-(MPU6050_GXOFFSET))/16.4;           // convert to (deg / sec)
	__GETW1R 3,4
	SUBI R30,LOW(65509)
	SBCI R31,HIGH(65509)
	CALL SUBOPT_0x1
	STS  _gyro_xrs,R30
	STS  _gyro_xrs+1,R31
	STS  _gyro_xrs+2,R22
	STS  _gyro_xrs+3,R23
; 0000 00A5     gyro_yrs= (gyro_y-(MPU6050_GYOFFSET))/16.4;
	__GETW1R 5,6
	SUBI R30,LOW(65534)
	SBCI R31,HIGH(65534)
	CALL SUBOPT_0x1
	STS  _gyro_yrs,R30
	STS  _gyro_yrs+1,R31
	STS  _gyro_yrs+2,R22
	STS  _gyro_yrs+3,R23
; 0000 00A6     gyro_zrs= (gyro_z-(MPU6050_GZOFFSET))/16.4;
	__GETW1R 7,8
	SBIW R30,22
	CALL SUBOPT_0x1
	STS  _gyro_zrs,R30
	STS  _gyro_zrs+1,R31
	STS  _gyro_zrs+2,R22
	STS  _gyro_zrs+3,R23
; 0000 00A7 
; 0000 00A8 
; 0000 00A9     roll=atan2(accel_yg,accel_zg);
	LDS  R30,_accel_yg
	LDS  R31,_accel_yg+1
	LDS  R22,_accel_yg+2
	LDS  R23,_accel_yg+3
	CALL SUBOPT_0x2
	CALL SUBOPT_0x3
; 0000 00AA     roll=roll*57.32;
	LDS  R26,_roll
	LDS  R27,_roll+1
	LDS  R24,_roll+2
	LDS  R25,_roll+3
	CALL SUBOPT_0x4
	CALL SUBOPT_0x3
; 0000 00AB 
; 0000 00AC     pitch=atan2(accel_xg,accel_zg);
	LDS  R30,_accel_xg
	LDS  R31,_accel_xg+1
	LDS  R22,_accel_xg+2
	LDS  R23,_accel_xg+3
	CALL SUBOPT_0x2
	CALL SUBOPT_0x5
; 0000 00AD     pitch=pitch*57.32;
	LDS  R26,_pitch
	LDS  R27,_pitch+1
	LDS  R24,_pitch+2
	LDS  R25,_pitch+3
	CALL SUBOPT_0x4
	CALL SUBOPT_0x5
; 0000 00AE 
; 0000 00AF 
; 0000 00B0     delay_ms(100);
	LDI  R26,LOW(100)
	LDI  R27,0
	CALL _delay_ms
; 0000 00B1 
; 0000 00B2       }
	RJMP _0x3
; 0000 00B3 }
_0x6:
	RJMP _0x6
; .FEND
;//============================================================================================
;#include "MPU_lib.h"
;#include "i2c_lib.h"
;
;void mpu_Initialize(){
; 0001 0004 void mpu_Initialize(){

	.CSEG
_mpu_Initialize:
; .FSTART _mpu_Initialize
; 0001 0005 i2c_Initialize(400000,0);
	__GETD1N 0x61A80
	CALL __PUTPARD1
	LDI  R26,LOW(0)
	RCALL _i2c_Initialize
; 0001 0006 mpu_WriteByte(MPU6050_REG_PWR_MGMT_1,0);
	LDI  R30,LOW(107)
	CALL SUBOPT_0x6
; 0001 0007 mpu_WriteByte(MPU6050_REG_SMPLRT_DIV,0); // Set Sample Rate To 8kHz
	LDI  R30,LOW(25)
	CALL SUBOPT_0x6
; 0001 0008 mpu_WriteByte(MPU6050_REG_CONFIG,0); // FSYNC = OFF , DLPF = OFF
	LDI  R30,LOW(26)
	CALL SUBOPT_0x6
; 0001 0009 mpu_WriteByte(MPU6050_REG_GYRO_CONFIG,(MPU6050_GYRO_FULL_SCALE_RANGE_2000<<3)); // = 000 11 XXX Set Gyro Full Scale Rang ...
	LDI  R30,LOW(27)
	ST   -Y,R30
	LDI  R26,LOW(24)
	RCALL _mpu_WriteByte
; 0001 000A mpu_WriteByte(MPU6050_REG_ACCEL_CONFIG,(MPU6050_ACCEL_FULL_SCALE_RANGE_16G<<3)); // = 000 11 XXX Set Accelerometer Full  ...
	LDI  R30,LOW(28)
	ST   -Y,R30
	LDI  R26,LOW(24)
	RCALL _mpu_WriteByte
; 0001 000B }
	RET
; .FEND
;unsigned char mpu_GetByte(unsigned char reg){
; 0001 000C unsigned char mpu_GetByte(unsigned char reg){
; 0001 000D unsigned char temp = i2c_ReadLastByte();
; 0001 000E i2c_Start();
;	reg -> Y+1
;	temp -> R17
; 0001 000F i2c_WriteDeviceAddress(MPU6050_DEVICE_ADRESS,TW_WRITE); // Device address
; 0001 0010 i2c_WriteByte(reg); // Reg address
; 0001 0011 i2c_ReStart();
; 0001 0012 i2c_WriteDeviceAddress(MPU6050_DEVICE_ADRESS,TW_READ); // Device address
; 0001 0013 temp = i2c_ReadLastByte();
; 0001 0014 i2c_Stop();
; 0001 0015 return temp;
; 0001 0016 }
;void mpu_WriteByte(unsigned char reg,unsigned char value){
; 0001 0017 void mpu_WriteByte(unsigned char reg,unsigned char value){
_mpu_WriteByte:
; .FSTART _mpu_WriteByte
; 0001 0018 i2c_Start();
	ST   -Y,R26
;	reg -> Y+1
;	value -> Y+0
	CALL SUBOPT_0x7
; 0001 0019 i2c_WriteDeviceAddress(MPU6050_DEVICE_ADRESS,TW_WRITE); // Device address
; 0001 001A i2c_WriteByte(reg); // Register address
	LDD  R26,Y+1
	RCALL _i2c_WriteByte
; 0001 001B i2c_WriteByte(value);
	LD   R26,Y
	RCALL _i2c_WriteByte
; 0001 001C i2c_Stop();
	RCALL _i2c_Stop
; 0001 001D }
	RJMP _0x2080006
; .FEND
;
;void mpu_BurstRead(unsigned char startRegAddress,unsigned char count, unsigned char * buffer){
; 0001 001F void mpu_BurstRead(unsigned char startRegAddress,unsigned char count, unsigned char * buffer){
_mpu_BurstRead:
; .FSTART _mpu_BurstRead
; 0001 0020 unsigned char i;
; 0001 0021 if (count<=0)
	ST   -Y,R27
	ST   -Y,R26
	ST   -Y,R17
;	startRegAddress -> Y+4
;	count -> Y+3
;	*buffer -> Y+1
;	i -> R17
	LDD  R26,Y+3
	CPI  R26,0
	BRNE _0x20003
; 0001 0022 {
; 0001 0023 return;
	LDD  R17,Y+0
	RJMP _0x2080007
; 0001 0024 }
; 0001 0025 i2c_Start();
_0x20003:
	CALL SUBOPT_0x7
; 0001 0026 i2c_WriteDeviceAddress(MPU6050_DEVICE_ADRESS,TW_WRITE); // Device address
; 0001 0027 i2c_WriteByte(startRegAddress); // REg address
	LDD  R26,Y+4
	RCALL _i2c_WriteByte
; 0001 0028 i2c_ReStart();
	RCALL _i2c_ReStart
; 0001 0029 i2c_WriteDeviceAddress(MPU6050_DEVICE_ADRESS,TW_READ); // Device address
	LDI  R30,LOW(104)
	ST   -Y,R30
	LDI  R26,LOW(1)
	RCALL _i2c_WriteDeviceAddress
; 0001 002A for ( i=0; i<count-1; i++)
	LDI  R17,LOW(0)
_0x20005:
	LDD  R30,Y+3
	LDI  R31,0
	SBIW R30,1
	MOV  R26,R17
	LDI  R27,0
	CP   R26,R30
	CPC  R27,R31
	BRGE _0x20006
; 0001 002B {
; 0001 002C buffer[i] = i2c_ReadByte();
	MOV  R30,R17
	LDD  R26,Y+1
	LDD  R27,Y+1+1
	LDI  R31,0
	ADD  R30,R26
	ADC  R31,R27
	PUSH R31
	PUSH R30
	RCALL _i2c_ReadByte
	POP  R26
	POP  R27
	ST   X,R30
; 0001 002D }
	SUBI R17,-1
	RJMP _0x20005
_0x20006:
; 0001 002E buffer[count-1] = i2c_ReadLastByte();
	LDD  R30,Y+3
	LDI  R31,0
	SBIW R30,1
	LDD  R26,Y+1
	LDD  R27,Y+1+1
	ADD  R30,R26
	ADC  R31,R27
	PUSH R31
	PUSH R30
	RCALL _i2c_ReadLastByte
	POP  R26
	POP  R27
	ST   X,R30
; 0001 002F i2c_Stop();
	RCALL _i2c_Stop
; 0001 0030 }
	LDD  R17,Y+0
	RJMP _0x2080007
; .FEND
;#include <mega328.h>
	#ifndef __SLEEP_DEFINED__
	#define __SLEEP_DEFINED__
	.EQU __se_bit=0x01
	.EQU __sm_mask=0x0E
	.EQU __sm_adc_noise_red=0x02
	.EQU __sm_powerdown=0x04
	.EQU __sm_powersave=0x06
	.EQU __sm_standby=0x0C
	.EQU __sm_ext_standby=0x0E
	.SET power_ctrl_reg=smcr
	#endif
;#include <i2c_lib.h>
;#include <math.h>
;#define F_CPU 8000000UL
;
;void  i2c_Initialize(unsigned long int bitrate,unsigned char prescale){
; 0002 0006 void  i2c_Initialize(unsigned long int bitrate,unsigned char prescale){

	.CSEG
_i2c_Initialize:
; .FSTART _i2c_Initialize
; 0002 0007 prescale &= 0x03; // Get 2 Least significant bits
	ST   -Y,R26
;	bitrate -> Y+1
;	prescale -> Y+0
	LD   R30,Y
	ANDI R30,LOW(0x3)
	ST   Y,R30
; 0002 0008 TWSR |= prescale;
	LDI  R26,LOW(185)
	LDI  R27,HIGH(185)
	MOV  R0,R26
	LD   R30,X
	LD   R26,Y
	OR   R30,R26
	MOV  R26,R0
	ST   X,R30
; 0002 0009 TWBR = (unsigned char)((F_CPU-(16*bitrate))/(2*bitrate*pow(4,prescale)));
	__GETD1S 1
	__GETD2N 0x10
	CALL __MULD12U
	__GETD2N 0x7A1200
	CALL __SWAPD12
	CALL __SUBD12
	PUSH R23
	PUSH R22
	PUSH R31
	PUSH R30
	__GETD1S 1
	CALL __LSLD1
	PUSH R23
	PUSH R22
	PUSH R31
	PUSH R30
	__GETD1N 0x40800000
	CALL __PUTPARD1
	LDD  R30,Y+4
	CLR  R31
	CLR  R22
	CLR  R23
	CALL __CDF1
	MOVW R26,R30
	MOVW R24,R22
	CALL _pow
	POP  R26
	POP  R27
	POP  R24
	POP  R25
	CALL __CDF2U
	CALL __MULF12
	POP  R26
	POP  R27
	POP  R24
	POP  R25
	CALL __CDF2U
	CALL __DIVF21
	CALL __CFD1U
	STS  184,R30
; 0002 000A }
_0x2080007:
	ADIW R28,5
	RET
; .FEND
;void  i2c_Start(){
; 0002 000B void  i2c_Start(){
_i2c_Start:
; .FSTART _i2c_Start
; 0002 000C TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN); // send start condition
	LDI  R30,LOW(164)
	STS  188,R30
; 0002 000D while (!(TWCR & (1 << TWINT)));
_0x40003:
	LDS  R30,188
	ANDI R30,LOW(0x80)
	BREQ _0x40003
; 0002 000E //while( TW_STATUS != TW_START); // Check for the acknowledgment
; 0002 000F }
	RET
; .FEND
;void  i2c_ReStart(){
; 0002 0010 void  i2c_ReStart(){
_i2c_ReStart:
; .FSTART _i2c_ReStart
; 0002 0011 TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN); // send start condition
	LDI  R30,LOW(164)
	STS  188,R30
; 0002 0012 while(!(TWCR & (1 << TWINT)));
_0x40006:
	LDS  R30,188
	ANDI R30,LOW(0x80)
	BREQ _0x40006
; 0002 0013 //while( TW_STATUS != TW_REP_START); // Check for the acknowledgment
; 0002 0014 }
	RET
; .FEND
;void  i2c_Stop(){
; 0002 0015 void  i2c_Stop(){
_i2c_Stop:
; .FSTART _i2c_Stop
; 0002 0016 TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN); // send stop condition
	LDI  R30,LOW(148)
	STS  188,R30
; 0002 0017 //while(!(TWCR & (1<<TWSTO))); // Wait till stop condition is transmitted
; 0002 0018 }
	RET
; .FEND
;
;void  i2c_WriteDeviceAddress(unsigned char address,unsigned char instruction){
; 0002 001A void  i2c_WriteDeviceAddress(unsigned char address,unsigned char instruction){
_i2c_WriteDeviceAddress:
; .FSTART _i2c_WriteDeviceAddress
; 0002 001B address = (address<<1) | (instruction & TW_INSTRUCTION_BIT); // put instruction bit at least significant bit of address  ...
	ST   -Y,R26
;	address -> Y+1
;	instruction -> Y+0
	LDD  R30,Y+1
	LSL  R30
	MOV  R26,R30
	LD   R30,Y
	ANDI R30,LOW(0x1)
	OR   R30,R26
	STD  Y+1,R30
; 0002 001C TWDR = address; // Address and write instruction
	STS  187,R30
; 0002 001D TWCR = (1<<TWINT) | (1<<TWEN); // Clear TWI interrupt flag,Enable TWI
	LDI  R30,LOW(132)
	STS  188,R30
; 0002 001E 
; 0002 001F while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte transmitted
_0x40009:
	LDS  R30,188
	ANDI R30,LOW(0x80)
	BREQ _0x40009
; 0002 0020 
; 0002 0021 //if ((instruction & TW_INSTRUCTION_BIT) == TW_WRITE )
; 0002 0022 //{
; 0002 0023 ////while(TW_STATUS != TW_MT_SLA_ACK); // Check for Address + W acknowledgment
; 0002 0024 //}
; 0002 0025 //
; 0002 0026 //else
; 0002 0027 //{
; 0002 0028 ////while(TW_STATUS != TW_MR_SLA_ACK); // Check for Address + R acknowledgment
; 0002 0029 //}
; 0002 002A //
; 0002 002B 
; 0002 002C }
_0x2080006:
	ADIW R28,2
	RET
; .FEND
;void  i2c_WriteByte(unsigned char data){
; 0002 002D void  i2c_WriteByte(unsigned char data){
_i2c_WriteByte:
; .FSTART _i2c_WriteByte
; 0002 002E TWDR=data; // put data in TWDR
	ST   -Y,R26
;	data -> Y+0
	LD   R30,Y
	STS  187,R30
; 0002 002F 
; 0002 0030 TWCR=(1<<TWINT)|(1<<TWEN); // Clear TWI interrupt flag,Enable TWI
	LDI  R30,LOW(132)
	STS  188,R30
; 0002 0031 while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte transmitted
_0x4000C:
	LDS  R30,188
	ANDI R30,LOW(0x80)
	BREQ _0x4000C
; 0002 0032 
; 0002 0033 //while(TW_STATUS != TW_MT_DATA_ACK); // Check for the acknowledgment
; 0002 0034 }
	ADIW R28,1
	RET
; .FEND
;unsigned char  i2c_ReadByte(){
; 0002 0035 unsigned char  i2c_ReadByte(){
_i2c_ReadByte:
; .FSTART _i2c_ReadByte
; 0002 0036 TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN); // Clear TWI interrupt flag,Enable TWI
	LDI  R30,LOW(196)
	STS  188,R30
; 0002 0037 while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte received
_0x4000F:
	LDS  R30,188
	ANDI R30,LOW(0x80)
	BREQ _0x4000F
; 0002 0038 //while(TW_STATUS != TW_MR_DATA_NACK); // Check for the acknowledgment
; 0002 0039 return TWDR;
	RJMP _0x2080005
; 0002 003A }
; .FEND
;unsigned char  i2c_ReadLastByte(){
; 0002 003B unsigned char  i2c_ReadLastByte(){
_i2c_ReadLastByte:
; .FSTART _i2c_ReadLastByte
; 0002 003C TWCR = (1 << TWINT) | (1 << TWEN); // Clear TWI interrupt flag,Enable TWI
	LDI  R30,LOW(132)
	STS  188,R30
; 0002 003D while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte received
_0x40012:
	LDS  R30,188
	ANDI R30,LOW(0x80)
	BREQ _0x40012
; 0002 003E //while(TW_STATUS != TW_MR_DATA_NACK); // Check for the acknowledgment
; 0002 003F return TWDR;
_0x2080005:
	LDS  R30,187
	RET
; 0002 0040 }
; .FEND

	.CSEG
_ftrunc:
; .FSTART _ftrunc
	CALL __PUTPARD2
   ldd  r23,y+3
   ldd  r22,y+2
   ldd  r31,y+1
   ld   r30,y
   bst  r23,7
   lsl  r23
   sbrc r22,7
   sbr  r23,1
   mov  r25,r23
   subi r25,0x7e
   breq __ftrunc0
   brcs __ftrunc0
   cpi  r25,24
   brsh __ftrunc1
   clr  r26
   clr  r27
   clr  r24
__ftrunc2:
   sec
   ror  r24
   ror  r27
   ror  r26
   dec  r25
   brne __ftrunc2
   and  r30,r26
   and  r31,r27
   and  r22,r24
   rjmp __ftrunc1
__ftrunc0:
   clt
   clr  r23
   clr  r30
   clr  r31
   clr  r22
__ftrunc1:
   cbr  r22,0x80
   lsr  r23
   brcc __ftrunc3
   sbr  r22,0x80
__ftrunc3:
   bld  r23,7
   ld   r26,y+
   ld   r27,y+
   ld   r24,y+
   ld   r25,y+
   cp   r30,r26
   cpc  r31,r27
   cpc  r22,r24
   cpc  r23,r25
   bst  r25,7
   ret
; .FEND
_floor:
; .FSTART _floor
	CALL SUBOPT_0x8
	CALL _ftrunc
	CALL SUBOPT_0x9
    brne __floor1
__floor0:
	CALL SUBOPT_0xA
	RJMP _0x2080002
__floor1:
    brtc __floor0
	CALL SUBOPT_0xB
	CALL __SUBF12
	RJMP _0x2080002
; .FEND
_log:
; .FSTART _log
	CALL __PUTPARD2
	SBIW R28,4
	ST   -Y,R17
	ST   -Y,R16
	CALL SUBOPT_0xC
	CALL __CPD02
	BRLT _0x200000C
	__GETD1N 0xFF7FFFFF
	RJMP _0x2080004
_0x200000C:
	CALL SUBOPT_0xD
	CALL __PUTPARD1
	IN   R26,SPL
	IN   R27,SPH
	SBIW R26,1
	PUSH R17
	PUSH R16
	CALL _frexp
	POP  R16
	POP  R17
	CALL SUBOPT_0xE
	CALL SUBOPT_0xC
	__GETD1N 0x3F3504F3
	CALL __CMPF12
	BRSH _0x200000D
	CALL SUBOPT_0xF
	CALL __ADDF12
	CALL SUBOPT_0xE
	__SUBWRN 16,17,1
_0x200000D:
	CALL SUBOPT_0x10
	CALL __SUBF12
	PUSH R23
	PUSH R22
	PUSH R31
	PUSH R30
	CALL SUBOPT_0x10
	CALL __ADDF12
	POP  R26
	POP  R27
	POP  R24
	POP  R25
	CALL __DIVF21
	CALL SUBOPT_0xE
	CALL SUBOPT_0xF
	CALL SUBOPT_0x11
	__GETD2N 0x3F654226
	CALL SUBOPT_0x12
	__GETD1N 0x4054114E
	CALL SUBOPT_0x13
	CALL SUBOPT_0xC
	CALL __MULF12
	PUSH R23
	PUSH R22
	PUSH R31
	PUSH R30
	CALL SUBOPT_0x14
	__GETD2N 0x3FD4114D
	CALL __SUBF12
	POP  R26
	POP  R27
	POP  R24
	POP  R25
	CALL __DIVF21
	PUSH R23
	PUSH R22
	PUSH R31
	PUSH R30
	MOVW R30,R16
	CALL __CWD1
	CALL __CDF1
	__GETD2N 0x3F317218
	CALL __MULF12
	POP  R26
	POP  R27
	POP  R24
	POP  R25
	CALL __ADDF12
_0x2080004:
	LDD  R17,Y+1
	LDD  R16,Y+0
	ADIW R28,10
	RET
; .FEND
_exp:
; .FSTART _exp
	CALL __PUTPARD2
	SBIW R28,8
	ST   -Y,R17
	ST   -Y,R16
	CALL SUBOPT_0x15
	__GETD1N 0xC2AEAC50
	CALL __CMPF12
	BRSH _0x200000F
	CALL SUBOPT_0x16
	RJMP _0x2080003
_0x200000F:
	__GETD1S 10
	CALL __CPD10
	BRNE _0x2000010
	__GETD1N 0x3F800000
	RJMP _0x2080003
_0x2000010:
	CALL SUBOPT_0x15
	__GETD1N 0x42B17218
	CALL __CMPF12
	BREQ PC+2
	BRCC PC+2
	RJMP _0x2000011
	__GETD1N 0x7F7FFFFF
	RJMP _0x2080003
_0x2000011:
	CALL SUBOPT_0x15
	__GETD1N 0x3FB8AA3B
	CALL __MULF12
	__PUTD1S 10
	CALL SUBOPT_0x15
	RCALL _floor
	CALL __CFD1
	MOVW R16,R30
	CALL SUBOPT_0x15
	CALL __CWD1
	CALL __CDF1
	CALL SUBOPT_0x13
	MOVW R26,R30
	MOVW R24,R22
	__GETD1N 0x3F000000
	CALL SUBOPT_0x13
	CALL SUBOPT_0xE
	CALL SUBOPT_0xF
	CALL SUBOPT_0x11
	__GETD2N 0x3D6C4C6D
	CALL __MULF12
	__GETD2N 0x40E6E3A6
	CALL __ADDF12
	CALL SUBOPT_0xC
	CALL __MULF12
	CALL SUBOPT_0xE
	CALL SUBOPT_0x14
	__GETD2N 0x41A68D28
	CALL __ADDF12
	__PUTD1S 2
	CALL SUBOPT_0xD
	__GETD2S 2
	CALL __ADDF12
	__GETD2N 0x3FB504F3
	CALL __MULF12
	PUSH R23
	PUSH R22
	PUSH R31
	PUSH R30
	CALL SUBOPT_0xC
	CALL SUBOPT_0x14
	CALL __SUBF12
	POP  R26
	POP  R27
	POP  R24
	POP  R25
	CALL __DIVF21
	CALL __PUTPARD1
	MOVW R26,R16
	CALL _ldexp
_0x2080003:
	LDD  R17,Y+1
	LDD  R16,Y+0
	ADIW R28,14
	RET
; .FEND
_pow:
; .FSTART _pow
	CALL __PUTPARD2
	SBIW R28,4
	CALL SUBOPT_0x17
	CALL __CPD10
	BRNE _0x2000012
	CALL SUBOPT_0x16
	RJMP _0x2080001
_0x2000012:
	CALL SUBOPT_0x18
	CALL __CPD02
	BRGE _0x2000013
	CALL SUBOPT_0x19
	CALL __CPD10
	BRNE _0x2000014
	__GETD1N 0x3F800000
	RJMP _0x2080001
_0x2000014:
	CALL SUBOPT_0x18
	CALL SUBOPT_0x1A
	RCALL _exp
	RJMP _0x2080001
_0x2000013:
	CALL SUBOPT_0x19
	MOVW R26,R28
	CALL __CFD1
	CALL __PUTDP1
	CALL SUBOPT_0xA
	CALL __CDF1
	MOVW R26,R30
	MOVW R24,R22
	CALL SUBOPT_0x19
	CALL __CPD12
	BREQ _0x2000015
	CALL SUBOPT_0x16
	RJMP _0x2080001
_0x2000015:
	CALL SUBOPT_0x17
	CALL SUBOPT_0x1B
	CALL SUBOPT_0x1A
	RCALL _exp
	__PUTD1S 8
	LD   R30,Y
	ANDI R30,LOW(0x1)
	BRNE _0x2000016
	CALL SUBOPT_0x17
	RJMP _0x2080001
_0x2000016:
	CALL SUBOPT_0x17
	CALL __ANEGF1
	RJMP _0x2080001
; .FEND
_xatan:
; .FSTART _xatan
	CALL __PUTPARD2
	SBIW R28,4
	CALL SUBOPT_0x19
	CALL SUBOPT_0x1C
	CALL SUBOPT_0x9
	CALL SUBOPT_0xA
	__GETD2N 0x40CBD065
	CALL SUBOPT_0x1D
	CALL SUBOPT_0x1C
	PUSH R23
	PUSH R22
	PUSH R31
	PUSH R30
	CALL SUBOPT_0xA
	__GETD2N 0x41296D00
	CALL __ADDF12
	CALL SUBOPT_0x1E
	CALL SUBOPT_0x1D
	POP  R26
	POP  R27
	POP  R24
	POP  R25
	CALL __DIVF21
	ADIW R28,8
	RET
; .FEND
_yatan:
; .FSTART _yatan
	CALL SUBOPT_0x8
	__GETD1N 0x3ED413CD
	CALL __CMPF12
	BRSH _0x2000020
	CALL SUBOPT_0x1E
	RCALL _xatan
	RJMP _0x2080002
_0x2000020:
	CALL SUBOPT_0x1E
	__GETD1N 0x401A827A
	CALL __CMPF12
	BREQ PC+2
	BRCC PC+2
	RJMP _0x2000021
	CALL SUBOPT_0xB
	CALL SUBOPT_0x1F
	__GETD2N 0x3FC90FDB
	CALL SUBOPT_0x13
	RJMP _0x2080002
_0x2000021:
	CALL SUBOPT_0xB
	CALL __SUBF12
	PUSH R23
	PUSH R22
	PUSH R31
	PUSH R30
	CALL SUBOPT_0xB
	CALL __ADDF12
	POP  R26
	POP  R27
	POP  R24
	POP  R25
	CALL SUBOPT_0x1F
	__GETD2N 0x3F490FDB
	CALL __ADDF12
_0x2080002:
	ADIW R28,4
	RET
; .FEND
_atan2:
; .FSTART _atan2
	CALL __PUTPARD2
	SBIW R28,4
	CALL SUBOPT_0x19
	CALL __CPD10
	BRNE _0x200002D
	CALL SUBOPT_0x17
	CALL __CPD10
	BRNE _0x200002E
	__GETD1N 0x7F7FFFFF
	RJMP _0x2080001
_0x200002E:
	CALL SUBOPT_0x18
	CALL __CPD02
	BRGE _0x200002F
	__GETD1N 0x3FC90FDB
	RJMP _0x2080001
_0x200002F:
	__GETD1N 0xBFC90FDB
	RJMP _0x2080001
_0x200002D:
	CALL SUBOPT_0x19
	CALL SUBOPT_0x18
	CALL __DIVF21
	CALL SUBOPT_0x9
	__GETD2S 4
	CALL __CPD02
	BRGE _0x2000030
	LDD  R26,Y+11
	TST  R26
	BRMI _0x2000031
	CALL SUBOPT_0x1E
	RCALL _yatan
	RJMP _0x2080001
_0x2000031:
	CALL SUBOPT_0xA
	CALL SUBOPT_0x1B
	RCALL _yatan
	CALL __ANEGF1
	RJMP _0x2080001
_0x2000030:
	LDD  R26,Y+11
	TST  R26
	BRMI _0x2000032
	CALL SUBOPT_0xA
	CALL SUBOPT_0x1B
	RCALL _yatan
	__GETD2N 0x40490FDB
	CALL SUBOPT_0x13
	RJMP _0x2080001
_0x2000032:
	CALL SUBOPT_0x1E
	RCALL _yatan
	__GETD2N 0xC0490FDB
	CALL __ADDF12
_0x2080001:
	ADIW R28,12
	RET
; .FEND

	.CSEG

	.DSEG

	.CSEG

	.CSEG

	.CSEG

	.DSEG
_str:
	.BYTE 0xF
_gyro_xrs:
	.BYTE 0x4
_gyro_yrs:
	.BYTE 0x4
_gyro_zrs:
	.BYTE 0x4
_accel_xg:
	.BYTE 0x4
_accel_yg:
	.BYTE 0x4
_accel_zg:
	.BYTE 0x4
_roll:
	.BYTE 0x4
_pitch:
	.BYTE 0x4
__seed_G101:
	.BYTE 0x4

	.CSEG
;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:17 WORDS
SUBOPT_0x0:
	CALL __CWD1
	CALL __CDF1
	MOVW R26,R30
	MOVW R24,R22
	__GETD1N 0x45000000
	CALL __DIVF21
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:17 WORDS
SUBOPT_0x1:
	CALL __CWD1
	CALL __CDF1
	MOVW R26,R30
	MOVW R24,R22
	__GETD1N 0x41833333
	CALL __DIVF21
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:7 WORDS
SUBOPT_0x2:
	CALL __PUTPARD1
	LDS  R26,_accel_zg
	LDS  R27,_accel_zg+1
	LDS  R24,_accel_zg+2
	LDS  R25,_accel_zg+3
	JMP  _atan2

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:3 WORDS
SUBOPT_0x3:
	STS  _roll,R30
	STS  _roll+1,R31
	STS  _roll+2,R22
	STS  _roll+3,R23
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x4:
	__GETD1N 0x426547AE
	CALL __MULF12
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:3 WORDS
SUBOPT_0x5:
	STS  _pitch,R30
	STS  _pitch+1,R31
	STS  _pitch+2,R22
	STS  _pitch+3,R23
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x6:
	ST   -Y,R30
	LDI  R26,LOW(0)
	JMP  _mpu_WriteByte

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:2 WORDS
SUBOPT_0x7:
	CALL _i2c_Start
	LDI  R30,LOW(104)
	ST   -Y,R30
	LDI  R26,LOW(0)
	JMP  _i2c_WriteDeviceAddress

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x8:
	CALL __PUTPARD2
	CALL __GETD2S0
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x9:
	CALL __PUTD1S0
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 10 TIMES, CODE SIZE REDUCTION:15 WORDS
SUBOPT_0xA:
	CALL __GETD1S0
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 4 TIMES, CODE SIZE REDUCTION:9 WORDS
SUBOPT_0xB:
	RCALL SUBOPT_0xA
	__GETD2N 0x3F800000
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 8 TIMES, CODE SIZE REDUCTION:11 WORDS
SUBOPT_0xC:
	__GETD2S 6
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 7 TIMES, CODE SIZE REDUCTION:9 WORDS
SUBOPT_0xD:
	__GETD1S 6
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 5 TIMES, CODE SIZE REDUCTION:5 WORDS
SUBOPT_0xE:
	__PUTD1S 6
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0xF:
	RCALL SUBOPT_0xD
	RJMP SUBOPT_0xC

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x10:
	RCALL SUBOPT_0xD
	__GETD2N 0x3F800000
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:5 WORDS
SUBOPT_0x11:
	CALL __MULF12
	__PUTD1S 2
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x12:
	CALL __MULF12
	MOVW R26,R30
	MOVW R24,R22
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 5 TIMES, CODE SIZE REDUCTION:5 WORDS
SUBOPT_0x13:
	CALL __SWAPD12
	CALL __SUBF12
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x14:
	__GETD1S 2
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 5 TIMES, CODE SIZE REDUCTION:5 WORDS
SUBOPT_0x15:
	__GETD2S 10
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x16:
	__GETD1N 0x0
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 5 TIMES, CODE SIZE REDUCTION:5 WORDS
SUBOPT_0x17:
	__GETD1S 8
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 4 TIMES, CODE SIZE REDUCTION:3 WORDS
SUBOPT_0x18:
	__GETD2S 8
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 6 TIMES, CODE SIZE REDUCTION:7 WORDS
SUBOPT_0x19:
	__GETD1S 4
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:3 WORDS
SUBOPT_0x1A:
	CALL _log
	__GETD2S 4
	RJMP SUBOPT_0x12

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x1B:
	CALL __ANEGF1
	MOVW R26,R30
	MOVW R24,R22
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x1C:
	__GETD2S 4
	CALL __MULF12
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:3 WORDS
SUBOPT_0x1D:
	CALL __MULF12
	__GETD2N 0x414A8F4E
	CALL __ADDF12
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 5 TIMES, CODE SIZE REDUCTION:5 WORDS
SUBOPT_0x1E:
	CALL __GETD2S0
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x1F:
	CALL __DIVF21
	MOVW R26,R30
	MOVW R24,R22
	JMP  _xatan


	.CSEG
_delay_ms:
	adiw r26,0
	breq __delay_ms1
__delay_ms0:
	__DELAY_USW 0x7D0
	wdr
	sbiw r26,1
	brne __delay_ms0
__delay_ms1:
	ret

_frexp:
	LD   R30,Y+
	LD   R31,Y+
	LD   R22,Y+
	LD   R23,Y+
	BST  R23,7
	LSL  R22
	ROL  R23
	CLR  R24
	SUBI R23,0x7E
	SBC  R24,R24
	ST   X+,R23
	ST   X,R24
	LDI  R23,0x7E
	LSR  R23
	ROR  R22
	BRTS __ANEGF1
	RET

_ldexp:
	LD   R30,Y+
	LD   R31,Y+
	LD   R22,Y+
	LD   R23,Y+
	BST  R23,7
	LSL  R22
	ROL  R23
	ADD  R23,R26
	LSR  R23
	ROR  R22
	BRTS __ANEGF1
	RET

__ANEGF1:
	SBIW R30,0
	SBCI R22,0
	SBCI R23,0
	BREQ __ANEGF10
	SUBI R23,0x80
__ANEGF10:
	RET

__ROUND_REPACK:
	TST  R21
	BRPL __REPACK
	CPI  R21,0x80
	BRNE __ROUND_REPACK0
	SBRS R30,0
	RJMP __REPACK
__ROUND_REPACK0:
	ADIW R30,1
	ADC  R22,R25
	ADC  R23,R25
	BRVS __REPACK1

__REPACK:
	LDI  R21,0x80
	EOR  R21,R23
	BRNE __REPACK0
	PUSH R21
	RJMP __ZERORES
__REPACK0:
	CPI  R21,0xFF
	BREQ __REPACK1
	LSL  R22
	LSL  R0
	ROR  R21
	ROR  R22
	MOV  R23,R21
	RET
__REPACK1:
	PUSH R21
	TST  R0
	BRMI __REPACK2
	RJMP __MAXRES
__REPACK2:
	RJMP __MINRES

__UNPACK:
	LDI  R21,0x80
	MOV  R1,R25
	AND  R1,R21
	LSL  R24
	ROL  R25
	EOR  R25,R21
	LSL  R21
	ROR  R24

__UNPACK1:
	LDI  R21,0x80
	MOV  R0,R23
	AND  R0,R21
	LSL  R22
	ROL  R23
	EOR  R23,R21
	LSL  R21
	ROR  R22
	RET

__CFD1U:
	SET
	RJMP __CFD1U0
__CFD1:
	CLT
__CFD1U0:
	PUSH R21
	RCALL __UNPACK1
	CPI  R23,0x80
	BRLO __CFD10
	CPI  R23,0xFF
	BRCC __CFD10
	RJMP __ZERORES
__CFD10:
	LDI  R21,22
	SUB  R21,R23
	BRPL __CFD11
	NEG  R21
	CPI  R21,8
	BRTC __CFD19
	CPI  R21,9
__CFD19:
	BRLO __CFD17
	SER  R30
	SER  R31
	SER  R22
	LDI  R23,0x7F
	BLD  R23,7
	RJMP __CFD15
__CFD17:
	CLR  R23
	TST  R21
	BREQ __CFD15
__CFD18:
	LSL  R30
	ROL  R31
	ROL  R22
	ROL  R23
	DEC  R21
	BRNE __CFD18
	RJMP __CFD15
__CFD11:
	CLR  R23
__CFD12:
	CPI  R21,8
	BRLO __CFD13
	MOV  R30,R31
	MOV  R31,R22
	MOV  R22,R23
	SUBI R21,8
	RJMP __CFD12
__CFD13:
	TST  R21
	BREQ __CFD15
__CFD14:
	LSR  R23
	ROR  R22
	ROR  R31
	ROR  R30
	DEC  R21
	BRNE __CFD14
__CFD15:
	TST  R0
	BRPL __CFD16
	RCALL __ANEGD1
__CFD16:
	POP  R21
	RET

__CDF1U:
	SET
	RJMP __CDF1U0
__CDF1:
	CLT
__CDF1U0:
	SBIW R30,0
	SBCI R22,0
	SBCI R23,0
	BREQ __CDF10
	CLR  R0
	BRTS __CDF11
	TST  R23
	BRPL __CDF11
	COM  R0
	RCALL __ANEGD1
__CDF11:
	MOV  R1,R23
	LDI  R23,30
	TST  R1
__CDF12:
	BRMI __CDF13
	DEC  R23
	LSL  R30
	ROL  R31
	ROL  R22
	ROL  R1
	RJMP __CDF12
__CDF13:
	MOV  R30,R31
	MOV  R31,R22
	MOV  R22,R1
	PUSH R21
	RCALL __REPACK
	POP  R21
__CDF10:
	RET

__SWAPACC:
	PUSH R20
	MOVW R20,R30
	MOVW R30,R26
	MOVW R26,R20
	MOVW R20,R22
	MOVW R22,R24
	MOVW R24,R20
	MOV  R20,R0
	MOV  R0,R1
	MOV  R1,R20
	POP  R20
	RET

__UADD12:
	ADD  R30,R26
	ADC  R31,R27
	ADC  R22,R24
	RET

__NEGMAN1:
	COM  R30
	COM  R31
	COM  R22
	SUBI R30,-1
	SBCI R31,-1
	SBCI R22,-1
	RET

__SUBF12:
	PUSH R21
	RCALL __UNPACK
	CPI  R25,0x80
	BREQ __ADDF129
	LDI  R21,0x80
	EOR  R1,R21

	RJMP __ADDF120

__ADDF12:
	PUSH R21
	RCALL __UNPACK
	CPI  R25,0x80
	BREQ __ADDF129

__ADDF120:
	CPI  R23,0x80
	BREQ __ADDF128
__ADDF121:
	MOV  R21,R23
	SUB  R21,R25
	BRVS __ADDF1211
	BRPL __ADDF122
	RCALL __SWAPACC
	RJMP __ADDF121
__ADDF122:
	CPI  R21,24
	BRLO __ADDF123
	CLR  R26
	CLR  R27
	CLR  R24
__ADDF123:
	CPI  R21,8
	BRLO __ADDF124
	MOV  R26,R27
	MOV  R27,R24
	CLR  R24
	SUBI R21,8
	RJMP __ADDF123
__ADDF124:
	TST  R21
	BREQ __ADDF126
__ADDF125:
	LSR  R24
	ROR  R27
	ROR  R26
	DEC  R21
	BRNE __ADDF125
__ADDF126:
	MOV  R21,R0
	EOR  R21,R1
	BRMI __ADDF127
	RCALL __UADD12
	BRCC __ADDF129
	ROR  R22
	ROR  R31
	ROR  R30
	INC  R23
	BRVC __ADDF129
	RJMP __MAXRES
__ADDF128:
	RCALL __SWAPACC
__ADDF129:
	RCALL __REPACK
	POP  R21
	RET
__ADDF1211:
	BRCC __ADDF128
	RJMP __ADDF129
__ADDF127:
	SUB  R30,R26
	SBC  R31,R27
	SBC  R22,R24
	BREQ __ZERORES
	BRCC __ADDF1210
	COM  R0
	RCALL __NEGMAN1
__ADDF1210:
	TST  R22
	BRMI __ADDF129
	LSL  R30
	ROL  R31
	ROL  R22
	DEC  R23
	BRVC __ADDF1210

__ZERORES:
	CLR  R30
	CLR  R31
	CLR  R22
	CLR  R23
	POP  R21
	RET

__MINRES:
	SER  R30
	SER  R31
	LDI  R22,0x7F
	SER  R23
	POP  R21
	RET

__MAXRES:
	SER  R30
	SER  R31
	LDI  R22,0x7F
	LDI  R23,0x7F
	POP  R21
	RET

__MULF12:
	PUSH R21
	RCALL __UNPACK
	CPI  R23,0x80
	BREQ __ZERORES
	CPI  R25,0x80
	BREQ __ZERORES
	EOR  R0,R1
	SEC
	ADC  R23,R25
	BRVC __MULF124
	BRLT __ZERORES
__MULF125:
	TST  R0
	BRMI __MINRES
	RJMP __MAXRES
__MULF124:
	PUSH R0
	PUSH R17
	PUSH R18
	PUSH R19
	PUSH R20
	CLR  R17
	CLR  R18
	CLR  R25
	MUL  R22,R24
	MOVW R20,R0
	MUL  R24,R31
	MOV  R19,R0
	ADD  R20,R1
	ADC  R21,R25
	MUL  R22,R27
	ADD  R19,R0
	ADC  R20,R1
	ADC  R21,R25
	MUL  R24,R30
	RCALL __MULF126
	MUL  R27,R31
	RCALL __MULF126
	MUL  R22,R26
	RCALL __MULF126
	MUL  R27,R30
	RCALL __MULF127
	MUL  R26,R31
	RCALL __MULF127
	MUL  R26,R30
	ADD  R17,R1
	ADC  R18,R25
	ADC  R19,R25
	ADC  R20,R25
	ADC  R21,R25
	MOV  R30,R19
	MOV  R31,R20
	MOV  R22,R21
	MOV  R21,R18
	POP  R20
	POP  R19
	POP  R18
	POP  R17
	POP  R0
	TST  R22
	BRMI __MULF122
	LSL  R21
	ROL  R30
	ROL  R31
	ROL  R22
	RJMP __MULF123
__MULF122:
	INC  R23
	BRVS __MULF125
__MULF123:
	RCALL __ROUND_REPACK
	POP  R21
	RET

__MULF127:
	ADD  R17,R0
	ADC  R18,R1
	ADC  R19,R25
	RJMP __MULF128
__MULF126:
	ADD  R18,R0
	ADC  R19,R1
__MULF128:
	ADC  R20,R25
	ADC  R21,R25
	RET

__DIVF21:
	PUSH R21
	RCALL __UNPACK
	CPI  R23,0x80
	BRNE __DIVF210
	TST  R1
__DIVF211:
	BRPL __DIVF219
	RJMP __MINRES
__DIVF219:
	RJMP __MAXRES
__DIVF210:
	CPI  R25,0x80
	BRNE __DIVF218
__DIVF217:
	RJMP __ZERORES
__DIVF218:
	EOR  R0,R1
	SEC
	SBC  R25,R23
	BRVC __DIVF216
	BRLT __DIVF217
	TST  R0
	RJMP __DIVF211
__DIVF216:
	MOV  R23,R25
	PUSH R17
	PUSH R18
	PUSH R19
	PUSH R20
	CLR  R1
	CLR  R17
	CLR  R18
	CLR  R19
	CLR  R20
	CLR  R21
	LDI  R25,32
__DIVF212:
	CP   R26,R30
	CPC  R27,R31
	CPC  R24,R22
	CPC  R20,R17
	BRLO __DIVF213
	SUB  R26,R30
	SBC  R27,R31
	SBC  R24,R22
	SBC  R20,R17
	SEC
	RJMP __DIVF214
__DIVF213:
	CLC
__DIVF214:
	ROL  R21
	ROL  R18
	ROL  R19
	ROL  R1
	ROL  R26
	ROL  R27
	ROL  R24
	ROL  R20
	DEC  R25
	BRNE __DIVF212
	MOVW R30,R18
	MOV  R22,R1
	POP  R20
	POP  R19
	POP  R18
	POP  R17
	TST  R22
	BRMI __DIVF215
	LSL  R21
	ROL  R30
	ROL  R31
	ROL  R22
	DEC  R23
	BRVS __DIVF217
__DIVF215:
	RCALL __ROUND_REPACK
	POP  R21
	RET

__CMPF12:
	TST  R25
	BRMI __CMPF120
	TST  R23
	BRMI __CMPF121
	CP   R25,R23
	BRLO __CMPF122
	BRNE __CMPF121
	CP   R26,R30
	CPC  R27,R31
	CPC  R24,R22
	BRLO __CMPF122
	BREQ __CMPF123
__CMPF121:
	CLZ
	CLC
	RET
__CMPF122:
	CLZ
	SEC
	RET
__CMPF123:
	SEZ
	CLC
	RET
__CMPF120:
	TST  R23
	BRPL __CMPF122
	CP   R25,R23
	BRLO __CMPF121
	BRNE __CMPF122
	CP   R30,R26
	CPC  R31,R27
	CPC  R22,R24
	BRLO __CMPF122
	BREQ __CMPF123
	RJMP __CMPF121

__SUBD12:
	SUB  R30,R26
	SBC  R31,R27
	SBC  R22,R24
	SBC  R23,R25
	RET

__ANEGD1:
	COM  R31
	COM  R22
	COM  R23
	NEG  R30
	SBCI R31,-1
	SBCI R22,-1
	SBCI R23,-1
	RET

__LSLD1:
	LSL  R30
	ROL  R31
	ROL  R22
	ROL  R23
	RET

__CBD1:
	MOV  R31,R30
	ADD  R31,R31
	SBC  R31,R31
	MOV  R22,R31
	MOV  R23,R31
	RET

__CWD1:
	MOV  R22,R31
	ADD  R22,R22
	SBC  R22,R22
	MOV  R23,R22
	RET

__MULD12U:
	MUL  R23,R26
	MOV  R23,R0
	MUL  R22,R27
	ADD  R23,R0
	MUL  R31,R24
	ADD  R23,R0
	MUL  R30,R25
	ADD  R23,R0
	MUL  R22,R26
	MOV  R22,R0
	ADD  R23,R1
	MUL  R31,R27
	ADD  R22,R0
	ADC  R23,R1
	MUL  R30,R24
	ADD  R22,R0
	ADC  R23,R1
	CLR  R24
	MUL  R31,R26
	MOV  R31,R0
	ADD  R22,R1
	ADC  R23,R24
	MUL  R30,R27
	ADD  R31,R0
	ADC  R22,R1
	ADC  R23,R24
	MUL  R30,R26
	MOV  R30,R0
	ADD  R31,R1
	ADC  R22,R24
	ADC  R23,R24
	RET

__PUTDP1:
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	RET

__GETD1S0:
	LD   R30,Y
	LDD  R31,Y+1
	LDD  R22,Y+2
	LDD  R23,Y+3
	RET

__GETD2S0:
	LD   R26,Y
	LDD  R27,Y+1
	LDD  R24,Y+2
	LDD  R25,Y+3
	RET

__PUTD1S0:
	ST   Y,R30
	STD  Y+1,R31
	STD  Y+2,R22
	STD  Y+3,R23
	RET

__PUTPARD1:
	ST   -Y,R23
	ST   -Y,R22
	ST   -Y,R31
	ST   -Y,R30
	RET

__PUTPARD2:
	ST   -Y,R25
	ST   -Y,R24
	ST   -Y,R27
	ST   -Y,R26
	RET

__CDF2U:
	SET
	RJMP __CDF2U0
__CDF2:
	CLT
__CDF2U0:
	RCALL __SWAPD12
	RCALL __CDF1U0

__SWAPD12:
	MOV  R1,R24
	MOV  R24,R22
	MOV  R22,R1
	MOV  R1,R25
	MOV  R25,R23
	MOV  R23,R1

__SWAPW12:
	MOV  R1,R27
	MOV  R27,R31
	MOV  R31,R1

__SWAPB12:
	MOV  R1,R26
	MOV  R26,R30
	MOV  R30,R1
	RET

__CPD10:
	SBIW R30,0
	SBCI R22,0
	SBCI R23,0
	RET

__CPD02:
	CLR  R0
	CP   R0,R26
	CPC  R0,R27
	CPC  R0,R24
	CPC  R0,R25
	RET

__CPD12:
	CP   R30,R26
	CPC  R31,R27
	CPC  R22,R24
	CPC  R23,R25
	RET

;END OF CODE MARKER
__END_OF_CODE:

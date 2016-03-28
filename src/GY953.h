/*
Copyright 2016 .s.u.m.o.t.o.y.
Version 0.01, early aplha stage!
*/

#ifndef gy953_h_
#define gy953_h_

#include <Arduino.h>
#include <SPI.h>

#define _GY953_MAGACC		0x01
#define _GY953_MAGGYR		0x02
#define _GY953_MAGMAG		0x04
#define _GY953_MAGRPY		0x08
#define _GY953_MAG_Q4		0x10
#define _GY953_SETREG		0x41
#define _GY953_CALREG		0x42
#define _GY953_INTREG		0xC1
#define _GY953_UPFREQ_50	0x73
#define _GY953_UPFREQ_100	0x74
#define _GY953_UPFREQ_200	0x75
#define _GY953_CAL_ACC		0x04
#define _GY953_CAL_MAG		0x08
#define _GY953_CAL_CLR		0x80

class GY953
{
public:
	GY953(const uint8_t cs_pin,const uint8_t int_pin);
	void	begin(void);
	bool 	update(uint8_t mode=0);
	void	getRPY(int *data);//Roll,Pitch,Yaw
	void 	getACC(int *data);//x,y,z,0
	void 	getGYR(int *data);//x,y,z,0
	void 	getMAG(int *data);//x,y,z,0
	void 	getQ(int *data);//x,y,z
	void 	setRefreshRate(uint8_t freq); //50,100,200
	void 	calibration(uint8_t mode);
	void	readAccuracy(byte *data);
	void 	readRange(byte *data);
	void 	sensorEnabled(uint8_t mode);
protected:
	void _disableCS(void);
	void _enableCS(void);
	void _startSPItransaction(void);
	void _endSPItransaction(void);
	
	volatile byte _stateReg;
private:
	uint8_t _CS;
	uint8_t _INTp;
	void 		 writeRegister(byte reg, byte *data, int len);
	void 		 readRegister(byte reg, byte *data, int len);
	void 		 enableInt(void);
	static void  isr(void);
	void 		 setMode(uint8_t mode);
	int			 _rpy[3] = {0};
	int			 _raw[4] = {0};
	uint8_t		_currentMode;
	uint8_t		_refreshRate;
};
#endif
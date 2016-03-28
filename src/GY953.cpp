#include "GY953.h"

static volatile bool _attention = false;
//static byte _gy953reg_a = 0x08;
//static byte _gy953reg_b = 0x11;
static byte _gyBuffer[41] = {0};


GY953::GY953(const uint8_t cs_pin,const uint8_t int_pin)
{
	_CS = cs_pin;
	_INTp = int_pin;
	_attention = false;
	_stateReg = 0;
	_currentMode = 0;
}

void GY953::begin(void)
{
	memset(_rpy,0,3);
	memset(_raw,0,4);
	pinMode(_CS,OUTPUT);
	SPI.begin();
	#if !defined(SPI_HAS_TRANSACTION)
		SPI.setBitOrder(MSBFIRST);
		SPI.setClockDivider(SPI_CLOCK_DIV64);
		SPI.setDataMode(SPI_MODE3);
	#endif
	//_disableCS();
	digitalWrite(_CS, HIGH);
	delay(10);
	//TODO: Check this
	setRefreshRate(100);
	//setMode(1);
	enableInt();
	while (!_attention); delay(1);
	//setRefreshRate(100);
	//setMode(1);
}

void GY953::_disableCS(void)
{
	#if defined(__MK20DX128__) || defined(__MK20DX256__) || defined(__MKL26Z64__)
		digitalWriteFast(_CS, HIGH);
	#else
		digitalWrite(_CS, HIGH);
	#endif
}

void GY953::_enableCS(void)
{
	#if defined(__MK20DX128__) || defined(__MK20DX256__) || defined(__MKL26Z64__)
		digitalWriteFast(_CS, LOW);
	#else
		digitalWrite(_CS, LOW);
	#endif
}

void GY953::_startSPItransaction(void)
{
	#if defined(SPI_HAS_TRANSACTION)
		SPI.beginTransaction(SPISettings(400000, MSBFIRST, SPI_MODE3));
	#else
		cli();//protect from interrupts
	#endif
}

void GY953::_endSPItransaction(void)
{
	#if defined(SPI_HAS_TRANSACTION)
		SPI.endTransaction();
	#else
		sei();//enable interrupts
	#endif
}

void GY953::writeRegister(byte reg, byte *data, int len) 
{
	byte i = 0;
	_startSPItransaction();
	_enableCS();
	SPI.transfer(reg); //Send register location
	while (i < len){
		SPI.transfer(data[i++]);
	}
	_disableCS();
	_endSPItransaction();
}



void GY953::readRegister(byte reg, byte *data, int len) 
{
	byte i = 0;
	_startSPItransaction();
	_enableCS();
	SPI.transfer(reg);
	while (i < len){
		data[i++] = SPI.transfer(0);
	}
	_disableCS();
	_endSPItransaction();
}

void GY953::isr(void)
{
	if (!_attention) _attention = true;
}

void GY953::enableInt(void)
{
	pinMode(_INTp,INPUT);
	_attention = false;
#ifdef digitalPinToInterrupt
	uint8_t theINT = digitalPinToInterrupt(_INTp);
	if (theINT != NOT_AN_INTERRUPT) {
		SPI.usingInterrupt(theINT);
		attachInterrupt(theINT, isr, RISING);
	}
#else
		attachInterrupt(0,isr,RISING);
#endif
	
}

bool GY953::update(uint8_t mode)
{
	uint8_t sum = 0;
	if (_attention){
		//TODO:disable other INT here
		readRegister(_GY953_INTREG, _gyBuffer, 41);//fill buffer
		setMode(mode);
		if (_gyBuffer[34] == 0x0D){
			if (_stateReg & _GY953_MAGRPY){
				for (uint8_t i = 0; i < 6; i++) sum += _gyBuffer[20 + i];
				if (sum == _gyBuffer[39]){
					_rpy[0] = (_gyBuffer[20] << 8) | _gyBuffer[21];//(float)_roll/100
					_rpy[1] = (_gyBuffer[22] << 8) | _gyBuffer[23];//(float)_pitch/100
					_rpy[2] = (_gyBuffer[24] << 8) | _gyBuffer[25];//(float)_yaw/100
				}
			}//end _GY953_MAGRPY
			if (_stateReg & _GY953_MAGACC){
				_raw[0] = (_gyBuffer[2] << 8) | _gyBuffer[3];//X
				_raw[1] = (_gyBuffer[4] << 8) | _gyBuffer[5];//Y
				_raw[2] = (_gyBuffer[6] << 8) | _gyBuffer[7];//Z
				_raw[3] = 0;//na
			}
			if (_stateReg & _GY953_MAGGYR){
				_raw[0] = (_gyBuffer[8] << 8) | _gyBuffer[9];//X
				_raw[1] = (_gyBuffer[10] << 8) | _gyBuffer[11];//Y
				_raw[2] = (_gyBuffer[12] << 8) | _gyBuffer[13];//Z
				_raw[3] = 0;//na
			}
			if (_stateReg & _GY953_MAGMAG){
				_raw[0] = (_gyBuffer[14] << 8) | _gyBuffer[15];//X
				_raw[1] = (_gyBuffer[16] << 8) | _gyBuffer[17];//Y
				_raw[2] = (_gyBuffer[18] << 8) | _gyBuffer[19];//Z
				_raw[3] = 0;//na
			}
			if (_stateReg & _GY953_MAG_Q4){
				_raw[0] = (_gyBuffer[26] << 8) | _gyBuffer[27];
				_raw[1] = (_gyBuffer[28] << 8) | _gyBuffer[29];
				_raw[2] = (_gyBuffer[30] << 8) | _gyBuffer[31];
				_raw[3] = (_gyBuffer[32] << 8) | _gyBuffer[33];
			}
		}
		_attention = false;
		//TODO:enable other INT here
		return 1;
	} else {
		return 0;
	}
}

void GY953::sensorEnabled(uint8_t mode)
{
	byte tempdata;
	switch(mode){
		case 0://all
			tempdata = 0x73 | 0x08;
			writeRegister(_GY953_SETREG, &tempdata, 1);
		break;
		case 1://close acc
			tempdata = 0x63 | 0x08;
			writeRegister(_GY953_SETREG, &tempdata, 1);
		break;
		case 2://close gyro
			tempdata = 0x53 | 0x08;
			writeRegister(_GY953_SETREG, &tempdata, 1);
		break;
		case 3://close magn
			tempdata = 0x33 | 0x08;
			writeRegister(_GY953_SETREG, &tempdata, 1);
		break;
		default:
			return;
		break;
	}
}

void GY953::setRefreshRate(uint8_t freq)
{
	byte tempdata;
	if (freq <= 50){
		tempdata = _GY953_UPFREQ_50 | 0x08;//_gy953reg_a;
		writeRegister(_GY953_SETREG, &tempdata, 1);
		_refreshRate = 0;
	} else if (freq > 50 && freq <= 100){
		tempdata = _GY953_UPFREQ_100 | 0x08;//_gy953reg_a;
		writeRegister(_GY953_SETREG, &tempdata, 1);
		_refreshRate = 1;
	} else {
		tempdata = _GY953_UPFREQ_200 | 0x08;//_gy953reg_a;
		writeRegister(_GY953_SETREG, &tempdata, 1);
		_refreshRate = 2;
	}
}

void GY953::calibration(uint8_t mode)
{
	//byte tempdata;
	if (mode < 1){			//0:Clear Internal Saved Calibration Data (CAUTION)
		/*
		tempdata = _GY953_CAL_CLR | _gy953reg_b;
		writeRegister(_GY953_CALREG, &tempdata, 1);
		*/
	} else if (mode > 1){	//2:Calibrate Compass
		/*
		tempdata = _GY953_CAL_MAG | _gy953reg_b;
		writeRegister(_GY953_CALREG, &tempdata, 1);
		*/
	} else {				//1:Calibrate Accellerometer/Gyroscope
		/*
		tempdata = _GY953_CAL_ACC | _gy953reg_b;
		writeRegister(_GY953_CALREG, &tempdata, 1);
		*/
	}
}

void GY953::setMode(uint8_t mode)
{
	if (mode != _currentMode){
	//byte data;
	switch(mode){
		case 0:
			//do nothing
		break;
		case 1://enable/disable R-P-Y out
			_stateReg ^= _GY953_MAGRPY;
		break;
		case 2://enable/disable ACC Raw data
			_stateReg ^= _GY953_MAGACC;
		break;
		case 3://enable/disable Gyroscope Raw data
			_stateReg ^= _GY953_MAGGYR;
		break;
		case 4://enable/disable Magnetometer Raw data
			_stateReg ^= _GY953_MAGMAG;
		break;
		case 5://enable/disable Q Raw data
			_stateReg ^= _GY953_MAG_Q4;
		break;
		default:
			mode = 0;
		break;
	}
	_currentMode = mode;
	}
}



void GY953::getRPY(int *data)
{
	//should we set ON RPY?
	if (_currentMode != 1) setMode(1);
	memcpy(data,_rpy,sizeof(_rpy));
}

void GY953::getACC(int *data)
{
	if (_currentMode != 2) setMode(2);
	memcpy(data,_raw,sizeof(_raw));
}

void GY953::getGYR(int *data)
{
	if (_currentMode != 3) setMode(3);
	memcpy(data,_raw,sizeof(_raw));
}

void GY953::getMAG(int *data)
{
	if (_currentMode != 4) setMode(4);
	memcpy(data,_raw,sizeof(_raw));
}

void GY953::getQ(int *data)
{
	if (_currentMode != 5) setMode(5);
	memcpy(data,_raw,sizeof(_raw));
}

void GY953::readAccuracy(byte *data)
{
	data[0] = ((_gyBuffer[35] >> 4) & 0x03);//MAG_ACC Accuracy
	data[1] = ((_gyBuffer[35] >> 2) & 0x03);//MAG_GYR Accuracy
	data[2] = (_gyBuffer[35] & 0x03);//MAG_MAGN Accuracy
	data[3] = (_gyBuffer[0] & 0x07);//output frequency. If 0:not working!
	//_stateReg = 0x00;
}

void GY953::readRange(byte *data)
{
	data[0] = ((_gyBuffer[34] >> 4) & 0x03);//MAG_ACC Range
	data[1] = ((_gyBuffer[34] >> 2) & 0x03);//MAG_GYR Range
	data[2] = (_gyBuffer[34] & 0x03);//MAG_MAGN Range
	//_stateReg = 0x00;
}

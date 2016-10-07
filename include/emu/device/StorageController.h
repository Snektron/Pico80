#ifndef INCLUDE_EMU_DEVICE_STORAGECONTROLLER_H_
#define INCLUDE_EMU_DEVICE_STORAGECONTROLLER_H_

#include "z80e/z80e.h"

class StorageController : public Z80e::BasicIODevice
{
public:
	bool is_locked()
	{
		return read() == 0;
	}
};

#endif /* INCLUDE_EMU_DEVICE_STORAGECONTROLLER_H_ */

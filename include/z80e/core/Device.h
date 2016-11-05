#ifndef INCLUDE_Z80E_CORE_DEVICE_H_
#define INCLUDE_Z80E_CORE_DEVICE_H_

#include <cstdint>
#include <mutex>

namespace Z80e
{
	class IODevice
	{
	public:
		static uint8_t io_read(void *devptr)
		{
			IODevice *device = (IODevice*) devptr;
			if (device)
				return device->read();
			return 0;
		}

		static void io_write(void *devptr, uint8_t value)
		{
			IODevice *device = (IODevice*) devptr;
			if (device)
				device->write(value);
		}

		virtual uint8_t read() = 0;
		virtual void write(uint8_t value) = 0;
		virtual ~IODevice() = default;
	};

	class BasicIODevice : public IODevice
	{
	private:
		uint8_t portvalue;
	public:
		virtual uint8_t read()
		{
			return portvalue;
		}

		virtual void write(uint8_t value)
		{
			portvalue = value;
		}
	};

	class ReadonlyIODevice : public BasicIODevice
	{
	public:
		virtual uint8_t read()
		{
			return BasicIODevice::read();
		}

		virtual void write(uint8_t value) {}

		void set_value(uint8_t value)
		{
			BasicIODevice::write(value);
		}
	};
}

#endif /* INCLUDE_Z80E_DEVICE_H_ */

#ifndef INCLUDE_Z80E_CORE_INTERRUPT_H_
#define INCLUDE_Z80E_CORE_INTERRUPT_H_

namespace Z80e
{
	class InterruptController
	{
	public:
		static int interrupting(void *interrupt)
		{
			InterruptController *ictrl = (InterruptController*) interrupt;
			if (ictrl)
				return ictrl->is_interrupting();
			return 0;
		}

		virtual bool is_interrupting() = 0;
		virtual ~InterruptController() = default;
	};
}

#endif /* INCLUDE_Z80E_INTERRUPT_H_ */

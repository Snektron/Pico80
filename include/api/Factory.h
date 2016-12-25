#ifndef FACTORY_H
#define FACTORY_H

template <typename T>
class Factory
{
public:
	virtual T* create()
	{
		return new T();
	}
};

#endif // FACTORY_H

#ifndef PICOQMLENGINE_H
#define PICOQMLENGINE_H

#include <QQmlApplicationEngine>

class QmlPicoEngine: public QQmlApplicationEngine
{
public:
	template <typename T>
	T findChild(QString name)
	{
		foreach (QObject* rootObject, rootObjects())
		{
			T object = rootObject->findChild<T>(name);
			if (object)
				return object;
		}

		return Q_NULLPTR;
	}
};

#endif // PICOQMLENGINE_H

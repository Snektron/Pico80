#ifndef IPICOQMLENGINE_H
#define IPICOQMLENGINE_H

#include <QQmlApplicationEngine>
#include <QUrl>
#include <QQuickItem>
#include <QString>

class IPicoQmlEngine: public QQmlApplicationEngine
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

	virtual QQuickItem* loadComponent(QUrl file) = 0;
	virtual void setDisplay(QQuickItem *display) = 0;
	virtual void addSidebarView(QQuickItem *item, QString id) = 0;
	virtual ~IPicoQmlEngine() = default;
};

#endif // IPICOQMLENGINE_H

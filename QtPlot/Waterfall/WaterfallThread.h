#pragma once

#include <QThread>
#include <QMutex>
#include <qreadwritelock.h>


//forward declaration
class WaterfallContent;
class QElapsedTimer;


class WaterfallThread : public QThread
{
	Q_OBJECT

public:
	explicit WaterfallThread(QObject* object = nullptr);
	~WaterfallThread() override;

protected:
	void run() override;

public:
	void quit();
	void stopAndClear();

	void setAutoUpdate(bool bAuto);
	bool getAutoUpdate();

	void setFPSLimit(quint32 fps = 0);
	quint32 getFPSLimit();

	void addData(double* data, int size);
	void setData(double* data, int width, int height);
	void setWaterfallContent(WaterfallContent* content);

signals:
	void update();
	void copyingCompleted();

private:
	WaterfallContent* content;

	QMutex			appendMutex;
	QMutex			copyMutex;

	QReadWriteLock	locker;

	qint64			frameDeltaTime;
	QElapsedTimer*	frameTimer;

	double* data;
	int		size;

	int setWidth;
	int setHeight;

	bool	bIsQuit;
	bool	bIsAuto;
	bool	bIsAppend;
};


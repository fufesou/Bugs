#ifndef CTESTTHREAD_H
#define CTESTTHREAD_H

#include  <QThread>

class CTestThread : public QThread
{
    Q_OBJECT

public:
    explicit CTestThread(QObject* vParent = 0);

protected:
    void run() Q_DECL_OVERRIDE;
};

#endif // CTESTTHREAD_H

#ifndef CTESTWIDGET_H
#define CTESTWIDGET_H

#include  <QTimer>
#include  <QWidget>
#include  <QPushButton>
#include  <QProgressBar>

class CTestThread;

class CTestWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CTestWidget(QWidget *parent = 0);

private slots:
    void beginProgress(void);
    void updateProgressBar(void);

private:
    void initWidget(void);

private:
    int m_elapsedCount;
    QTimer* m_pTimer;
    CTestThread* m_pThread;
    QPushButton* m_pbtnClick;
    QProgressBar* m_ppbProgress;
};

#endif // CTESTWIDGET_H

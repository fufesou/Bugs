#include    "testwidget.h"
#include    "testthread.h"

#include  <QVBoxLayout>

CTestWidget::CTestWidget(QWidget *parent) 
: QWidget(parent)
, m_pTimer(new QTimer(this))
, m_pThread(new CTestThread(this))
, m_pbtnClick(new QPushButton(tr("click"), this))
, m_ppbProgress(new QProgressBar(this))
{
    initWidget();
    setGeometry(200, 200, 500, 400);
}

void CTestWidget::initWidget()
{
    QVBoxLayout* pMainLayout = new QVBoxLayout(this);
    setLayout(pMainLayout);

    m_ppbProgress->setRange(0, 300 * 100);

    pMainLayout->addWidget(m_ppbProgress);
    pMainLayout->addWidget(m_pbtnClick);

    bool isBeginConOK = connect(m_pbtnClick, SIGNAL(clicked(bool)), this, SLOT(beginProgress()));
    Q_ASSERT(isBeginConOK);

    bool isUpdateConOK = connect(m_pTimer, SIGNAL(timeout()), this, SLOT(updateProgressBar()));
    Q_ASSERT(isUpdateConOK);
}

void CTestWidget::beginProgress()
{
    m_elapsedCount = 0;
    m_pTimer->setInterval(300);
    m_pTimer->start();
    m_pThread->start();
}

void CTestWidget::updateProgressBar()
{
    ++ m_elapsedCount;

    if (m_elapsedCount >= 30)
    {
        m_pTimer->stop();
    }
    else
    {
        m_ppbProgress->setValue(300 * m_elapsedCount);
    }
}

#include  "testthread.h"
#include  <QDebug>
#include  <unistd.h>
#include  <setjmp.h>
#include  <signal.h>

static sigjmp_buf s_jmpbuf;
static void s_sig_alarm(int signo);
static void s_process(void);

static void (*s_signal(int signo, void (*sigfunc)(int)))(int);

CTestThread::CTestThread(QObject* vParent)
    : QThread(vParent)
{

}

void CTestThread::run()
{
    qDebug() << "begin process.";
    s_process();
    qDebug() << "end process.";
}

void s_process()
{
    int count = 0;
    void (*prehandler)(int) = s_signal(SIGALRM, s_sig_alarm);

doagain:
    alarm(5);

    if (sigsetjmp(s_jmpbuf, 1) != 0)
    {
        qDebug() << "in s_process - after sigsetjmp " << count;
        if (count++ > 5)
        {
            (void)s_signal(SIGALRM, prehandler);
            qDebug() << "return";
            return;
        }
        else
        {
            goto doagain;
        }
    }
    while (1);
    alarm(0);
}

static void s_sig_alarm(int signo)
{
    (void)signo;
    qDebug() << "in s_sig_alarm - before siglongjmp";
    siglongjmp(s_jmpbuf, 1);
    qDebug() << "in s_sig_alarm - after siglongjmp";
}

static void (*s_signal(int signo, void (*sigfunc)(int)))(int)
{
	struct sigaction	act, oact;

    act.sa_handler = sigfunc;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if (signo == SIGALRM) {
#ifdef	SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;	/* SunOS 4.x */
#endif
	} else {
#ifdef	SA_RESTART
		act.sa_flags |= SA_RESTART;		/* SVR4, 44BSD */
#endif
	}
	if (sigaction(signo, &act, &oact) < 0)
		return(SIG_ERR);
	return(oact.sa_handler);
}


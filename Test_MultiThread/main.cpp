#include <QApplication>
#include    "testwidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    CTestWidget widget;
    widget.show();

    return app.exec();
}

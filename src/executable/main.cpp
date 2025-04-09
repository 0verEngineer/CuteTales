
#include "app/ui/MainWindow.h"
#include "app/init.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    init(&a);
    MainWindow w;
    w.setMinimumSize(400, 220);
    w.resize(800, 600);
    w.show();
    return QApplication::exec();
}

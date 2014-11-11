#include "opencl.hxx"

#include <QtCore/QVector>

#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>

using namespace ww;

int main(int argc, char ** argv)
{
    QApplication app(argc, argv);

    auto platforms = cl::getPlatforms<QVector>();

    QListWidget mainWindow;
    for (auto & platform : platforms)
        mainWindow.addItem(platform.info<cl::Platform::Name>());
    mainWindow.show();

    return app.exec();
}

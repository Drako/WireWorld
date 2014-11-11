#include "opencl.hxx"

#include <vector>

#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>

using namespace ww;

int main(int argc, char ** argv)
{
    QApplication app(argc, argv);

    auto platforms = cl::get_platforms<std::vector>();

    QListWidget mainWindow;
    for (auto & platform : platforms)
        mainWindow.addItem(platform.info<cl::Platform::Name>());
    mainWindow.show();

    return app.exec();
}

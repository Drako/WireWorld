#include "settings.hxx"

#include <QtWidgets/QApplication>

using namespace ww;

int main(int argc, char ** argv)
{
    QApplication app(argc, argv);
    app.setApplicationName(QStringLiteral("WireWorld"));
    app.setApplicationDisplayName(QStringLiteral("WireWorld"));

    Settings settings;
    if (settings.exec() == QDialog::Accepted)
    {
        // open main window here
        return app.exec();
    }
    return 0;
}

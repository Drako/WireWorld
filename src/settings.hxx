#ifndef WIREWORLD_SETTINGS_HXX
#define WIREWORLD_SETTINGS_HXX

#include <QtWidgets/QDialog>

namespace ww {
    class Settings
        : public QDialog
    {
        Q_OBJECT

    public:
        Settings(QWidget * parent = nullptr);
        virtual ~Settings();
    };
}

#endif // WIREWORLD_SETTINGS_HXX

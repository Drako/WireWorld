#ifndef WIREWORLD_SETTINGS_HXX
#define WIREWORLD_SETTINGS_HXX

#include <QtWidgets/QDialog>

class QComboBox;

namespace ww {
    class Settings
        : public QDialog
    {
        Q_OBJECT

    public:
        Settings(QWidget * parent = nullptr);
        virtual ~Settings();

    private slots:
        void loadDevices();
        void loadDeviceInfo();

    private:
        QComboBox * m_platform;
        QComboBox * m_device;
    };
}

#endif // WIREWORLD_SETTINGS_HXX

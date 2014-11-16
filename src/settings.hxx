#ifndef WIREWORLD_SETTINGS_HXX
#define WIREWORLD_SETTINGS_HXX

#include <QtCore/QAbstractItemModel>

#include <QtWidgets/QDialog>

class QComboBox;

namespace ww {
    namespace cl {
        class Device;
    }

    class DeviceInfoModel;

    class Settings
        : public QDialog
    {
        Q_OBJECT

    public:
        Settings(QWidget * parent = nullptr);
        virtual ~Settings();

        cl::Device selectedDevice() const;

    private slots:
        void loadDevices();
        void loadDeviceInfo();

    private:
        QComboBox * m_platform;
        QComboBox * m_device;

        DeviceInfoModel * m_infoModel;
    };

    class DeviceInfoModel
        : public QAbstractItemModel
    {
        Q_OBJECT

    public:
        DeviceInfoModel(QObject * parent = nullptr);
        virtual ~DeviceInfoModel();
    };
}

#endif // WIREWORLD_SETTINGS_HXX

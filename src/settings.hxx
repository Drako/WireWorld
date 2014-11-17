#ifndef WIREWORLD_SETTINGS_HXX
#define WIREWORLD_SETTINGS_HXX

#include <QtCore/QAbstractItemModel>
#include <QtCore/QScopedPointer>

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

        virtual int columnCount(QModelIndex const & parent = QModelIndex()) const;
        virtual QVariant data(QModelIndex const & index, int role = Qt::DisplayRole) const;
        virtual Qt::ItemFlags flags(QModelIndex const & index) const;
        virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
        virtual QModelIndex index(int row, int column, QModelIndex const & parent = QModelIndex()) const;
        virtual QModelIndex parent(QModelIndex const & index) const;
        virtual int rowCount(QModelIndex const & parent = QModelIndex()) const;

        void setDevice(cl::Device const & device);

    private:
        QScopedPointer<cl::Device> m_device;
    };
}

#endif // WIREWORLD_SETTINGS_HXX

#include "opencl.hxx"
#include "settings.hxx"

#include <QtCore/QVector>

#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

namespace ww {
    /********************************************************
     *                        Settings                      *
     ********************************************************/
    Settings::Settings(QWidget * parent /* = nullptr */)
        : QDialog(parent)
    {
        setWindowTitle(tr("WireWorld - Settings"));
        setFixedSize(400, 600);

        auto mainLayout = new QVBoxLayout();
        setLayout(mainLayout);

        auto selectionGroup = new QGroupBox(tr("OpenCL - Settings"), this);
        mainLayout->addWidget(selectionGroup);

        auto selectionLayout = new QFormLayout();
        selectionGroup->setLayout(selectionLayout);

        m_platform = new QComboBox(selectionGroup);
        m_platform->addItem(QStringLiteral(""));
        for (auto & platform : cl::getPlatforms<QVector>())
            m_platform->addItem(platform.info<cl::Platform::Name>(), QVariant::fromValue(platform));
        selectionLayout->addRow(tr("Platform: "), m_platform);
        connect(m_platform, SIGNAL(currentIndexChanged(int)), this, SLOT(loadDevices()));

        m_device = new QComboBox(selectionGroup);
        m_device->setEnabled(false);
        selectionLayout->addRow(tr("Device: "), m_device);
        connect(m_device, SIGNAL(currentIndexChanged(int)), this, SLOT(loadDeviceInfo()));

        auto infoGroup = new QGroupBox(tr("OpenCL - Device Info"), this);
        mainLayout->addWidget(infoGroup);

        auto infoLayout = new QVBoxLayout();
        infoGroup->setLayout(infoLayout);

        auto infoTable = new QTableView(infoGroup);
        infoLayout->addWidget(infoTable);

        //m_infoModel = new DeviceInfoModel();
        //infoTable->setModel(m_infoModel);
    }

    Settings::~Settings()
    {
    }

    cl::Device Settings::selectedDevice() const
    {
        return m_device->currentData().value<cl::Device>();
    }

    void Settings::loadDevices()
    {
        m_device->clear();
        m_device->addItem(QStringLiteral(""));
        
        auto platform = m_platform->currentData().value<cl::Platform>();
        for (auto & device : platform.getDevices<QVector>())
            m_device->addItem(device.info<cl::Device::Name>(), QVariant::fromValue(device));

        m_device->setEnabled(m_device->count() > 1);
    }

    void Settings::loadDeviceInfo()
    {
    }

    /********************************************************
     *                   DeviceInfoModel                    *
     ********************************************************/
    DeviceInfoModel::DeviceInfoModel(QObject * parent /* = nullptr */)
        : QAbstractItemModel(parent)
    {
    }

    DeviceInfoModel::~DeviceInfoModel()
    {
    }
}

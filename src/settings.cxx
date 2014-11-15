#include "opencl.hxx"
#include "settings.hxx"

#include <QtCore/QVector>

#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QVBoxLayout>

namespace ww {
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

        m_platform = new QComboBox(this);
        m_platform->addItem(QStringLiteral(""));
        for (auto & platform : cl::getPlatforms<QVector>())
            m_platform->addItem(platform.info<cl::Platform::Name>(), QVariant::fromValue(platform));
        selectionLayout->addRow(tr("Platform: "), m_platform);
        connect(m_platform, SIGNAL(currentIndexChanged(int)), this, SLOT(loadDevices()));

        m_device = new QComboBox(this);
        m_device->setEnabled(false);
        selectionLayout->addRow(tr("Device: "), m_device);
        connect(m_device, SIGNAL(currentIndexChanged(int)), this, SLOT(loadDeviceInfo()));
    }

    Settings::~Settings()
    {
    }

    void Settings::loadDevices()
    {
        m_device->clear();
        m_device->addItem(QStringLiteral(""));

        if (m_platform->currentIndex() > 0)
        {
            auto platform = m_platform->currentData().value<cl::Platform>();
            for (auto & device : platform.getDevices<QVector>())
                m_device->addItem(device.info<cl::Device::Name>(), QVariant::fromValue(device));
        }

        m_device->setEnabled(m_device->count() > 1);
    }

    void Settings::loadDeviceInfo()
    {
    }
}

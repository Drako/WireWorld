#include "opencl.hxx"
#include "settings.hxx"

#include <QtCore/QVector>

#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

namespace {
    template <typename>
    struct array_size;

    template <typename T, std::size_t N>
    struct array_size<T[N]>
    {
        static std::size_t const value = N;
    };
}

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
        infoTable->verticalHeader()->hide();
        auto hheader = infoTable->horizontalHeader();
        hheader->setMinimumSectionSize(140);
        hheader->setStretchLastSection(true);
        hheader->update();
        hheader->setSectionResizeMode(QHeaderView::Fixed);

        m_infoModel = new DeviceInfoModel();
        infoTable->setModel(m_infoModel);
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
        m_infoModel->setDevice(m_device->currentData().value<cl::Device>());
    }

    /********************************************************
     *                   DeviceInfoModel                    *
     ********************************************************/
    DeviceInfoModel::DeviceInfoModel(QObject * parent /* = nullptr */)
        : QAbstractItemModel(parent)
        , m_device(new cl::Device())
    {
    }

    DeviceInfoModel::~DeviceInfoModel()
    {
    }

    int DeviceInfoModel::columnCount(QModelIndex const & parent /* = QModelIndex() */) const
    {
        if (parent.isValid())
            return 0;
        return 2;
    }

    QVariant DeviceInfoModel::data(QModelIndex const & index, int role /* = Qt::DisplayRole */) const
    {
        if (!index.isValid() || role != Qt::DisplayRole)
            return QVariant();

        // attribute
        if (index.column() == 0)
        {
            static QString const attributes[] = {
                tr("Profile"),
                tr("Type"),
                tr("Vendor"),
                tr("Version"),
                tr("Driver Version")
            };

            if (index.row() < 0 || index.row() >= ::array_size<decltype(attributes)>::value)
                return QVariant();

            return attributes[index.row()];
        }
        // value
        else if (index.column() == 1)
        {
            if (!m_device)
                return QStringLiteral("");

            switch (index.row())
            {
                case 0: return m_device->info<cl::Device::Profile>(); break;
                case 1:
                {
                    auto type = m_device->info<cl::Device::Type>();
                    switch (type)
                    {
                        case CL_DEVICE_TYPE_CPU: return tr("Central Processing Unit"); break;
                        case CL_DEVICE_TYPE_GPU: return tr("Graphics Processing Unit"); break;
                        case CL_DEVICE_TYPE_ACCELERATOR: return tr("OpenCL Accelerator"); break;
                    }
                } break;
                case 2: return m_device->info<cl::Device::Vendor>(); break;
                case 3: return m_device->info<cl::Device::Version>(); break;
                case 4: return m_device->info<cl::Device::DriverVersion>(); break;
            }
        }

        return QVariant();
    }

    Qt::ItemFlags DeviceInfoModel::flags(QModelIndex const & index) const
    {
        Q_UNUSED(index);
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }

    QVariant DeviceInfoModel::headerData(int section, Qt::Orientation orientation, int role /* = Qt::DisplayRole */) const
    {
        if (orientation == Qt::Horizontal)
        {
            if (role == Qt::DisplayRole)
            {
                static QString const headers[] = {
                    tr("Attribute"),
                    tr("Value")
                };

                if (section >= 0 && section <= 1)
                    return headers[section];
            }
        }

        return QVariant();
    }

    QModelIndex DeviceInfoModel::index(int row, int column, QModelIndex const & parent /* = QModelIndex() */) const
    {
        if (parent.isValid() || column < 0 || column > 1 || row < 0 || row >= rowCount())
            return QModelIndex();

        return createIndex(row, column, nullptr);
    }

    QModelIndex DeviceInfoModel::parent(QModelIndex const & index) const
    {
        Q_UNUSED(index);
        return QModelIndex();
    }

    int DeviceInfoModel::rowCount(QModelIndex const & parent) const
    {
        if (parent.isValid())
            return 0;

        return 5;
    }

    void DeviceInfoModel::setDevice(cl::Device const & device)
    {
        beginResetModel();
        m_device.reset(device ? new cl::Device(device) : nullptr);
        endResetModel();
    }
}

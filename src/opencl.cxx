#include "opencl.hxx"
#include "benchmark.hxx"

namespace ww { namespace cl {
    /************************************************************
     *                        Device                            *
     ************************************************************/
    Device::Device(cl_device_id id /* = nullptr */)
        : m_id(id)
    {
    }
    
    Device::Device(Device const & source)
        : m_id(source.m_id)
    {
    }
    
    Device::~Device()
    {
    }
    
    Device & Device::operator = (Device const & source)
    {
        m_id = source.m_id;
        return *this;
    }
    
    bool Device::operator ! () const
    {
        return m_id == nullptr;
    }

#ifdef CXX11_FEATURE_EXPLICITCAST
    Device::operator bool() const
    {
        return m_id != nullptr;
    }
#else
    Device::operator safe_bool() const
    {
        return (safe_bool)(m_id != nullptr);
    }
#endif

    cl_device_id Device::id() const
    {
        return m_id;
    }
    
    QByteArray Device::getInfo(Device::DeviceInfo info) const
    {
        // WW_BENCHMARK(ww::cl::Device::getInfo);

        std::size_t size;
        if (clGetDeviceInfo(m_id, info, 0, nullptr, &size) != CL_SUCCESS)
            return QByteArray();
        
        QByteArray buffer(size, 0);
        if (clGetDeviceInfo(m_id, info, size, buffer.data(), nullptr) != CL_SUCCESS)
            return QByteArray();

        return buffer;
    }
    
    /************************************************************
     *                       Platform                           *
     ************************************************************/
    Platform::Platform(cl_platform_id id /* = nullptr */)
        : m_id(id)
    {
    }

    Platform::Platform(Platform const & source)
        : m_id(source.m_id)
    {
    }

    Platform::~Platform()
    {
    }

    Platform & Platform::operator = (Platform const & source)
    {
        m_id = source.m_id;
        return *this;
    }

    bool Platform::operator ! () const
    {
        return m_id == nullptr;
    }

#ifdef CXX11_FEATURE_EXPLICITCAST
    Platform::operator bool() const
    {
        return m_id != nullptr;
    }
#else
    Platform::operator safe_bool() const
    {
        return (safe_bool)(m_id != nullptr);
    }
#endif

    cl_platform_id Platform::id() const
    {
        return m_id;
    }

    QString Platform::getInfo(Platform::PlatformInfo info) const
    {
        // WW_BENCHMARK(ww::cl::Platform::getInfo);

        std::size_t size;
        if (clGetPlatformInfo(m_id, info, 0, nullptr, &size) != CL_SUCCESS)
            return QString();
        
        QVector<char> buffer(size);
        if (clGetPlatformInfo(m_id, info, size, buffer.data(), nullptr) != CL_SUCCESS)
            return QString();
        
        return QString::fromLocal8Bit(buffer.data());
    }
    
    QVector<cl_device_id> Platform::getDeviceIDs() const
    {
        // WW_BENCHMARK(ww::cl::Platform::getDeviceIDs);

        QVector<cl_device_id> deviceIDs;
        
        cl_uint count;
        if (clGetDeviceIDs(m_id, CL_DEVICE_TYPE_ALL, 0, nullptr, &count) != CL_SUCCESS)
            return deviceIDs;
        
        deviceIDs.resize(count);
        if (clGetDeviceIDs(m_id, CL_DEVICE_TYPE_ALL, count, deviceIDs.data(), nullptr) != CL_SUCCESS)
            deviceIDs.clear();
        
        return deviceIDs;
    }
    
    namespace detail
    {
        QVector<cl_platform_id> getPlatformIDs()
        {
            // WW_BENCHMARK(ww::cl::detail::getPlatformIDs);

            QVector<cl_platform_id> platformIDs;
            
            cl_uint count;
            if (clGetPlatformIDs(0, nullptr, &count) != CL_SUCCESS)
                return platformIDs;
            
            platformIDs.resize(count);
            if (clGetPlatformIDs(count, platformIDs.data(), nullptr) != CL_SUCCESS)
                platformIDs.clear();
            
            return platformIDs;
        }
    }
}}

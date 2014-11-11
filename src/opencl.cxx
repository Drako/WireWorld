#include "opencl.hxx"

#include <utility>

namespace ww { namespace cl {
    Platform::Platform(cl_platform_id id /* = nullptr */)
        : m_id(id)
    {
    }

    Platform::Platform(Platform const & source)
        : m_id(source.m_id)
    {
    }

    Platform::Platform(Platform && source)
        : m_id(std::move(source.m_id))
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

    Platform & Platform::operator = (Platform && source)
    {
        m_id = std::move(source.m_id);
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

    QString Platform::getInfo(Platform::PlatformInfo info) const
    {
        std::size_t size;
        if (clGetPlatformInfo(m_id, info, 0, nullptr, &size) != CL_SUCCESS)
            return QString();
        
        QVector<char> buffer(size);
        if (clGetPlatformInfo(m_id, info, size, buffer.data(), nullptr) != CL_SUCCESS)
            return QString();
        
        return QString::fromLocal8Bit(buffer.data());
    }
    
    namespace detail
    {
        QVector<cl_platform_id> getPlatformIDs()
        {
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

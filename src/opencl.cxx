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
}}

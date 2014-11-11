#ifndef WIREWORLD_OPENCL_HXX
#define WIREWORLD_OPENCL_HXX

#include "cxx11_features.hxx"

#include <algorithm>
#include <iterator>
#include <memory>
#include <vector>

#include <CL/cl.h>

#include <QtCore/QString>

namespace ww { namespace cl {
    class Platform
    {
    public:
        Platform(cl_platform_id id = nullptr);
        Platform(Platform const & source);
        Platform(Platform && source);
        ~Platform();

        Platform & operator = (Platform const & source);
        Platform & operator = (Platform && source);

        bool operator ! () const;
#ifdef CXX11_FEATURE_EXPLICITCAST
        explicit operator bool() const;
#else
    private:
        struct safe_bool_helper;
        typedef safe_bool_helper * safe_bool;

    public:
        operator safe_bool() const;
#endif

        enum PlatformInfo
        {
            Profile = CL_PLATFORM_PROFILE,
            Version = CL_PLATFORM_VERSION,
            Name = CL_PLATFORM_NAME,
            Vendor = CL_PLATFORM_VENDOR,
            Extensions = CL_PLATFORM_EXTENSIONS
        };

        template <PlatformInfo Info>
        QString info() const
        {
            std::size_t size;
            if (clGetPlatformInfo(m_id, Info, 0, nullptr, &size) != CL_SUCCESS)
                return QString();

            std::vector<char> buffer(size);
            if (clGetPlatformInfo(m_id, Info, size, buffer.data(), nullptr) != CL_SUCCESS)
                return QString();

            return QString::fromUtf8(buffer.data());
        }

    private:
        cl_platform_id m_id;
    };

#ifdef CXX11_FEATURE_VARIADIC
    template <template <typename...> class Container>
#else
    template <template <typename, typename> class Container>
#endif
    Container<Platform, std::allocator<Platform>> get_platforms()
    {
        Container<Platform, std::allocator<Platform>> platforms;

        cl_uint count;
        if (clGetPlatformIDs(0, nullptr, &count) != CL_SUCCESS)
            return platforms;

        std::vector<cl_platform_id> platform_ids(count);
        if (clGetPlatformIDs(count, platform_ids.data(), nullptr) != CL_SUCCESS)
            return platforms;

        platforms.resize(count);
        std::copy(std::begin(platform_ids), std::end(platform_ids), std::begin(platforms));
        return platforms;
    }
}}

#endif // WIREWORLD_OPENCL_HXX

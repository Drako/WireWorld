#ifndef WIREWORLD_OPENCL_HXX
#define WIREWORLD_OPENCL_HXX

#include "cxx11_features.hxx"

#include <algorithm>
#include <iterator>
#include <memory>

#include <CL/cl.h>

#include <QtCore/QString>
#include <QtCore/QVector>

namespace ww { namespace cl {
    class Device
    {
    };
    
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
        inline QString info() const
        {
            return getInfo(Info);
        }

    private:
        cl_platform_id m_id;
        
        QString getInfo(PlatformInfo info) const;
    };
    
    namespace detail
    {
        QVector<cl_platform_id> getPlatformIDs();
    }

    template <template <typename> class Container>
    Container<Platform> getPlatforms()
    {
        Container<Platform> platforms;
        
        auto platformIDs = detail::getPlatformIDs();

        platforms.resize(platformIDs.size());
        std::copy(std::begin(platformIDs), std::end(platformIDs), std::begin(platforms));
        return platforms;
    }
}}

#endif // WIREWORLD_OPENCL_HXX

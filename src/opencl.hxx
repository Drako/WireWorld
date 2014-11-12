#ifndef WIREWORLD_OPENCL_HXX
#define WIREWORLD_OPENCL_HXX

#include "cxx11_features.hxx"

#include <algorithm>
#include <iterator>
#include <memory>

#include <CL/cl.h>

#ifndef CL_DEVICE_HALF_FP_CONFIG
#define CL_DEVICE_HALF_FP_CONFIG 0x1033
#endif

#include <QtCore/QByteArray>
#include <QtCore/QString>
#include <QtCore/QVector>

namespace ww { namespace cl {
    class Platform;
    
    /************************************************************
     *                        Device                            *
     ************************************************************/
    class Device
    {
    public:
        Device(cl_device_id id = nullptr);
        Device(Device const & source);
        ~Device();
        
        Device & operator = (Device const & source);
        
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
        
        cl_device_id id() const;
        
        enum DeviceInfo
        {
            AddressBits = CL_DEVICE_ADDRESS_BITS,
            Available = CL_DEVICE_AVAILABLE,
            CompilerAvailable = CL_DEVICE_COMPILER_AVAILABLE,
            DoubleFpConfig = CL_DEVICE_DOUBLE_FP_CONFIG,
            EndianLittle = CL_DEVICE_ENDIAN_LITTLE,
            ErrorCorrectionSupport = CL_DEVICE_ERROR_CORRECTION_SUPPORT,
            ExecutionCapabilities = CL_DEVICE_EXECUTION_CAPABILITIES,
            Extensions = CL_DEVICE_EXTENSIONS,
            GlobalMemCacheSize = CL_DEVICE_GLOBAL_MEM_CACHE_SIZE,
            GlobalMemCacheType = CL_DEVICE_GLOBAL_MEM_CACHE_TYPE,
            GlobalMemCachelineSize = CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE,
            GlobalMemSize = CL_DEVICE_GLOBAL_MEM_SIZE,
            HalfFpConfig = CL_DEVICE_HALF_FP_CONFIG,
            ImageSupport = CL_DEVICE_IMAGE_SUPPORT,
            Image2dMaxHeight = CL_DEVICE_IMAGE2D_MAX_HEIGHT,
            Image2dMaxWidth = CL_DEVICE_IMAGE2D_MAX_WIDTH,
            Image3dMaxDepth = CL_DEVICE_IMAGE3D_MAX_DEPTH,
            Image3dMaxHeight = CL_DEVICE_IMAGE3D_MAX_HEIGHT,
            Image3dMaxWidth = CL_DEVICE_IMAGE3D_MAX_WIDTH,
            LocalMemSize = CL_DEVICE_LOCAL_MEM_SIZE,
            LocalMemType = CL_DEVICE_LOCAL_MEM_TYPE,
            MaxClockFrequency = CL_DEVICE_MAX_CLOCK_FREQUENCY,
            MaxComputeUnits = CL_DEVICE_MAX_COMPUTE_UNITS,
            MaxConstantArgs = CL_DEVICE_MAX_CONSTANT_ARGS,
            MaxConstantBufferSize = CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE,
            MaxMemAllocSize = CL_DEVICE_MAX_MEM_ALLOC_SIZE,
            MaxParameterSize = CL_DEVICE_MAX_PARAMETER_SIZE,
            MaxReadImageArgs = CL_DEVICE_MAX_READ_IMAGE_ARGS,
            MaxSamplers = CL_DEVICE_MAX_SAMPLERS,
            MaxWorkGroupSize = CL_DEVICE_MAX_WORK_GROUP_SIZE,
            MaxWorkItemDimensions = CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,
            MaxWorkItemSizes = CL_DEVICE_MAX_WORK_ITEM_SIZES,
            MaxWriteImageArgs = CL_DEVICE_MAX_WRITE_IMAGE_ARGS,
            MemBaseAddrAlign = CL_DEVICE_MEM_BASE_ADDR_ALIGN,
            MinDataTypeAlignSize = CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE,
            Name = CL_DEVICE_NAME,
            Platform = CL_DEVICE_PLATFORM,
            PreferredVectorWidthChar = CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR,
            PreferredVectorWidthShort = CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT,
            PreferredVectorWidthInt = CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT,
            PreferredVectorWidthLong = CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG,
            PreferredVectorWidthFloat = CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT,
            PreferredVectorWidthDouble = CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE,
            Profile = CL_DEVICE_PROFILE,
            ProfilingTimerResolution = CL_DEVICE_PROFILING_TIMER_RESOLUTION,
            QueueProperties = CL_DEVICE_QUEUE_PROPERTIES,
            SingleFpConfig = CL_DEVICE_SINGLE_FP_CONFIG,
            Type = CL_DEVICE_TYPE,
            Vendor = CL_DEVICE_VENDOR,
            VendorId = CL_DEVICE_VENDOR_ID,
            Version = CL_DEVICE_VERSION,
            DriverVersion = CL_DRIVER_VERSION
        };
        
        template <DeviceInfo Info>
        struct DeviceInfoTraits;
    
        template <DeviceInfo Info>
        inline auto info() const -> typename DeviceInfoTraits<Info>::type
        {
            return info<typename DeviceInfoTraits<Info>::type>(Info);
        }
        
        // for simple types
        template <typename ReturnType>
        inline ReturnType info(DeviceInfo which) const
        {
            QByteArray result = getInfo(which);
            if (result.isEmpty())
                return ReturnType();
            
            return *(ReturnType *)(result.data());
        }
        
    private:
        cl_device_id m_id;
        
        QByteArray getInfo(DeviceInfo info) const;
    };
    
#define DIT(Info, Type) template <> struct Device::DeviceInfoTraits<Device::Info> { typedef Type type; };
    DIT(AddressBits, cl_uint)
    DIT(Available, cl_bool)
    DIT(CompilerAvailable, cl_bool)
    DIT(DoubleFpConfig, cl_device_fp_config)
    DIT(EndianLittle, cl_bool)
    DIT(ErrorCorrectionSupport, cl_bool)
    DIT(ExecutionCapabilities, cl_device_exec_capabilities)
    DIT(Extensions, QString)
    DIT(GlobalMemCacheSize, cl_ulong)
    DIT(GlobalMemCacheType, cl_device_mem_cache_type)
    DIT(GlobalMemCachelineSize, cl_uint)
    DIT(GlobalMemSize, cl_ulong)
    DIT(HalfFpConfig, cl_device_fp_config)
    DIT(ImageSupport, cl_bool)
    DIT(Image2dMaxHeight, std::size_t)
    DIT(Image2dMaxWidth, std::size_t)
    DIT(Image3dMaxDepth, std::size_t)
    DIT(Image3dMaxHeight, std::size_t)
    DIT(Image3dMaxWidth, std::size_t)
    DIT(LocalMemSize, cl_ulong)
    DIT(LocalMemType, cl_device_local_mem_type)
    DIT(MaxClockFrequency, cl_uint)
    DIT(MaxComputeUnits, cl_uint)
    DIT(MaxConstantArgs, cl_uint)
    DIT(MaxConstantBufferSize, cl_ulong)
    DIT(MaxMemAllocSize, cl_ulong)
    DIT(MaxParameterSize, std::size_t)
    DIT(MaxReadImageArgs, cl_uint)
    DIT(MaxSamplers, cl_uint)
    DIT(MaxWorkGroupSize, std::size_t)
    DIT(MaxWorkItemDimensions, cl_uint)
    DIT(MaxWorkItemSizes, cl_uint)
    DIT(MaxWriteImageArgs, cl_uint)
    DIT(MemBaseAddrAlign, cl_uint)
    DIT(MinDataTypeAlignSize, cl_uint)
    DIT(Name, QString)
    DIT(Platform, class Platform)
    DIT(PreferredVectorWidthChar, cl_uint)
    DIT(PreferredVectorWidthShort, cl_uint)
    DIT(PreferredVectorWidthInt, cl_uint)
    DIT(PreferredVectorWidthLong, cl_uint)
    DIT(PreferredVectorWidthFloat, cl_uint)
    DIT(PreferredVectorWidthDouble, cl_uint)
    DIT(Profile, QString)
    DIT(ProfilingTimerResolution, std::size_t)
    DIT(QueueProperties, cl_command_queue_properties)
    DIT(SingleFpConfig, cl_device_fp_config)
    DIT(Type, cl_device_type)
    DIT(Vendor, QString)
    DIT(VendorId, cl_uint)
    DIT(Version, QString)
    DIT(DriverVersion, QString)
#undef DIT
    
    template <>
    inline QString Device::info<QString>(Device::DeviceInfo which) const
    {
        return QString::fromLocal8Bit(getInfo(which));
    }
    
    /************************************************************
     *                       Platform                           *
     ************************************************************/
    class Platform
    {
    public:
        Platform(cl_platform_id id = nullptr);
        Platform(Platform const & source);
        ~Platform();

        Platform & operator = (Platform const & source);

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
        
        cl_platform_id id() const;

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
        
        template <template <typename> class Container>
        Container<Device> getDevices() const
        {
            Container<Device> devices;
            
            auto deviceIDs = getDeviceIDs();

            devices.resize(deviceIDs.size());
            std::copy(std::begin(deviceIDs), std::end(deviceIDs), std::begin(devices));
            return devices;
        }

    private:
        cl_platform_id m_id;
        
        QString getInfo(PlatformInfo info) const;
        QVector<cl_device_id> getDeviceIDs() const;
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

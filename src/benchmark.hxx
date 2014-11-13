#ifndef WIREWORLD_BENCHMARK_HXX
#define WIREWORLD_BENCHMARK_HXX

#include "cxx11_features.hxx"

#include <chrono>

#include <QtCore/QString>

namespace ww {
    class Benchmark
    {
    public:
        typedef std::chrono::nanoseconds::rep DurationType;

        Benchmark(QString const & what);
        ~Benchmark();
        
#ifdef CXX11_FEATURE_EXPLICITCAST
        explicit operator bool() const;
#else
    private:
        struct safe_bool_helper;
        typedef safe_bool_helper * safe_bool;

    public:
        operator safe_bool() const;
#endif

    private:
        QString m_what;
        std::chrono::high_resolution_clock::time_point m_start;
        mutable bool m_first;
    };
}

#define WW_BENCHMARK_(what) for (auto bm = ::ww::Benchmark(what); bm;)
#define WW_BENCHMARK(what) ::ww::Benchmark bm(#what)

#endif // WIREWORLD_BENCHMARK_HXX

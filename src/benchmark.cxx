#include "benchmark.hxx"

#include <QtCore/QDebug>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

namespace ww {
    Benchmark::Benchmark(QString const & what)
        : m_what(what)
        , m_start(std::chrono::high_resolution_clock::now())
        , m_first(true)
    {
    }

    Benchmark::~Benchmark()
    {
        static QMutex mutex;

        auto end = std::chrono::high_resolution_clock::now();

        QMutexLocker locker(&mutex);
        Q_UNUSED(locker);

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - m_start).count();
        qDebug() << "Benchmark:" << m_what << "took" << duration << "nanoseconds.";
    }

#ifdef CXX11_FEATURE_EXPLICITCAST
    Benchmark::operator bool() const
    {
        return m_first ? (m_first = false, true) : m_first;
    }
#else
    Benchmark::operator safe_bool() const
    {
        return m_first ? (m_first = false, (safe_bool)true) : (safe_bool)m_first;
    }
#endif
}

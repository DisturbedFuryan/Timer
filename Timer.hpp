#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>


//==================================================================================================
/** Just measures the time.
 *
 *  @author  Marcin Rainka
 *  @version  1.0
 */
class Timer {
public:
    enum TimeUnit { nanoseconds, microseconds, milliseconds, seconds, minutes, hours };

    Timer() : m_isRunning( false ), m_isStopped( false ) {}

    /** Starts time measuring. */
    void Start();

    /** Stops time measuring. */
    void Stop();

    /** Gets time in given unit (milliseconds by default).
     *  
     *  @param  timeUnit  desired unit of time
     *  @return  measured time
     */
    unsigned long long GetTime( TimeUnit timeUnit = milliseconds );

    /* Getters. */
    bool IsRunning() const { return m_isRunning; }
    bool IsStopped() const { return m_isStopped; }

private:
    /** Start point in time. */
    std::chrono::steady_clock::time_point m_startPoint;

    /** End point in time. */
    std::chrono::steady_clock::time_point m_endPoint;

    /** Additional point in time to preserve high precision. */
    std::chrono::steady_clock::time_point m_tempPoint;

    /* Flags keeping status. */
    bool m_isRunning, m_isStopped;
};
//==================================================================================================


inline void Timer::Start() {
    // We can not start timer again.
    if ( m_isRunning ) {
        return;
    }

    // Set flags.
    m_isRunning = true;
    m_isStopped = false;

    // Get a start point in time. It is important that we do it at the end of the method.
    // Instructions above take some time, we do not want to measure it.
    m_startPoint = std::chrono::steady_clock::now();
}


inline void Timer::Stop() {
    // Get a point in time just in case. It is important to do it here, at start, because...
    m_tempPoint = std::chrono::steady_clock::now();

    if ( m_isRunning ) {  // ...we do not want to measure this validation.
        m_endPoint = m_tempPoint;

        // Set flags.
        m_isRunning = false;
        m_isStopped = true;
    }
}


inline unsigned long long Timer::GetTime( TimeUnit timeUnit ) {
    if ( m_isStopped ) {
        switch ( timeUnit ) {
            case nanoseconds:
                return std::chrono::duration_cast< std::chrono::nanoseconds >
                       ( m_endPoint - m_startPoint ).count();

            case microseconds:
                return std::chrono::duration_cast< std::chrono::microseconds >
                       ( m_endPoint - m_startPoint ).count();

            case milliseconds:
                return std::chrono::duration_cast< std::chrono::milliseconds >
                       ( m_endPoint - m_startPoint ).count();
                
            case seconds:
                return std::chrono::duration_cast< std::chrono::seconds >
                       ( m_endPoint - m_startPoint ).count();

            case minutes:
                return std::chrono::duration_cast< std::chrono::minutes >
                       ( m_endPoint - m_startPoint ).count();

            case hours:
                return std::chrono::duration_cast< std::chrono::hours >
                       ( m_endPoint - m_startPoint ).count();
        }
    }

    return 0;
}


#endif

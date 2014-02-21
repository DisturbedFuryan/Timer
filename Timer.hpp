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
    /** Starts time measuring. */
    void Start();

    /** Stops time measuring. */
    void Stop() {
        m_endPoint = std::chrono::steady_clock::now();
        if ( m_isRunningAfterUnpause ) m_startPoint += ( m_unpausePoint - m_pausePoint );
        m_isRunning = false; m_isPaused = false; m_isRunningAfterUnpause = false;
    }

    /** Pauses time measuring. */
    void Pause() {
        m_tempPoint = std::chrono::steady_clock::now();
        if ( m_isRunningAfterUnpause )
            { m_startPoint += ( m_unpausePoint - m_pausePoint ); m_isRunningAfterUnpause = false; }
        if ( m_isRunning && !m_isPaused ) { m_pausePoint = m_tempPoint; m_isPaused = true; }
    }

    /** Unpauses time measuring. */
    void Unpause() {
        if ( !m_isPaused ) return;
        m_isPaused = false;
        m_isRunningAfterUnpause = true;
        m_unpausePoint = std::chrono::steady_clock::now();
    }

    /* Getters. */
    bool IsRunning() const { return m_isRunning; }
    bool IsPaused() const { return m_isPaused; }

private:
    /** Start point in time. */
    std::chrono::steady_clock::time_point m_startPoint;

    /** Pause point in time. */
    std::chrono::steady_clock::time_point m_pausePoint;

    /** Unpause point in time. */
    std::chrono::steady_clock::time_point m_unpausePoint;

    /** End point in time. */
    std::chrono::steady_clock::time_point m_endPoint;

    /** Additional point in time to preserve high precision in case of pausing. */
    std::chrono::steady_clock::time_point m_tempPoint;

    /* Flags keeping status. */
    bool m_isRunning, m_isPaused, m_isRunningAfterUnpause;
};
//==================================================================================================


inline void Timer::Start() {
    // Set flags.
    m_isRunning = true;
    m_isPaused = false;
    m_isRunningAfterUnpause = false;

    // Get a start point in time. It is important that we do it at the end of the method.
    // Instructions above take some time, we do not want to measure it.
    m_startPoint = std::chrono::steady_clock::now();
}


#endif

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
    void Stop();

    /** Pauses time measuring. */
    void Pause();

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


inline void Timer::Stop() {
    // Get an end point in time. It is important to do this at the beginning of the method.
    // We do not want measure instructions below.
    m_endPoint = std::chrono::steady_clock::now();

    // If the timer was paused and then unpaused,
    // we must shift forward a start point by the idle time.
    if ( m_isRunningAfterUnpause ) {
        m_startPoint += ( m_unpausePoint - m_pausePoint );
    }

    // Set flags.
    m_isRunning = false;
    m_isPaused = false;
    m_isRunningAfterUnpause = false;
}


inline void Timer::Pause() {
    m_tempPoint = std::chrono::steady_clock::now();

    // Hey! We want to get a pause point in time, why we use a temporary point
    // instead of the prepared variable m_pausePoint?!
    // First, we need to check if the timer can be paused, but that verification costs some time.
    // We do not want measure additional instructions,
    // so we remember a point in time at start just in case.
    
    // If the timer was paused and then unpaused,
    // we must shift forward a start point by the idle time.
    if ( m_isRunningAfterUnpause ) {
        m_startPoint += ( m_unpausePoint - m_pausePoint );
        m_isRunningAfterUnpause = false;
    }

    if ( m_isRunning && !m_isPaused ) {
        m_pausePoint = m_tempPoint;
        m_isPaused = true;
    }
}


#endif

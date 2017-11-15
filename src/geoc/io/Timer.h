#ifndef _GEOC_TIMER_H
#define _GEOC_TIMER_H

#include <geoc/geoc.h>


namespace geoc {


#ifdef WIN32
typedef __int64 timeReading;
#else
typedef double timeReading;
#endif


/** \ingroup IO */
//! A high resolution timer.
class Timer
{
    double secondsPerCount;
    double deltaTime;
    
    timeReading baseTime;
    timeReading pausedTime;
    timeReading stopTime;
    timeReading prevTime;
    timeReading curTime;
    
    bool stopped;
    
public:
    
    Timer();
    
    //! Updates the timer.
    /**
     * Computes and caches the time elapsed since the last tick.
     * Updates the timer accordingly.
     */
    void tick();
    
    //! Resets the timer.
    /**
     * Resets the timer's stop time and sets the base and current times to now.
     * getDeltaTime() returns 0 after reset().
    */
    void reset();
    
    //! Stops the timer.
    /**
     * The time the timer is stopped for is not taken into account in getTime().
     */
    void stop();
    
    //! Starts the timer.
    /**
     * 
     */
    void start();
    
    //! Returns the total running time in seconds.
    /**
     * The time the timer has been stopped for is not taken into account.
     */
    float getTime() const;
    
    //! Returns the time elapsed since the last tick in seconds.
    num getDeltaTime() const { return deltaTime; }
    
    //! Returns true if the timer is running, false otherwise.
    bool running() const { return !stopped; }
};


} // namespace geoc

#endif //_GEOC_TIMER_H

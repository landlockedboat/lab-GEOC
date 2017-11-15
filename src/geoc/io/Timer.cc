#include "Timer.h"

using namespace geoc;


#ifdef __APPLE__
#include <mach/mach_time.h>
#elif WIN32
#include <windows.h>
#else // Linux
#include <time.h>
const double NSEC_TO_SEC = 1.0f/1000000000.0f;
#endif


timeReading now();


Timer::Timer()
    : secondsPerCount(0.0), deltaTime(0.0), baseTime(0), pausedTime(0.0), curTime(0.0), stopped(true)
{
#ifdef WIN32
    __int64 countsPerSec;
    QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
    secondsPerCount = 1.0 / (double)countsPerSec;
#else
    /*timespec ts;
    clock_getres(CLOCK_REALTIME, &ts);
    secondsPerCount = (double)ts.tv_sec + ((double)ts.tv_nsec * NSEC_TO_SEC);*/
    secondsPerCount = 1.0f;
#endif
}

float Timer::getTime() const
{
    //If we are stopped, we do not count the time we have been stopped for.
    if (stopped)
    {
        return (float)((stopTime - baseTime) * secondsPerCount);
    }
    //Otherwise return the time elapsed since the start of the game without counting the time we have been paused for.
    else
    {
        return (float)((curTime - baseTime - pausedTime) * secondsPerCount);
    }
}

void Timer::tick()
{
    if (stopped)
    {
        deltaTime = 0.0;
        return;
    }
    
    //Get the time on this frame.
    curTime = now();
    
    //Time delta between the current frame and the previous.
    deltaTime = (curTime - prevTime) * secondsPerCount;
    
    //Update for next frame.
    prevTime = curTime;
    
    // Force nonnegative. The DXSDK's CDXUTTimer mentions that if the
    // processor goes into a power save mode or we get shuffled to
    // another processor, then mDeltaTime can be negative.
    if(deltaTime < 0.0)
    {
        deltaTime = 0.0;
    }
}

void Timer::reset()
{
    deltaTime  = 0;
    curTime    = now();
    baseTime   = curTime;
    pausedTime = 0;
    prevTime   = curTime;
    stopTime   = 0;
    stopped    = false;
}

void Timer::stop()
{
    //Don't do anything if we are already stopped.
    if (!stopped)
    {
        //Grab the stop time.
        stopTime = now();
        
        //Now we are stopped.
        stopped = true;
    }
}

void Timer::start()
{
    //Only start if we are stopped.
    if (stopped)
    {
        timeReading startTime = now();
        
        //Accumulate the paused time.
        pausedTime = pausedTime + startTime - stopTime;
        
        //Make the previous time valid.
        prevTime = startTime;
        
        //Now we are running.
        stopTime = 0;
        stopped = false;
    }
}

timeReading now()
{
    timeReading t;
    
    
#ifdef __APPLE__
    t = mach_absolute_time();
#elif WIN32
    QueryPerformanceCounter((LARGE_INTEGER*)&t);
#else
    timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    t = ts.tv_sec + ((double)ts.tv_nsec * NSEC_TO_SEC);
#endif
    
    return t;
}

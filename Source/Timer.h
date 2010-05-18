/*
 *  Timer.h
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/17/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#ifndef Timer_h
#define Timer_h

#include <mach/mach_time.h>

namespace PixelKit {
    class Timer {
    public:
        Timer()
        : m_startTime(0)
        , m_endTime(0)
        , m_latency(0.0)
        , m_lastTime(0.0)
        , m_bestTime(INFINITY)
        {
            mach_timebase_info_data_t info;
            kern_return_t err = mach_timebase_info( &info );
            if (err == 0)
                m_conversion = 1e-9 * (double) info.numer / (double) info.denom;
            
            for (int i = 0; i < 1024; i++) {
                start();
                stop();
            }
            m_latency = m_bestTime;
        }
        
        void start()
        {
            m_startTime = mach_absolute_time();
        }
        
        void stop()
        {
            m_endTime = mach_absolute_time();
            uint64_t difference = m_endTime - m_startTime;
            m_lastTime = m_conversion * (double)difference;
            if (m_lastTime < m_bestTime) {
                m_bestTime = m_lastTime;
            }
        }
        
        double bestTime() const { return m_bestTime; }
        double lastTime() const { return m_lastTime; }
        
    private:
        uint64_t m_startTime;
        uint64_t m_endTime;
        double m_latency;
        double m_lastTime;
        double m_bestTime;
        double m_conversion;
    };
}

#endif

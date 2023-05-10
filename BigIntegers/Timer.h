#pragma once
#include <stdlib.h>
#include <time.h>
#include <windows.h>
class CHighPerfTimer 
{
public:
      CHighPerfTimer();
      void Start(void);
      double GetSeconds() const;
      long long GetTickTime() const;
      long long GetTicksElapsed() const;
      unsigned long GetMilliseconds() const;
      unsigned long long GetMicroseconds() const;
      unsigned long GetMilliseconds(long long tickCount) const;
      long long GetFrequency() const;
private:
      LARGE_INTEGER m_StartTime;
      LARGE_INTEGER m_freq;
};
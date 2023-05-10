#include "Timer.h"
#include <stdio.h>
CHighPerfTimer::CHighPerfTimer() 
{
    m_StartTime.QuadPart = 0;
    BOOL bRet = QueryPerformanceFrequency(&m_freq);
    if (!bRet)
    {  // likely memory not alligned
        unsigned long err = GetLastError();
    }

}

void CHighPerfTimer::Start(void)
{
    QueryPerformanceCounter(&m_StartTime);
}

double CHighPerfTimer::GetSeconds() const
{
    LARGE_INTEGER endTime;
    QueryPerformanceCounter(&endTime);
    return (endTime.QuadPart - m_StartTime.QuadPart) / static_cast<double>(m_freq.QuadPart);
}

long long CHighPerfTimer::GetTickTime() const
{
  LARGE_INTEGER endtime;
  QueryPerformanceCounter(&endtime);
  return endtime.QuadPart;
}

long long CHighPerfTimer::GetTicksElapsed() const
{
    return GetTickTime() - m_StartTime.QuadPart;
}

unsigned long CHighPerfTimer::GetMilliseconds() const
{
    LARGE_INTEGER endTime;
    QueryPerformanceCounter(&endTime);
    return (unsigned long) ((endTime.QuadPart - m_StartTime.QuadPart)/(m_freq.QuadPart/1000));
}

unsigned long long CHighPerfTimer::GetMicroseconds() const
{
    LARGE_INTEGER endTime;
    QueryPerformanceCounter(&endTime);
    return ((endTime.QuadPart - m_StartTime.QuadPart)/(m_freq.QuadPart/1000000));
}

unsigned long CHighPerfTimer::GetMilliseconds(long long tickCount) const
{
    return (unsigned long) ((tickCount)/(m_freq.QuadPart/1000));
}

long long CHighPerfTimer::GetFrequency() const
{
    return m_freq.QuadPart;
}
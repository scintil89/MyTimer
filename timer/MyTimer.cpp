#include "stdafx.h"
#include "MyTimer.h"


MyTime::MyTime()
{
	hours = minutes = seconds = 0;
	millsec = 0.0f;
}

MyTime::MyTime(int h, int m, int s, float ms)
{
	hours = h;
	minutes = m;
	seconds = s;
	millsec = ms;
}

MyTime::~MyTime()
{
}

void MyTime::AddHr(int h)
{
	hours += h;
}

void MyTime::AddMin(int m)
{
	minutes += m;
	hours += minutes / 60;
	minutes %= 60;
}

void MyTime::AddSec(int s)
{
	seconds += s;
	minutes += seconds / 60;
	seconds %= 60;
}

void MyTime::MinusHr(int h)
{
	if (hours > 0)
		hours -= h;
}

void MyTime::MinusMin(int m)
{
	if (minutes > 0)
	{
		minutes -= m;
	}
	else
	{
		if (hours > 0)
		{
			MinusHr(1);
			minutes += 60;
			minutes -= m;
		}
		else
		{
			//TODO : print error
			return;
		}
	}
}

void MyTime::MinusSec(int s)
{
	if (seconds > 0)
	{
		seconds -= s;
	}
	else
	{
		if (minutes > 0 || hours > 0)
		{
			MinusMin(1);
			seconds += 60;
			seconds -= s;
		}
		else
		{
			//TODO : print error
			return;
		}
	}
}

void MyTime::Reset(int h, int m, int s)
{
	hours = h;
	minutes = m;
	seconds = s;
	millsec = 0.0f;

	isRun = false;
} 

void MyTime::Start()
{
	isRun = true;

	//myt 초기화
	Init();
}

void MyTime::Stop()
{
	isRun = false;
}

void MyTime::Process(float dt)
{
	if (hours <= 0 && minutes <= 0 && seconds <= 0)
	{
		isRun = false;
	}

	if (millsec <= 0.0f)
	{
		MinusSec(1);
		millsec += 1.0f;
	}

	millsec -= dt;
}

MyTime MyTime::Sum(const MyTime & t) const
{
	MyTime sum;
	sum.seconds = seconds + t.seconds;
	sum.minutes = minutes + t.minutes;
	sum.hours = hours + t.hours;

	return MyTime();
}

std::wstring MyTime::print() const
{
	std::wstring retstr;
	retstr += std::to_wstring(hours);
	retstr += L" : ";
	retstr += std::to_wstring(minutes);
	retstr += L" : ";
	retstr += std::to_wstring(seconds);
	
	return retstr;
}

MyTime MyTime::operator+(const MyTime & t) const
{
	MyTime sum;
	sum.seconds = seconds + t.seconds;
	sum.minutes = minutes + t.minutes;
	sum.hours = hours + t.hours;

	return sum;
}

MyTime MyTime::operator-(const MyTime & t) const
{
	MyTime sum;
	sum.seconds = seconds - t.seconds;
	sum.minutes = minutes - t.minutes;
	sum.hours = hours - t.hours;

	return sum;
}

void MyTime::Init()
{
	m_bUseQPF = false;
	m_fElapsedTime = 0.f;
	m_llQPFTicksPerSec = 0;
	m_llLastElapsedTime = 0;

	LARGE_INTEGER qwTicksPerSec, qwTime;

	m_bUseQPF = (bool)(QueryPerformanceFrequency(&qwTicksPerSec) != 0);

	if (!m_bUseQPF)	
		return;

	m_llQPFTicksPerSec = qwTicksPerSec.QuadPart;

	QueryPerformanceCounter(&qwTime);
	m_llLastElapsedTime = qwTime.QuadPart;
}

void MyTime::ProcessTime()
{
	if (!m_bUseQPF)
	{
		// 시스템이 QP를 지원안하는 경우.
		// 다른 시간 처리 필요
		return;
	}

	LARGE_INTEGER qwTime;
	QueryPerformanceCounter(&qwTime);

	m_fElapsedTime = (float)
		((double)(qwTime.QuadPart - m_llLastElapsedTime)
			/ (double)m_llQPFTicksPerSec);
	//(현재 시간 - 이전 시간) / 초당 틱 수

	m_llLastElapsedTime = qwTime.QuadPart; //이전 시간을 현재 시간으로 설정
}

#pragma once
#include <string>
class MyTime
{
public:
	MyTime();
	MyTime(int h, int m = 0, int s = 0, float ms = 0.f);
	~MyTime();
	
	void AddHr(int h);
	void AddMin(int m);
	void AddSec(int s);
	
	void MinusHr(int h);
	void MinusMin(int m);
	void MinusSec(int s);

	inline int GetHr() const { return hours; }
	inline int GetMin() const { return minutes; }
	inline int GetSec() const { return seconds; }

	void Reset(int h = 0, int m = 0, int s = 0);
	void Start();
	void Stop();
	void Process(float dt);

	MyTime Sum(const MyTime& t) const;
	
	std::wstring print() const;

	MyTime operator+(const MyTime& t) const;
	MyTime operator-(const MyTime& t) const;

	bool isRun = false;

private:
	int hours;
	int minutes;
	int seconds;
	float millsec;

//고해상도 타이머
//http://www.gpgstudy.com/gpgiki/%EC%8B%9C%EA%B0%84%20%EB%8B%A4%EB%A3%A8%EA%B8%B0

private:
	bool		m_bUseQPF;
	float		m_fElapsedTime;
	LONGLONG	m_llQPFTicksPerSec;
	LONGLONG	m_llLastElapsedTime;

public:
	inline float GetElapsedTime() const
	{
		return m_fElapsedTime;
	};

	void Init();
	void ProcessTime();
};


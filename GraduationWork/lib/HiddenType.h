#pragma once

#include <process.h>
#include <Windows.h>

struct CriticalSection
{
	CriticalSection() { InitializeCriticalSection(&cs); }
	~CriticalSection() { DeleteCriticalSection(&cs); }
	CRITICAL_SECTION cs;
};

struct LOCK
{
	LOCK(CriticalSection& _cs) :cs(_cs) { EnterCriticalSection(&cs.cs); }
	~LOCK() { LeaveCriticalSection(&cs.cs); }
	CriticalSection& cs;
};

struct Event
{
	Event() { handle = CreateEvent(nullptr, FALSE, TRUE, nullptr); }
	~Event() { CloseHandle(handle); }
	void Signal() { SetEvent(handle); }
	void NonSignal() { ResetEvent(handle); }
	HANDLE handle;
};

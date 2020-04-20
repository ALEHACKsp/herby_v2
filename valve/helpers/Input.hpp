#pragma once
#include <Windows.h>
#include <vector>
#include "Singleton.hpp"

using EventFn = bool(*)(HWND window, UINT message, WPARAM wparam, LPARAM lparam);

class Input : public Singleton< Input >
{
public:
	void Initialize();
	void Restore();

	void SetWindow(HWND window);
	HWND GetWindow() const;

	bool AddEvent(EventFn procedure);
	LRESULT ExecuteEventArray(HWND window, UINT message, WPARAM wparam, LPARAM lparam);

private:
	static BOOL WINAPI EnumProcedure(HWND window, LPARAM lparam);
	static LRESULT WINAPI MessageProcedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
private:
	HWND m_window = nullptr;
	WNDPROC m_procedure = nullptr;
	std::vector< EventFn > m_event_array = { };
};

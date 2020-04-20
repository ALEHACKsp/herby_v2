#include "Input.hpp"

void Input::Initialize()
{
	EnumWindows(&Input::EnumProcedure, GetCurrentProcessId());

	if (!m_window)
		return;

	m_procedure = reinterpret_cast<WNDPROC>(SetWindowLongW(m_window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Input::MessageProcedure)));

	if (!m_procedure)
		return;
}

void Input::Restore()
{
	if (m_procedure)
		SetWindowLongW(m_window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(m_procedure));

	m_window = nullptr;
	m_procedure = nullptr;
	m_event_array.clear();
}

void Input::SetWindow(HWND window)
{
	m_window = window;
}

HWND Input::GetWindow() const
{
	return m_window;
}

bool Input::AddEvent(EventFn procedure)
{
	if (!procedure)
		return false;

	if (!m_event_array.empty())
	{
		for (const auto& event : m_event_array)
		{
			if (event == procedure)
				return false;
		}
	}

	m_event_array.emplace_back(procedure);
	return true;
}

LRESULT Input::ExecuteEventArray(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
	auto code = false;

	if (!m_event_array.empty())
	{
		for (auto& event : m_event_array)
			code = event(window, message, wparam, lparam);
	}

	if (code)
		return FALSE;

	return (m_procedure ?
		CallWindowProcW(m_procedure, window, message, wparam, lparam) :
		DefWindowProcW(window, message, wparam, lparam));
}

BOOL WINAPI Input::EnumProcedure(HWND window, LPARAM lparam)
{
	auto& input = Input::Get();

	wchar_t class_name[256] = { };
	GetClassNameW(window, class_name, 256);

	if (!std::wcscmp(class_name, L"Valve001"))
	{
		input.SetWindow(window);
		return FALSE;
	}

	return TRUE;
}

LRESULT WINAPI Input::MessageProcedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
	auto& input = Input::Get();
	return input.ExecuteEventArray(window, message, wparam, lparam);
}
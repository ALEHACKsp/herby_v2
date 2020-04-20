#include "System.hpp"

System::~System()
{
	Restore();
}

void System::Initialize()
{
	auto& input = Input::Get();

	if (!input.AddEvent(&MessageProcedure))
		return;
}

void System::Restore()
{
	m_execute_state = ExecuteState::Quit;
}

bool System::Quit()
{
	return m_quit;
}

void System::Quit(bool value)
{
	m_quit = value;
	m_gui = !value;
}

bool System::Gui()
{
	return m_gui;
}

void System::Gui(bool value)
{
	m_gui = value;
}

ExecuteState System::GetExecuteState() const
{
	return m_execute_state;
}

void System::SetExecuteState(ExecuteState state)
{
	m_execute_state = state;
}

bool System::MessageProcedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
	auto& system = System::Get();

	auto execute = false;

	switch (message)
	{
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	{
		if (wparam == VK_F11)
		{
			execute = true;
			system.Quit(true);
		}
		else if (wparam == VK_INSERT)
		{
			execute = true;
			system.Gui(!system.Gui());
		}

		break;
	}
	}

	return execute;
}




#pragma once
#include "Input.hpp"
#include "Singleton.hpp"

enum ExecuteState
{
	Work,
	Question,
	Quit,
	Gui,
};

class System : public Singleton< System >
{
public:
	~System();

public:
	void Initialize();
	void Restore();

	ExecuteState GetExecuteState() const;
	void SetExecuteState(const ExecuteState execute_state);

public:
	bool Gui();
	void Gui(bool value);

	bool Quit();
	void Quit(bool value);

private:
	static bool MessageProcedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
private:
	bool m_quit = false;
	bool m_gui = false;
	ExecuteState m_execute_state = ExecuteState::Work;
};
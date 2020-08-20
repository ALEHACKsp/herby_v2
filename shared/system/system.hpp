#pragma once

#include "shared/include/auto.hpp"
#include "shared/include/win32.hpp"

#include "shared/detail/singleton.hpp"

namespace shared::win32
{

enum ExecuteState
{
	None,
	Work,
	Question,
	Quit,
	Gui,
	Load,
	Save
};

class System : public detail::Singleton< System >
{
public:
	~System();

public:
	bool Create();
	void Destroy();

	ExecuteState GetExecuteState() const;
	void SetExecuteState( const ExecuteState execute_state );

	const std::string& GetExecuteDirectory() const;
	void SetExecuteDirectory(const std::string& execute_directory);

public:
	bool Gui();
	void Gui( bool gui );

private:
	static bool MessageProcedure( HWND window, UINT message, WPARAM wparam, LPARAM lparam );

private:
	std::string m_execute_directory = { "auto" };
	ExecuteState m_execute_state = ExecuteState::Work;
};

}
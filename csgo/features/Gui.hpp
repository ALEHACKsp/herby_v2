#pragma once
#include "valve/auto.hpp"
#include "csgo/renderer/renderer.hpp"

enum gui_tab
{
	tab_aimbot,
	tab_triggerbot,
	tab_esp,
	tab_removal,
	tab_misc,
	tab_config,
};

struct gui_tab_t
{
	bool m_render = false;
	int m_index = -1;
	std::string m_name = { };

	gui_tab_t() = default;

	gui_tab_t(bool render, int index, const std::string& name)
		: m_render(render)
		, m_index(index)
		, m_name(name)
	{ }
};

class GUI : public Singleton<GUI>
{
public:
	void Initialize();

	void Render();
private:
	void CreateTab(const std::string& name, bool render = false);
private:
	void CreateStyle();
	std::vector< gui_tab_t > m_tab_array = { };
public:
	static bool MessageProcedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
};
#include "Gui.hpp"
#include "csgo/hooks/hooks.hpp"
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void GUI::Initialize()
{
	auto& input = Input::Get();
	input.AddEvent(&GUI::MessageProcedure);

	CreateStyle();
	CreateTab("aimbot", false);
	CreateTab("triggerbot", false);
	CreateTab("esp", false);
	CreateTab("removal", false);
	CreateTab("misc", false);
	CreateTab("config", false);
}

void GUI::Render()
{
	auto visible = System::Get().Gui();

	ImGui::GetIO().MouseDrawCursor = visible;

	if (!visible)
		return;

	auto render_style = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;

	auto frame_height = 0.f;

	D3DVIEWPORT9 viewport = { };
	if (SUCCEEDED(csgo::m_direct_device->GetViewport(&viewport)))
		frame_height = static_cast<float>(viewport.Height);

	auto frame_pos = ImVec2{ 0.f, 0.f };
	auto frame_size = ImVec2{ 156.f, frame_height };

	ImGui::SetNextWindowPos(frame_pos, ImGuiCond_Always);
	ImGui::SetNextWindowSize(frame_size, ImGuiCond_Always);

	auto frame_render_style = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse;
	
	if (ImGui::Begin("frame", nullptr, frame_render_style))
	{
		auto& gui_style = ImGui::GetStyle();

		auto tab_size = ImVec2{ 140.f, 30.f };
		auto tab_array_size = ((30.f * (static_cast<float>(m_tab_array.size()) + gui_style.ItemSpacing.y)) - gui_style.ItemSpacing.y) * 0.5f;

		auto frame_tab_center_y = frame_height * 0.5f;
		auto frame_tab_start_y = (frame_tab_center_y - tab_array_size) * 0.5f;

		ImGui::Dummy({ 0.f, frame_tab_start_y });
		ImGui::Dummy({ 0.f, 0.f });

		auto frame_name = "herby";
		auto frame_name_size = ImGui::CalcTextSize(frame_name, nullptr, true);

		ImGui::SameLine(0.f, (frame_size.x * 0.5f) - (frame_name_size.x * 0.5f) - gui_style.ItemSpacing.x);
		ImGui::Text(frame_name);
		ImGui::Dummy({ 0.f, frame_tab_start_y });

		ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, { 0.f, 0.5f });
		ImGui::PushStyleColor(ImGuiCol_Text, { 1.f, 1.f, 1.f, 1.f });
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.1f, 0.1f, 0.1f, 1.f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.12f, 0.12f, 0.12f, 1.f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.15f, 0.15f, 0.15f, 1.f });

		for (auto& tab : m_tab_array)
		{
			if (ImGui::Button(tab.m_name.c_str(), tab_size))
				tab.m_render = !tab.m_render;
		}

		ImGui::PopStyleColor(4);
		ImGui::PopStyleVar(1);
	}
	ImGui::End();
}

void GUI::CreateTab(const std::string& name, bool render /* = false*/)
{
	auto index = static_cast<int>(m_tab_array.size());
	m_tab_array.emplace_back(render, index, name);
}

void GUI::CreateStyle()
{
	auto& style = ImGui::GetStyle();
	auto& system = System::Get();

	style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.24f, 0.24f, 0.61f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.24f, 0.24f, 0.24f, 0.39f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.02f, 0.02f, 0.02f, 1.00f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.02f, 0.02f, 0.02f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(1.00f, 0.50f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(1.00f, 0.50f, 0.00f, 0.61f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.00f, 0.50f, 0.00f, 0.39f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 0.50f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 0.50f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 0.50f, 0.00f, 0.61f);
	style.Colors[ImGuiCol_Button] = ImVec4(1.00f, 0.50f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(1.00f, 0.50f, 0.00f, 0.61f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(1.00f, 0.50f, 0.00f, 0.39f);
	style.Colors[ImGuiCol_Header] = ImVec4(1.00f, 0.50f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(1.00f, 0.50f, 0.00f, 0.61f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(1.00f, 0.50f, 0.00f, 0.39f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(1.00f, 0.50f, 0.00f, 0.39f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);

	style.WindowPadding = { 8.f, 8.f };
	style.WindowRounding = 0.f;
	style.ChildRounding = 0.f;
	style.FramePadding = { 4.f, 4.f };
	style.FrameRounding = 0.f;
	style.ItemSpacing = { 8, 4 };
	style.ItemInnerSpacing = { 4.f, 4.f };
	style.TouchExtraPadding = { 0.f, 0.f };
	style.IndentSpacing = 20.f;
	style.ScrollbarSize = 20.f;
	style.ScrollbarRounding = 0.f;
	style.GrabRounding = 0.f;
}

bool GUI::MessageProcedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
	auto& system = System::Get();

	if (!system.Gui())
		return false;

	return ImGui_ImplWin32_WndProcHandler(window, message, wparam, lparam);
}
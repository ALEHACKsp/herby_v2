#include "renderer.hpp"
#include "csgo/hooks/hooks.hpp"

Renderer::~Renderer()
{
	Restore();
}

void Renderer::Initialize(IDirect3DDevice9* device)
{
	ImGui::CreateContext();

	ImGui_ImplWin32_Init(Input::Get().GetWindow());

	ImGui_ImplDX9_Init(device);

	ImFontConfig font_config = { };

	font_config.OversampleH = 1;
	font_config.OversampleV = 1;
	font_config.PixelSnapH = true;

	auto& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 16.f, &font_config, io.Fonts->GetGlyphRangesCyrillic());
}

void Renderer::Restore()
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();

	ImGui::DestroyContext();
}

bool Renderer::Begin()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0, 0, 0, 0 });
	auto result = ImGui::Begin("overlay", reinterpret_cast<bool*>(true), ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs);

	auto& io = ImGui::GetIO();
	ImGui::SetWindowPos({ 0.f, 0.f }, ImGuiCond_Always);
	ImGui::SetWindowSize(io.DisplaySize, ImGuiCond_Always);

	return result;
}

void Renderer::End()
{
	ImGui::End();
	ImGui::PopStyleColor();
}

void Renderer::Present()
{
	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

void Renderer::Lost()
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
}

void Renderer::Reset(const HRESULT result)
{
	if (SUCCEEDED(result))
		ImGui_ImplDX9_CreateDeviceObjects();
}

void Renderer::DrawQuad(const ImVec2& p0, const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImColor& color)
{
	auto render = GetDrawList();
	render->AddQuadFilled({ p0[0], p0[1] }, { p1[0], p1[1] }, { p2[0], p2[1] }, { p3[0], p3[1] }, color);
}

void Renderer::DrawRect(const ImVec2& begin, const ImVec2& size, const ImColor& color, bool fill /*= true*/)
{
	auto render = GetDrawList();

	(fill ?
		render->AddRectFilled({ begin[0], begin[1] }, { begin[0] + size[0], begin[1] + size[1] }, color) :
		render->AddRect({ begin[0], begin[1] }, { begin[0] + size[0], begin[1] + size[1] }, color));
}

void Renderer::DrawOutRect(const ImVec2& begin, const ImVec2& size, const ImColor& color)
{
	DrawRect(begin, size, color);
	DrawRect(begin, size, { 0.f, 0.f, 0.f }, false);
}

void Renderer::DrawLine(const ImVec2& begin, const ImVec2& end, const ImColor& color, float width /*= 1.f*/)
{
	auto render = GetDrawList();
	render->AddLine({ begin[0], begin[1] }, { end[0], end[1] }, color, width);
}

void Renderer::DrawCircle(const ImVec2& begin, float radius, const ImColor& color)
{
	auto render = GetDrawList();
	render->AddCircle(begin, radius, ImGui::ColorConvertFloat4ToU32(color), 512, 1.1f);
}

void Renderer::DrawText(const ImVec2& begin, const std::uint32_t layout, const float size, const ImColor& color, const char* message, ...)
{
	char output[1024] = { };

	va_list args;
	va_start(args, message);
	vsprintf_s(output, message, args);
	va_end(args);

	auto text_coord = ImVec2(begin[0], begin[1]);
	auto text_size = ImGui::CalcTextSize(output);

	if (layout & TextRight)
		text_coord.x -= text_size.x;
	else if (layout & TextCenterH)
		text_coord.x -= text_size.x / 2.f;

	if (layout & TextCenterV)
		text_coord.y -= text_size.y / 2.f;

	auto render = GetDrawList();

	render->AddText(nullptr, size, { text_coord.x + 1.f, text_coord.y }, ImColor{ 0.f, 0.f, 0.f, 1.f }, output);
	render->AddText(nullptr, size, { text_coord.x, text_coord.y + 1.f }, ImColor{ 0.f, 0.f, 0.f, 1.f }, output);
	render->AddText(nullptr, size, { text_coord.x - 1.f, text_coord.y }, ImColor{ 0.f, 0.f, 0.f, 1.f }, output);
	render->AddText(nullptr, size, { text_coord.x, text_coord.y - 1.f }, ImColor{ 0.f, 0.f, 0.f, 1.f }, output);

	render->AddText(nullptr, size, text_coord, color, output);
}

void Renderer::DrawText(const ImVec2& begin, const std::uint32_t layout, const ImColor& color, const char* message, ...)
{
	char output[1024] = { };

	va_list args;
	va_start(args, message);
	vsprintf_s(output, message, args);
	va_end(args);

	auto text_coord = ImVec2(begin[0], begin[1]);
	auto text_size = ImGui::CalcTextSize(output);

	if (layout & TextRight)
		text_coord.x -= text_size.x;
	else if (layout & TextCenterH)
		text_coord.x -= text_size.x / 2.f;

	if (layout & TextCenterV)
		text_coord.y -= text_size.y / 2.f;

	auto render = GetDrawList();

	render->AddText({ text_coord.x + 1.f, text_coord.y }, ImColor{ 0.f, 0.f, 0.f, 1.f }, output);
	render->AddText({ text_coord.x, text_coord.y + 1.f }, ImColor{ 0.f, 0.f, 0.f, 1.f }, output);
	render->AddText({ text_coord.x - 1.f, text_coord.y }, ImColor{ 0.f, 0.f, 0.f, 1.f }, output);
	render->AddText({ text_coord.x, text_coord.y - 1.f }, ImColor{ 0.f, 0.f, 0.f, 1.f }, output);

	render->AddText(text_coord, color, output);
}

void Renderer::GetTextSize(ImVec2& output, const char* message, ...)
{
	char format[1024] = { };

	va_list args;
	va_start(args, message);
	vsprintf_s(format, message, args);
	va_end(args);

	auto size = ImGui::CalcTextSize(format);
	output = size;
}

ImDrawList* Renderer::GetDrawList()
{
	return (ImGui::GetOverlayDrawList());
}
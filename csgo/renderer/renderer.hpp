#pragma once
#include <string>
#include <sstream>
#include <stdint.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "valve/auto.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

#if defined( DrawText )
#undef DrawText
#endif // DrawText

enum TextLayout
{
	TextLeft = 0x00,
	TextRight = 0x01,
	TextCenterV = 0x02,
	TextCenterH = 0x04,
	TextCenter = (TextCenterV | TextCenterH),
};

class Renderer : public Singleton< Renderer >
{
public:
	~Renderer();
public:
	void Initialize(IDirect3DDevice9* device);
	void Restore();

	bool Begin();
	void End();

	void Present();

	void Lost();
	void Reset(const HRESULT result);
public:
	void DrawQuad(const ImVec2& p0, const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImColor& color);
	void DrawRect(const ImVec2& begin, const ImVec2& size, const ImColor& color, bool fill = true);
	void DrawOutRect(const ImVec2& begin, const ImVec2& size, const ImColor& color);
	void DrawLine(const ImVec2& begin, const ImVec2& end, const ImColor& color, float width = 1.f);
	void DrawCircle(const ImVec2& begin, float radius, const ImColor& color);
	void DrawText(const ImVec2& begin, const std::uint32_t layout, const float size, const ImColor& color, const char* message, ...);
	void DrawText(const ImVec2& begin, const std::uint32_t layout, const ImColor& color, const char* message, ...);
	void GetTextSize(ImVec2& output, const char* message, ...);
private:
	ImDrawList* GetDrawList();
};
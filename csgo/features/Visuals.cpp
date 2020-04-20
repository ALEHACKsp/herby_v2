#include "Visuals.hpp"
#include "csgo/renderer/renderer.hpp"
#include "csgo/options.h"
struct VisualsStruct
{
	C_CSPlayer* player;
	bool bEnemy;
	bool isVisible;
	Color clr;
	Color clr_text;
	Color clr_fill;
	Color clr_pov;
	Vector head_pos;
	Vector feet_pos;
	RECT bbox;
	float fl_opacity;
}ctx;

RECT GetBBox(C_BaseEntity* ent, Vector pointstransf[])
{
	RECT rect{};
	auto collideable = ent->GetCollideable();

	if (!collideable)
		return rect;

	auto min = collideable->OBBMins();
	auto max = collideable->OBBMaxs();

	const matrix3x4_t& trans = ent->m_rgflCoordinateFrame();

	Vector points[] =
	{
		Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, max.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(min.x, min.y, max.z),
		Vector(max.x, min.y, max.z)
	};

	Vector pointsTransformed[8];
	for (int i = 0; i < 8; i++) {
		math::VectorTransform(points[i], trans, pointsTransformed[i]);
	}

	Vector pos = ent->m_vecOrigin();
	Vector screen_points[8] = {};

	for (int i = 0; i < 8; i++)
		if (!Utils::WorldToScreen(pointsTransformed[i], screen_points[i]))
			return rect;
		else
			pointstransf[i] = screen_points[i];

	auto left = screen_points[0].x;
	auto top = screen_points[0].y;
	auto right = screen_points[0].x;
	auto bottom = screen_points[0].y;

	for (int i = 1; i < 8; i++)
	{
		if (left > screen_points[i].x)
			left = screen_points[i].x;
		if (top < screen_points[i].y)
			top = screen_points[i].y;
		if (right < screen_points[i].x)
			right = screen_points[i].x;
		if (bottom > screen_points[i].y)
			bottom = screen_points[i].y;
	}
	return RECT{ (long)left, (long)top, (long)right, (long)bottom };
}

void Visuals::RenderNadeEsp(C_BaseCombatWeapon* nade)
{
	if (!Options::Visual.grenade_esp)
		return;

	const model_t* model = nade->GetModel();
	if (!model)
		return;

	studiohdr_t* hdr = csgo::m_model_info_client->GetStudioModel(model);
	if (!hdr)
		return;

	ImColor Nadecolor;
	std::string entityName = hdr->name, icon_character;

	switch (nade->GetClientClass()->m_ClassID)
	{
	case 9:
		if (entityName[16] == 's')
		{
			Nadecolor = ImColor(255, 255, 0, 200);
			entityName = "Flash";
			icon_character = "G";
		}
		else
		{
			Nadecolor = ImColor(255, 0, 0, 200);
			entityName = "Frag";
			icon_character = "H";
		}
		break;
	case 134:
		Nadecolor = ImColor(170, 170, 170, 200);
		entityName = "Smoke";
		icon_character = "P";
		break;
	case 98:
		Nadecolor = ImColor(255, 0, 0, 200);
		entityName = "Fire";
		icon_character = "P";
		break;
	case 41:
		Nadecolor = ImColor(255, 255, 0, 200);
		entityName = "Decoy";
		icon_character = "G";
		break;
	default:
		return;
	}

	Vector points_transformed[8];
	RECT size = GetBBox(nade, points_transformed);
	if (size.right == 0 || size.bottom == 0)
		return;

	int width, height, width_icon, height_icon;

	switch (Options::Visual.grenade_esp_type)
	{
	case 0:
		Renderer::Get().DrawText({ size.left + ((size.right - size.left) * 0.5), size.bottom + (size.top - size.bottom) + height * 0.5f + 2 }, TextCenter, Nadecolor, entityName.c_str());
		break;
	case 1:
		Renderer::Get().DrawLine({ size.left - 1, size.bottom - 1 }, { size.left - 1, size.top + 1 }, ImColor(20, 20, 20, 240));
		Renderer::Get().DrawLine({ size.right + 1, size.top + 1 }, { size.right + 1, size.bottom - 1 }, ImColor(20, 20, 20, 240));
		Renderer::Get().DrawLine({ size.left - 1, size.top + 1 }, { size.right + 1, size.top + 1 }, ImColor(20, 20, 20, 240));
		Renderer::Get().DrawLine({ size.right + 1, size.bottom - 1 }, { size.left + -1, size.bottom - 1 }, ImColor(20, 20, 20, 240));

		Renderer::Get().DrawLine({ size.left, size.bottom }, { size.left, size.top }, Nadecolor);
		Renderer::Get().DrawLine({ size.left, size.top }, { size.right, size.top }, Nadecolor);
		Renderer::Get().DrawLine({ size.right, size.top }, { size.right, size.bottom }, Nadecolor);
		Renderer::Get().DrawLine({ size.right, size.top }, { size.right, size.bottom }, Nadecolor);
	}
}
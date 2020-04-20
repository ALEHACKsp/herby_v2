#pragma once
#include "valve/auto.hpp"

class Visuals : public Singleton<Visuals>
{
private:
	bool Begin(C_CSPlayer* player);
	bool ValidPlayer(C_CSPlayer* player, bool = true);
	bool IsVisibleScan(C_CSPlayer* player);
	void RenderBox();
	void RenderFill();
	void RenderName();
	void RenderHealth();
	void RenderWeapon();
	void RenderSnapline();
	void RenderSkelet();
	void RenderWeapon(C_BaseCombatWeapon* entity);
	void RenderNadeEsp(C_BaseCombatWeapon* nade);
	void RenderPlantedC4(C_BaseEntity* entity);
	void RenderSpectatorList();
	void DrawWatermark();
	void DrawFlags();
	void ModulateWorld();
	void DrawPoV();
	void DrawCapsuleOverlay(int idx, float duration);
	void DrawhealthIcon(int x, int y, C_BasePlayer* player = nullptr);
public:
	void Render();
};
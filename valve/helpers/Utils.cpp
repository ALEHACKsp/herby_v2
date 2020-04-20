#include "valve/auto.hpp"
#include "csgo/hooks/hooks.hpp"
namespace Utils
{
	void FlashTaskbarIcon()
	{
		FLASHWINFO fi;
		fi.cbSize = sizeof(FLASHWINFO);
		fi.hwnd = Input::Get().GetWindow();
		fi.dwFlags = FLASHW_ALL | FLASHW_TIMERNOFG;
		fi.uCount = 0;
		fi.dwTimeout = 0;
		FlashWindowEx(&fi);
	}
	bool ScreenTransform(const Vector& point, Vector& screen)
	{
		const auto& w2sMatrix = csgo::m_engine_client->WorldToScreenMatrix();
		screen.x = w2sMatrix.m[0][0] * point.x + w2sMatrix.m[0][1] * point.y + w2sMatrix.m[0][2] * point.z + w2sMatrix.m[0][3];
		screen.y = w2sMatrix.m[1][0] * point.x + w2sMatrix.m[1][1] * point.y + w2sMatrix.m[1][2] * point.z + w2sMatrix.m[1][3];
		screen.z = 0.0f;

		const auto w = w2sMatrix.m[3][0] * point.x + w2sMatrix.m[3][1] * point.y + w2sMatrix.m[3][2] * point.z + w2sMatrix.m[3][3];
		if (w < 0.001f)
		{
			screen.x *= 100000;
			screen.y *= 100000;
			return true;
		}
		const auto invw = 1.f / w;
		screen.x *= invw;
		screen.y *= invw;
		return false;

	}
	bool WorldToScreen(const Vector& origin, Vector& screen)
	{
		if (!ScreenTransform(origin, screen)) 
		{
			int iScreenWidth, iScreenHeight;
			csgo::m_engine_client->GetScreenSize(iScreenWidth, iScreenHeight);
			screen.x = iScreenWidth / 2.f + screen.x * iScreenWidth / 2;
			screen.y = iScreenHeight / 2.f - screen.y * iScreenHeight / 2;
			return true;
		}
		return false;
	}
}
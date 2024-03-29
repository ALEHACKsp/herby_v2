#pragma once
#include "sdk/definitions.hpp"
#include "sdk/math/base.hpp"

class CMoveData
{
public:
	bool			m_bFirstRunOfFunctions : 1;
	bool			m_bGameCodeMovedPlayer : 1;
	bool			m_bNoAirControl : 1;

	unsigned long	m_nPlayerHandle;
	int				m_nImpulseCommand;
	QAngle			m_vecViewAngles;
	QAngle			m_vecAbsViewAngles;
	int				m_nButtons;
	int				m_nOldButtons;
	float			m_flForwardMove;
	float			m_flSideMove;
	float			m_flUpMove;

	float			m_flMaxSpeed;
	float			m_flClientMaxSpeed;

	Vector			m_vecVelocity;
	Vector			m_vecOldVelocity;
	float			somefloat;
	QAngle			m_vecAngles;
	QAngle			m_vecOldAngles;

	float			m_outStepHeight;
	Vector			m_outWishVel;
	Vector			m_outJumpVel;

	Vector			m_vecConstraintCenter;
	float			m_flConstraintRadius;
	float			m_flConstraintWidth;
	float			m_flConstraintSpeedFactor;
	bool			m_bConstraintPastRadius;

	void SetAbsOrigin(const Vector& vec)
	{
		m_vecAbsOrigin = vec;
	}
	const Vector& GetMoveAbsOrigin()
	{
		return m_vecAbsOrigin;
	}

private:
	Vector m_vecAbsOrigin;
};

class C_CSPlayer;

class IGameMovement
{
public:
	virtual			~IGameMovement(void) {}

	virtual void	ProcessMovement(void* pPlayer, CMoveData* pMove) = 0;
	virtual void	Reset(void) = 0;
	virtual void	StartTrackPredictionErrors(void* pPlayer) = 0;
	virtual void	FinishTrackPredictionErrors(void* pPlayer) = 0;
	virtual void	DiffPrint(char const* fmt, ...) = 0;

	virtual Vector const& GetPlayerMins(bool ducked) const = 0;
	virtual Vector const& GetPlayerMaxs(bool ducked) const = 0;
	virtual Vector const& GetPlayerViewOffset(bool ducked) const = 0;

	virtual bool			IsMovingPlayerStuck(void) const = 0;
	virtual C_CSPlayer* GetMovingPlayer(void) const = 0;
	virtual void			UnblockPusher(void* pPlayer, void* pPusher) = 0;

	virtual void SetupMovementBounds(CMoveData* pMove) = 0;
};

class CGameMovement
	: public IGameMovement
{
public:
	virtual ~CGameMovement(void) {}
};
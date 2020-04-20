#include "csgo/hooks/hooks.hpp"
#include <intrin.h>
namespace Hooks
{
	void __stdcall CreateMove(int sequenceNumber, float inputSampleFrametime, bool active, bool& bSendPacket)
	{
		static auto original = client_hook->GetOriginal<decltype(&CreateMove_Proxy)>(22);
		original(sequenceNumber, inputSampleFrametime, active);

		auto cmd = csgo::m_input->GetUserCmd(sequenceNumber);
		auto verified = csgo::m_input->GetVerifiedUserCmd(sequenceNumber);

		if (!cmd || !cmd->command_number)
			return;

		verified->m_cmd = *cmd;
		verified->m_crc = cmd->GetChecksum();
	}
	void  __stdcall CreateMove_Proxy(int sequenceNumber, float inputSampleFrametime, bool active)
	{
		__asm
		{
			push ebp
			mov  ebp, esp
			push ebx
			lea  ecx, [esp]
			push ecx
			push dword ptr[active]
			push dword ptr[inputSampleFrametime]
			push dword ptr[sequenceNumber]
			call CreateMove
			pop  ebx
			pop  ebp
			retn 0Ch
		}
	}
}
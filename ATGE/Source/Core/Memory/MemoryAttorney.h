#pragma once

#include "MemoryManager.h"

namespace ATGE
{
	class MemoryAttorney
	{
		friend class ATGEngine;

		static bool InitMemMan() { return MemoryManager::Initialize(); };
		static bool OpenArena() { return MemoryManager::OpenArena(); };
		static void CloseArena() { MemoryManager::CloseArena(); };
	};
}
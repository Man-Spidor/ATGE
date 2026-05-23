#include "MemoryManager.h"

namespace ATGE
{
	alignas(MemoryManager) static char s_MemoryManagerStorage[sizeof(MemoryManager)];

	MemoryManager* MemoryManager::s_Instance;

	MemoryManager::MemoryManager() :
		m_pMemoryBuffer(nullptr),
		m_pNextFree(nullptr),
		m_BufferSize(g_ATGEArenaSizeDefault),
		m_FreeSize(g_ATGEArenaSizeDefault)
	{
	}

	bool MemoryManager::initMemMan()
	{
#ifdef FRAMEWORK_H
		PLACEMENT_NEW_BEGIN
#undef new
			s_Instance = new(s_MemoryManagerStorage) MemoryManager();
		PLACEMENT_NEW_END
#else
		s_Instance = new(s_MemoryManagerStorage) MemoryManager();
#endif

		return s_Instance != nullptr;
	}

	bool MemoryManager::OpenArena()
	{
		auto& inst = *s_Instance;

		inst.m_pMemoryBuffer = new char[inst.m_BufferSize];
		inst.m_pNextFree = inst.m_pMemoryBuffer;
		inst.m_FreeSize = inst.m_BufferSize;

		Logger::info("Creating Memory Arena at %p. Size of %d\n", inst.m_pMemoryBuffer, inst.m_BufferSize);

		return inst.m_pMemoryBuffer != nullptr;
	}

	void MemoryManager::CloseArena()
	{
		auto& inst = Instance();

		Logger::info("Closing Memory Arena! \n--> Total Size of %d\n", inst.m_BufferSize - inst.m_FreeSize);

		delete[] inst.m_pMemoryBuffer;
	}

	void MemoryManager::setEngineArenaSize(u32 _BufferSize)
	{
		Instance().m_BufferSize = _BufferSize;
	}

	void* MemoryManager::privAllocate(size_t size, u32 num)
	{
		Logger::info("Allocating %d bytes to Address: [%p]\n", size * num, this->m_pNextFree);
		Logger::info("--> Size Remaining: [%d]\n", this->m_FreeSize - (size * num));

		ATGE_ASSERT_MSG(size > 0, "Allocation size must be a positive number.\n\n");
		ATGE_ASSERT_MSG((size * num) < this->m_FreeSize, "Reached engine memory limit. \n    Tried to allocate more memory than was available. \n    Please increase the memory limit or decrease memory usage.");

		char* pRet = nullptr;

#ifdef FRAMEWORK_H
		PLACEMENT_NEW_BEGIN
#undef new
			pRet = new((void*)this->m_pNextFree) char[size * num];
		PLACEMENT_NEW_END
#else
		pRet = new((void*)this->m_pNextFree) char[size * num];
#endif
		this->m_pNextFree += size * num;
		this->m_FreeSize -= static_cast<u32>(size) * num;

		return pRet;
	}
}

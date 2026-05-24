#pragma once

namespace ATGE
{
	class MemoryManager
	{
		friend class MemoryAttorney;

	public:
		struct AllocKey final
		{
			friend class MemoryManager;
		private:
			AllocKey() = default;
		};

	private:
		MemoryManager();
		MemoryManager(const MemoryManager& other) = default;
		MemoryManager& operator=(const MemoryManager& other) = default;
		MemoryManager(MemoryManager&& other) = default;
		MemoryManager& operator=(MemoryManager&& other) = default;
		~MemoryManager() = default;

		static bool Initialize();
		static bool OpenArena();
		static void CloseArena();

	public:
		static void SetEngineArenaSize(u32 _BufferSize);

		template<typename T>
		static T* allocate(u32 num = 1)
		{
#ifdef FRAMEWORK_H
			PLACEMENT_NEW_BEGIN
#undef new
				return new(Instance().privAllocate(sizeof(T), num)) T();
			PLACEMENT_NEW_END
#else
			return new(Instance().privPush(sizeof(T), num)) T();
#endif
		}
		template<typename T>
		static T* allocatePrivate(u32 num = 1)
		{
#ifdef FRAMEWORK_H
			PLACEMENT_NEW_BEGIN
#undef new
				return new(Instance().privAllocate(sizeof(T), num)) T(AllocKey{});
			PLACEMENT_NEW_END
#else
			return new(Instance().privPush(sizeof(T), num)) T(AllocKey{});
#endif
		}

		template<typename T, typename... Args>
		static T* allocate(u32 num = 1, Args&&... args)
		{
#ifdef FRAMEWORK_H
			PLACEMENT_NEW_BEGIN
#undef new
				return new(Instance().privAllocate(sizeof(T), num)) T(std::forward<Args>(args)...);
			PLACEMENT_NEW_END
#else
			return new(Instance().privPush(sizeof(T), num)) T(std::forward<Args>(args)...);
#endif
		}

		template<typename T, typename... Args>
		static T* allocatePrivate(u32 num = 1, Args&&... args)
		{
#ifdef FRAMEWORK_H
			PLACEMENT_NEW_BEGIN
#undef new
				return new(Instance().privAllocate(sizeof(T), num)) T(AllocKey{}, std::forward<Args>(args)...);
			PLACEMENT_NEW_END
#else
			return new(Instance().privPush(sizeof(T), num)) T(AllocKey{}, std::forward<Args>(args)...);
#endif
		}

	private:
		void* privAllocate(size_t size, u32 num);

	private:
		static MemoryManager& Instance()
		{
			return *s_Instance;
		}
		static MemoryManager* s_Instance;

	private:
		u8* m_pMemoryBuffer;
		u8* m_pNextFree;
		u32 m_BufferSize;
		u32 m_FreeSize;
	};
}


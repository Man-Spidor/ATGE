#pragma once

#include "Core/Memory/MemoryManager.h"

namespace ATGE
{
	template <typename T>
	struct SwapbackArray final
	{
	public:
		SwapbackArray() :
			m_pList(nullptr),
			m_MaxSize(0),
			m_CurrSize(0)
		{
		}

		SwapbackArray(const SwapbackArray& other) = delete;
		SwapbackArray& operator=(const SwapbackArray& other) = delete;
		SwapbackArray(SwapbackArray&& other) = delete;
		SwapbackArray& operator=(SwapbackArray&& other) = delete;
		~SwapbackArray() = default;

		void createArray(u32 arraySize)
		{
			ATGE_ASSERT_MSG(this->m_pList == nullptr, "Cannot call createArray twice!\n");

			this->m_MaxSize = arraySize;

#ifdef SWAPBACK_DEBUG
			Logger::info("Creating SwapbackArray of max size %d!!\n", this->m_MaxSize);
#endif

			this->m_pList = MemoryManager::allocate<T>(this->m_MaxSize);	
			ATGE_ASSERT(this->m_pList);
		}

		void add(const T& t)
		{
			ATGE_ASSERT_DEBUG_MSG(this->m_pList != nullptr, "Tried to add to SwapbackArray without initializing first!");
			ATGE_ASSERT_DEBUG_MSG(this->m_CurrSize < this->m_MaxSize, "Error, you have reached the maximum size of the array and still tried to add to it :(. \nTo fix please allocate more memory to the array in the createArray() function., ");

#ifdef SWAPBACK_DEBUG
			Logger::debug("Adding to SwapbackArray!! \n--> New Size is %d\n", this->m_CurrSize + 1);
#endif
			this->m_pList[this->m_CurrSize++] = t;
		}

		template <typename... Args>
		void emplace(Args&&... args)
		{
			ATGE_ASSERT_DEBUG_MSG(this->m_pList != nullptr, "Tried to emplace into SwapbackArray without initializing first!");
			ATGE_ASSERT_DEBUG_MSG(this->m_CurrSize < this->m_MaxSize, "SwapbackArray is full");
			// new (&this->m_pList[this->m_CurrSize]) T(std::forward<Args>(args)...);

			this->m_pList[this->m_CurrSize] = T(std::forward<Args>(args)...);

			this->m_CurrSize++;
		}

		void remove(u32 index)
		{
#ifdef SWAPBACK_DEBUG
			Logger::debug("Removing from the SwapbackArray!! \n--> New Size is %d\n", this->m_CurrSize - 1);
#endif
			ATGE_ASSERT_DEBUG_MSG(index < this->m_CurrSize, "Tried to remove an object from the array that doesn't exist :(");
			
			if (index != m_CurrSize - 1)
				m_pList[index] = m_pList[m_CurrSize - 1];
			this->m_CurrSize--;
		}

		T& pop()
		{
			if (this->m_CurrSize < 1) {
				Logger::fatal("You tried to pop from an empty SwapbackArray!");
			}

			return this->m_pList[--this->m_CurrSize];
		}

		u32 size() const
		{
			return this->m_CurrSize;
		}

		u32 maxSize() const
		{
			return this->m_MaxSize;
		}

		b8 empty() const
		{
			return this->m_CurrSize == 0;
		}

		const T& operator[] (const u32 index) const 
		{
			ATGE_ASSERT_DEBUG_MSG(index < this->m_CurrSize, "Can not index past the maximum size of the SwapbackArray :(");
			return this->m_pList[index]; 
		};

		T& operator[] (const u32 index)
		{
			ATGE_ASSERT_DEBUG_MSG(index < this->m_CurrSize, "Can not index past the maximum size of the SwapbackArray :(");
			return this->m_pList[index];
		};

	private:
		T* m_pList;

		u32 m_MaxSize;
		u32 m_CurrSize;
	};
}


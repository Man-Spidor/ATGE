#pragma once

namespace ATGE
{
	class ATGEngine final
	{
		friend class MemoryManager;

	private:
		ATGEngine();
		ATGEngine(const ATGEngine& other) = default;
		ATGEngine& operator=(const ATGEngine& other) = default;
		ATGEngine(ATGEngine&& other) = default;
		ATGEngine& operator=(ATGEngine&& other) = default;
		~ATGEngine();

	public:
		static void Run();
	};
}


#pragma once

namespace ATGE
{
	class UpdateManager final
	{
	public:
		UpdateManager() = default;
		UpdateManager(const UpdateManager& other) = default;
		UpdateManager& operator=(const UpdateManager& other) = default;
		UpdateManager(UpdateManager&& other) = default;
		UpdateManager& operator=(UpdateManager&& other) = default;
		~UpdateManager() = default;

	};
}


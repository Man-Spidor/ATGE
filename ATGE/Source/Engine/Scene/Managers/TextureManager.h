#pragma once

namespace ATGE
{
	class TextureManager
	{
	public:
		TextureManager() = default;
		TextureManager(const TextureManager& other) = default;
		TextureManager& operator=(const TextureManager& other) = default;
		TextureManager(TextureManager&& other) = default;
		TextureManager& operator=(TextureManager&& other) = default;
		~TextureManager() = default;

	};
}


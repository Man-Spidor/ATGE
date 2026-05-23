#pragma once

namespace ATGE
{
	class Texture final
	{
	public:
		Texture() = default;
		Texture(const Texture& other) = default;
		Texture& operator=(const Texture& other) = default;
		Texture(Texture&& other) = default;
		Texture& operator=(Texture&& other) = default;
		~Texture() = default;



	};
}
#pragma once

namespace ATGE
{
	class ShaderBase
	{
	public:
		ShaderBase() = delete;
		ShaderBase(const ShaderBase& other) = default;
		ShaderBase& operator=(const ShaderBase& other) = default;
		ShaderBase(ShaderBase&& other) = default;
		ShaderBase& operator=(ShaderBase&& other) = default;
		~ShaderBase();

		ShaderBase(void* m_pRenderHandle, const char* pFileName);

	private:
		void* m_pShaderHandles;
	};
}

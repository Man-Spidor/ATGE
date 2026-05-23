#pragma once

namespace ATGE
{
	class Model final
	{
	public:
		Model() = default;
		Model(const Model& other) = default;
		Model& operator=(const Model& other) = default;
		Model(Model&& other) = default;
		Model& operator=(Model&& other) = default;
		~Model() = default;

		void bindModel();
		void renderModel();

	private:
		u32 m_Temp;
	};
}
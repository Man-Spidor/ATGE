#pragma once

#include "Graphics/Model.h"
#include "DataStructures/SwapbackArray.h"

namespace ATGE
{
	class ModelManager
	{
	public:
		ModelManager();
		ModelManager(const ModelManager& other) = default;
		ModelManager& operator=(const ModelManager& other) = default;
		ModelManager(ModelManager&& other) = default;
		ModelManager& operator=(ModelManager&& other) = default;
		~ModelManager() = default;

		void addModelData();
		Model& getModelData(ModelID mID);

		void clearModels();

	private:
		ModelID m_CurrModel;
		SwapbackArray<Model> m_ModelList;
	};
}


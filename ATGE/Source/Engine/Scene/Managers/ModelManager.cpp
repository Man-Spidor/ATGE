#include "ModelManager.h"

namespace ATGE
{
	ModelManager::ModelManager() :
		m_CurrModel(g_ATGEUndefinedID),
		m_ModelList()
	{
	}

	void ModelManager::addModelData()
	{
	}

	Model& ATGE::ModelManager::getModelData(ModelID mID)
	{
		Logger::trace("--->--->Fetching Model with ID: [%d]", mID);

		return this->m_ModelList[mID];
	}
}

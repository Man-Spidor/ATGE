#include "MaterialComponent.h"

namespace ATGE
{
	MaterialComponent::MaterialComponent(const Material& _mat, MaterialID _mID) :
		m_Material(_mat),
		m_MaterialID(_mID)
	{
	}
}

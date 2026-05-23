#include "TransformManager.h"

namespace ATGE
{
    const TransformComponent& TransformManager::getTransform(EntityID id) const
    {
        return this->m_TransComponents[id];
    }
}

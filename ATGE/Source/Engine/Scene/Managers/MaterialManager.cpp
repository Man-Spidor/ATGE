#include "MaterialManager.h"

namespace ATGE
{
    void MaterialManager::addMaterial(const Material& mat)
    {
        this->m_MatComps.emplace(mat, this->m_CurrID++);
    }

    const Material& MaterialManager::getMaterial(MaterialID mID) const
    {
        return this->m_MatComps[mID].m_Material;
    }
}

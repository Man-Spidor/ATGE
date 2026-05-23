#include "DrawManager.h"

#include "Graphics/Data_InstanceCB.h"
#include "Graphics/Data_MaterialCB.h"

namespace ATGE
{
    void DrawManager::drawAll()
    {
        Logger::info("Starting Draw Loop\n");

        Logger::trace("---> Sorting draw list by model id...\n");
        const u32 size = this->m_DrawComps.size();
        for (u32 i = 0; i < size; i++) {
            const DrawComponent& key = this->m_DrawComps[i];

            u32 j = i;
            while (j > 0 && this->m_DrawComps[j - 1].m_ModelID > key.m_ModelID) {
                this->m_DrawComps[j] = this->m_DrawComps[j - 1];
                j--;
            }
            this->m_DrawComps[j] = key;
        }

        Data_InstanceCB instBuffer;
        Data_MaterialCB matBuffer;
        Logger::trace("--> Drawing all models...\n");
        for (u32 i = 0; i < size; i++) {
            Logger::info("--->--->Setting Model To ModelID[%d]\n", this->m_DrawComps[i].m_ModelID);
           
            const ModelID currMID = this->m_DrawComps[i].m_ModelID;
            auto pModel = this->m_ModelMan.getModelData(currMID);
            pModel.bindModel();

            while (i < size && this->m_DrawComps[i].m_ModelID == currMID) {
				Logger::trace("--->--->Updating CBs and Rendering Model with ModelID[%d]\n", this->m_DrawComps[i].m_ModelID);

                EntityID eID = this->m_DrawComps[i].m_EntityID;
                const DrawComponent& drawComp = this->m_DrawComps[eID];
                
                auto& transComp = this->m_TransMan.getTransform(eID);

                instBuffer.m_WorldInv = transComp.m_Transform;
                instBuffer.m_WorldInv = transComp.m_Transform.getInv();
                Logger::trace("--->--->Copied Transform Data\n");

                auto& matComp = this->m_MatMan.getMaterial(drawComp.m_MaterialID);
                matBuffer.m_Material.m_Ambient = matComp.m_Ambient;
                matBuffer.m_Material.m_Diffuse = matComp.m_Diffuse;
                matBuffer.m_Material.m_Specular = matComp.m_Specular;
                Logger::trace("--->--->Copied Material Data\n");

                Logger::trace("--->--->Setting Texture Data\n");
                
                pModel.renderModel();

                i++;
            }
        }
    }
}
//!//////////////////////////////////////////////
//!         (The Sweet) Bullet Impact          //
//!               Project File                 //
//! by Roussel Nicolas & Kieliger Leandro 2012 //
//!//////////////////////////////////////////////

#include "Items.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

enum
{
    ID_IsNotPickable = 0,
    IDFlag_IsPickable = 1 << 0,
};

CItem::CItem(vector3df posItem ,int dureeDeVieItem)
{

    m_itemSelector  = 0;
    m_dureeDeVie    = dureeDeVieItem;
    m_pos           = posItem;

}

CItem::~CItem()
{

}

CAmmoBox::CAmmoBox(vector3df posItem ,int dureeDeVieItem) : CItem(posItem, dureeDeVieItem)
{


}

CAmmoBox::~CAmmoBox()
{

}

void CAmmoBox::initItemAmmoBox3D(scene::ISceneManager* smgr, video::IVideoDriver* driver ,map<scene::IAnimatedMeshSceneNode*, CAmmoBox*>& NodeItemAmmoBoxMap)
{

    m_AmmoBoxTex = driver->getTexture("MODELS/PICKUPS/AMMOBOX/AmmoBox_tex.png");

    m_AmmoBoxNode = smgr->addAnimatedMeshSceneNode(smgr->getMesh("MODELS/PICKUPS/AMMOBOX/AmmoBox.b3d"),0,IDFlag_IsPickable);
    //((irr::scene::ISkinnedMesh*)m_AmmoBoxNode)->convertMeshToTangents();

    scene::ITriangleSelector* selector = 0;
    selector = smgr->createTriangleSelector(m_AmmoBoxNode->getMesh(), m_AmmoBoxNode);
    m_AmmoBoxNode->setTriangleSelector(selector);


    m_AmmoBoxNode->setMaterialTexture(0, m_AmmoBoxTex);
    //m_AmmoBoxNode->setMaterialTexture(1, m_zombTexMap);
    m_AmmoBoxNode->setScale(core::vector3df(5, 5, 5));
    //m_AmmoBoxNode->setRotation(core::vector3df(0,0,0));
    m_AmmoBoxNode->setMaterialType(EMT_SOLID);
    //m_AmmoBoxNode->setMaterialFlag(EMF_LIGHTING, true);
    m_AmmoBoxNode->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
    //m_AmmoBoxNode->setMaterialFlag(EMF_GOURAUD_SHADING, true);
    m_AmmoBoxNode->setMaterialFlag(EMF_ANISOTROPIC_FILTER, true);
    m_AmmoBoxNode->setMaterialFlag(EMF_ANTI_ALIASING, true);
    //m_AmmoBoxNode->setMaterialFlag(EMF_TRILINEAR_FILTER, true);
    m_AmmoBoxNode->setMaterialFlag(EMF_FOG_ENABLE, true);
    m_AmmoBoxNode->getMaterial(0).EmissiveColor = SColor(255,70,70,70);
    //m_AmmoBoxNode->addShadowVolumeSceneNode(0,-1,false);
    m_AmmoBoxNode->setPosition(m_pos);


    NodeItemAmmoBoxMap[m_AmmoBoxNode] = this;

}

IAnimatedMeshSceneNode* CAmmoBox::getAmmoBoxNode() const
{
    return m_AmmoBoxNode;
}

void CAmmoBox::destroy()
{

    m_AmmoBoxNode->remove();
    delete this;
}

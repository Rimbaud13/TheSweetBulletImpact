//!//////////////////////////////////////////////
//!         (The Sweet) Bullet Impact          //
//!               Project File                 //
//! by Roussel Nicolas & Kieliger Leandro 2012 //
//!//////////////////////////////////////////////

#include "Niveau.h"
#include <irrlicht.h>
#include <irrTypes.h>
#include <irrBullet.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;


enum
{
    ID_IsNotPickable = 0,
    IDFlag_IsPickable = 1 << 0,
};


CLevel::CLevel(std::string nom)
{
    m_nomMap        = nom;
    m_mapTex        = 0;
    m_mapTexMap     = 0;
    m_mapNode       = 0;
    m_MapSelector   = 0;
    m_mapShape      = 0;
    m_mapBody       = 0;
}

CLevel::~CLevel()
{

}

void CLevel::loadMap3D(scene::ISceneManager* smgr,video::IVideoDriver* driver, irrBulletWorld* world)
{
    driver->setFog(video::SColor(255,20,20,20), video::EFT_FOG_LINEAR, 10, 400, .04f, true, false);

    /*
        //!m_mapNode = smgr->addOctreeSceneNode(smgr->getMesh("MODELS/MAPS/TEST/placeFinale.obj"), 0, IDFlag_IsPickable);
        m_mapNode = smgr->addOctreeSceneNode(smgr->getMesh("MODELS/MAPS/HELLOWORLD/mapTest.obj"), 0, IDFlag_IsPickable, 32);

        //((irr::scene::ISkinnedMesh*)m_mapNode)->convertMeshToTangents();

        m_MapSelector = smgr->createOctreeTriangleSelector(m_mapNode->getMesh(), m_mapNode, 32);
        m_mapNode->setTriangleSelector(m_MapSelector);
    */
    m_mapNode = smgr->addMeshSceneNode(smgr->getMesh("MODELS/MAPS/HELLOWORLD/mapTest.obj"), 0);

    //((irr::scene::ISkinnedMesh*)m_mapNode)->convertMeshToTangents();

    m_MapSelector = smgr->createTriangleSelector(m_mapNode->getMesh(), m_mapNode);
    m_mapNode->setTriangleSelector(m_MapSelector);

    // Parametrage du material
    m_mapTex = driver->getTexture("MODELS/MAPS/HELLOWORLD/mapTest_tex.png");
    //m_mapTexMap = driver->getTexture ("MODELS/MAPS/TEST/placeFinale_map.png");
    m_mapNode->setPosition(irr::core::vector3df(0,0,0));
    //!m_mapNode->setScale(irr::core::vector3df(12,12,12));
    m_mapNode->setScale(irr::core::vector3df(340,340,340));
    m_mapNode->setMaterialTexture(0, m_mapTex);
    //m_mapNode->setMaterialTexture(1, m_mapTexMap);
    m_mapNode->setMaterialType(EMT_SOLID);
    m_mapNode->setMaterialFlag(EMF_LIGHTING, true);
    m_mapNode->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
    m_mapNode->setMaterialFlag(EMF_ANISOTROPIC_FILTER,true);
    m_mapNode->setMaterialFlag(EMF_ANTI_ALIASING, true);
    m_mapNode->setMaterialFlag(EMF_BILINEAR_FILTER, true);
    m_mapNode->setMaterialFlag(EMF_GOURAUD_SHADING, true);
    m_mapNode->setMaterialFlag(EMF_FOG_ENABLE, true);

    m_mapShape = new IBvhTriangleMeshShape(m_mapNode, m_mapNode->getMesh(), 0);
    m_mapBody = world->addRigidBody(m_mapShape);
}

void CLevel::loadSkyDome(scene::ISceneManager* smgr,video::IVideoDriver* driver)
{
    smgr->addSkyDomeSceneNode(driver->getTexture("MISC/ciel.jpg"), 20, 20, 1, 1.2);
}

IMeshSceneNode* CLevel::getMapNode() const
{
    return m_mapNode;
}

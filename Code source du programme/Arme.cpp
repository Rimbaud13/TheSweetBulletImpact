//!//////////////////////////////////////////////
//!         (The Sweet) Bullet Impact          //
//!               Project File                 //
//! by Roussel Nicolas & Kieliger Leandro 2012 //
//!//////////////////////////////////////////////

#include "Arme.h"
#include <irrlicht.h>
#include <irrTypes.h>


using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

CArme::CArme(stringw nom, int degats, int maxChargeur, int maxMunChargeur, int cadenceTir, int cadenceRecharge, bool coupParCoup)
{
    m_gun3D                     = 0;
    m_handR3D                   = 0;
    m_handL3D                   = 0;
    m_gunTex                    = 0;
    m_gunTexMap                 = 0;
    m_handTex                   = 0;
    m_handTexMap                = 0;
    m_munitions                 = 0;
    m_chargeurs                 = 0;
    m_isLooped                  = false;
    m_coupParCoup               = coupParCoup;
    m_nomArme                   = nom;
    m_boneHandR                 = 0;
    m_boneHandL                 = 0;
    m_degatsArme                = degats;
    m_maxChargeursArme          = maxChargeur;
    m_maxMunitionsChargeurArme  = maxMunChargeur;
    m_cadenceTirArme            = cadenceTir;
    m_cadenceRechargeArme       = cadenceRecharge;
}

CArme::~CArme()
{

}

IAnimatedMeshSceneNode* CArme::getGunMesh() const
{
    return m_gun3D;
}

IAnimatedMeshSceneNode* CArme::getHandRMesh() const
{
    return m_handR3D;
}

IAnimatedMeshSceneNode* CArme::getHandLMesh() const
{
    return m_handL3D;
}

stringw CArme::getNomArme() const
{
    return m_nomArme;
}

void CArme::setNomArme(stringw nouveauNomArme)
{
    m_nomArme = nouveauNomArme;
}

void CArme::setDegatsArme(int nouveauxDegatsArme)
{
    m_degatsArme = nouveauxDegatsArme;
}

void CArme::Init3D(scene::ISceneManager* smgr, video::IVideoDriver* driver,scene::ICameraSceneNode* camera)
{

    m_handTex = driver->getTexture("TEXTURES/HANDS/hand_tex.png");
    m_handTexMap = driver->getTexture("TEXTURES/HANDS/hand_tex_map.png");

    if(m_nomArme =="Beretta M9")
    {

        m_handR3D = smgr->addAnimatedMeshSceneNode(smgr->getMesh("MODELS/WEAPONS/BERETTAM9/handR.b3d"));
        m_handL3D = smgr->addAnimatedMeshSceneNode(smgr->getMesh("MODELS/WEAPONS/BERETTAM9/handL.b3d"));
        m_gun3D   = smgr->addAnimatedMeshSceneNode(smgr->getMesh("MODELS/WEAPONS/BERETTAM9/BerettaM9.b3d"));
        m_gunTex  = driver->getTexture("TEXTURES/BERETTAM9/BerettaM9_tex.png");
        m_gunTexMap = driver->getTexture("TEXTURES/BERETTAM9/BerettaM9_tex_map.png");
    }
    else if(m_nomArme =="IMI Uzi")
    {

        m_handR3D = smgr->addAnimatedMeshSceneNode(smgr->getMesh("MODELS/WEAPONS/IMIUZI/handR.b3d"));
        m_handL3D = smgr->addAnimatedMeshSceneNode(smgr->getMesh("MODELS/WEAPONS/IMIUZI/handL.b3d"));
        m_gun3D   = smgr->addAnimatedMeshSceneNode(smgr->getMesh("MODELS/WEAPONS/IMIUZI/IMIUzi.b3d"));
        m_gunTex  = driver->getTexture("TEXTURES/IMIUZI/IMIUzi_tex.png");
        m_gunTexMap = driver->getTexture("TEXTURES/IMIUZI/IMIUzi_tex_map.png");
    }
    else
    {

        m_handR3D = smgr->addAnimatedMeshSceneNode(smgr->getMesh("MODELS/WEAPONS/BERETTAM9/handR.b3d"));
        m_handL3D = smgr->addAnimatedMeshSceneNode(smgr->getMesh("MODELS/WEAPONS/BERETTAM9/handL.b3d"));
        m_gun3D   = smgr->addAnimatedMeshSceneNode(smgr->getMesh("MODELS/WEAPONS/BERETTAM9/BerettaM9.b3d"));
        m_gunTex  = driver->getTexture("TEXTURES/BERETTAM9/BerettaM9_tex.png");
        m_gunTexMap = driver->getTexture("TEXTURES/BERETTAM9/BerettaM9_tex_map.png");
    }



    if(m_nomArme == "Beretta M9")
    {

        //! la main :

        ((scene::ISkinnedMesh*) m_handR3D)->convertMeshToTangents();

        m_handR3D->setJointMode(EJUOR_READ);
        m_handR3D->setMaterialTexture(0, m_handTex);
        m_handR3D->setMaterialTexture(1, m_handTexMap);
        m_handR3D->setMaterialType(EMT_NORMAL_MAP_SOLID);
        camera->addChild(m_handR3D);
        m_handR3D->setScale(core::vector3df(0.4f, 0.4f, 0.4f));
        m_handR3D->setRotation(core::vector3df(0,-14.4,0));
        m_handR3D->setPosition(core::vector3df(2,-1.8,4.8));
        m_handR3D->setMaterialFlag(EMF_LIGHTING, true);
        m_handR3D->setMaterialFlag(EMF_ANTI_ALIASING, true);
        //m_handR3D->setMaterialFlag(EMF_ANISOTROPIC_FILTER, true);
        m_handR3D->setMaterialFlag(EMF_TRILINEAR_FILTER, true);
        m_handR3D->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
        m_handR3D->setAnimationSpeed(200);

        m_boneHandR = m_handR3D->getJointNode("Main");


//! Gauche !

        ((scene::ISkinnedMesh*) m_handL3D)->convertMeshToTangents();

        m_handL3D->setJointMode(EJUOR_NONE);
        m_handL3D->setMaterialTexture(0, m_handTex);
        m_handL3D->setMaterialTexture(1, m_handTexMap);
        m_handL3D->setMaterialType(EMT_NORMAL_MAP_SOLID);
        m_handR3D->addChild(m_handL3D);
        //m_handL3D->setScale(core::vector3df(0.2f, 0.2f, 0.2f));
        //m_handL3D->setPosition(core::vector3df(1.0f,-0.6f,2.5f));
        m_handL3D->setMaterialFlag(EMF_LIGHTING, true);
        m_handL3D->setMaterialFlag(EMF_ANTI_ALIASING, true);
        //m_handL3D->setMaterialFlag(EMF_ANISOTROPIC_FILTER, true);
        m_handL3D->setMaterialFlag(EMF_TRILINEAR_FILTER, true);
        m_handL3D->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
        m_handL3D->setAnimationSpeed(200);

//m_boneHandL = m_handL3D->getJointNode("Main");

//! Le flingue

        ((scene::ISkinnedMesh*) m_gun3D)->convertMeshToTangents();  //conversion du mesh pour utiliser les normal maps


        m_gun3D->setJointMode(EJUOR_NONE);
        m_gun3D->setMaterialTexture(0, m_gunTex);
        m_gun3D->setMaterialTexture(1, m_gunTexMap);
        m_gun3D->setMaterialType(EMT_NORMAL_MAP_SOLID);
        m_boneHandR->addChild(m_gun3D);
        m_gun3D->setRotation(vector3df(90,0,180));
        m_gun3D->setPosition(core::vector3df(0.0f,5.8f,-0.6f));
        m_gun3D->setMaterialFlag(EMF_LIGHTING, true);
        //m_gun3D->setMaterialFlag(EMF_ANISOTROPIC_FILTER, true);
        m_gun3D->setMaterialFlag(EMF_ANTI_ALIASING, true);
        m_gun3D->setMaterialFlag(EMF_TRILINEAR_FILTER, true);
        m_gun3D->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
        m_gun3D->setAnimationSpeed(200);
    }

    else if(m_nomArme == "IMI Uzi")
    {

        //! la main :


        ((scene::ISkinnedMesh*) m_handR3D)->convertMeshToTangents();

        m_handR3D->setJointMode(EJUOR_READ);
        m_handR3D->setMaterialTexture(0, m_handTex);
        m_handR3D->setMaterialTexture(1, m_handTexMap);
        m_handR3D->setMaterialType(EMT_NORMAL_MAP_SOLID);
        camera->addChild(m_handR3D);
        m_handR3D->setScale(core::vector3df(0.4f, 0.4f, 0.4f));
        m_handR3D->setRotation(core::vector3df(0,-14.4,0));
        m_handR3D->setPosition(core::vector3df(2,-1.8,4.8));
        m_handR3D->setMaterialFlag(EMF_LIGHTING, true);
        m_handR3D->setMaterialFlag(EMF_ANTI_ALIASING, true);
        //m_handR3D->setMaterialFlag(EMF_ANISOTROPIC_FILTER, true);
        m_handR3D->setMaterialFlag(EMF_TRILINEAR_FILTER, true);
        m_handR3D->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
        m_handR3D->setAnimationSpeed(200);

        m_boneHandR = m_handR3D->getJointNode("Main");
// m_boneHandR->setRotation(vector3df(0.0f,0.0f,0.0f));

//! Gauche !

        ((scene::ISkinnedMesh*) m_handL3D)->convertMeshToTangents();

        m_handL3D->setJointMode(EJUOR_NONE);
        m_handL3D->setMaterialTexture(0, m_handTex);
        m_handL3D->setMaterialTexture(1, m_handTexMap);
        m_handL3D->setMaterialType(EMT_NORMAL_MAP_SOLID);
        m_handR3D->addChild(m_handL3D);
        //m_handL3D->setScale(core::vector3df(0.2f, 0.2f, 0.2f));
        //m_handL3D->setPosition(core::vector3df(1.0f,-0.6f,2.5f));
        m_handL3D->setMaterialFlag(EMF_LIGHTING, true);
        m_handL3D->setMaterialFlag(EMF_ANTI_ALIASING, true);
        //m_handL3D->setMaterialFlag(EMF_ANISOTROPIC_FILTER, true);
        m_handL3D->setMaterialFlag(EMF_TRILINEAR_FILTER, true);
        m_handL3D->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
        m_handL3D->setAnimationSpeed(200);

//m_boneHandL = m_handL3D->getJointNode("Main");

//! Le flingue

        ((scene::ISkinnedMesh*) m_gun3D)->convertMeshToTangents();  //conversion du mesh pour utiliser les normal maps


        m_gun3D->setJointMode(EJUOR_NONE);
        m_gun3D->setMaterialTexture(0, m_gunTex);
        m_gun3D->setMaterialTexture(1, m_gunTexMap);
        m_gun3D->setMaterialType(EMT_NORMAL_MAP_SOLID);
        m_boneHandR->addChild(m_gun3D);
        m_gun3D->setRotation(vector3df(90,0,180));
        m_gun3D->setPosition(core::vector3df(0.0f,6.0f,-0.6f));
        m_gun3D->setMaterialFlag(EMF_LIGHTING, true);
        //m_gun3D->setMaterialFlag(EMF_ANISOTROPIC_FILTER, true);
        m_gun3D->setMaterialFlag(EMF_ANTI_ALIASING, true);
        m_gun3D->setMaterialFlag(EMF_TRILINEAR_FILTER, true);
        m_gun3D->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
        m_gun3D->setAnimationSpeed(200);
    }

    else
    {

        //! la main :


        ((scene::ISkinnedMesh*) m_handR3D)->convertMeshToTangents();

        m_handR3D->setJointMode(EJUOR_READ);
        m_handR3D->setMaterialTexture(0, m_handTex);
        m_handR3D->setMaterialTexture(1, m_handTexMap);
        m_handR3D->setMaterialType(EMT_NORMAL_MAP_SOLID);
        camera->addChild(m_handR3D);
        m_handR3D->setScale(core::vector3df(0.4f, 0.4f, 0.4f));
        m_handR3D->setRotation(core::vector3df(0,-14.4,0));
        m_handR3D->setPosition(core::vector3df(1.6,-1.4,4.8));
        m_handR3D->setMaterialFlag(EMF_LIGHTING, true);
        m_handR3D->setMaterialFlag(EMF_ANTI_ALIASING, true);
        //m_handR3D->setMaterialFlag(EMF_ANISOTROPIC_FILTER, true);
        m_handR3D->setMaterialFlag(EMF_TRILINEAR_FILTER, true);
        m_handR3D->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
        m_handR3D->setAnimationSpeed(200);

        m_boneHandR = m_handR3D->getJointNode("Main");

//! Gauche !

        ((scene::ISkinnedMesh*) m_handL3D)->convertMeshToTangents();

        m_handL3D->setJointMode(EJUOR_NONE);
        m_handL3D->setMaterialTexture(0, m_handTex);
        m_handL3D->setMaterialTexture(1, m_handTexMap);
        m_handL3D->setMaterialType(EMT_NORMAL_MAP_SOLID);
        m_handR3D->addChild(m_handL3D);
        //m_handL3D->setScale(core::vector3df(0.2f, 0.2f, 0.2f));
        //m_handL3D->setPosition(core::vector3df(1.0f,-0.6f,2.5f));
        m_handL3D->setMaterialFlag(EMF_LIGHTING, true);
        m_handL3D->setMaterialFlag(EMF_ANTI_ALIASING, true);
        //m_handL3D->setMaterialFlag(EMF_ANISOTROPIC_FILTER, true);
        m_handL3D->setMaterialFlag(EMF_TRILINEAR_FILTER, true);
        m_handL3D->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
        m_handL3D->setAnimationSpeed(200);

//m_boneHandL = m_handL3D->getJointNode("Main");

//! Le flingue


        ((scene::ISkinnedMesh*) m_gun3D)->convertMeshToTangents();  //conversion du mesh pour utiliser les normal maps


        m_gun3D->setJointMode(EJUOR_NONE);
        m_gun3D->setMaterialTexture(0, m_gunTex);
        m_gun3D->setMaterialTexture(1, m_gunTexMap);
        m_gun3D->setMaterialType(EMT_NORMAL_MAP_SOLID);
        m_boneHandR->addChild(m_gun3D);
        m_gun3D->setRotation(vector3df(90,0,180));
        m_gun3D->setPosition(core::vector3df(0.0f,5.8f,-0.6f));
        m_gun3D->setMaterialFlag(EMF_LIGHTING, true);
        //m_gun3D->setMaterialFlag(EMF_ANISOTROPIC_FILTER, true);
        m_gun3D->setMaterialFlag(EMF_ANTI_ALIASING, true);
        m_gun3D->setMaterialFlag(EMF_TRILINEAR_FILTER, true);
        m_gun3D->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
        m_gun3D->setAnimationSpeed(200);
    }



    m_gun3D->setVisible(false);
    m_handR3D->setVisible(false);
    m_handL3D->setVisible(false);
    m_isActive = false;
    this->setGunFL(0,0);
    this->setHandRFL(0,0);
    this->setHandLFL(0,0);
    this->setLooped(false);
}

void CArme::majMunition(int maj_muni)
{
    m_munitions += maj_muni;

    if(m_munitions > m_maxMunitionsChargeurArme)
        m_munitions = m_maxMunitionsChargeurArme;

}

void CArme::majChargeur(int maj_chrg)
{
    m_chargeurs += maj_chrg;

    if(m_chargeurs > m_maxChargeursArme)
        m_chargeurs = m_maxChargeursArme;

}

void CArme::setLooped(bool newValue)
{
    m_isLooped = newValue;
}

void CArme::setFL(int begin, int end)
{
    m_gun3D->setFrameLoop(begin,end);
    m_handR3D->setFrameLoop(begin,end);
}

void CArme::setGunFL(int begin, int end)
{
    m_gun3D->setFrameLoop(begin,end);
}

void CArme::setHandRFL(int begin, int end)
{
    m_handR3D->setFrameLoop(begin,end);
}

void CArme::setHandLFL(int begin, int end)
{
    m_handL3D->setFrameLoop(begin, end);
}

void CArme::setArmeActive(bool newValue)
{
    m_gun3D->setVisible(newValue);
    m_handR3D->setVisible(newValue);
    m_handL3D->setVisible(newValue);

    m_isActive = newValue;
}

bool CArme::isLooped()
{
    return m_isLooped;
}

bool CArme::isCoupParCoup()
{
    return m_coupParCoup;
}

int CArme::getDegats() const
{
    return m_degatsArme;
}

int CArme::getMunitions() const
{
    return m_munitions;
}

int CArme::getChargeurs() const
{
    return m_chargeurs;
}

int CArme::getCadenceTirArme() const
{
    return m_cadenceTirArme;
}

int CArme::getCadenceRechargeArme() const
{
    return m_cadenceRechargeArme;
}

int CArme::getCapaciteArmeChargeurs() const
{
    return m_maxChargeursArme;
}

int CArme::getCapaciteArmeMunitions() const
{
    return m_maxMunitionsChargeurArme;
}

//!//////////////////////////////////////////////
//!         (The Sweet) Bullet Impact          //
//!               Project File                 //
//! by Roussel Nicolas & Kieliger Leandro 2012 //
//!//////////////////////////////////////////////

#include "Zombie.h"
#include "framework.h"
#include "irrMath.h"
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

CZombie::CZombie(irr::core::vector3df pos, int vie)
{
    m_HP            = vie;
    m_pos           = pos;
    m_zombieNode    = 0;
    m_zombBody      = 0;
    m_delaiAttaque  = 0;

    m_wayPointNord  = vector3df(0,20,0);
    m_wayPointEst   = vector3df(-190,20,50);
    m_wayPointSud   = vector3df(0,20,0);
    m_wayPointOuest = vector3df(600,20,60);

    m_WPcheckNord   = false;
    m_WPcheckEst    = false;
    m_WPcheckSud    = false;
    m_WPcheckOuest  = false;

}

CZombie::~CZombie()
{

}
IAnimatedMeshSceneNode* CZombie::getZombieNode() const
{
    return m_zombieNode;
}

IRigidBody* CZombie::getZombieBody() const
{
    return m_zombBody;
}

void CZombie::initZombie3D(scene::ISceneManager* smgr,video::IVideoDriver* driver, irrBulletWorld* world, map<scene::IAnimatedMeshSceneNode*, CZombie*> &NodeZombieMap)
{
    m_zombTex = driver->getTexture("MODELS/ZOMBIES/zombie_tex.png");
    //m_zombTexMap = driver->getTexture("MODELS/ZOMBIES/zombie_tex_map.png");

    m_zombieNode = smgr->addAnimatedMeshSceneNode(smgr->getMesh("MODELS/ZOMBIES/zombie.b3d"),0,IDFlag_IsPickable);
    //((irr::scene::ISkinnedMesh*)m_zombieNode)->convertMeshToTangents();

    scene::ITriangleSelector* selector = 0;
    selector = smgr->createTriangleSelector(m_zombieNode->getMesh(), m_zombieNode);
    m_zombieNode->setTriangleSelector(selector);


    m_zombieNode->setJointMode(EJUOR_NONE);
    m_zombieNode->setMaterialTexture(0, m_zombTex);
    //m_zombieNode->setMaterialTexture(1, m_zombTexMap);
    m_zombieNode->setScale(core::vector3df(1.6, 1.6, 1.6));
    //m_zombieNode->setRotation(core::vector3df(0,0,0));
    m_zombieNode->setMaterialType(EMT_SOLID);
    //m_zombieNode->setMaterialFlag(EMF_LIGHTING, true);
    //m_zombieNode->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
    //m_zombieNode->setMaterialFlag(EMF_ANISOTROPIC_FILTER, true);
    //m_zombieNode->setMaterialFlag(EMF_ANTI_ALIASING, true);
    //m_zombieNode->setMaterialFlag(EMF_TRILINEAR_FILTER, true);
    m_zombieNode->setMaterialFlag(EMF_FOG_ENABLE, true);
    //m_zombieNode->addShadowVolumeSceneNode(0,-1,false);
    m_zombieNode->setAnimationSpeed(50);
    m_zombieNode->setPosition(m_pos);
    m_zombieNode->setLoopMode(true);
    //m_zombieNode->animateJoints();


    ICollisionShape*  shape = new IConvexHullShape(m_zombieNode, m_zombieNode->getMesh(), 80);

    m_zombBody = world->addRigidBody(shape);

    NodeZombieMap[m_zombieNode] = this;
}


void CZombie::addHP(int newHP)
{
    m_HP += newHP;
}

vector3df CZombie::getPos() const
{
    return m_zombieNode->getAbsolutePosition();
}


int CZombie::getHP() const
{
    return m_HP;
}

void CZombie::recevoirDegats(int degats)
{
    m_HP -= degats;

}

bool CZombie::isAlive()
{
    if(m_HP < 1)
    {
        m_zombBody->remove();
        return false;
    }
    else
    {
        return true;
    }
}

//! SYSTEME D'INTELLIGENCE ARTIFICIELLE ULTRA-BASIQUE

void CZombie::updateStatus(vector3df targetPos)
{
    core::line3d<f32> rayTarget;
    rayTarget.start = m_zombieNode->getAbsolutePosition();
    rayTarget.end = targetPos;

    float rayLength = rayTarget.getVector().getLength();

    if(rayLength>290) //! SI TROP ELOIGNÉ DU JOUEUR, FAIRE AVANCER AU WAYPOINT
    {
        //! PARMI TOUS LES WAY POINTS, TROUVER LE PLUS PROCHE
        //!
        //! waypoints possibles: -50,20,50 coté EST
        //!                      600,20,60 coté OUEST
        //!
        line3d<f32> rayWayPoint1;
        rayWayPoint1.start = m_zombieNode->getAbsolutePosition();
        rayWayPoint1.end   = m_wayPointEst;
        line3d<f32> rayWayPoint2;
        rayWayPoint2.start = m_zombieNode->getAbsolutePosition();
        rayWayPoint2.end   = m_wayPointOuest;


        //! TROUVONS LE WAYPOINT LE PLUS PROCHE
        if(rayWayPoint1.getVector().getLengthSQ()>rayWayPoint2.getVector().getLengthSQ() //! ouest plus proche
                && m_WPcheckOuest == false)
        {
            rayTarget.end = m_wayPointOuest;
        }
        else if(rayWayPoint1.getVector().getLengthSQ()<rayWayPoint2.getVector().getLengthSQ() //! est plus proche
                && m_WPcheckEst == false)
        {
            rayTarget.end = m_wayPointEst;
        }
        else if(m_WPcheckEst==true)
        {
            rayTarget.end = m_wayPointOuest;
        }
        else if(m_WPcheckOuest==true)
        {
            rayTarget.end = m_wayPointEst;
        }

        //! S'IL EST DEJA ATTEINT ON POSE COMME OBJECTIF L'AUTRE WAYPOINT
        if(rayWayPoint1.getVector().getLengthSQ()<400)
        {
            rayTarget.end = m_wayPointOuest;
            m_WPcheckEst = true;
            m_WPcheckOuest = false;
        }
        else if(rayWayPoint2.getVector().getLengthSQ()<400)
        {
            rayTarget.end = m_wayPointEst;
            m_WPcheckOuest = true;
            m_WPcheckEst = false;
        }


    }

    m_zombBody->faceTarget(rayTarget.end);

    if(m_zombBody->getLinearVelocity().getLengthSQ()<3)
    {
        m_zombBody->setFriction(0.01f);
        m_zombBody->activate();
        m_zombBody->setLinearVelocity(vector3df(0,1,0)*17);

    }
    else if(m_zombBody->getLinearVelocity().getLengthSQ()>4 && m_zombBody->getFriction()<0.09)
    {
        m_zombBody->setFriction(0.2f);
    }

    m_zombBody->applyCentralImpulse((rayTarget.getVector().normalize()*120), ERBTS_WORLD);

}

bool CZombie::attaqueJoueur(vector3df targetPos)
{
    core::line3d<f32> rayTarget;
    rayTarget.start = m_zombieNode->getAbsolutePosition();
    rayTarget.end = targetPos;

    if(rayTarget.getLength()<20 && m_delaiAttaque>8)
    {
        m_delaiAttaque = 0;
        m_zombBody->setLinearVelocity(vector3df(0,0,0));
        return true;
    }
    else
    {
        m_delaiAttaque ++;
        return false;
    }

}

void CZombie::preDelete()
{
    delete this;
}

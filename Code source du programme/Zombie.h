//!//////////////////////////////////////////////
//!         (The Sweet) Bullet Impact          //
//!               Project File                 //
//! by Roussel Nicolas & Kieliger Leandro 2012 //
//!//////////////////////////////////////////////

#ifndef ZOMBIE
#define ZOMBIE

#include <irrlicht.h>
#include <irrTypes.h>
#include "framework.h"
#include <string>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;


class CZombie : public CFramework
{

public :

    CZombie(vector3df, int);
    ~CZombie();

    IAnimatedMeshSceneNode* getZombieNode() const;
    IRigidBody* getZombieBody() const;
    vector3df getPos()const;
    void initZombie3D(scene::ISceneManager*,video::IVideoDriver* , irrBulletWorld*, map<scene::IAnimatedMeshSceneNode*, CZombie*> &NodeZombieMap);
    void addHP(int);
    int  getHP() const;
    void recevoirDegats(int);
    bool isAlive();
    void updateStatus(vector3df targetPos);
    bool attaqueJoueur(vector3df targetPos);
    void preDelete();

private :

    IAnimatedMeshSceneNode* m_zombieNode;
    IRigidBody* m_zombBody;
    std::string m_zombNom;
    ITexture*                   m_zombTex;
    //ITexture*                   m_zombTexMap;
    ITriangleSelector*          m_zombSelector;
    int m_HP;
    int m_delaiAttaque;
    vector3df m_pos;
    vector3df m_wayPointNord;
    vector3df m_wayPointEst;
    vector3df m_wayPointSud;
    vector3df m_wayPointOuest;
    bool      m_WPcheckNord;
    bool      m_WPcheckEst;
    bool      m_WPcheckSud;
    bool      m_WPcheckOuest;

};


#endif

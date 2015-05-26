//!//////////////////////////////////////////////
//!         (The Sweet) Bullet Impact          //
//!               Project File                 //
//! by Roussel Nicolas & Kieliger Leandro 2012 //
//!//////////////////////////////////////////////

#ifndef NIVEAU
#define NIVEAU
#include <string>
#include <irrlicht.h>
#include <irrTypes.h>
#include <irrBullet.h>


using namespace irr;
using namespace core;
using namespace scene;
using namespace video;


class CLevel
{

public :

    CLevel(std::string nom);
    ~CLevel();

    void                        loadMap3D(scene::ISceneManager*,video::IVideoDriver* , irrBulletWorld*);
    void                        loadSkyDome(scene::ISceneManager*,video::IVideoDriver*);
    IMeshSceneNode*             getMapNode() const;


private :

    std::string                 m_nomMap;
    ITexture*                   m_mapTex;
    ITexture*                   m_mapTexMap;
    ITriangleSelector*          m_MapSelector;
    IMeshSceneNode*             m_mapNode;
    IBvhTriangleMeshShape*      m_mapShape;
    IRigidBody*                 m_mapBody;



};


#endif

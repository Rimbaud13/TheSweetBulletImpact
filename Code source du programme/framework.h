//!//////////////////////////////////////////////
//!         (The Sweet) Bullet Impact          //
//!               Project File                 //
//! by Roussel Nicolas & Kieliger Leandro 2012 //
//!//////////////////////////////////////////////

#ifndef FRAMEWORK
#define FRAMEWORK
#include <irrTypes.h>
#include <vector3d.h>
#include <SColor.h>
#include <SMaterial.h>
#include <IEventReceiver.h>


using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

namespace irr
{
class IrrlichtDevice;

namespace scene
{
class ICameraSceneNode;
class IParticleSystemSceneNode;
}
}
class irrBulletWorld;
class IRigidBody;

class CFramework
{
public:

    CFramework();
    ~CFramework();

    void InitFramework();
    IRigidBody*  addCrate(const irr::core::vector3df &pos, const irr::core::vector3df &scale, irr::f32 mass, irr::core::map<irr::scene::ISceneNode*, IRigidBody*>& nodeBodyMap);
    IRigidBody* const shootCube(const irr::core::vector3df &scale, irr::f32 mass, irr::core::stringc textureFile="rockwall.jpg") const;
    IRigidBody* const shootSphere(const irr::core::vector3df &scale, irr::f32 mass) const;
    IRigidBody* const ejecterDouille(irr::core::vector3df posRepere, irr::core::vector3df posRepere2, irr::core::vector3df vel) const;
    IRigidBody* const ejecterChargeur(irr::scene::IAnimatedMeshSceneNode* gun3D) const;

    irr::scene::IParticleSystemSceneNode* const createParticleSystem(const irr::core::vector3df& pos,const irr::core::vector3df& dir, irr::f32 min, irr::f32 max,
            const irr::video::SColor& darkest, const irr::video::SColor& brightest, irr::f32 minAge, irr::f32 maxAge, irr::f32 angle,
            const irr::core::dimension2df& minSize, const irr::core::dimension2df maxSize, const irr::core::stringc& textureFile,
            irr::f32 lifeTime, bool gravity, irr::video::E_MATERIAL_TYPE materialType, bool fadeOut) const;



    bool debugPos;
    bool debugMode;
    bool drawProperties;
    bool drawWireFrame;

protected:

    irr::IrrlichtDevice*            device;
    irrBulletWorld*                 world;
    irr::scene::ICameraSceneNode*   camera;

    ITexture*                       m_douilleTex;
    ITexture*                       m_magTex;
    ITexture*                       m_crateTex;


};

#endif

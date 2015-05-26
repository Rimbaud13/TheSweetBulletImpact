//!//////////////////////////////////////////////
//!         (The Sweet) Bullet Impact          //
//!               Project File                 //
//! by Roussel Nicolas & Kieliger Leandro 2012 //
//!//////////////////////////////////////////////
#include <cstdlib>
#include <ctime>
#include <irrlicht.h>
#include <irrBullet.h>
/*
#include <bulletworld.h>
#include <rigidbody.h>
#include <boxshape.h>
#include <sphereshape.h>
#include <gimpactmeshshape.h>
#include <convexhullshape.h>
#include <raycastvehicle.h>
#include <collisionobjectaffectordelete.h>
#include <collisionobjectaffectorattract.h>
//#include <collisionobjectaffectorbuoyancy.h>
*/
#include "framework.h"



using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

enum
{
    ID_IsNotPickable = 0,
    IDFlag_IsPickable = 1 << 0,
};

CFramework::CFramework()
{
}

void CFramework::InitFramework()
{
    m_douilleTex = device->getVideoDriver()->getTexture("MODELS/OTHER/douille9m_tex.png");
    m_magTex = device->getVideoDriver()->getTexture("MODELS/OTHER/M9mag_tex.png");
    m_crateTex = device->getVideoDriver()->getTexture("MODELS/OTHER/crate_tex.png");

    srand(time(NULL));
}


IRigidBody* const CFramework::ejecterDouille(vector3df posRepere, vector3df posRepere2, vector3df vel) const
{
    vector3df pos = posRepere;
    vector3df rot (camera->getRotation().X,(camera->getRotation().Y)+50,camera->getRotation().Z);
    IMeshSceneNode *Node = device->getSceneManager()->addMeshSceneNode(device->getSceneManager()->getMesh("MODELS/OTHER/douille.b3d"));
    /*
    ((ISkinnedMesh*)Node)->convertMeshToTangents();
    Node->setMaterialTexture(1, m_douilleMap);
                    Node->getMaterial(0).SpecularColor.set(0,0,0,0);
                Node->setMaterialType(EMT_NORMAL_MAP_SOLID);
    */
    Node->setMaterialTexture(0, m_douilleTex);
    Node->setScale(vector3df(0.05,0.05,0.05));
    Node->setPosition(pos);
    Node->setRotation(rot);
    Node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
    Node->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
    Node->setMaterialFlag(EMF_FOG_ENABLE, true);


    if(drawWireFrame)
        Node->setMaterialFlag(irr::video::EMF_WIREFRAME, drawWireFrame);


    //ICollisionShape*  shape = new IConvexHullShape(Node, Node->getMesh(), 0.02);
    ICollisionShape*  shape = new IBoxShape(Node, 0.02, false);
    shape->setMargin(0.02);
    IRigidBody *body = world->addRigidBody(shape);
    body->setDamping(0.04,0.01);
    body->setCcdValues(0.04,0.04);

//   matrix4 mat;
//   mat.setRotationDegrees(rot);

    core::line3d<f32> rayDouille;
    rayDouille.start = posRepere;
    rayDouille.end = posRepere2;
    vector3df vDouille = rayDouille.getVector();

    float alea = (rand()/(double)RAND_MAX)+0.85;
    float alea2 = (rand()/(double)RAND_MAX)* (-0.1-0.1) + 0.1;
    float alea3 = (rand()/(double)RAND_MAX)* (-0.1-0.1) + 0.1;
    float alea4 = (rand()/(double)RAND_MAX)* (-0.1-0.1) + 0.1;

    //vDouille.Y += alea;

    //  vector3df forwardDir(vector3df(mat[8],mat[9]+alea,mat[10]) * 7);
    body->setLinearVelocity(vDouille*5 +vel);
    body->applyTorque(vector3df(alea2,alea3,alea4), ERBTS_LOCAL);

    return body;
}

IRigidBody* const CFramework::ejecterChargeur(IAnimatedMeshSceneNode* gun3D) const
{
    vector3df pos = camera->getAbsolutePosition();
    //pos.Y-=1.6;
    IMeshSceneNode *Node = device->getSceneManager()->addMeshSceneNode(device->getSceneManager()->getMesh("MODELS/OTHER/M9mag.b3d"));
    /*
    ((ISkinnedMesh*)Node)->convertMeshToTangents();
    Node->setMaterialTexture(1, m_douilleMap);
                    Node->getMaterial(0).SpecularColor.set(0,0,0,0);
                Node->setMaterialType(EMT_NORMAL_MAP_SOLID);
    */
    Node->setMaterialTexture(0, m_magTex);
    Node->setScale(vector3df(0.5,0.5,0.5));
    Node->setPosition(pos);
    Node->setRotation(vector3df(20,0,0));
    Node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
    Node->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
    Node->setMaterialFlag(EMF_FOG_ENABLE, true);


    if(drawWireFrame)
        Node->setMaterialFlag(irr::video::EMF_WIREFRAME, drawWireFrame);

    //ICollisionShape*  shape = new IConvexHullShape(Node, Node->getMesh(), 0.02);
    ICollisionShape*  shape = new IBoxShape(Node, 0.02, false);


    IRigidBody *body = world->addRigidBody(shape);
    //body->setDamping(0.04,0.010);
    //body->setCcdValues(0.04,0.04);

    // matrix4 mat;
    //mat.setRotationDegrees(rot);
    //vector3df forwardDir(vector3df(mat[8],mat[9]+1.5,mat[10]) * 5);
    // body->setLinearVelocity(forwardDir);
    //body->applyTorque(vector3df(0.04,0.02,-0.01), ERBTS_LOCAL);

    return body;
}

IRigidBody*  CFramework::addCrate(const irr::core::vector3df &pos, const irr::core::vector3df &scale, irr::f32 mass, irr::core::map<irr::scene::ISceneNode*, IRigidBody*>& nodeBodyMap)
{

    irr::scene::IAnimatedMeshSceneNode *Node = device->getSceneManager()->addAnimatedMeshSceneNode(device->getSceneManager()->getMesh("MODELS/OTHER/crate.b3d"),0,IDFlag_IsPickable);
    //((irr::scene::ISkinnedMesh*)Node)->convertMeshToTangents();

    Node->setScale(scale);
    Node->setPosition(pos);
    Node->setMaterialType(EMT_SOLID);
    Node->setMaterialFlag(EMF_LIGHTING, true);
    Node->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
    //Node->setMaterialFlag(EMF_ANTI_ALIASING, true);
    //Node->setMaterialFlag(EMF_ANISOTROPIC_FILTER, true);
    //Node->setMaterialFlag(EMF_TRILINEAR_FILTER, true);
    Node->setMaterialFlag(EMF_FOG_ENABLE, true);
    Node->setMaterialTexture(0, m_crateTex);
    //Node->setMaterialTexture(1, device->getVideoDriver()->getTexture("MODELS/OTHER/crate_tex_map.jpg"));
    //Node->addShadowVolumeSceneNode(0,-1,false);


    scene::ITriangleSelector* selector = 0;
    selector = device->getSceneManager()->createTriangleSelector(Node->getMesh(), Node);
    Node->setTriangleSelector(selector);
    selector->drop();
    ICollisionShape *shape = new IBoxShape(Node, mass, false);

    //shape->setMargin(0.01);

    IRigidBody *body;
    body = world->addRigidBody(shape);
    nodeBodyMap[Node] = body;
    return body;
}

IRigidBody* const CFramework::shootCube(const irr::core::vector3df &scale, irr::f32 mass, irr::core::stringc textureFile) const
{
    irr::core::vector3df pos(camera->getPosition().X,camera->getPosition().Y,camera->getPosition().Z);

    irr::scene::ISceneNode *Node = device->getSceneManager()->addCubeSceneNode(1.0f);
    Node->setScale(scale);
    Node->setPosition(pos);
    Node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
    Node->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
    Node->setMaterialTexture(0, device->getVideoDriver()->getTexture(textureFile.c_str()));

    Node->setMaterialFlag(irr::video::EMF_WIREFRAME, drawWireFrame);

    ICollisionShape *shape = new IBoxShape(Node, mass, true);

    //shape->setMargin(0.01);

    IRigidBody *body = world->addRigidBody(shape);

    irr::core::vector3df rot = camera->getRotation();
    irr::core::matrix4 mat;
    mat.setRotationDegrees(rot);
    irr::core::vector3df forwardDir(irr::core::vector3df(mat[8],mat[9],mat[10]) * 120);

    body->setLinearVelocity(forwardDir);
    //body->setActivationState(EAS_DISABLE_DEACTIVATION);

    body->setDamping(0.2,0.2);
    body->setFriction(0.4f);

    //ICollisionObjectAffectorDelete *deleteAffector = new ICollisionObjectAffectorDelete(4000);
    //body->addAffector(deleteAffector);

    body->getAttributes()->addBool("collide", true);

    //ICollisionObjectAffectorAttract* affector = new ICollisionObjectAffectorAttract(irr::core::vector3df(0,1000,0), 2500);
    //ICollisionObjectAffectorAttract* affector = new ICollisionObjectAffectorAttract(device->getSceneManager()->getActiveCamera(), 2500);
    //body->addAffector(affector);

    return body;
}

IRigidBody* const CFramework::shootSphere(const irr::core::vector3df &scale, irr::f32 mass) const
{
    irr::core::vector3df pos(camera->getPosition().X,camera->getPosition().Y,camera->getPosition().Z);
    irr::scene::ISceneNode *Node = device->getSceneManager()->addSphereSceneNode();
    Node->setScale(scale);
    Node->setPosition(pos);
    Node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
    Node->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
    Node->setMaterialTexture(0, device->getVideoDriver()->getTexture("MODELS/OTHER/rockwall.jpg"));

    if(drawWireFrame)
        Node->setMaterialFlag(irr::video::EMF_WIREFRAME, drawWireFrame);

    ICollisionShape *shape = new ISphereShape(Node, mass, true);

    //shape->setMargin(0.01);

    IRigidBody *body = world->addRigidBody(shape);
    body->setDamping(0.2,0.2);

    // Since we use a "bumpy" triangle mesh for the terrain, we need to set the CCD radius and
    // motion threshold to ensure that we don't have any tunneling problems.
    // This doesn't work very well for box shapes.
    // ALSO: If you use setLocalScaling() on the collision shape, be sure to call this again
    // after scaling to make sure that it matches the actual object.

    body->setCcdValues(0.2,0.6);

    irr::core::vector3df rot = camera->getRotation();
    irr::core::matrix4 mat;
    mat.setRotationDegrees(rot);
    irr::core::vector3df forwardDir(irr::core::vector3df(mat[8],mat[9],mat[10]) * 300);

    body->setLinearVelocity(forwardDir);



    //ICollisionObjectAffectorDelete *deleteAffector = new ICollisionObjectAffectorDelete(4000);
    //body->addAffector(deleteAffector);

    return body;
}

irr::scene::IParticleSystemSceneNode* const CFramework::createParticleSystem(const irr::core::vector3df& pos, const irr::core::vector3df& dir, irr::f32 min, irr::f32 max,
        const irr::video::SColor& darkest, const irr::video::SColor& brightest, irr::f32 minAge, irr::f32 maxAge, irr::f32 angle,
        const irr::core::dimension2df& minSize, const irr::core::dimension2df maxSize, const irr::core::stringc& textureFile,
        irr::f32 lifeTime, bool gravity, irr::video::E_MATERIAL_TYPE materialType, bool fadeOut) const
{
    irr::scene::IParticleSystemSceneNode* ps =
        device->getSceneManager()->addParticleSystemSceneNode(false);

    irr::scene::IParticleEmitter* em = ps->createBoxEmitter(
                                           irr::core::aabbox3d<irr::f32>(-3,0,-3,3,1,3), // emitter size
                                           dir,   // initial direction core::vector3df(0.0f,0.01f,0.0f)
                                           min,max,                             // emit rate
                                           darkest,       // darkest color
                                           brightest,       // brightest color
                                           minAge,maxAge,angle,                         // min and max age, angle
                                           minSize,         // min size
                                           maxSize);        // max size

    ps->setEmitter(em); // this grabs the emitter
    em->drop(); // so we can drop it here without deleting it

    if(fadeOut)
    {
        irr::scene::IParticleAffector* paf = ps->createFadeOutParticleAffector();
        ps->addAffector(paf); // same goes for the affector
        paf->drop();
    }

    if(gravity==true)
    {
        irr::scene::IParticleAffector* paf = ps->createGravityAffector(irr::core::vector3df(0.0f,-0.007f, 0.0f), 1800);
        ps->addAffector(paf); // same goes for the affector
        paf->drop();
    }

    ps->setScale(irr::core::vector3df(0.2,0.2,0.2));
    ps->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    ps->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
    ps->setMaterialTexture(0, device->getVideoDriver()->getTexture(textureFile.c_str()));
    ps->setMaterialType(materialType);

    //ps->setParent(info->getBody0()->getCollisionShape()->getSceneNode());
    ps->setPosition(pos);

    if(lifeTime > 0.0f)
    {
        irr::scene::ISceneNodeAnimator* anim = device->getSceneManager()->createDeleteAnimator(lifeTime);
        ps->addAnimator(anim);
        anim->drop();
    }

    return ps;
}



CFramework::~CFramework()
{
}

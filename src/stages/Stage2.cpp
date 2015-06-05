//#include <string>

#include <Urho3D/Urho3D.h>

#include <Urho3D/Graphics/Camera.h>
//#include <Urho3D/Engine/Engine.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Resource/XMLFile.h>

#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Physics/CollisionShape.h>

#include <Urho3D/Graphics/Animation.h>
#include <Urho3D/Graphics/AnimatedModel.h>
#include <Urho3D/Graphics/AnimationState.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Graphics/DebugRenderer.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/Graphics/Light.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/Graphics/Zone.h>

#include "Stage2.h"
#include "../pieces/State.h"
#include "../core/ApplicationHandler.h"
#include "../core/CameraLogic.h"

#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>


Stage2::Stage2(Context* context) :
    Object(context)
{
}

//-------------------
//-------------------
//void Stage2::Setup(SharedPtr<Scene> scene, SharedPtr<Node> cameraNode)
void Stage2::Setup(ApplicationHandler* applicationHandler)
{

    applicationHandler_ = applicationHandler;
	scene_ = applicationHandler->scene_;
	//cameraNode_ = cameraNode;

	ResourceCache* cache = GetSubsystem<ResourceCache>();

    /*for (unsigned j=0; j<50; ++j)
    {
        cache->BackgroundLoadResource("Model",String( "Models/States/state_"+String(j+1)+".001.mdl" ));
        cache->BackgroundLoadResource("Model",String( "Models/States/state_convex_"+String(j+1)+".001.mdl" ));
    }*/

    // Create scene node & StaticModel component for showing a static plane
    /*Node* planeNode = scene_->CreateChild("Plane");
    planeNode->SetScale(Vector3(100.0f, 1.0f, 100.0f));
    StaticModel* planeObject = planeNode->CreateComponent<StaticModel>();
    planeObject->SetModel(cache->GetResource<Model>("Models/Plane.mdl"));
    planeObject->SetMaterial(cache->GetResource<Material>("Materials/StoneTiled.xml"));*/

    // Create a Zone component for ambient lighting & fog control
    Node* zoneNode = scene_->CreateChild("Zone");
    Zone* zone = zoneNode->CreateComponent<Zone>();
    zone->SetBoundingBox(BoundingBox(-1000.0f, 1000.0f));
    zone->SetAmbientColor(Color(0.15f, 0.15f, 0.15f));
    zone->SetFogColor(Color(0.5f, 0.5f, 0.7f));
    zone->SetFogStart(100.0f);
    zone->SetFogEnd(300.0f);

    // Create a directional light to the world. Enable cascaded shadows on it
    Node* lightNode = scene_->CreateChild("DirectionalLight");
    lightNode->SetDirection(Vector3(0.6f, -1.0f, 0.8f));
    Light* light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);
    light->SetCastShadows(true);
    light->SetShadowBias(BiasParameters(0.00025f, 0.5f));
    // Set cascade splits at 10, 50 and 200 world units, fade shadows out at 80% of maximum shadow distance
    light->SetShadowCascade(CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f));

    {

        Node* floorNode = scene_->CreateChild("Floor");
        floorNode->SetPosition(Vector3(0.0f, -1.0f, 0.0f));
        floorNode->SetScale(Vector3(1000.0f, 1.0f, 1000.0f));
        StaticModel* floorObject = floorNode->CreateComponent<StaticModel>();
        floorObject->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
        floorObject->SetMaterial(cache->GetResource<Material>("Materials/StoneTiled.xml"));
        
        // Make the floor physical by adding RigidBody and CollisionShape components. The RigidBody's default
        // parameters make the object static (zero mass.) Note that a CollisionShape by itself will not participate
        // in the physics simulation
        /*RigidBody* body = */floorNode->CreateComponent<RigidBody>();
        CollisionShape* shape = floorNode->CreateComponent<CollisionShape>();
        // Set a box shape of size 1 x 1 x 1 for collision. The shape will be scaled with the scene node scale, so the
        // rendering and physics representation sizes should match (the box model is also 1 x 1 x 1.)
        shape->SetBox(Vector3::ONE);
    }

    for (unsigned j=0; j<50; ++j)
    {
        Node* stateNode = scene_->CreateChild("state");
        /*Vector3 corrected = Vector3(positions_[j].z_,positions_[j].y_,positions_[j].x_)*10.0f;
        stateNode->SetPosition(corrected);
        StaticModel* stateModel = stateNode->CreateComponent<StaticModel>();
        //stateModel->SetModel( cache->GetResource<Model>(String("Models/States/")+states_[j]) );
        stateModel->SetModel( cache->GetResource<Model>(String("Models/States/state_"+String(j+1)+".001.mdl") ) );
        
        RigidBody* body = stateNode->CreateComponent<RigidBody>();
        body->SetMass(1.0f);
        body->SetFriction(0.75f);
        CollisionShape* sshape = stateNode->CreateComponent<CollisionShape>();
        sshape->SetConvexHull(cache->GetResource<Model>(String("Models/States/state_convex_"+String(j+1)+".001.mdl") ));
        //LOGINFO(positions_[j].ToString());

        stateNode->SetPosition(stateNode->GetWorldPosition()+Vector3(0.0f,20.0f+float(j)*0.5,0.0f));
        */

        stateObjs_[j] = stateNode->CreateComponent<State>();
        stateObjs_[j]->Setup(j);
        //Character* character_ = 

    }
    /*Node* stateNode = scene_->CreateChild("state");
    stateNode->SetPosition(positions_[0]);
    StaticModel* stateModel = stateNode->CreateComponent<StaticModel>();
    stateModel->SetModel( cache->GetResource<Model>(String("Models/States/")+states_[0]) );*/

    // Create the camera. Limit far clip distance to match the fog
    //cameraNode_ = scene_->CreateChild("Camera");
    //Camera* camera = cameraNode_->CreateComponent<Camera>();
    //camera->SetFarClip(300.0f);

    // Set an initial position for the camera scene node above the plane
    cameraTarget_ = scene_->CreateChild("CameraTarget");
    cameraTarget_->SetPosition(Vector3(15.0f, 0.0f, 25.0f));
    //cameraNode_->SetPosition(Vector3(0.0f, 5.0f, 0.0f));

    VariantMap camParms;
    camParms["type"] = String("sidescrolling");
    camParms["cameraDistance"] = 50.0f;
    camParms["targetOffset"] = Vector3(0.0f,0.0f,0.0f);
    camParms["orientation"] = Quaternion(45.0f,-90.0f,0.0f);
    //applicationInput_->SetCameraType(String("sidescrolling"));
    applicationHandler->applicationInput_->SetCameraParameters(camParms);
    applicationHandler->applicationInput_->SetCameraTarget(cameraTarget_);

    //give the camera the logic I want
    //CameraLogic* cameralogic = cameraNode_->CreateComponent<CameraLogic>();
}
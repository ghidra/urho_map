#include <Urho3D/Urho3D.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/Scene.h>

#include <Urho3D/IO/MemoryBuffer.h>
#include <Urho3D/Physics/PhysicsEvents.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Scene/SceneEvents.h>

//#include <Urho3D/Graphics/AnimatedModel.h>
//#include <Urho3D/Graphics/AnimationController.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Model.h>

#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Resource/XMLFile.h>

#include <Urho3D/Input/Controls.h>

//-----

//-------

#include "State.h"
#include "StateData.h"
#include "../core/PickingComponent.h"

#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>


State::State(Context* context) :
    Actor(context)
{
    // Only the scene update event is needed: unsubscribe from the rest for optimization
    //SetUpdateEventMask(USE_FIXEDUPDATE);
    //stateData_ = new StateData(context);
}

void State::RegisterObject(Context* context)
{
    context->RegisterFactory<State>();
}

void State::FixedUpdate(float timeStep)
{
    //Actor::FixedUpdate(timeStep); 
    //this is causing shit to fuck up, if i call the above function, its making shit not load up roght
    //LOGINFO("hahah");
    //something
}

void State::Setup(unsigned index,StateData* stateData)
{

    id_ = index;

    name_ = stateData->GetName(index);
    mdl_ = stateData->GetMdl(index);
    home_ = stateData->GetPosition(index);

    //LOGINFO(states_name_[index]);

    ResourceCache* cache = GetSubsystem<ResourceCache>();

    Vector3 corrected = Vector3(home_.z_,home_.y_,home_.x_)*10.0f;
    //Vector3 corrected = Vector3(0.0f,4.0f,0.0f);
    node_->SetPosition(corrected);
    StaticModel* stateModel = node_->CreateComponent<StaticModel>();
    //stateModel->SetModel( cache->GetResource<Model>("Models/States/state_6.001.mdl") );
    stateModel->SetModel( cache->GetResource<Model>(String( "Models/States/state_"+String(index+1)+".001.mdl" ) ) );
    
    RigidBody* body = node_->CreateComponent<RigidBody>();
    body->SetMass(1.0f);
    body->SetFriction(0.75f);
    CollisionShape* sshape = node_->CreateComponent<CollisionShape>();
    sshape->SetConvexHull(cache->GetResource<Model>(String( "Models/States/state_convex_"+String(index+1)+".001.mdl" ) ));
    
    //LOGINFO(home_.ToString());

    node_->CreateComponent<PickingComponent>();

}

void State::HandleNodeCollision(StringHash eventType, VariantMap& eventData)
{
    Actor::HandleNodeCollision(eventType, eventData);
    //
}
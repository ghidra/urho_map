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
//#include "../core/ApplicationInput.h"

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
    /*const String states_mdl_[50] = 
    {
        String("state_1.001.mdl"),
        String("state_2.001.mdl"),
        String("state_3.001.mdl"),
        String("state_4.001.mdl"),
        String("state_5.001.mdl"),
        String("state_6.001.mdl"),
        String("state_7.001.mdl"),
        String("state_8.001.mdl"),
        String("state_9.001.mdl"),
        String("state_10.001.mdl"),
        String("state_11.001.mdl"),
        String("state_12.001.mdl"),
        String("state_13.001.mdl"),
        String("state_14.001.mdl"),
        String("state_15.001.mdl"),
        String("state_16.001.mdl"),
        String("state_17.001.mdl"),
        String("state_18.001.mdl"),
        String("state_19.001.mdl"),
        String("state_20.001.mdl"),
        String("state_21.001.mdl"),
        String("state_22.001.mdl"),
        String("state_23.001.mdl"),
        String("state_24.001.mdl"),
        String("state_25.001.mdl"),
        String("state_26.001.mdl"),
        String("state_27.001.mdl"),
        String("state_28.001.mdl"),
        String("state_29.001.mdl"),
        String("state_30.001.mdl"),
        String("state_31.001.mdl"),
        String("state_32.001.mdl"),
        String("state_33.001.mdl"),
        String("state_34.001.mdl"),
        String("state_35.001.mdl"),
        String("state_36.001.mdl"),
        String("state_37.001.mdl"),
        String("state_38.001.mdl"),
        String("state_39.001.mdl"),
        String("state_40.001.mdl"),
        String("state_41.001.mdl"),
        String("state_42.001.mdl"),
        String("state_43.001.mdl"),
        String("state_44.001.mdl"),
        String("state_45.001.mdl"),
        String("state_46.001.mdl"),
        String("state_47.001.mdl"),
        String("state_48.001.mdl"),
        String("state_49.001.mdl"),
        String("state_50.001.mdl")
    };

    const String states_name_[50] = 
    {
        String("state_1"),
        String("state_2"),
        String("state_3"),
        String("state_4"),
        String("state_5"),
        String("state_6"),
        String("state_7"),
        String("state_8"),
        String("state_9"),
        String("state_10"),
        String("state_11"),
        String("state_12"),
        String("state_13"),
        String("state_14"),
        String("state_15"),
        String("state_16"),
        String("state_17"),
        String("state_18"),
        String("state_19"),
        String("state_20"),
        String("state_21"),
        String("state_22"),
        String("state_23"),
        String("state_24"),
        String("state_25"),
        String("state_26"),
        String("state_27"),
        String("state_28"),
        String("state_29"),
        String("state_30"),
        String("state_31"),
        String("state_32"),
        String("state_33"),
        String("state_34"),
        String("state_35"),
        String("state_36"),
        String("state_37"),
        String("state_38"),
        String("state_39"),
        String("state_40"),
        String("state_41"),
        String("state_42"),
        String("state_43"),
        String("state_44"),
        String("state_45"),
        String("state_46"),
        String("state_47"),
        String("state_48"),
        String("state_49"),
        String("state_50")
    };

    const Vector3 positions_[50] = 
    {
        Vector3(0.21888011694f,0.0156500004232f,2.09723997116f),
        Vector3(2.54229521751f,-0.00904999952763f,1.75292992592f),
        Vector3(2.41885995865f,-0.00999999977648f,1.90676009655f),
        Vector3(0.673485100269f,0.0166000016034f,2.30860519409f),
        Vector3(0.369050145149f,0.0175500009209f,1.11237001419f),
        Vector3(0.516425132751f,0.0185000002384f,0.181779891253f),
        Vector3(0.423860132694f,0.0185000002384f,0.481095075607f),
        Vector3(0.577625155449f,0.0185000002384f,1.04367494583f),
        Vector3(0.837990105152f,0.0185000002384f,1.52935504913f),
        Vector3(0.935640096664f,0.0185000002384f,1.02947998047f),
        Vector3(0.837135195732f,0.0185000002384f,0.446817427874f),
        Vector3(1.17873501778f,0.0185000002384f,0.342575073242f),
        Vector3(1.26694011688f,0.0185000002384f,0.743340015411f),
        Vector3(1.27813506126f,0.0185000002384f,1.56136512756f),
        Vector3(1.73834013939f,0.0175500009209f,1.89084005356f),
        Vector3(1.36196017265f,0.0185000002384f,1.13154006004f),
        Vector3(1.85952007771f,0.0185000002384f,1.51079499722f),
        Vector3(1.88827514648f,0.000450000166893f,1.21628499031f),
        Vector3(1.77227497101f,0.0175500009209f,0.656964957714f),
        Vector3(1.77993512154f,-0.00144999939948f,0.365104973316f),
        Vector3(2.22174501419f,-0.0052499989979f,0.468360185623f),
        Vector3(2.69981503487f,-0.0052499989979f,0.614735066891f),
        Vector3(2.4618601799f,-0.0052499989979f,0.627650141716f),
        Vector3(2.53034496307f,-0.00810000021011f,1.0825150013f),
        Vector3(2.75453519821f,-0.00714999902993f,1.07339000702f),
        Vector3(2.99251008034f,-0.00714999902993f,0.980669975281f),
        Vector3(3.74992036819f,-0.00810000021011f,0.702120065689f),
        Vector3(3.66952991486f,-0.00619999971241f,0.732804954052f),
        Vector3(3.72557497025f,-0.00619999971241f,0.641584992409f),
        Vector3(3.53317499161f,-0.00904999952763f,1.00545012951f),
        Vector3(3.5650601387f,-0.00619999971241f,0.886059999466f),
        Vector3(3.40220499039f,-0.00429999921471f,1.02564501762f),
        Vector3(3.82462024689f,-0.00239999918267f,0.349364906549f),
        Vector3(3.70352506638f,-0.0052499989979f,0.491724967957f),
        Vector3(3.60558986664f,-0.0052499989979f,0.511260032654f),
        Vector3(3.44979000092f,-0.00429999921471f,0.630430102348f),
        Vector3(3.3455851078f,-0.0052499989979f,0.875915110111f),
        Vector3(2.3500752449f,-0.0052499989979f,1.56273007393f),
        Vector3(3.1991353035f,-0.00144999939948f,1.08977997303f),
        Vector3(3.26395010948f,-0.00144999939948f,1.17536497116f),
        Vector3(2.79603528976f,-0.00714999902993f,1.73529994488f),
        Vector3(2.81455516815f,-0.00144999939948f,1.42764496803f),
        Vector3(3.25786995888f,-0.00144999939948f,1.38491988182f),
        Vector3(3.21765995026f,-0.00619999971241f,1.58336496353f),
        Vector3(3.04369020462f,-0.00429999921471f,1.68953490257f),
        Vector3(3.07175517082f,-0.00999999977648f,2.11033010483f),
        Vector3(1.79783010483f,0.0185000002384f,0.926185011864f),
        Vector3(2.24017524719f,-0.00619999971241f,0.882490038872f),
        Vector3(2.32092523575f,-0.0052499989979f,1.23307991028f),
        Vector3(2.81634521484f,-0.00429999921471f,1.25435996056f)
    };*/

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

    //node_->SetPosition(node_->GetWorldPosition()+Vector3(0.0f,2.0f+float(index)*1.5,0.0f));
    

    /*ResourceCache* cache = GetSubsystem<ResourceCache>();

    node_->SetPosition(Vector3(0.0f, 1.0f, 0.0f));//objectNode

    // Create the rendering component + animation controller
    AnimatedModel* object = node_->CreateComponent<AnimatedModel>();
    object->SetModel(cache->GetResource<Model>("Models/"+mesh_));
    //object->SetMaterial(cache->GetResource<Material>("Materials/Jack.xml"));
    object->SetCastShadows(true);
    node_->CreateComponent<AnimationController>();

    // Set the head bone for manual control
    //object->GetSkeleton().GetBone("Bip01_Head")->animated_ = false;

    // Create rigidbody, and set non-zero mass so that the body becomes dynamic
    RigidBody* body = node_->CreateComponent<RigidBody>();
    body->SetCollisionLayer(collision_layer_);
    body->SetCollisionMask(collision_mask_);
    body->SetMass(1.0f);

    // Set zero angular factor so that physics doesn't turn the character on its own.
    // Instead we will control the character yaw manually
    body->SetAngularFactor(Vector3::ZERO);

    // Set the rigidbody to signal collision also when in rest, so that we get ground collisions properly
    body->SetCollisionEventMode(COLLISION_ALWAYS);

    //we still need to setup the collisionshape in the child class
    */
}

void State::HandleNodeCollision(StringHash eventType, VariantMap& eventData)
{
    Actor::HandleNodeCollision(eventType, eventData);
    //
}
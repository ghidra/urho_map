#include <Urho3D/Urho3D.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/Scene.h>

#include <Urho3D/IO/MemoryBuffer.h>
#include <Urho3D/Physics/PhysicsEvents.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Scene/SceneEvents.h>

#include <Urho3D/Input/Controls.h>

#include "Actor.h"
#include "../core/ApplicationInput.h"

#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>


Actor::Actor(Context* context) :
    LogicComponent(context)//,
    //collision_layer_(1),
    //collision_mask_(60)
{
    // Only the scene update event is needed: unsubscribe from the rest for optimization
    SetUpdateEventMask(USE_FIXEDUPDATE);
}

void Actor::FixedUpdate(float timeStep)
{
    //LOGINFO("inside actor fixedupdate");
	timeIncrement_+=timeStep;
    // Disappear when duration expired
    if (duration_ >= 0){
      duration_ -= timeStep;
      if (duration_ <= 0)
          node_->Remove();
    }
}

void Actor::HandleNodeCollision(StringHash eventType, VariantMap& eventData)
{
    // Check collision contacts and see if character is standing on ground (look for a contact that has near vertical normal)
    using namespace NodeCollision;
    
    MemoryBuffer contacts(eventData[P_CONTACTS].GetBuffer());
    
    while (!contacts.IsEof())
    {
        Vector3 contactPosition = contacts.ReadVector3();
        Vector3 contactNormal = contacts.ReadVector3();
        /*float contactDistance = */contacts.ReadFloat();
        /*float contactImpulse = */contacts.ReadFloat();
        
        // If contact is below node center and mostly vertical, assume it's a ground contact
        if (contactPosition.y_ < (node_->GetPosition().y_ + 1.0f))
        {
            float level = Abs(contactNormal.y_);
            if (level > 0.75)
                onGround_ = true;
        }
    }
}
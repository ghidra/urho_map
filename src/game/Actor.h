#ifndef ACTOR_H
#define ACTOR_H

#pragma once

#include <Urho3D/Scene/LogicComponent.h>
#include "../core/ApplicationInput.h"

using namespace Urho3D;

/// Custom logic component for moving the animated model and rotating at area edges.
class Actor : public LogicComponent
{
    OBJECT(Actor);
    
public:
    Actor(Context* context);

    virtual void FixedUpdate(float timeStep);
    
protected:

    virtual void HandleNodeCollision(StringHash eventType, VariantMap& eventData);

    ApplicationInput* applicationInput_ = NULL;

    String mesh_;
    String mesh_convex_;
    String material_;
  
    bool onGround_;
    bool isSliding_;
    float duration_;
    float timeIncrement_;

    uint creatorID_;

    uint collision_layer_;//=1;
    uint collision_mask_;//=60;
};
#endif
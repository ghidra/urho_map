#ifndef STATE_H
#define STATE_H

#pragma once

#include "../game/Actor.h"
//#include "../core/ApplicationInput.h"

using namespace Urho3D;

namespace Urho3D
{

class Node;
class Scene;

}

class State : public Actor
{

    OBJECT(State);

public:

    State(Context* context);

    static void RegisterObject(Context* context);
    virtual void FixedUpdate(float timeStep);
    virtual void Setup(uint index);

protected:

    virtual void HandleNodeCollision(StringHash eventType, VariantMap& eventData);

    ApplicationInput* applicationInput_ = NULL;

private:

    int id_;

    const String states_mdl_[50];
    const String states_name_[50];
    const Vector3 positions_[50];
    //stored data from stateData
    String name_;
    String mdl_;
    Vector3 home_;

   
};
#endif
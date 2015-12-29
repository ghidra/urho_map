#ifndef STATE_H
#define STATE_H

#pragma once

#include "../game/Actor.h"
#include "StateData.h"
//#include "../core/ApplicationInput.h"

using namespace Urho3D;

namespace Urho3D
{

class Node;
class Scene;

}

class State : public Actor
{

    URHO3D_OBJECT(State, Actor);

public:

    State(Context* context);

    static void RegisterObject(Context* context);
    virtual void FixedUpdate(float timeStep);
    virtual void Setup(unsigned index, StateData* stateData);

protected:

    virtual void HandleNodeCollision(StringHash eventType, VariantMap& eventData);

    //ApplicationInput* applicationInput_ = NULL;

private:

    unsigned id_;

    //stored data from stateData
    String name_;
    String mdl_;
    Vector3 home_;

   
};
#endif
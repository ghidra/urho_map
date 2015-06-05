#ifndef STAGE2_H
#define STAGE2_H

#pragma once

//#include <string>
#include <Urho3D/Core/Object.h>
#include "../core/ApplicationHandler.h"
#include "../pieces/State.h"

using namespace Urho3D;

namespace Urho3D
{

class Node;
class Scene;

}

class Stage2 : public Object
{

    OBJECT(Stage2);

public:

    Stage2(Context* context);

    //virtual void Setup(SharedPtr<Scene> scene, SharedPtr<Node> cameraNode);
    virtual void Setup(ApplicationHandler* applicationHandler);

    SharedPtr<Node> cameraTarget_;

protected:

    SharedPtr<Scene> scene_;
    //SharedPtr<Node> cameraNode_;
    ApplicationHandler* applicationHandler_;

    State* stateObjs_[50]; 
    
};
#endif
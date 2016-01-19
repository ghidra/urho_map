#ifndef DRAGGABLE_H
#define DRAGGABLE_H

#pragma once

#include "../core/PickingComponent.h"

using namespace Urho3D;

namespace Urho3D
{

class Node;
class Scene;

}

class Draggable : public PickingComponent
{

    URHO3D_OBJECT(Draggable, PickingComponent);

public:

    Draggable(Context* context);
    ~Draggable();

    static void RegisterObject(Context* context);
    
    //void HoverOver();
    void UnHoverOver();

    void SetPickPosition(const Vector3 pos);

//protected:
    //void OnNodeSet(Node* node);
    //void HandleUpdate(StringHash eventType, VariantMap& eventData);

//private:

    //unsigned id_;

    //stored data from stateData
    //String name_;
    //String mdl_;
    //Vector3 home_;

   
};
#endif
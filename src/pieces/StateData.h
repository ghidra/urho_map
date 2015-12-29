#ifndef STATEDATA_H
#define STATEDATA_H

#pragma once

#include <Urho3D/Container/Vector.h>
#include <Urho3D/Container/Str.h>

#include <Urho3D/Core/Object.h>

using namespace Urho3D;

/*namespace Urho3D
{
    class Controls;
    class Engine;
    class Node;
}*/


class StateData : public Object
{
    URHO3D_OBJECT(StateData, Object);

public:
    /// Construct.
    StateData(Context* context);

    String GetName(unsigned i){return stateNames_[i];}
    String GetMdl(unsigned i){return stateMdls_[i];}
    Vector3 GetPosition(unsigned i){return statePositions_[i];}

private:
    //void Init();
    Vector<String> stateNames_;
    //const String stateNames_[50];
    //const String stateMdls_[50];
    Vector<String> stateMdls_;
    //const Vector3 statePositions_[50];
    Vector<Vector3> statePositions_; 

};
#endif
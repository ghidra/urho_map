#ifndef APPLICATIONINPUT_H
#define APPLICATIONINPUT_H

#pragma once

#include <Urho3D/Input/Controls.h>
#include <Urho3D/Core/Object.h>

#include "CameraLogic.h"

//#include "Actor.h"
//#include "ApplicationHandler.h"

using namespace Urho3D;

namespace Urho3D
{
    class Controls;
    class Engine;
    class Node;
    class Ray;
}

const int CTRL_UP = 1;
const int CTRL_DOWN = 2;
const int CTRL_LEFT = 4;
const int CTRL_RIGHT = 8;
const int CTRL_FIRE = 16;
const int CTRL_JUMP = 32;
const int CTRL_ALL = 63;


class ApplicationInput : public Object
{
    URHO3D_OBJECT(ApplicationInput, Object);

public:
    /// Construct.
    ApplicationInput(Context* context);

    bool GetQuit(){return quit_;};
    Ray GetMouseRay() const;

    void SetCameraNode(SharedPtr<Node> cameraNode);
    //these all just get passes along
    void SetCameraTarget(SharedPtr<Node> target);//whom the camera should target
    void SetCameraType(const String& cameraType );
    void SetCameraParameters(const float distance, const float distance_min = 1.0f, const float distance_max = 20.0f, const Quaternion orientation = Quaternion(30.0f,0.0f,0.0f) );
    void SetCameraParameters( VariantMap& parms );

    //void Possess(Actor* actor);

    void HandleUpdate(StringHash eventType, VariantMap& eventData);//this is called from outside this class
    void UpdateHover();// called during Update

    Controls controls_;

    bool IsDebugCamera(){return debugCamera_;}
    bool IsDebugDrawPhysics(){return debugDrawPhysics_;}
private:
    /// Construct a new Text instance, containing the 'Hello World' String, and add it to the UI root element.
    //void CreateText();
    //void SetParameters(SharedPtr<Engine>& engine, ApplicationHandler* applicationHandler);
    /// Subscribe to application-wide logic update events.
    void InitTouchInput();
    /// Handle the logic update event.
    void HandleKeyDown(StringHash eventType, VariantMap& eventData);

    //
    void HandleTouchBegin(StringHash eventType, VariantMap& eventData);

    virtual String GetScreenJoystickPatchString() const { return String::EMPTY; }

    void UpdateGrab();

    /// Movement controls. Assigned by the main program each frame.
    

    //SharedPtr<Actor> actor_;

    bool touchEnabled_;
    /// Screen joystick index for navigational controls (mobile platforms only).
    unsigned screenJoystickIndex_;
    /// Screen joystick index for settings (mobile platforms only).
    unsigned screenJoystickSettingsIndex_;

    bool paused_;
    bool quit_;
    //debug bools
    bool debugCamera_;
    bool debugDrawPhysics_;

    SharedPtr<Node> cameraNode_;
    CameraLogic* cameraLogic_;//i might not need to store this in the end
    String cameraType_;//store this hear because when i use the debug camera to go into debug view, i need to be able to switch it back, so this stores it

    /// Touch sensitivity.
    float touchSensitivity_;
    /// Current camera zoom distance.
    
    /// Zoom flag.
    //bool zoom_;
    /// Gyroscope on/off flag.
    bool useGyroscope_;


};
#endif
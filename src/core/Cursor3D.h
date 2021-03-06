#pragma once

//#define CURSOR3D_DEBUG

#include "ApplicationHandler.h"

#include <Urho3D/Urho3D.h>
#include <Urho3D/Core/Variant.h>
#include <Urho3D/Scene/Component.h>
#include <Urho3D/Math/Plane.h>
#include <Urho3D/Scene/Node.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Physics/RigidBody.h>

class ApplicationHandler;

namespace Urho3D {
class StringHash;
}

class Cursor3D : public Urho3D::Component {
URHO3D_OBJECT(Cursor3D, Urho3D::Component);

public:
    Cursor3D(Urho3D::Context* context);
    ~Cursor3D();
    static void RegisterObject(Urho3D::Context* context);

    /// Scene node representing the actual 3D cursor, automatically created.
    Urho3D::SharedPtr<Urho3D::Node> cursorNode_;
    /// Plane whose transform matches the node's each scene update.
    Urho3D::Plane hitPlane_;
    Urho3D::Plane hitPlaneSecondary_;

    void SetSecondaryPlane(const Vector3 normal, const Vector3 position, const bool use = true);
    void SetUseSecondary(const bool use);
    bool GetUseSecondary(){return useSecondary_;};

    Vector3 GetCursorWorldPosition();
    void SetConstrainee(RigidBody* body);
    void ReleaseConstrainee();

protected:
    void OnNodeSet(Urho3D::Node* node);
    void HandleUpdate(Urho3D::StringHash eventType, Urho3D::VariantMap& eventData);
#if defined(CURSOR3D_DEBUG)
    void HandleKeyDown(StringHash eventType, VariantMap& eventData);
#endif
    ApplicationHandler* appHandler_;
    Urho3D::SharedPtr<Urho3D::Graphics> graphics_;
    Urho3D::SharedPtr<Urho3D::Input> input_;

    bool useSecondary_;

    Vector2 position_;
    float hitDistance_;
    bool constrained_;
    //Urho3D::SharedPtr<Urho3D::RigidBody> constrainee_;

    void ProjectPosition();
};

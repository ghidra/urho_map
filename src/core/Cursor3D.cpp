#include "Cursor3D.h"
#include "ApplicationHandler.h"

#include <Urho3D/Core/Context.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Core/Variant.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Math/StringHash.h>
#include <Urho3D/Scene/Node.h>
#include <Urho3D/Scene/Scene.h>

#if defined(CURSOR3D_DEBUG)
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/Engine/DebugHud.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/DebugRenderer.h>
#include <Urho3D/IO/Log.h>
#endif

using namespace Urho3D;

Cursor3D::Cursor3D(Context* context) :
   Component(context)
    , appHandler_(GetSubsystem<ApplicationHandler>())
    , graphics_(GetSubsystem<Graphics>())
    , input_(GetSubsystem<Input>())
    , useSecondary_(false)
{
}

Cursor3D::~Cursor3D() {
}

void Cursor3D::RegisterObject(Context* context) {
    context->RegisterFactory<Cursor3D>();
}

void Cursor3D::OnNodeSet(Node* node) {
    if (!node)
      return;

    // Create a node representing our 3D cursor.
    cursorNode_ = node->GetScene()->CreateChild("Cursor3D");

    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(Cursor3D, HandleUpdate));
#if defined(CURSOR3D_DEBUG)
    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(Cursor3D, HandleKeyDown));
#endif
}

void Cursor3D::HandleUpdate(StringHash eventType, VariantMap& eventData) {
    if (!input_->GetMouseButtonDown(MOUSEB_LEFT))
        return;

    // Set a new Cursor3D node position from mouse coordinates and plane distance from camera.
    IntVector2 mousePos(input_->GetMousePosition());
    float posX((float)mousePos.x_ / graphics_->GetWidth());
    float posY((float)mousePos.y_ / graphics_->GetHeight());
    Node* camNode(appHandler_->cameraNode_);
    Camera* cam(camNode->GetComponent<Camera>());
    Ray ray(cam->GetScreenRay(posX, posY));
#if defined(CURSOR3D_DEBUG)
        GetSubsystem<DebugHud>()->SetAppStats("mouse pos", String(mousePos.x_ )+":"+String(mousePos.y_ ) );
        GetSubsystem<DebugHud>()->SetAppStats("mouse pos graphics", String(posX )+":"+String(posY) );
        GetSubsystem<DebugHud>()->SetAppStats("ray origin", String(ray.origin_) );
        GetSubsystem<DebugHud>()->SetAppStats("ray direction", String(ray.direction_) );
#endif

    float hitDist;
    Vector3 planeNormal;

    if(useSecondary_)
    {
#if defined(CURSOR3D_DEBUG)
        GetSubsystem<DebugHud>()->SetAppStats("use secondary", String("true"));
#endif
        hitDist = ray.HitDistance(hitPlaneSecondary_);
    }
    else
    {
#if defined(CURSOR3D_DEBUG)
        GetSubsystem<DebugHud>()->SetAppStats("use secondary", String("false"));
#endif
        //use the default plane
        // Make our hit plane's transform reflect that of our node.
        planeNormal = node_->GetWorldRotation() * Vector3::FORWARD;
        hitPlane_.Define(planeNormal, node_->GetWorldPosition());
        hitDist = ray.HitDistance(hitPlane_);
    }
    
    Vector3 cursorPos(cam->ScreenToWorldPoint(Vector3(posX, posY, hitDist)));
    cursorNode_->SetWorldPosition(cursorPos);

#if defined(CURSOR3D_DEBUG)
    GetSubsystem<DebugHud>()->SetAppStats("cursor hitDist", hitDist);
    GetSubsystem<DebugHud>()->SetAppStats("cursor pos", cursorPos);
    node_->GetScene()->GetComponent<DebugRenderer>()->AddNode(node_, 4.0f);
    node_->GetScene()->GetComponent<DebugRenderer>()->AddNode(cursorNode_);
    GetSubsystem<Renderer>()->DrawDebugGeometry(false);
#endif
}

void Cursor3D::SetSecondaryPlane(const Vector3 normal, const Vector3 position, const bool use)
{
    hitPlaneSecondary_.Define(normal, position);
    SetUseSecondary(use);
}

void Cursor3D::SetUseSecondary(const bool use)
{
    useSecondary_ = use;
}

#if defined(CURSOR3D_DEBUG)
void Cursor3D::HandleKeyDown(StringHash eventType, VariantMap& eventData) {
    using namespace KeyDown;
    int key = eventData[P_KEY].GetInt();
    if (key == KEY_KP_8) {
        node_->Pitch(10.0f);
    } else if (key == KEY_KP_2) {
        node_->Pitch(-10.0f);
    } else if (key == KEY_KP_4) {
        node_->Yaw(-10.0f);
    } else if (key == KEY_KP_6) {
        node_->Yaw(10.0f);
    } else if (key == KEY_KP_0) {
        node_->SetPosition(Vector3::ZERO); // plane distance
        node_->SetRotation(Quaternion::IDENTITY);
    } else if (key == KEY_KP_MINUS) {
        node_->Translate(Vector3::BACK);
    } else if (key == KEY_KP_PLUS) {
        node_->Translate(Vector3::FORWARD);
    }
    URHO3D_LOGINFO(String("CursorBase pos ") + String(node_->GetPosition()) + " rot " + String(node_->GetRotation().EulerAngles()));
}
#endif

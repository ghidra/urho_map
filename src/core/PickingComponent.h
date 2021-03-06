#pragma once
#include <Urho3D/Urho3D.h>
#include <Urho3D/Core/Object.h>
#include <Urho3D/Scene/Component.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Math/StringHash.h>
#include <Urho3D/Scene/Node.h>
#include <Urho3D/UI/Text.h>
//#include <Urho3D/Physics/RigidBody.h>

using namespace Urho3D;

namespace Urho3D {
class Context;
class Node;
class Text;
class Graphics;
class Renderer;
}

//URHO3D_EVENT(E_HOVEROVER, HoverOver) {}
//URHO3D_EVENT(E_UNHOVEROVER, UnHoverOver) {}

class PickingComponent: public Component {
  URHO3D_OBJECT(PickingComponent, Component);

public:
  PickingComponent(Context* context);
  ~PickingComponent();

  static void RegisterObject(Context* context);

  void HoverOver();
  void UnHoverOver();

  void SetPickPosition(const Vector3 pos);

protected:
  void OnNodeSet(Node* node);
  void HandleUpdate(StringHash eventType, VariantMap& eventData);

  SharedPtr<Node> textNode_;
  SharedPtr<Text> text_;
  Graphics* graphics_;
  Renderer* renderer_;

  Vector3 pickPosition_;
};

#pragma once
#include <Urho3D/Urho3D.h>
#include <Urho3D/Core/Object.h>
#include <Urho3D/Scene/Component.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Math/StringHash.h>
#include <Urho3D/Scene/Node.h>
#include <Urho3D/UI/Text.h>

using namespace Urho3D;

namespace Urho3D {
class Context;
class Node;
class Text;
class Graphics;
class Renderer;
}

EVENT(E_HOVEROVER, HoverOver) {}
EVENT(E_UNHOVEROVER, UnHoverOver) {}

class PickingComponent: public Component {
  OBJECT(PickingComponent);

public:
  PickingComponent(Context* context);
  ~PickingComponent();

  static void RegisterObject(Context* context);

protected:
  void OnNodeSet(Node* node);
  void HandleUpdate(StringHash eventType, VariantMap& eventData);
  void HandleHoverOver(StringHash eventType, VariantMap& eventData);
  void HandleUnHoverOver(StringHash eventType, VariantMap& eventData);

protected:
  SharedPtr<Node> textNode_;
  SharedPtr<Text> text_;
  Graphics* graphics_;
  Renderer* renderer_;
};

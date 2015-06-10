#include "PickingComponent.h"

#include <Urho3D/Core/Context.h>
#include <Urho3D/Math/BoundingBox.h>
#include <Urho3D/Graphics/AnimatedModel.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Scene/Node.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Core/Object.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/Math/Vector2.h>
#include <Urho3D/Graphics/Viewport.h>

#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>


PickingComponent::PickingComponent(Context* context):
  Component(context), textNode_(NULL), text_(NULL), graphics_(GetSubsystem<Graphics>()), renderer_(GetSubsystem<Renderer>()) {
}
PickingComponent::~PickingComponent() {
}
void PickingComponent::RegisterObject(Context* context) {
  context->RegisterFactory<PickingComponent>();
}

void PickingComponent::OnNodeSet(Node* node) {
  if (!node) return;

  textNode_ = node->CreateChild();

  text_ = new Text(context_);
  GetSubsystem<UI>()->GetRoot()->AddChild(text_);
  text_->SetStyleAuto();
  text_->SetFont("Fonts/Ubuntu-R.ttf", 12);
  text_->SetColor(Color(1.0f, 1.0f, 0.0f));
  text_->SetAlignment(HA_CENTER, VA_CENTER);
  text_->SetTextEffect(TE_SHADOW);

  SubscribeToEvent(E_UPDATE, HANDLER(PickingComponent, HandleUpdate));
  //node_->SubscribeToEvent(E_HOVEROVER, HANDLER(PickingComponent, HandleHoverOver));
  //node_->SubscribeToEvent(node, E_UNHOVEROVER, HANDLER(PickingComponent, HandleUnHoverOver));
}

void PickingComponent::HandleUpdate(StringHash eventType, VariantMap& eventData) {
  Viewport* viewport = renderer_->GetViewport(0);
  IntVector2 textPos = viewport->WorldToScreenPoint(textNode_->GetPosition());
  textPos.x_ -= graphics_->GetWidth() / 2;
  textPos.y_ -= graphics_->GetHeight() / 2;
  text_->SetPosition(textPos);
}

//void PickingComponent::HandleHoverOver(StringHash eventType, VariantMap& eventData) {
void PickingComponent::HoverOver() {
  /*Drawable* drawable = static_cast<Drawable*>(node_->GetComponent<StaticModel>());
  if (!drawable) {
    drawable = static_cast<Drawable*>(node_->GetComponent<AnimatedModel>());
  }
  if (drawable) {
    BoundingBox box = drawable->GetBoundingBox();
    textNode_->SetPosition(node_->GetPosition() + Vector3(0, box.Size().y_, 0));
  }*/
  textNode_->SetPosition(node_->GetPosition());
  text_->SetText(node_->GetName());

//    SubscribeToEvent(node_, E_UPDATE, HANDLER(PickingComponent, HandleUpdate));
}

//void PickingComponent::HandleUnHoverOver(StringHash eventType, VariantMap& eventData) {
void PickingComponent::UnHoverOver() {
  text_->SetText("");

//    UnsubscribeFromEvent(node_, E_UPDATE);
}

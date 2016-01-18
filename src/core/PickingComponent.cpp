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
#include <Urho3D/Physics/RigidBody.h>

#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Engine/DebugHud.h>


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

  SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(PickingComponent, HandleUpdate));
  //node_->SubscribeToEvent(E_HOVEROVER, URHO3D_HANDLER(PickingComponent, HandleHoverOver));
  //node_->SubscribeToEvent(node, E_UNHOVEROVER, URHO3D_HANDLER(PickingComponent, HandleUnHoverOver));
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

  GetSubsystem<DebugHud>()->SetAppStats(" Pickinging offset: ", String(pickPosition_) );

  Drawable* drawable = static_cast<Drawable*>(node_->GetComponent<StaticModel>());
  if (!drawable) {
    drawable = static_cast<Drawable*>(node_->GetComponent<AnimatedModel>());
  }
  if (drawable) {
    //URHO3D_LOGWARNING("happy");
    BoundingBox box = drawable->GetBoundingBox();
    textNode_->SetPosition(node_->GetPosition() + Vector3(0, box.Size().y_, 0));
  }
  //textNode_->SetPosition(node_->GetPosition());
  text_->SetText(node_->GetName());

//    SubscribeToEvent(node_, E_UPDATE, URHO3D_HANDLER(PickingComponent, HandleUpdate));
}

//void PickingComponent::HandleUnHoverOver(StringHash eventType, VariantMap& eventData) {
void PickingComponent::UnHoverOver() {
  text_->SetText("");

  //reset the angular factor
  RigidBody* rb = node_->GetComponent<RigidBody>();
  rb->SetAngularFactor(Vector3(1.0f,1.0f,1.0f));

//    UnsubscribeFromEvent(node_, E_UPDATE);
}
/*RigidBody* PickingComponent::GetBody()
{
  //GetSubsystem<DebugHud>()->SetAppStats(" Pickinging NODE: ", String(node_->GetComponent<RigidBody>()->GetPosition()) );
  return node_->GetComponent<RigidBody>();
}*/
void PickingComponent::SetPickPosition(const Vector3 pos)
{
  //this is called when the object is initially picked...
  //position might be irrelevant.. but I can set the orientation and angular factor
  pickPosition_=pos;
  ///
  RigidBody* rb = node_->GetComponent<RigidBody>();
  rb->SetAngularFactor(Vector3(0.0f,0.0f,0.0f));

  node_->SetRotation(Quaternion());
}

void PickingComponent::Drag(const Vector3 pos)
{
  //pickPosition_=pos;
}
#include "Draggable.h"

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


Draggable::Draggable(Context* context):
  PickingComponent(context)
{
}
Draggable::~Draggable() {
}
void Draggable::RegisterObject(Context* context) {
  context->RegisterFactory<Draggable>();
}

/*void Draggable::OnNodeSet(Node* node) {
  if (!node) return;

  textNode_ = node->CreateChild();

  text_ = new Text(context_);
  GetSubsystem<UI>()->GetRoot()->AddChild(text_);
  text_->SetStyleAuto();
  text_->SetFont("Fonts/Ubuntu-R.ttf", 12);
  text_->SetColor(Color(1.0f, 1.0f, 0.0f));
  text_->SetAlignment(HA_CENTER, VA_CENTER);
  text_->SetTextEffect(TE_SHADOW);

  SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(Draggable, HandleUpdate));
  //node_->SubscribeToEvent(E_HOVEROVER, URHO3D_HANDLER(PickingComponent, HandleHoverOver));
  //node_->SubscribeToEvent(node, E_UNHOVEROVER, URHO3D_HANDLER(PickingComponent, HandleUnHoverOver));
}

void Draggable::HandleUpdate(StringHash eventType, VariantMap& eventData) {
  Viewport* viewport = renderer_->GetViewport(0);
  IntVector2 textPos = viewport->WorldToScreenPoint(textNode_->GetPosition());
  textPos.x_ -= graphics_->GetWidth() / 2;
  textPos.y_ -= graphics_->GetHeight() / 2;
  text_->SetPosition(textPos);
}
*/
/*

//void PickingComponent::HandleHoverOver(StringHash eventType, VariantMap& eventData) {
void Draggable::HoverOver() {

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
*/

//void PickingComponent::HandleUnHoverOver(StringHash eventType, VariantMap& eventData) {
void Draggable::UnHoverOver() {
  PickingComponent::UnHoverOver();

  //reset the angular factor
  RigidBody* rb = node_->GetComponent<RigidBody>();
  rb->SetAngularFactor(Vector3(1.0f,1.0f,1.0f));

}

void Draggable::SetPickPosition(const Vector3 pos)
{
  PickingComponent::SetPickPosition(pos);
  ///
  RigidBody* rb = node_->GetComponent<RigidBody>();
  rb->SetAngularFactor(Vector3(0.0f,0.0f,0.0f));

  node_->SetRotation(Quaternion());
  Vector3 wp =  node_->GetWorldPosition();
  node_->SetWorldPosition(Vector3(wp.x_,1.0f,wp.z_));
}
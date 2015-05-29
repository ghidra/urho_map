#include <Urho3D/Urho3D.h>


#include <Urho3D/Engine/Application.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Engine/Console.h>
#include <Urho3D/UI/Cursor.h>
#include <Urho3D/Engine/DebugHud.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>
#include <Urho3D/UI/Sprite.h>
#include <Urho3D/Graphics/Texture2D.h>
#include <Urho3D/Core/Timer.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/Resource/XMLFile.h>


#include <Urho3D/Core/CoreEvents.h>
//#include <Urho3D/Engine/Engine.h>
#include <Urho3D/UI/Font.h>
//#include <Urho3D/Input/Input.h>
#include <Urho3D/Core/ProcessUtils.h>
#include <Urho3D/UI/Text.h>
//#include <Urho3D/UI/UI.h>

#include "Main.h"
#include "stages/Stage2.h"
//#include "core/ApplicationInput.h"


#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>


// Expands to this example's entry-point
DEFINE_APPLICATION_MAIN(Main)

Main::Main(Context* context) :
    ApplicationHandler(context)
{
}

//-------------------
//-------------------
void Main::Start()
{
    // Execute base class startup
    ApplicationHandler::Start();

    applicationInput_ = new ApplicationInput(context_);
    SetApplicationInput(applicationInput_);

    stage_ = new Stage2(context_);
    stage_->Setup(scene_, cameraNode_);

}

void Main::SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent(E_UPDATE, HANDLER(Main, HandleUpdate));
}

void Main::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    // Do nothing for now, could be extended to eg. animate the display
}

#include <Urho3D/Urho3D.h>

#include <Urho3D/Input/Controls.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Graphics/Renderer.h>

#include <Urho3D/Engine/Application.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Engine/Console.h>
#include <Urho3D/UI/Cursor.h>
#include <Urho3D/Engine/DebugHud.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/Math/Ray.h>
#include <Urho3D/Graphics/Octree.h>

#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>
#include <Urho3D/UI/Sprite.h>
#include <Urho3D/Graphics/Texture2D.h>
#include <Urho3D/Core/Timer.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/Resource/XMLFile.h>

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Graphics/DebugRenderer.h>

//#include <Urho3D/Core/StringHash.h>
//#include <Urho3D/Core/Variant.h>

#include "ApplicationInput.h"
#include "CameraLogic.h"
#include "ApplicationHandler.h"
#include "PickingComponent.h"
#include "Cursor3D.h"

#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>

ApplicationInput::ApplicationInput(Context* context):
    Object(context),
    touchSensitivity_(2.0f),
    paused_(false),
    quit_(false),
    debugCamera_(false),
    debugDrawPhysics_(false),
    hoverEnabled_(false),
    hoverGrabEnabled_(true),
    hoverNode_(NULL)
{
    if (GetPlatform() == "Android" || GetPlatform() == "iOS")
        // On mobile platform, enable touch by adding a screen joystick
        InitTouchInput();
    else if (GetSubsystem<Input>()->GetNumJoysticks() == 0)
        // On desktop platform, do not detect touch when we already got a joystick
        SubscribeToEvent(E_TOUCHBEGIN, URHO3D_HANDLER(ApplicationInput, HandleTouchBegin));

    // Subscribe key down event
    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(ApplicationInput, HandleKeyDown));
    // Subscribe scene update event
    //SubscribeToEvent(E_SCENEUPDATE, URHO3D_HANDLER(ApplicationInput, HandleSceneUpdate));
    //update is called from the class using this class to ahndle input, main.cpp
}

//void ApplicationInput::SetParameters(ApplicationHandler * applicationHandler)
//{
//    applicationHandler_ = applicationHandler;
//}
void ApplicationInput::SetCameraNode(SharedPtr<Node> cameraNode)
{
    cameraNode_ = cameraNode;
    cameraLogic_ = cameraNode_->CreateComponent<CameraLogic>();
    //cameraLogic_->SetCameraType(cameraType);
}
void ApplicationInput::SetCameraTarget(SharedPtr<Node> target)
{
    cameraLogic_->SetCameraTarget(target);
}
void ApplicationInput::SetCameraType(const String& cameraType)
{
    cameraLogic_->SetCameraType(cameraType);
    cameraType_ = cameraType;
}
void ApplicationInput::SetCameraParameters(const float distance, const float distance_min, const float distance_max, const Quaternion orientation)
{
    cameraLogic_->SetCameraParameters(distance,distance_max,distance_min,orientation);
}
void ApplicationInput::SetCameraParameters( VariantMap& parms )
{
    cameraLogic_->SetCameraParameters( parms );
}

/*void ApplicationInput::Possess(Actor* actor)
{
    actor_ = actor;
}*/

void ApplicationInput::InitTouchInput()
{
    touchEnabled_ = true;

    ResourceCache* cache = GetSubsystem<ResourceCache>();
    Input* input = GetSubsystem<Input>();
    XMLFile* layout = cache->GetResource<XMLFile>("UI/ScreenJoystick_Samples.xml");
    const String& patchString = GetScreenJoystickPatchString();
    if (!patchString.Empty())
    {
        // Patch the screen joystick layout further on demand
        SharedPtr<XMLFile> patchFile(new XMLFile(context_));
        if (patchFile->FromString(patchString))
            layout->Patch(patchFile);
    }
    screenJoystickIndex_ = input->AddScreenJoystick(layout, cache->GetResource<XMLFile>("UI/DefaultStyle.xml"));
    input->SetScreenJoystickVisible(screenJoystickSettingsIndex_, true);
}

void ApplicationInput::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;

    Input* input = GetSubsystem<Input>();

    controls_.Set(CTRL_UP | CTRL_DOWN | CTRL_LEFT | CTRL_RIGHT | CTRL_FIRE |CTRL_JUMP, false);

    //URHO3D_LOGINFO("hi");

    //if(actor_)
    //{
        /*this is from character demo for touch controls, which might be worth using here
        // Update controls using touch utility class
        if (touch_)
            touch_->UpdateTouches(character_->controls_);
        */
    UI* ui = GetSubsystem<UI>();
    if (!ui->GetFocusElement())
    {
        UpdateHover();
        UpdateGrab();

        //if (!touch_ || !touch_->useGyroscope_)
        //{
        controls_.Set(CTRL_UP, input->GetKeyDown('W'));
        controls_.Set(CTRL_DOWN, input->GetKeyDown('S'));
        controls_.Set(CTRL_LEFT, input->GetKeyDown('A'));
        controls_.Set(CTRL_RIGHT, input->GetKeyDown('D'));
        //}
        if(input->GetKeyDown(KEY_LCTRL) || input->GetKeyPress(KEY_RCTRL) || input->GetMouseButtonDown(MOUSEB_LEFT) || input->GetMouseButtonPress(MOUSEB_LEFT) )
        {
            controls_.Set(CTRL_FIRE, true);
        }
        controls_.Set(CTRL_JUMP, input->GetKeyDown(KEY_SPACE));

    }

}

void ApplicationInput::HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
    using namespace KeyDown;

    int key = eventData[P_KEY].GetInt();

    // Close console (if open) or exit when ESC is pressed
    if (key == KEY_ESC)
    {
        Console* console = GetSubsystem<Console>();
        if (console->IsVisible())
            console->SetVisible(false);
        else
            //engine_->Exit();
            quit_=true;
    }

    // Toggle console with F1
    else if (key == KEY_F1)
        GetSubsystem<Console>()->Toggle();
    
    // Toggle debug HUD with F2
    else if (key == KEY_F2)
        GetSubsystem<DebugHud>()->ToggleAll();

    else if (key == KEY_F3)
        debugDrawPhysics_ = !debugDrawPhysics_;
    else if (key == KEY_F4)
    {
        //turn on the debug camera
        debugCamera_ = !debugCamera_;
        if(debugCamera_)
            cameraLogic_->SetCameraType(String("default"));
        else
            cameraLogic_->SetCameraType(cameraType_);
    }


    
    // Common rendering quality controls, only when UI has no focused element
    else if (!GetSubsystem<UI>()->GetFocusElement())
    {
        Renderer* renderer = GetSubsystem<Renderer>();
        
        // Preferences / Pause
        if (key == KEY_SELECT && touchEnabled_)
        {
            paused_ = !paused_;

            Input* input = GetSubsystem<Input>();
            if (screenJoystickSettingsIndex_ == M_MAX_UNSIGNED)
            {
                // Lazy initialization
                ResourceCache* cache = GetSubsystem<ResourceCache>();
                screenJoystickSettingsIndex_ = input->AddScreenJoystick(cache->GetResource<XMLFile>("UI/ScreenJoystickSettings_Samples.xml"), cache->GetResource<XMLFile>("UI/DefaultStyle.xml"));
            }
            else
                input->SetScreenJoystickVisible(screenJoystickSettingsIndex_, paused_);
        }

        else if (key == '1')
        {
            int quality = renderer->GetTextureQuality();
            ++quality;
            if (quality > QUALITY_HIGH)
                quality = QUALITY_LOW;
            renderer->SetTextureQuality(quality);
        }
        
        // Material quality
        else if (key == '2')
        {
            int quality = renderer->GetMaterialQuality();
            ++quality;
            if (quality > QUALITY_HIGH)
                quality = QUALITY_LOW;
            renderer->SetMaterialQuality(quality);
        }
        
        // Specular lighting
        else if (key == '3')
            renderer->SetSpecularLighting(!renderer->GetSpecularLighting());
        
        // Shadow rendering
        else if (key == '4')
            renderer->SetDrawShadows(!renderer->GetDrawShadows());
        
        // Shadow map resolution
        else if (key == '5')
        {
            int shadowMapSize = renderer->GetShadowMapSize();
            shadowMapSize *= 2;
            if (shadowMapSize > 2048)
                shadowMapSize = 512;
            renderer->SetShadowMapSize(shadowMapSize);
        }
        
        // Shadow depth and filtering quality
        else if (key == '6')
        {
            ShadowQuality quality = renderer->GetShadowQuality();
            quality = (ShadowQuality)(quality + 1);
            if (quality > SHADOWQUALITY_PCF_24BIT)
                quality = SHADOWQUALITY_PCF_16BIT;
            renderer->SetShadowQuality(quality);
        }
        
        // Occlusion culling
        else if (key == '7')
        {
            bool occlusion = renderer->GetMaxOccluderTriangles() > 0;
            occlusion = !occlusion;
            renderer->SetMaxOccluderTriangles(occlusion ? 5000 : 0);
        }
        
        // Instancing
        else if (key == '8')
            renderer->SetDynamicInstancing(!renderer->GetDynamicInstancing());
        
        // Take screenshot
        else if (key == '9')
        {
            Graphics* graphics = GetSubsystem<Graphics>();
            Image screenshot(context_);
            graphics->TakeScreenShot(screenshot);
            // Here we save in the Data folder with date and time appended
            screenshot.SavePNG(GetSubsystem<FileSystem>()->GetProgramDir() + "Data/Screenshot_" +
                Time::GetTimeStamp().Replaced(':', '_').Replaced('.', '_').Replaced(' ', '_') + ".png");
        }
    }
}

void ApplicationInput::HandleTouchBegin(StringHash eventType, VariantMap& eventData)
{
    // On some platforms like Windows the presence of touch input can only be detected dynamically
    InitTouchInput();
    UnsubscribeFromEvent("TouchBegin");
}

Ray ApplicationInput::GetMouseRay() const
{
    // Construct a ray based on current mouse coordinates.
    Camera* camera = cameraNode_->GetComponent<Camera>();
    Graphics* graphics = GetSubsystem<Graphics>();
    IntVector2 pos = GetSubsystem<UI>()->GetCursorPosition();
    return camera->GetScreenRay((float)pos.x_ / graphics->GetWidth(), (float)pos.y_ / graphics->GetHeight());
}

void ApplicationInput::UpdateHover()
{
    //ApplicationHandler* appHandler = GetSubsystem<ApplicationHandler>();
    if (!hoverEnabled_)
        return;

    Node* hitNode = GetDrawable();

    if(hitNode!=NULL)
    {
        if (hoverNode_)
        {
            if (hoverNode_ != hitNode)
            {
                PickingComponent* pc = hoverNode_->GetComponent<PickingComponent>();
                if(pc){
                    pc->UnHoverOver();
                }
            }
        }
       
        PickingComponent* pc = hitNode->GetComponent<PickingComponent>();
        if(pc){
            pc->HoverOver();
            hoverNode_ = hitNode;
        }
    }
    else if(hoverNode_!=NULL)
    {
        PickingComponent* pc = hoverNode_->GetComponent<PickingComponent>();
        if(pc){
            pc->UnHoverOver();
        }
    }
}

void ApplicationInput::UpdateGrab()
{
    if (!hoverGrabEnabled_)
        return;

    Input* input = GetSubsystem<Input>();
    ApplicationHandler* appHandler = GetSubsystem<ApplicationHandler>();

    Node* hitNode = GetDrawable();

    //input->GetMouseButtonDown(MOUSEB_LEFT) || input->GetMouseButtonPress(MOUSEB_LEFT)
    //check to see if we are intialting a grab
    if(hoverNode_==NULL && !hoverHold_ && input->GetMouseButtonPress(MOUSEB_LEFT))
    {
        hoverHold_=true;
        //set the hoverNode
        hoverNode_=hitNode;
        PickingComponent* pc = hoverNode_->GetComponent<PickingComponent>();
        if(pc)
        {
            //set the initial drag offset
            pc->SetPickPosition(appHandler->GetCursor()->GetCursorWorldPosition());
            pc->HoverOver();
            //get the rigidbody and set it
            appHandler->GetCursor()->SetConstrainee(hitNode->GetComponent<RigidBody>());
        }
    }
    else if(!input->GetMouseButtonDown(MOUSEB_LEFT) && hoverHold_ && hoverNode_)
    {
        hoverHold_=false;
        //relase the hoverNode
        appHandler->GetCursor()->ReleaseConstrainee();
        PickingComponent* pc = hoverNode_->GetComponent<PickingComponent>();
        if(pc)
            pc->UnHoverOver();
        
        hoverNode_=NULL;

    }
    //lets do some dragging
    else if(hoverNode_!=NULL && hoverHold_ && input->GetMouseButtonDown(MOUSEB_LEFT))
    {
        //drag the node around
        //PickingComponent* pc = hoverNode_->GetComponent<PickingComponent>();
        //if(pc)
            //pc->Drag(appHandler->GetCursor()->GetCursorWorldPosition());
            //pc->HoverOver();
    }
    //debigging
    //String debugHold = String(hoverHold_);
    //GetSubsystem<DebugHud>()->SetAppStats("Holding:", debugHold);
}
// 
//get the node that we are over
Node* ApplicationInput::GetDrawable()
{
    ApplicationHandler* appHandler = GetSubsystem<ApplicationHandler>();
    Graphics* graphics = GetSubsystem<Graphics>();
    Ray ray = GetMouseRay();
    Vector3 hitPos;

    PODVector<RayQueryResult> results;
    RayOctreeQuery query(results, ray, RAY_TRIANGLE, M_INFINITY, DRAWABLE_GEOMETRY);
    appHandler->scene_->GetComponent<Octree>()->RaycastSingle(query);
    if (results.Size())
    {
        RayQueryResult& result = results[0];
        Vector3& hitPos = result.position_;
        Drawable* hitDrawable = result.drawable_;

        Node* hitNode = TopLevelNodeFromDrawable(hitDrawable);
        String debugHover = String((hitNode ? hitNode->GetName() : "") + " @ " + hitPos.ToString());
        GetSubsystem<DebugHud>()->SetAppStats("hitNode:", debugHover);
        if (hitNode)
        {
            return hitNode;
        }
    }
    return NULL;
}

Node* ApplicationInput::TopLevelNodeFromDrawable(Drawable* drawable) const
{
    ApplicationHandler* appHandler = GetSubsystem<ApplicationHandler>();
    Node* n = drawable->GetNode();
    if (!n)
        return NULL;
    while (n->GetParent() != appHandler->GetScene() )
    {
        if (n->GetParent() == NULL)
            return NULL;
        else
            n = n->GetParent();
    }
    return n;
}
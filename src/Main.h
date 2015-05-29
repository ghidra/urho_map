#ifndef MAIN_H
#define MAIN_H

#pragma once

#include "core/ApplicationHandler.h"
#include "stages/Stage2.h"
//#include "core/ApplicationInput.h"

class Main : public ApplicationHandler
{
    OBJECT(Main);

public:
    /// Construct.
    Main(Context* context);

    virtual void Start();

private:
    /// Construct a new Text instance, containing the 'Hello World' String, and add it to the UI root element.
    //void CreateText();
    /// Subscribe to application-wide logic update events.
    void SubscribeToEvents();
    /// Handle the logic update event.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);

    ApplicationInput * applicationInput_ = NULL;
    Stage2 * stage_ = NULL;

};
#endif
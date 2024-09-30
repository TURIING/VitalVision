#include "Core/Application.h"
#include "Foundation/Log.h"

int main(int argc, char **argv) {
    //Log::GetInstance()->OnCreate();

    Application app;
    app.run();

    //Log::GetInstance()->OnDestroy();
}
#include <glog/logging.h>
#include "core/Application.h"

int main(int argc, char **argv) {
    google::InitGoogleLogging(argv[0]);
    google::SetStderrLogging(google::INFO);

    Application app;
    app.run();
}
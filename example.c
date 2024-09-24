#include "logs.h"

int main() {
    LOG_INFO("Application started");

    LOG_DEBUG("This is a debug message");
    LOG_INFO("This is an info message");
    LOG_WARN("This is a warning message");
    LOG_ERROR("This is an error message");

    LOG_INFO("Application finished");
    
    return 0;
}

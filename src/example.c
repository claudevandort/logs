#include "logs.h"

int main() {
    logs_init(LOG_OUTPUT_STDOUT, 0);

    log_debug("This is a debug message");
    log_info("This is an info message");
    log_warn("This is a warning message");
    log_error("This is an error message");

    return 0;
}

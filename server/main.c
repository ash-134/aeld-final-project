#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>

int main() {
    openlog("sensor-daemon", LOG_PID | LOG_CONS, LOG_USER);
    syslog(LOG_INFO, "Sprint 1: Sensor polling daemon initialized successfully.");
    printf("Sprint 1: Base daemon skeleton started successfully.\n");
    printf("Simulating sensor poll: Temperature = 25.4 C, Humidity = 60.2 %%%%\n");
    closelog();
    return 0;
}

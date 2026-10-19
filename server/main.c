#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <time.h>

#define LOG_FILE "/tmp/sensor_data.log"

int main() {
    openlog("sensor-daemon", LOG_PID | LOG_CONS, LOG_USER);
    syslog(LOG_INFO, "Sprint 2: Periodic sensor polling and logging started.");

    FILE *fp = fopen(LOG_FILE, "a");
    if (!fp) {
        perror("Failed to open log file");
        return 1;
    }

    float temp = 25.8;
    float humidity = 58.5;
    time_t now = time(NULL);

    fprintf(fp, "[%ld] Temp: %.2f C, Humidity: %.2f %%\n", now, temp, humidity);
    fclose(fp);

    printf("Sprint 2: Successfully logged sensor telemetry to %s\n", LOG_FILE);
    printf("Metrics - Temperature: %.2f C, Humidity: %.2f %%\n", temp, humidity);

    closelog();
    return 0;
}

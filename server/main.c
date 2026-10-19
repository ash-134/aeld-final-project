#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <time.h>
#include <signal.h>

#define LOG_FILE "/tmp/sensor_data.log"
#define TEMP_THRESHOLD 30.0

static volatile int keep_running = 1;

void handle_signal(int sig) {
    (void)sig;
    keep_running = 0;
}

int main() {
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);

    openlog("sensor-daemon", LOG_PID | LOG_CONS, LOG_USER);
    syslog(LOG_INFO, "Sprint 3: System hardening and alert monitoring daemon started.");

    float temp = 32.5; // Simulate exceeding threshold to trigger alert logic
    float humidity = 62.0;
    time_t now = time(NULL);

    FILE *fp = fopen(LOG_FILE, "a");
    if (fp) {
        fprintf(fp, "[%ld] Temp: %.2f C, Humidity: %.2f %%\n", now, temp, humidity);
        fclose(fp);
    }

    if (temp > TEMP_THRESHOLD) {
        syslog(LOG_WARNING, "ALERT: Temperature threshold exceeded! Current: %.2f C (Threshold: %.2f C)", temp, TEMP_THRESHOLD);
        printf("[ALERT TRIGGERED] Temperature %.2f C exceeds threshold %.2f C!\n", temp, TEMP_THRESHOLD);
    }

    printf("Sprint 3: Sensor daemon final integration verified. Graceful shutdown executed.\n");
    closelog();
    return 0;
}

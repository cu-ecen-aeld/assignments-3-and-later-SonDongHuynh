#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>

int main(int argc, char *argv[]) {
    // open syslog using LOG_USER facility
    openlog("writer", LOG_PID, LOG_USER);

    if(argc != 3) {
        syslog(LOG_ERR, "Usage: %s <file path> <string>", argv[0]);
        closelog();
        return 1;
    }

    const char *writefile = argv[1];
    const char *writestr = argv[2];

    // write log debug when write file
    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);

    FILE *fp = fopen(writefile, "w");
    if (!fp) {
        syslog(LOG_ERR, "Could not open file %s for writing", writefile);
        closelog();
        return 1;
    }

    if (fprintf(fp, "%s", writestr) < 0) {
        syslog(LOG_ERR, "Failed to write to file %s", writefile);
        fclose(fp);
        closelog();
        return 1;
    }

    fclose(fp);
    closelog();
    return 0;
}
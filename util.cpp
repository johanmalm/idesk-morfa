// SPDX-License-Identifier: GPL-2.0-only
#include <unistd.h>
#include "util.h"

void spawn(QString command)
{
    pid_t pid = fork();
    if (!pid) {
        execl("/bin/sh", "sh", "-c", command.toLatin1().data(), (void *)NULL);
        exit(1);
    }
}

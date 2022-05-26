#include "semver.h"

#include <stdio.h>

w2_semver_t w2_semver_parse(const char *str, uint8_t length) {
	w2_semver_t version;
	sscanf(str, "%d.%d.%d", (int *)&version.major, (int *)&version.minor, (int *)&version.patch);
	return version;
}

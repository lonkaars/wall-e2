#pragma once

/** @file semver.h */

#include <stdint.h>

typedef struct {
	uint8_t major;
	uint8_t minor;
	uint8_t patch;
} w2_semver_t;

w2_semver_t w2_semver_parse(const char *str, uint8_t length);

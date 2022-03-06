#pragma once

#include <stdint.h>

//Thankyou Prof Long for this hash key code!

uint32_t hash(uint64_t *salt, char *key);

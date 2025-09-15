#pragma once
#include <stdint.h>
#include "structs.h"
#include <cstddef>

Image load_image_from_memory(const uint8_t *data, size_t size);
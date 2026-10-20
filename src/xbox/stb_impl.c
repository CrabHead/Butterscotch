#if defined(__clang__)
    #pragma clang diagnostic ignored "-Wall"
    #pragma clang diagnostic ignored "-Wextra"
    #pragma clang diagnostic ignored "-Wuninitialized"
#elif defined(__GNUC__)
    #pragma GCC diagnostic ignored "-Wall"
    #pragma GCC diagnostic ignored "-Wextra"
    #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif

#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_SIMD
#define STBI_ONLY_PNG
#define STBI_ONLY_JPEG
#define STBI_ONLY_GIF
#include "stb_image.h" 

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#ifndef _fopen_s_defined
int fopen_s(FILE **f, const char *name, const char *mode) {
    *f = fopen(name, mode);
    return *f ? 0 : 1;
}
#endif
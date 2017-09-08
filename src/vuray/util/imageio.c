/*
 * imageio.c
 * Raster image I/O.
 *
 * Author: hm2code
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "imageio.h"

// Extracts file extension into `buf`.
// Returns 0 on success, which means that contents of `buf` has been modified.
static int get_file_ext(const char* file_name, char* buf, size_t buf_len) {
    if (!file_name || !buf || !buf_len) {
        return 1;
    }

    char* ext_ptr = strrchr(file_name, '.');
    if (!ext_ptr) {
        buf[0] = 0;
        return 0;
    }

    ++ext_ptr; // skip '.'
    --buf_len; // reserve space for 0 at the very end of the buffer
    int i = 0;
    while (*ext_ptr && i < buf_len) {
        buf[i] = tolower(*ext_ptr);
        ++ext_ptr;
        ++i;
    }
    buf[i] = 0;

    return 0;
}

// Netbpm:
// - .ppm - color
// - .pgm - greyscale
// See https://en.wikipedia.org/wiki/Netpbm_format

static int ppm_write(const char* file_name, const struct image* img) {
    // TODO: error codes
    FILE* file = fopen(file_name, "w");
    if (!file) {
        return 1;
    }

    int size = img->width * img->height * img->components;
    if (img->components == 1) {
        fprintf(file, "P2\n%zu %zu\n255\n", img->width, img->height);
        for (int i = 0; i < size; ++i) {
            fprintf(file, "%hhu\n", img->pixels[i]);
        }
    } else {
        fprintf(file, "P3\n%zu %zu\n255\n", img->width, img->height);
        for (int i = 0; i < size; i += img->components) {
            fprintf(file, "%hhu %hhu %hhu\n", img->pixels[i],
                    img->pixels[i + 1], img->pixels[i + 2]);
        }
    }

    fclose(file);
    return 0;
}

static int ppm_read(const char* file_name, struct image* img) {
    // TODO: error codes
    FILE* file = fopen(file_name, "r");
    if (!file) {
        return 1;
    }

    int format, max_val, result = 0;
    int rc = fscanf(file, "P%d %zu %zu %d", &format, &img->width, &img->height,
            &max_val);
    if (rc != 4 || format != 3 || img->width < 1 || img->height < 1 ||
            max_val != 255) {
        result = 2;
        goto done;
    }
    img->components = 3;

    const size_t size = img->width * img->height * img->components;
    img->pixels = malloc(size);
    if (!img->pixels) {
        result = 3;
        goto done;
    }

    for (int i = 0; i < size; ++i) {
        rc = fscanf(file, " %hhu", &img->pixels[i]);
        if (rc != 1) {
            free(img->pixels);
            img->pixels = 0;
            result = 4;
            goto done;
        }
    }

done:
    fclose(file);
    return result;
}

// Public API

int imageio_write(const char* file_name, const struct image* img) {
    // TODO: error codes
    char ext[8];

    if (get_file_ext(file_name, ext, sizeof(ext))) {
        return 1;
    }

    if (!strcmp("ppm", ext)) {
        return ppm_write(file_name, img);
    }
    return 2;
}

int imageio_read(const char* file_name, struct image* img) {
    // TODO: error codes
    char ext[8];

    if (get_file_ext(file_name, ext, sizeof(ext))) {
        return 1;
    }

    if (!strcmp("ppm", ext)) {
        return ppm_read(file_name, img);
    }
    return 2;
}

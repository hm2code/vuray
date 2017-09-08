/*
 * imageio.c
 * Raster Image I/O.
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
        return IMAGEIO_ERR_ILLEGALARG;
    }

    int i = 0;
    char* ext_ptr = strrchr(file_name, '.');
    if (ext_ptr) {
        ++ext_ptr; // skip '.'
        --buf_len; // reserve space for 0 at the very end of the buffer
        while (*ext_ptr && i < buf_len) {
            buf[i] = tolower(*ext_ptr);
            ++ext_ptr;
            ++i;
        }
    }
    buf[i] = 0;

    return IMAGEIO_OK;
}

// Netbpm:
// - .pgm - grayscale
// - .ppm - color
// See https://en.wikipedia.org/wiki/Netpbm_format

static int pgm_write(const char* file_name, const struct image* img) {
    if (img->components != 1) {
        return IMAGEIO_ERR_UNSUPPORTED;
    }

    FILE* file = fopen(file_name, "w");
    if (!file) {
        return IMAGEIO_ERR_BADFILE;
    }

    int result = IMAGEIO_OK;
    const int size = img->width * img->height * img->components;
    fprintf(file, "P2\n%zu %zu\n255\n", img->width, img->height);
    for (int i = 0; i < size; ++i) {
        if (fprintf(file, "%hhu\n", img->pixels[i]) < 0) {
            result = IMAGEIO_ERR_BADFILE;
            break;
        }
    }

    fclose(file);
    return result;
}

static int ppm_write(const char* file_name, const struct image* img) {
    if (img->components != 3 && img->components != 4) {
        return IMAGEIO_ERR_UNSUPPORTED;
    }

    FILE* file = fopen(file_name, "w");
    if (!file) {
        return IMAGEIO_ERR_BADFILE;
    }

    int result = IMAGEIO_OK;
    const int size = img->width * img->height * img->components;
    fprintf(file, "P3\n%zu %zu\n255\n", img->width, img->height);
    for (int i = 0; i < size; i += img->components) {
        if (fprintf(file, "%hhu %hhu %hhu\n", img->pixels[i],
                img->pixels[i + 1], img->pixels[i + 2]) < 0) {
            result = IMAGEIO_ERR_BADFILE;
            break;
        }
    }

    fclose(file);
    return result;
}

static int pgm_read(const char* file_name, struct image* img) {
    FILE* file = fopen(file_name, "r");
    if (!file) {
        return IMAGEIO_ERR_BADFILE;
    }

    int format, max_val, result = IMAGEIO_OK;
    int rc = fscanf(file, "P%d %zu %zu %d", &format, &img->width, &img->height,
            &max_val);
    if (rc != 4 || img->width < 1 || img->height < 1) {
        result = IMAGEIO_ERR_BADFILE;
        goto done;
    }
    if (format != 2 || max_val != 255) {
        result = IMAGEIO_ERR_UNSUPPORTED;
        goto done;
    }
    img->components = 1;

    const size_t size = img->width * img->height * img->components;
    img->pixels = malloc(size);
    if (!img->pixels) {
        result = IMAGEIO_ERR_NOMEMORY;
        goto done;
    }

    for (int i = 0; i < size; ++i) {
        rc = fscanf(file, " %hhu", &img->pixels[i]);
        if (rc != 1) {
            free(img->pixels);
            img->pixels = 0;
            result = IMAGEIO_ERR_BADFILE;
            goto done;
        }
    }

done:
    fclose(file);
    return result;
}

static int ppm_read(const char* file_name, struct image* img) {
    FILE* file = fopen(file_name, "r");
    if (!file) {
        return IMAGEIO_ERR_BADFILE;
    }

    int format, max_val, result = IMAGEIO_OK;
    int rc = fscanf(file, "P%d %zu %zu %d", &format, &img->width, &img->height,
            &max_val);
    if (rc != 4 || img->width < 1 || img->height < 1) {
        result = IMAGEIO_ERR_BADFILE;
        goto done;
    }
    if (format != 3 || max_val != 255) {
        result = IMAGEIO_ERR_UNSUPPORTED;
        goto done;
    }
    img->components = 3;

    const size_t size = img->width * img->height * img->components;
    img->pixels = malloc(size);
    if (!img->pixels) {
        result = IMAGEIO_ERR_NOMEMORY;
        goto done;
    }

    for (int i = 0; i < size; ++i) {
        rc = fscanf(file, " %hhu", &img->pixels[i]);
        if (rc != 1) {
            free(img->pixels);
            img->pixels = 0;
            result = IMAGEIO_ERR_BADFILE;
            goto done;
        }
    }

done:
    fclose(file);
    return result;
}

// Public API

int imageio_write(const char* file_name, const struct image* img) {
    char ext[8];

    const int err = get_file_ext(file_name, ext, sizeof(ext));
    if (err) {
        return err;
    }

    if (!strcmp("ppm", ext)) {
        return ppm_write(file_name, img);
    } else if (!strcmp("pgm", ext)) {
        return pgm_write(file_name, img);
    }
    return IMAGEIO_ERR_UNSUPPORTED;
}

int imageio_read(const char* file_name, struct image* img) {
    char ext[8];

    const int err = get_file_ext(file_name, ext, sizeof(ext));
    if (err) {
        return err;
    }

    if (!strcmp("ppm", ext)) {
        return ppm_read(file_name, img);
    } else if (!strcmp("pgm", ext)) {
        return pgm_read(file_name, img);
    }
    return IMAGEIO_ERR_UNSUPPORTED;
}

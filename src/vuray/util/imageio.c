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
static void get_file_ext(const char* file_name, char* buf, size_t buf_len) {
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

static int pgm_read(FILE* file, struct image* img) {
    int format, max_val;
    int rc = fscanf(file, "P%d %zu %zu %d", &format, &img->width, &img->height,
            &max_val);
    if (rc != 4 || img->width < 1 || img->height < 1) {
        return IMAGEIO_ERR_BADFILE;
    }
    if (format != 2 || max_val != 255) {
        return IMAGEIO_ERR_UNSUPPORTED;
    }
    img->components = 1;

    const size_t size = img->width * img->height * img->components;
    img->pixels = malloc(size);
    if (!img->pixels) {
        return IMAGEIO_ERR_NOMEMORY;
    }

    for (int i = 0; i < size; ++i) {
        rc = fscanf(file, " %hhu", &img->pixels[i]);
        if (rc != 1) {
            free(img->pixels);
            img->pixels = 0;
            return IMAGEIO_ERR_BADFILE;
        }
    }

    return IMAGEIO_OK;
}

static int ppm_read(FILE* file, struct image* img) {
    int format, max_val;
    int rc = fscanf(file, "P%d %zu %zu %d", &format, &img->width, &img->height,
            &max_val);
    if (rc != 4 || img->width < 1 || img->height < 1) {
        return IMAGEIO_ERR_BADFILE;
    }
    if (format != 3 || max_val != 255) {
        return IMAGEIO_ERR_UNSUPPORTED;
    }
    img->components = 3;

    const size_t size = img->width * img->height * img->components;
    img->pixels = malloc(size);
    if (!img->pixels) {
        return IMAGEIO_ERR_NOMEMORY;
    }

    for (int i = 0; i < size; ++i) {
        rc = fscanf(file, " %hhu", &img->pixels[i]);
        if (rc != 1) {
            free(img->pixels);
            img->pixels = 0;
            return IMAGEIO_ERR_BADFILE;
        }
    }

    return IMAGEIO_OK;
}

typedef int (*write_driver)(const char*, const struct image*);

// Returns pointer to a function for writing files with the given extension.
static write_driver get_write_driver(const char* ext) {
    write_driver result = (write_driver)0;

    if (!strcmp(ext, "ppm")) {
        result = ppm_write;
    } else if (!strcmp(ext, "pgm")) {
        result = pgm_write;
    }

    return result;
}

typedef int (*read_driver)(FILE*, struct image*);

// Returns pointer to a function for reading files with the given extension.
static read_driver get_read_driver(const char* ext) {
    read_driver result = (read_driver)0;

    if (!strcmp(ext, "ppm")) {
        result = ppm_read;
    } else if (!strcmp(ext, "pgm")) {
        result = pgm_read;
    }

    return result;
}

// Public API

int imageio_write(const char* file_name, const struct image* img) {
    if (!file_name || !img) {
        return IMAGEIO_ERR_ILLEGALARG;
    }

    char ext[8];
    get_file_ext(file_name, ext, sizeof(ext));

    const write_driver write_fn = get_write_driver(ext);
    if (!write_fn) {
        return IMAGEIO_ERR_UNSUPPORTED;
    }

    return write_fn(file_name, img);
}

int imageio_read(const char* file_name, struct image* img) {
    if (!file_name || !img) {
        return IMAGEIO_ERR_ILLEGALARG;
    }

    char ext[8];
    get_file_ext(file_name, ext, sizeof(ext));

    const read_driver read_fn = get_read_driver(ext);
    if (!read_fn) {
        return IMAGEIO_ERR_UNSUPPORTED;
    }

    // Opening / closing file here greatly simplifies the read functions.
    FILE* file = fopen(file_name, "r");
    if (!file) {
        return IMAGEIO_ERR_BADFILE;
    }

    const int result = read_fn(file, img);

    fclose(file);
    return result;
}

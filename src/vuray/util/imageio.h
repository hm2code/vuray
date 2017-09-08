/**
 * \file    imageio.h
 * \brief   Raster image I/O.
 *
 * \author  hm2code
 */
#pragma once
#include <stddef.h>
#include <stdint.h>

/**
 * Describes raster image with byte color components.
 */
struct image {
    /**
     * Pointer to the image color data - pixels.
     * All pixels are expected to be stored in a contiguous array of
     * `width * height` pixels length (`width * height * components` bytes).
     */
    uint8_t* pixels;

    /**
     * Width of the image in pixels.
     */
    size_t width;

    /**
     * Height of the image in pixels.
     */
    size_t height;

    /**
     * Number of color components per pixel.
     * Valid values:
     * - 1 - each pixel is represented by a single byte (e.g. luminocity).
     * - 3 - each pixel is represented by three bytes: RGB.
     * - 4 - each pixel is represented by four bytes: RGBA.
     */
    int components;
};

/**
 * Writes a raster image to disk.
 * This function writes the raster image with byte color components to disk and
 * returns 0 if successful, an error code otherwise.
 * \param file_name - the name of the file to be written. If a file with the
 * given name exists, then its content will be replaced with the new data.
 * \param img - the raster image to be written.
 */
int imageio_write(const char* file_name, const struct image* img);

/**
 * Reads a raster image from disk.
 * This function reads a raster image from disk and returns 0 if successful,
 * an error code otherwise.
 * \param file_name - the name of the file to read from.
 * \param img - the image data will be stored in this structure. The image
 * color data (pixels) will be allocated using `malloc()` so it needs to be
 * deallocated using `free()`.
 */
int imageio_read(const char* file_name, struct image* img);

/*
 * main.c
 * The main function.
 *
 * Author: hm2code
 */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include <vuray/util/imageio.h>

int main(int argc, const char* argv[]) {
    const char* out_file_name = 0;

    for (int i = 1; i < argc; ++i) {
        const char* cur = argv[i];
        const bool has_next = (i + 1) < argc;
        if (!strcmp(cur, "--outfile")) {
            if (!has_next) {
                fprintf(stderr, "Missing file name for --outfile option.\n");
                return 1;
            }
            out_file_name = argv[++i];
        }
    }
    if (!out_file_name) {
        out_file_name = "vuray.ppm";
    }

    const int nx = 200;
    const int ny = 100;

    const size_t size = 3 * nx * ny;

    float* frame_buf = malloc(size * sizeof(float));

    int pixel = 0;
    const float b = 0.2f;
    for (int j = ny - 1; j >= 0; --j) {
        const float g = (float)j / (float)ny;
        for (int i = 0; i < nx; ++i) {
            const float r = (float)i / (float)nx;

            frame_buf[pixel + 0] = r;
            frame_buf[pixel + 1] = g;
            frame_buf[pixel + 2] = b;
            pixel += 3;
        }
    }

    struct image img = (struct image) {
        .pixels = malloc(size),
        .width = nx,
        .height = ny,
        .components = 3
    };
    for (int i = 0; i < size; ++i) {
        img.pixels[i] = (uint8_t)(255.99f * frame_buf[i]);
    }
    free(frame_buf);

    imageio_write(out_file_name, &img);
    free(img.pixels);
}

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

#include <vuray/math/vec.h>
#include <vuray/util/imageio.h>

static struct vec3 color(struct vec3 origin, struct vec3 direction) {
    const struct vec3 white = { 1.f, 1.f, 1.f };
    const struct vec3 blue = { 0.5f, 0.7f, 1.f };

    const struct vec3 unit_dir = vec3_normalize(direction);
    const float t = 0.5f * (unit_dir.y + 1.f);
    return vec3_add(vec3_mul(white, 1.f - t), vec3_mul(blue, t));
}

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

    const struct vec3 ll_corner = { -2.f, -1.f, -1.f };
    const struct vec3 horiz = { 4.f, 0.f, 0.f };
    const struct vec3 vert = { 0.f, 2.f, 0.f };
    const struct vec3 origin = { 0.f, 0.f, 0.f };

    const size_t size = 3 * nx * ny;

    float* frame_buf = malloc(size * sizeof(float));

    int pixel = 0;
    for (int j = ny - 1; j >= 0; --j) {
        const float v = (float)j / (float)ny;
        const struct vec3 s_vert = vec3_mul(vert, v);
        for (int i = 0; i < nx; ++i) {
            const float u = (float)i / (float)nx;
            const struct vec3 s_horiz = vec3_mul(horiz, u);

            const struct vec3 direction = vec3_add(ll_corner,
                    vec3_add(s_horiz, s_vert));
            const struct vec3 col = color(origin, direction);
            frame_buf[pixel + 0] = col.x;
            frame_buf[pixel + 1] = col.y;
            frame_buf[pixel + 2] = col.z;
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

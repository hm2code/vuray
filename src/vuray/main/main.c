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

static float hit_sphere(struct vec3 center, float radius, struct vec3 ray_origin,
        struct vec3 ray_direction) {
    const struct vec3 oc = vec3_sub(ray_origin, center);
    const float a = vec3_dot(ray_direction, ray_direction);
    const float b = 2.f * vec3_dot(oc, ray_direction);
    const float c = vec3_dot(oc, oc) - radius * radius;
    const float discriminant = b * b - 4.f * a * c;
    if (discriminant < 0.f) {
        return -1.f;
    }
    return (-b - sqrt(discriminant)) / (2.f * a);
}

static struct vec3 color(struct vec3 origin, struct vec3 direction) {
    const struct vec3 s_center = { 0.f, 0.f, -1.f };
    const float s_radius = 0.5f;
    float t = hit_sphere(s_center, s_radius, origin, direction);
    if (t > 0.f) {
        const struct vec3 normal = vec3_normalize(
                vec3_sub(ray_point_at(origin, direction, t), s_center)
                );
        return vec3_mul(vec3_add(normal, 1.f), 0.5f); // [-1, 1] -> [0, 1]
    }

    // Background
    const struct vec3 white = { 1.f, 1.f, 1.f };
    const struct vec3 blue = { 0.5f, 0.7f, 1.f };

    const struct vec3 unit_dir = vec3_normalize(direction);
    t = 0.5f * (unit_dir.y + 1.f);
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
            vec3_store(&frame_buf[pixel], color(origin, direction));
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

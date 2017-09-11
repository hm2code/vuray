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

#define define_table(name, element_type) \
    struct name { \
        element_type* records; \
        size_t size; \
        size_t capacity; \
    }; \
static inline struct name name##_create(size_t capacity) { \
    element_type* records; \
    if (posix_memalign((void**)&records, 16, capacity * sizeof(element_type))){\
        abort(); \
    } \
    return (struct name) { \
        .records = records, \
        .size = 0, \
        .capacity = capacity \
    }; \
} \
static inline void name##_destroy(struct name* tbl) { \
    free(tbl->records); \
    tbl->records = 0; \
} \
static inline void name##_add(struct name* tbl, const element_type* record) { \
    if (tbl->size == tbl->capacity) { \
        tbl->capacity <<= 1; \
        element_type* records; \
        if (posix_memalign((void**)&records, 16, \
                    tbl->capacity * sizeof(element_type))) { \
            abort(); \
        } \
        memcpy(records, tbl->records, tbl->size); \
        free(tbl->records); \
        tbl->records = records; \
    } \
    tbl->records[tbl->size++] = *record; \
} \
static inline void name##_clear(struct name* tbl) { \
    tbl->size = 0; \
}

struct hit_record {
    struct vec3 point; // intersection point
    float t; // distance from the ray origin
    struct vec3 normal; // normal at the intersection point
    float reserved;
};

define_table(hit_table, struct hit_record);

struct sphere {
    struct vec3 center;
    float radius;
};

define_table(sphere_table, struct sphere);

struct ray {
    struct vec3 origin;
    struct vec3 direction;
};

struct scene {
    struct sphere_table spheres;
    struct hit_table hits;
};

static void scene_init(struct scene* s) {
    s->spheres = sphere_table_create(16);
    s->hits = hit_table_create(16);

    struct sphere sph = (struct sphere) {
        .center = { 0.f, 0.f, -1.f },
        .radius = 0.5f
    };
    sphere_table_add(&s->spheres, &sph);

    sph.center = (struct vec3) { -1.f, 0.f, -1.5f };
    sphere_table_add(&s->spheres, &sph);

    sph.center = (struct vec3) { 1.f, 0.f, -1.5f };
    sphere_table_add(&s->spheres, &sph);
}

static void scene_destroy(struct scene* s) {
    sphere_table_clear(&s->spheres); // just to suppress unused warning...
    sphere_table_destroy(&s->spheres);
    hit_table_destroy(&s->hits);
}

static void ray_intersect_spheres(const struct ray* r,
        const struct sphere_table* s_tbl, struct hit_table* h_tbl) {
    struct hit_record hit;
    const float a = vec3_dot(r->direction, r->direction);
    for (size_t i = 0; i < s_tbl->size; ++i) {
        const struct sphere* s = &s_tbl->records[i];
        const struct vec3 oc = vec3_sub(r->origin, s->center);
        const float b = 2.f * vec3_dot(oc, r->direction);
        const float c = vec3_dot(oc, oc) - s->radius * s->radius;
        const float d = b * b - 4.f * a * c;
        if (d >= 0.f) {
            hit.t = (-b - sqrt(d)) / (2.f * a);
            hit.point = ray_point_at(r->origin, r->direction, hit.t);
            hit.normal = vec3_normalize(vec3_sub(hit.point, s->center));
            hit_table_add(h_tbl, &hit);
        }
    }
}

static struct vec3 back_color(const struct ray* r) {
    const struct vec3 white = { 1.f, 1.f, 1.f };
    const struct vec3 blue = { 0.5f, 0.7f, 1.f };

    const struct vec3 unit_dir = vec3_normalize(r->direction);
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

    struct scene scn;
    scene_init(&scn);

    int pixel = 0;
    for (int j = ny - 1; j >= 0; --j) {
        const float v = (float)j / (float)ny;
        const struct vec3 s_vert = vec3_mul(vert, v);
        for (int i = 0; i < nx; ++i) {
            const float u = (float)i / (float)nx;
            const struct vec3 s_horiz = vec3_mul(horiz, u);

            const struct ray r = (struct ray) {
                .origin = origin,
                .direction = vec3_add(ll_corner, vec3_add(s_horiz, s_vert))
            };
            hit_table_clear(&scn.hits);
            ray_intersect_spheres(&r, &scn.spheres, &scn.hits);
            if (scn.hits.size) {
                vec3_store(&frame_buf[pixel],
                        vec3_mul(vec3_add(scn.hits.records[0].normal, 1.f),
                            0.5f));

            } else {
                vec3_store(&frame_buf[pixel], back_color(&r));
            }
            pixel += 3;
        }
    }

    scene_destroy(&scn);

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

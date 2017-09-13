/*
 * main.c
 * The main function.
 *
 * Author: hm2code
 */
#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>

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
    struct vec3 point;  // intersection point
    float t;            // distance from the ray origin
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

struct camera {
    struct vec3 origin;
    struct vec3 lower_left;
    struct vec3 horizontal;
    struct vec3 vertical;
};

static struct ray camera_get_ray(const struct camera* c, float u, float v) {
    return (struct ray) {
        .origin = c->origin,
        .direction = vec3_sub(
                vec3_add(
                    c->lower_left,
                    vec3_add(
                        vec3_mul(c->horizontal, u),
                        vec3_mul(c->vertical, v)
                        )
                    ),
                c->origin)
    };
}

struct scene {
    struct sphere_table spheres;
    struct hit_table hits;
};

static void scene_init(struct scene* s) {
    s->spheres = sphere_table_create(16);
    s->hits = hit_table_create(16);

    struct sphere sph = (struct sphere) {
        .center = { -1.f, 0.f, -1.5f },
        .radius = 0.5f
    };
    sphere_table_add(&s->spheres, &sph);

    sph.center = (struct vec3) { 0.f, 0.f, -1.f };
    sphere_table_add(&s->spheres, &sph);

    sph.center = (struct vec3) { 1.f, 0.f, -1.5f };
    sphere_table_add(&s->spheres, &sph);

    sph.center = (struct vec3) { 0.f, -100.5f, -1.f };
    sph.radius = 100.f;
    sphere_table_add(&s->spheres, &sph);
}

static void scene_destroy(struct scene* s) {
    sphere_table_clear(&s->spheres); // just to suppress "unused" warning...
    sphere_table_destroy(&s->spheres);
    hit_table_destroy(&s->hits);
}

static struct vec3 random_in_unit_sphere(void) {
    struct vec3 p = (struct vec3) { drand48(), drand48(), drand48() };
    p = vec3_sub(vec3_mul(p, 2.f), 1.f);
    const float len_sq = vec3_len_sq(p);
    if (len_sq > 1.f) {
        p = vec3_mul(p, 1.f / sqrt(len_sq));
    }
    return p;
}

static void ray_intersect_spheres(const struct ray* r,
        const struct sphere_table* s_tbl, struct hit_table* h_tbl) {
    struct hit_record hit = (struct hit_record) { .t = FLT_MAX };
    const float a = vec3_dot(r->direction, r->direction);
    for (size_t i = 0; i < s_tbl->size; ++i) {
        const struct sphere* s = &s_tbl->records[i];
        const struct vec3 oc = vec3_sub(r->origin, s->center);
        const float b = vec3_dot(oc, r->direction);
        const float c = vec3_dot(oc, oc) - s->radius * s->radius;
        const float d = b * b - a * c;
        if (d >= 0.f) {
            const float inva = 1.f / a;
            const float sqrtd = sqrt(d);
            float t = (-b - sqrtd) * inva;
            if (t < hit.t && t > 0.f) {
                hit.t = t;
                hit.point = ray_point_at(r->origin, r->direction, t);
                hit.normal = vec3_div(vec3_sub(hit.point, s->center),
                        s->radius);
                hit_table_add(h_tbl, &hit);
            } else {
                t = (-b + sqrtd) * inva;
                if (t < hit.t && t > 0.f) {
                    hit.t = t;
                    hit.point = ray_point_at(r->origin, r->direction, t);
                    hit.normal = vec3_div(vec3_sub(hit.point, s->center),
                            s->radius);
                    hit_table_add(h_tbl, &hit);
                }
            }
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

static struct vec3 color(const struct ray* r,
        const struct sphere_table* s_tbl, struct hit_table* h_tbl) {
    hit_table_clear(h_tbl);
    ray_intersect_spheres(r, s_tbl, h_tbl);
    if (h_tbl->size) {
        const struct hit_record* closest = &h_tbl->records[h_tbl->size - 1];
        const struct vec3 target = vec3_add(
                closest->normal,
                random_in_unit_sphere()
                );
        const struct ray new_r = (struct ray) {
            .origin = closest->point,
            .direction = target //vec3_normalize(target)
        };
        return vec3_mul(color(&new_r, s_tbl, h_tbl), 0.5f);

    }
    return back_color(r);
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
    const int ns = 100;

    const float invnx = 1.f / nx;
    const float invny = 1.f / ny;
    const float invns = 1.f / ns;

    const struct camera cam = (struct camera) {
        .origin = (struct vec3) { 0.f, 0.f, 0.f },
        .lower_left = (struct vec3) { -2.f, -1.f, -1.f },
        .horizontal = (struct vec3) { 4.f, 0.f, 0.f },
        .vertical = (struct vec3) { 0.f, 2.f, 0.f }
    };

    const size_t size = 3 * nx * ny;

    float* frame_buf = malloc(size * sizeof(float));

    struct scene scn;
    scene_init(&scn);

    const struct sphere_table* spheres = &scn.spheres;
    struct hit_table* hits = &scn.hits;

    int pixel = 0;
    for (int j = ny - 1; j >= 0; --j) {
        for (int i = 0; i < nx; ++i) {
            struct vec3 col = { 0.f, 0.f, 0.f };
            for (int s = 0; s < ns; ++s) {
                const float u = (i + drand48()) * invnx;
                const float v = (j + drand48()) * invny;
                const struct ray r = camera_get_ray(&cam, u, v);
                col = vec3_add(col, color(&r, spheres, hits));
            }
            col = vec3_mul(col, invns);
            col = (struct vec3) { sqrt(col.x), sqrt(col.y), sqrt(col.z) };
            vec3_store(&frame_buf[pixel], col);
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

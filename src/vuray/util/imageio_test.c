/*
 * imageio_test.c
 * Unit tests for imageio.c
 *
 * Author: hm2code
 */
#include <stdio.h>
#include <string.h>

#include "utest.h"

#include "imageio.c"

static void test_get_file_ext(void) {
    char ext[8];
    ext[0] = 1;
    ext[7] = 0;

    get_file_ext("a", ext, 8);
    expect_str_eq("", ext);
    ext[0] = 1;

    get_file_ext("a.", ext, 8);
    expect_str_eq("", ext);

    get_file_ext("a.b", ext, 8);
    expect_str_eq("b", ext);

    get_file_ext("a.bCD", ext, 8);
    expect_str_eq("bcd", ext);

    get_file_ext("a.BCD", ext, 3);
    expect_str_eq("bc", ext);
}

static void test_get_write_driver(void) {
    expect_that(!get_write_driver("abc"));

    expect_that(get_write_driver("ppm") == ppm_write);
    expect_that(get_write_driver("pgm") == pgm_write);
}

static void test_get_read_driver(void) {
    expect_that(!get_read_driver("abc"));

    expect_that(get_read_driver("ppm") == ppm_read);
    expect_that(get_read_driver("pgm") == pgm_read);
}

static void test_imageio_pgm(void) {
    struct image image_to_write = (struct image) {
        .pixels = (uint8_t[]) {
            255, 128,  64,
             32,  16,   0
        },
        .width = 3,
        .height = 2,
        .components = 1
    };

    const char* file_name = "test_imageio.pgm";
    assert_that(!imageio_write(file_name, &image_to_write));

    FILE* file = fopen(file_name, "r");
    assert_that_m(file, "File must exist");
    fclose(file);

    struct image image_to_read;
    memset(&image_to_read, 0, sizeof(image_to_read));
    assert_that(!imageio_read(file_name, &image_to_read));

    assert_that(image_to_read.pixels);
    assert_that(image_to_read.width == image_to_write.width);
    assert_that(image_to_read.height == image_to_write.height);
    assert_that(image_to_read.components == image_to_write.components);

    const int c_size = image_to_read.width * image_to_read.height *
        image_to_read.components;
    for (int i = 0; i < c_size; ++i) {
        assert_that(image_to_read.pixels[i] == image_to_write.pixels[i]);
    }

    free(image_to_read.pixels);
    remove(file_name);
}

static void test_imageio_ppm(void) {
    struct image image_to_write = (struct image) {
        .pixels = (uint8_t[]) {
            255,   0,   0,   0, 255,   0,   0,   0, 255,
            255, 255,   0, 255, 255, 255,   0,   0,   0
        },
        .width = 3,
        .height = 2,
        .components = 3
    };

    const char* file_name = "test_imageio.ppm";
    assert_that(!imageio_write(file_name, &image_to_write));

    FILE* file = fopen(file_name, "r");
    assert_that_m(file, "File must exist");
    fclose(file);

    struct image image_to_read;
    memset(&image_to_read, 0, sizeof(image_to_read));
    assert_that(!imageio_read(file_name, &image_to_read));

    assert_that(image_to_read.pixels);
    assert_that(image_to_read.width == image_to_write.width);
    assert_that(image_to_read.height == image_to_write.height);
    assert_that(image_to_read.components == image_to_write.components);

    const int c_size = image_to_read.width * image_to_read.height *
        image_to_read.components;
    for (int i = 0; i < c_size; ++i) {
        assert_that(image_to_read.pixels[i] == image_to_write.pixels[i]);
    }

    free(image_to_read.pixels);
    remove(file_name);
}

static void test_imageio_write_errors(void) {
    const char* file_name = "test";
    struct image img = (struct image) {
        .pixels = (uint8_t[]) {
            255,   0,   0,   0, 255,   0,   0,   0, 255,
            255, 255,   0, 255, 255, 255,   0,   0,   0
        },
        .width = 3,
        .height = 2,
        .components = 3
    };

    expect_that(imageio_write(0, 0) == IMAGEIO_ERR_ILLEGALARG);
    expect_that(imageio_write(file_name, 0) == IMAGEIO_ERR_ILLEGALARG);
    expect_that(imageio_write(0, &img) == IMAGEIO_ERR_ILLEGALARG);
    expect_that(imageio_write(file_name, &img) == IMAGEIO_ERR_UNSUPPORTED);
    expect_that(imageio_write("/\\<>#$;:.ppm", &img) == IMAGEIO_ERR_BADFILE);
}

static void test_imageio_read_errors(void) {
    const char* file_name = "test";
    struct image img;

    expect_that(imageio_read(0, 0) == IMAGEIO_ERR_ILLEGALARG);
    expect_that(imageio_read(file_name, 0) == IMAGEIO_ERR_ILLEGALARG);
    expect_that(imageio_read(0, &img) == IMAGEIO_ERR_ILLEGALARG);
    expect_that(imageio_read(file_name, &img) == IMAGEIO_ERR_UNSUPPORTED);
    expect_that(imageio_read("/\\<>#$;:.ppm", &img) == IMAGEIO_ERR_BADFILE);
}

int main(void) {
    test_get_file_ext();
    test_get_write_driver();
    test_get_read_driver();

    test_imageio_write_errors();
    test_imageio_read_errors();

    test_imageio_pgm();
    test_imageio_ppm();

    utest_exit();
}

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

static void test_get_file_ext() {
    char ext[16];
    ext[0] = 1;
    ext[15] = 0;

    expect_that(get_file_ext(0, ext, 16));
    expect_that(get_file_ext("a", 0, 16));
    expect_that(get_file_ext("a", ext, 0));

    expect_that(!get_file_ext("a", ext, 16));
    expect_str_eq("", ext);
    ext[0] = 1;

    expect_that(!get_file_ext("a.", ext, 16));
    expect_str_eq("", ext);

    expect_that(!get_file_ext("a.b", ext, 16));
    expect_str_eq("b", ext);

    expect_that(!get_file_ext("a.bCD", ext, 16));
    expect_str_eq("bcd", ext);

    expect_that(!get_file_ext("a.BCD", ext, 3));
    expect_str_eq("bc", ext);
}

static void test_imageio_ppm() {
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

int main(void) {
    test_get_file_ext();
    test_imageio_ppm();

    utest_exit();
}

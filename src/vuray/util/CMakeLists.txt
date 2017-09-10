add_library(imageio STATIC imageio.h imageio.c)

# Unit tests
add_executable(utest_test utest.h utest_test.c)
add_test(utest_test utest_test)

add_executable(imageio_test imageio_test.c)
add_test(imageio_test imageio_test)

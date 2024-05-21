#include <stdint.h>

// SHAPE: [0], HAS_EBO: [0]

// 0 - TRIANGLE
// 1 - QUAD

// 0 - NO EBO
// 1 - HAVE EBO

uint8_t get_pkd_model(uint8_t shape, uint8_t has_ebo)
{
    uint8_t attribute = (1 << 1) + shape;
    attribute = (attribute << 1) + has_ebo;
    attribute = (attribute << 6);
    return attribute;
}

uint8_t from_pkd_model_get_shape(uint8_t pkd)
{
    return (pkd & 0b10000000) >> 7;
}

uint8_t from_pkd_model_get_ebov(uint8_t pkd)
{
    return (pkd & 0b01000000) >> 6;
}

int main(int argc, char *argv[])
{
    uint8_t d = get_pkd_model(0, 1);
    printf(
        "D is %d, Shape: %s and Has EBO? %s\n",
        (int)d,
        ((from_pkd_model_get_shape(d) == 0) ? "Triangle" : "Quad"),
        ((from_pkd_model_get_ebov(d) == 0) ? "No" : "Yes")
    );
    return 0;
}
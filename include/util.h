#ifndef UTIL_H
#define UTIL_H

#include <Arduino.h>
#include <stdint.h>


static const uint8_t smile[128] = {
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x0f, 0xf0, 0x00, 
    0x00, 0x3f, 0xfc, 0x00, 
    0x00, 0xff, 0xff, 0x00, 
    0x01, 0xff, 0xff, 0x80, 
    0x03, 0xff, 0xff, 0xc0, 
    0x07, 0x9f, 0xf9, 0xe0, 
    0x07, 0x0f, 0xf0, 0xe0, 
    0x0f, 0x0f, 0xf0, 0xf0, 
    0x0f, 0x9f, 0xf9, 0xf0, 
    0x1f, 0xff, 0xff, 0xf8, 
    0x1f, 0xff, 0xff, 0xf8, 
    0x1f, 0xff, 0xff, 0xf8, 
    0x1f, 0xff, 0xff, 0xf8, 
    0x1f, 0xff, 0xff, 0xf8, 
    0x1f, 0xff, 0xff, 0xf8, 
    0x1f, 0xff, 0xff, 0xf8, 
    0x1f, 0xff, 0xff, 0xf8, 
    0x0f, 0x9f, 0xf8, 0xf0, 
    0x0f, 0x0f, 0xf0, 0xf0, 
    0x07, 0x07, 0xe0, 0xe0, 
    0x07, 0x80, 0x01, 0xe0, 
    0x03, 0xe0, 0x07, 0xc0, 
    0x01, 0xf8, 0x1f, 0x80, 
    0x00, 0xff, 0xff, 0x00, 
    0x00, 0x3f, 0xfc, 0x00, 
    0x00, 0x0f, 0xf0, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00
};


static const uint8_t neutral[128] = {
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x0f, 0xf0, 0x00, 
    0x00, 0x7f, 0xfc, 0x00, 
    0x00, 0xff, 0xff, 0x00, 
    0x01, 0xff, 0xff, 0x80, 
    0x03, 0xff, 0xff, 0xc0, 
    0x07, 0xff, 0xff, 0xe0, 
    0x07, 0xff, 0xff, 0xe0, 
    0x0f, 0x9f, 0xf9, 0xf0, 
    0x0f, 0x0f, 0xf0, 0xf0, 
    0x1f, 0x0f, 0xf0, 0xf8, 
    0x1f, 0x0f, 0xf0, 0xf8, 
    0x1f, 0x9f, 0xf9, 0xf8, 
    0x1f, 0xff, 0xff, 0xf8, 
    0x1f, 0xff, 0xff, 0xf8, 
    0x1f, 0xff, 0xff, 0xf8, 
    0x1f, 0xff, 0xff, 0xf8, 
    0x1f, 0xff, 0xff, 0xf8, 
    0x0f, 0xc0, 0x03, 0xf0, 
    0x0f, 0xc0, 0x03, 0xf0, 
    0x07, 0xff, 0xff, 0xe0, 
    0x07, 0xff, 0xff, 0xe0, 
    0x03, 0xff, 0xff, 0xc0, 
    0x01, 0xff, 0xff, 0x80, 
    0x00, 0xff, 0xff, 0x00, 
    0x00, 0x7f, 0xfc, 0x00, 
    0x00, 0x0f, 0xf0, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00
};

static const uint8_t sad[132] = {
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x03, 0xc0, 0x00, 
    0x00, 0x1f, 0xf8, 0x00, 
    0x00, 0x7f, 0xfe, 0x00, 
    0x00, 0xff, 0xff, 0x00, 
    0x03, 0xff, 0xff, 0x80, 
    0x03, 0xff, 0xff, 0xc0, 
    0x07, 0xff, 0xff, 0xe0, 
    0x0f, 0xff, 0xff, 0xf0, 
    0x0f, 0xcf, 0xf3, 0xf0, 
    0x0f, 0x87, 0xe1, 0xf0, 
    0x1f, 0x87, 0xe1, 0xf8, 
    0x1f, 0xcf, 0xf3, 0xf8, 
    0x1f, 0xff, 0xff, 0xf8, 
    0x1f, 0xff, 0xff, 0xf8, 
    0x1f, 0xff, 0xff, 0xf8, 
    0x1f, 0xff, 0xff, 0xf8, 
    0x0f, 0xff, 0xff, 0xf0, 
    0x0f, 0xfc, 0x1f, 0xf0, 
    0x0f, 0xf0, 0x07, 0xf0, 
    0x07, 0xc3, 0xe1, 0xe0, 
    0x07, 0x8f, 0xf9, 0xe0, 
    0x03, 0xdf, 0xfd, 0xc0, 
    0x01, 0xff, 0xff, 0x80, 
    0x00, 0xff, 0xff, 0x00, 
    0x00, 0x3f, 0xfc, 0x00, 
    0x00, 0x07, 0xe0, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00
};

static const uint8_t intro[1040] = {
    0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xfd, 0xff, 0xff, 0xcf, 0xff, 0xff, 0x80, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xfc, 0xff, 0xff, 0x9f, 0xff, 0xff, 0x80, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xfe, 0x7f, 0xff, 0x3f, 0xff, 0xff, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0x78, 0x0f, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xf1, 0xe3, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xe7, 0xf8, 0x3f, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xcf, 0xf8, 0x1f, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0x9f, 0xf3, 0xcf, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0x9f, 0xf7, 0xe7, 0xff, 0xfe, 0x00, 0x01, 0x80, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xbf, 0xe7, 0xe7, 0xff, 0xfe, 0x00, 0x1f, 0xf0, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xc3, 0xbf, 0x87, 0xf1, 0xff, 0xfe, 0x00, 0x3f, 0xfc, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xc3, 0xbf, 0xbf, 0xfc, 0xff, 0xfe, 0x01, 0xff, 0xfe, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xbf, 0x3f, 0xfe, 0xff, 0xfe, 0x01, 0xff, 0xff, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0x9f, 0x3f, 0xfc, 0xff, 0xfe, 0x01, 0xff, 0xff, 0x83, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xfc, 0x1f, 0x9f, 0xfd, 0xff, 0xfe, 0x00, 0xff, 0xff, 0x83, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xf1, 0x8f, 0xc0, 0x01, 0xff, 0xfe, 0x00, 0xff, 0xff, 0x83, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xf7, 0xc3, 0xf3, 0xff, 0xff, 0xfe, 0x00, 0xff, 0xff, 0x83, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xe7, 0xe0, 0x07, 0xff, 0xff, 0xfe, 0x00, 0x1f, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xc7, 0xe2, 0x1f, 0xff, 0xff, 0xfe, 0x00, 0x0e, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0x9f, 0xf1, 0xff, 0x3f, 0xff, 0xfe, 0x00, 0x0e, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0x3f, 0xfd, 0xff, 0x9f, 0xff, 0xfe, 0x00, 0x06, 0x16, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0x7f, 0xfc, 0xff, 0xcf, 0xff, 0xff, 0x00, 0x07, 0x80, 0x83, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0x3f, 0xfd, 0x3f, 0xff, 0xff, 0xfe, 0x00, 0x07, 0x80, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0x80, 0x01, 0x3f, 0xff, 0xff, 0xff, 0x00, 0x07, 0x80, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xe0, 0x07, 0x3f, 0xff, 0xff, 0xff, 0x00, 0x07, 0xd3, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0x00, 0x03, 0xff, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x07, 0xff, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x02, 0x07, 0xff, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x04, 0x07, 0xff, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x04, 0x07, 0xff, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x04, 0x06, 0x3f, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x04, 0x04, 0x3f, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x1f, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x07, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x01, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x01, 0x01, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x0b, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc2, 0x00, 0x4e, 0x1f, 0xff, 0xff, 0xfd, 0xb7, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0xfe, 0x1f, 0xff, 0xff, 0xed, 0xe6, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x01, 0xf2, 0x3f, 0xff, 0xff, 0xe6, 0x1d, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x01, 0xf0, 0x3f, 0xff, 0xff, 0xfd, 0xe7, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0xe0, 0x7f, 0xff, 0xff, 0xcb, 0xfa, 0x07, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xf9, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x01, 0xff, 0xff, 0xff, 0xf7, 0x81, 0xfe, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x03, 0xff, 0xff, 0xff, 0xf6, 0x7f, 0xff, 0x7f, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x02, 0x7f, 0xff, 0xff, 0xfe, 0xff, 0xff, 0x7f, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x0e, 0x7f, 0xff, 0xff, 0xca, 0xff, 0xff, 0xbf, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x3e, 0x3f, 0xff, 0xff, 0xf1, 0xff, 0xff, 0xbf, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x60, 0x07, 0xfe, 0x3f, 0xff, 0xff, 0xef, 0xff, 0xff, 0xbf, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xc0, 0x07, 0xfe, 0x1f, 0xff, 0xff, 0x9f, 0xff, 0xff, 0xbf, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 0xc0, 0x7f, 0xfe, 0x1f, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0x9f, 
    0xff, 0xff, 0xff, 0xff, 0xfe, 0x7b, 0xc0, 0x7f, 0xfe, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xdf, 
    0xff, 0xff, 0xff, 0xff, 0xf0, 0xf3, 0xc0, 0x5f, 0xfe, 0x0f, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xef, 
    0xff, 0xff, 0xff, 0xff, 0xe3, 0xf7, 0xc0, 0x7f, 0xfc, 0x0f, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xef, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xc0, 0x7f, 0xfc, 0x0f, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xef, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xc0, 0x7f, 0xfc, 0x07, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xef, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xc1, 0xff, 0xf8, 0x07, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0x9f, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xc3, 0xff, 0xf8, 0x07, 0xff, 0xff, 0x00, 0x00, 0x00, 0x3f, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0x9f, 0xc1, 0xff, 0xf0, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};


static const uint8_t intro_inverted[1040] = {
    0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x02, 0x00, 0x00, 0x30, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x03, 0x00, 0x00, 0x60, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x01, 0x80, 0x00, 0xc0, 0x00, 0x00, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x87, 0xf0, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x0e, 0x1c, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x18, 0x07, 0xc0, 0x00, 0x01, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x30, 0x07, 0xe0, 0x00, 0x01, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x60, 0x0c, 0x30, 0x00, 0x03, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x60, 0x08, 0x18, 0x00, 0x01, 0xff, 0xfe, 0x7f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x40, 0x18, 0x18, 0x00, 0x01, 0xff, 0xe0, 0x0f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x3c, 0x40, 0x78, 0x0e, 0x00, 0x01, 0xff, 0xc0, 0x03, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x3c, 0x40, 0x40, 0x03, 0x00, 0x01, 0xfe, 0x00, 0x01, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x40, 0xc0, 0x01, 0x00, 0x01, 0xfe, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x60, 0xc0, 0x03, 0x00, 0x01, 0xfe, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x03, 0xe0, 0x60, 0x02, 0x00, 0x01, 0xff, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x0e, 0x70, 0x3f, 0xfe, 0x00, 0x01, 0xff, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x08, 0x3c, 0x0c, 0x00, 0x00, 0x01, 0xff, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x18, 0x1f, 0xf8, 0x00, 0x00, 0x01, 0xff, 0xe0, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x38, 0x1d, 0xe0, 0x00, 0x00, 0x01, 0xff, 0xf1, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x60, 0x0e, 0x00, 0xc0, 0x00, 0x01, 0xff, 0xf1, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0xc0, 0x02, 0x00, 0x60, 0x00, 0x01, 0xff, 0xf9, 0xe9, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x80, 0x03, 0x00, 0x30, 0x00, 0x00, 0xff, 0xf8, 0x7f, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0xc0, 0x02, 0xc0, 0x00, 0x00, 0x01, 0xff, 0xf8, 0x7f, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x7f, 0xfe, 0xc0, 0x00, 0x00, 0x00, 0xff, 0xf8, 0x7f, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x1f, 0xf8, 0xc0, 0x00, 0x00, 0x00, 0xff, 0xf8, 0x2c, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0xff, 0xfc, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xf8, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0xf8, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfb, 0xf8, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfb, 0xf8, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfb, 0xf9, 0xc0, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfb, 0xfb, 0xc0, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xe0, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xf8, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xfe, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xfe, 0xfe, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xf4, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3d, 0xff, 0xb1, 0xe0, 0x00, 0x00, 0x02, 0x48, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0x01, 0xe0, 0x00, 0x00, 0x12, 0x19, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xfe, 0x0d, 0xc0, 0x00, 0x00, 0x19, 0xe2, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xfe, 0x0f, 0xc0, 0x00, 0x00, 0x02, 0x18, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0x1f, 0x80, 0x00, 0x00, 0x34, 0x05, 0xf8, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x07, 0x06, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x08, 0x7e, 0x01, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x09, 0x80, 0x00, 0x80, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xfd, 0x80, 0x00, 0x00, 0x01, 0x00, 0x00, 0x80, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xf1, 0x80, 0x00, 0x00, 0x35, 0x00, 0x00, 0x40, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xc1, 0xc0, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x40, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x9f, 0xf8, 0x01, 0xc0, 0x00, 0x00, 0x10, 0x00, 0x00, 0x40, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x3f, 0xf8, 0x01, 0xe0, 0x00, 0x00, 0x60, 0x00, 0x00, 0x40, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x3f, 0x80, 0x01, 0xe0, 0x00, 0x01, 0x80, 0x00, 0x00, 0x60, 
    0x00, 0x00, 0x00, 0x00, 0x01, 0x84, 0x3f, 0x80, 0x01, 0xe0, 0x00, 0x01, 0x00, 0x00, 0x00, 0x20, 
    0x00, 0x00, 0x00, 0x00, 0x0f, 0x0c, 0x3f, 0xa0, 0x01, 0xf0, 0x00, 0x02, 0x00, 0x00, 0x00, 0x10, 
    0x00, 0x00, 0x00, 0x00, 0x1c, 0x08, 0x3f, 0x80, 0x03, 0xf0, 0x00, 0x02, 0x00, 0x00, 0x00, 0x10, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x3f, 0x80, 0x03, 0xf0, 0x00, 0x02, 0x00, 0x00, 0x00, 0x10, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x3f, 0x80, 0x03, 0xf8, 0x00, 0x02, 0x00, 0x00, 0x00, 0x10, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x3e, 0x00, 0x07, 0xf8, 0x00, 0x01, 0x80, 0x00, 0x00, 0x60, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x3c, 0x00, 0x07, 0xf8, 0x00, 0x00, 0xff, 0xff, 0xff, 0xc0, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x3e, 0x00, 0x0f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#ifdef DEBUG
    #define DEBUG_PRINT_VERBOSE(fmt,...)\
        _printf((char*)" [%u] ",fmt);\
            _printf(__VA_ARGS__)
    #define DEBUG_PRINT(...)\
        _printf(__VA_ARGS__)
#else
    #define DEBUG_PRINT(...) 
    #define DEBUG_PRINT_VERBOSE(fmt,...)
#endif

char *myITOA(uint32_t num, uint8_t base, uint8_t decimal_points);
char *myFTOA(float float_part, uint8_t decimal_points , uint8_t base);
void _printf(char* format,...);


#endif
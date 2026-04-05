#include "images.h"
#include <string.h>


typedef struct {
    const char* code;
    const lv_img_dsc_t* img;
} image_map_t;

static const image_map_t image_map[] = {
};

const lv_img_dsc_t* get_image_by_code(const char* code) {
    for (int i = 0; i < sizeof(image_map)/sizeof(image_map[0]); i++) {
        if (strcmp(image_map[i].code, code) == 0) return image_map[i].img;
    }
    return nullptr;
}

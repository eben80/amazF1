#include "images.h"
#include <string.h>

LV_IMG_DECLARE(ae);
LV_IMG_DECLARE(ar);
LV_IMG_DECLARE(at);
LV_IMG_DECLARE(au);
LV_IMG_DECLARE(az);
LV_IMG_DECLARE(be);
LV_IMG_DECLARE(bh);
LV_IMG_DECLARE(br);
LV_IMG_DECLARE(ca);
LV_IMG_DECLARE(cn);
LV_IMG_DECLARE(de);
LV_IMG_DECLARE(dk);
LV_IMG_DECLARE(es);
LV_IMG_DECLARE(fi);
LV_IMG_DECLARE(fr);
LV_IMG_DECLARE(gb);
LV_IMG_DECLARE(hard);
LV_IMG_DECLARE(hu);
LV_IMG_DECLARE(it);
LV_IMG_DECLARE(jp);
LV_IMG_DECLARE(mc);
LV_IMG_DECLARE(medium);
LV_IMG_DECLARE(mx);
LV_IMG_DECLARE(nl);
LV_IMG_DECLARE(nz);
LV_IMG_DECLARE(sa);
LV_IMG_DECLARE(sg);
LV_IMG_DECLARE(soft);
LV_IMG_DECLARE(th);
LV_IMG_DECLARE(un);
LV_IMG_DECLARE(us);

typedef struct {
    const char* code;
    const lv_img_dsc_t* img;
} image_map_t;

static const image_map_t image_map[] = {
    {"ae", &ae},
    {"ar", &ar},
    {"at", &at},
    {"au", &au},
    {"az", &az},
    {"be", &be},
    {"bh", &bh},
    {"br", &br},
    {"ca", &ca},
    {"cn", &cn},
    {"de", &de},
    {"dk", &dk},
    {"es", &es},
    {"fi", &fi},
    {"fr", &fr},
    {"gb", &gb},
    {"hard", &hard},
    {"hu", &hu},
    {"it", &it},
    {"jp", &jp},
    {"mc", &mc},
    {"medium", &medium},
    {"mx", &mx},
    {"nl", &nl},
    {"nz", &nz},
    {"sa", &sa},
    {"sg", &sg},
    {"soft", &soft},
    {"th", &th},
    {"un", &un},
    {"us", &us},
};

const lv_img_dsc_t* get_image_by_code(const char* code) {
    for (int i = 0; i < sizeof(image_map)/sizeof(image_map[0]); i++) {
        if (strcmp(image_map[i].code, code) == 0) return image_map[i].img;
    }
    return nullptr;
}

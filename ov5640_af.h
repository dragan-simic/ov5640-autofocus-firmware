#include <stdint.h>
#include <stdbool.h>

#define AF_DIR  "firmware"
#define AF_BIN  "ov5640_af_%d.bin"
#define AF_REGS "ov5640_af_%d.regs"

#define AF_BASE 0x8000

typedef struct af_reg {
	uint16_t reg;
	uint8_t val;
} af_reg;

typedef struct af {
	union { uint8_t *bin; af_reg *regs; } data;
	int len;
	bool regs;
} af;

#include "ov5640_af_1.h"
#include "ov5640_af_2.h"
#include "ov5640_af_3.h"
#include "ov5640_af_4.h"
#include "ov5640_af_5.h"
#include "ov5640_af_6.h"
#include "ov5640_af_7.h"

af ov5640_af[] = { {
	.data = { .bin = ov5640_af_1 },
	.len  = sizeof(ov5640_af_1) / sizeof(uint8_t),
	.regs = false
}, {
	.data = { .bin = ov5640_af_2 },
	.len  = sizeof(ov5640_af_2) / sizeof(uint8_t),
	.regs = false
}, {
	.data = { .regs = ov5640_af_3 },
	.len  = sizeof(ov5640_af_3) / sizeof(af_reg),
	.regs = true
}, {
	.data = { .regs = ov5640_af_4 },
	.len  = sizeof(ov5640_af_4) / sizeof(af_reg),
	.regs = true
}, {
	.data = { .regs = ov5640_af_5 },
	.len  = sizeof(ov5640_af_5) / sizeof(af_reg),
	.regs = true
}, {
	.data = { .regs = ov5640_af_6 },
	.len  = sizeof(ov5640_af_6) / sizeof(af_reg),
	.regs = true
}, {
	.data = { .bin = ov5640_af_7 },
	.len  = sizeof(ov5640_af_7) / sizeof(uint8_t),
	.regs = false
} };


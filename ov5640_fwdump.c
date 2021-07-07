#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "ov5640_af.h"

int main()
{
	unsigned int i, j, r, c, bw, len = sizeof(ov5640_af) / sizeof(af);
	uint16_t rc, rl;
	char fnb[100], fnr[100];
	bool cf;
	struct stat ds;
	FILE *fp;
	af_reg regs[100];

	if (stat(AF_DIR, &ds) == -1)	/* not a TOCTOU bug */
		if (mkdir(AF_DIR, 0755) == 0)
			puts("Directory `" AF_DIR "' created");

	for (i = 0; i < len; i++) {
		r = c = 0;
		cf = false;

		sprintf(fnb, AF_DIR "/" AF_BIN, i + 1);
		fp = fopen(fnb, "w");

		if (!ov5640_af[i].regs) {	/* flat firmware data? */
			bw = ov5640_af[i].len;

			for (j = 0; j < ov5640_af[i].len; j++)
				fputc(ov5640_af[i].data.bin[j], fp);
		} else {
			bw = rl = 0;

			for (j = 0; j < ov5640_af[i].len; j++) {
				rc = ov5640_af[i].data.regs[j].reg;

				if (rc >= AF_BASE) {	/* firmware data? */
					if ((rl > 0) && ((rl + 1) != rc))
						printf("ERROR: File `%s' not continuous, register 0x%04x expected, 0x%04x found\n",
						       fnb, rl + 1, rc);

					fputc(ov5640_af[i].data.regs[j].val, fp);

					rl = rc;
					bw++;

					if (!cf) {	/* new data chunk? */
						cf = true;
						c++;
					}
				} else {	/* standalone registers */
					if (cf) {
						regs[r++] = (af_reg) { 0, 0 };
						cf = false;
					}

					regs[r++] = (af_reg) {
						.reg = rc,
						.val = ov5640_af[i].data.regs[j].val
					};
				}
			}

			if (cf && (r > 0))	/* tailing data chunk? */
				regs[r++] = (af_reg) { 0, 0 };

			if (c > 1)
				printf("ERROR: File `%s' not continuous, %d data chunks found\n", fnb, c);
		}

		fclose(fp);

		if (r > 0) {	/* standalone registers? */
			sprintf(fnr, AF_DIR "/" AF_REGS, i + 1);
			fp = fopen(fnr, "w");

			for (j = 0; j < r; j++)
				if (regs[j].reg > 0)
					fprintf(fp, "0x%04x: 0x%02x\n", regs[j].reg, regs[j].val);
				else
					fputs("[firmware image]\n", fp);

			fclose(fp);
			printf("Files `%s' (%d bytes) and `%s' (%d registers) created\n", fnb, bw, fnr, r);
		} else
			printf("File `%s' created (%d bytes)\n", fnb, bw);
	}

	return 0;
}


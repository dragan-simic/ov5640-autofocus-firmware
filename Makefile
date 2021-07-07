af_dir = firmware

all:
	gcc -Wall -O2 ov5640_fwdump.c -o ov5640_fwdump

clean: clean-bin
	rm -f $(af_dir)/ov5640_af_*.bin $(af_dir)/ov5640_af_*.regs
	if [ -d $(af_dir) ]; then rmdir $(af_dir); fi

clean-bin:
	rm -f ov5640_fwdump


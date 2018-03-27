1. static volatile struct __ase_reg_t *ase_dev[DE_NUM][CHN_NUM];
int de_ase_set_reg_base(unsigned int sel, unsigned int chno, void *base)
{
	ase_dev[sel][chno] = (struct __ase_reg_t *) base;

	return 0;
}

struct __ase_reg_t {
	union ASE_CTRL_REG ctrl;
	union ASE_SIZE_REG size;
	union ASE_WIN0_REG win0;
	union ASE_WIN1_REG win1;
	union ASE_GAIN_REG gain;
};

union ASE_CTRL_REG {
	unsigned int dwval;
	struct {
		unsigned int en:1;
		unsigned int win_en:1;
		unsigned int res0:30;
	} bits;
};

2. static void __iomem *de_base;
s32 de_clk_set_reg_base(uintptr_t reg_base)
{
	de_base = (void __iomem *)reg_base;

	return 0;
}

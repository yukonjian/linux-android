#ifndef PNX8181_CLOCK_H
#define PNX8181_CLOCK_H
#include <linux/module.h>
#include <linux/types.h>

#define FLAG_NONE	0
#define FLAG_ENABLE	1
#define FLAG_PLL	2

struct clk {
	struct list_head	childs;
	unsigned long		rate;
	struct module		*owner;
	const char		*name;
	int			enable_bit;
	int			flags;
};

struct pnx8181_clk_usage {
	u32 *gatesc;
};

#define CLK_GATED_FLAGS(_name, _bit, _flags) \
	{\
		.name = _name,\
		.enable_bit = _bit,\
		.flags = _flags,\
	},
#define CLK_GATED(_name, _bit) \
	CLK_GATED_FLAGS(_name, _bit, FLAG_NONE)
#define CLK_PLL(_name, _rate) \
	{\
		.name = _name,\
		.rate = _rate, \
		.flags = FLAG_PLL \
	},

#endif /* PNX8181_CLOCK_H */

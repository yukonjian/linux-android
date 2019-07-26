1. 寄存器操作
#define SW_FIELD_MASK_NOT_U32(len, offset) \
		(~(SW_BIT_MASK_U32(len) << (offset)))

#define SW_BIT_MASK_U32(nr) (~(0xFFFFFFFF << (nr)))

#define SW_REG_SET_BY_FIELD_U32(reg_value, field_value, bit_offset, field_len)\
    do { \
        (reg_value) = \
            (((reg_value) & SW_FIELD_MASK_NOT_U32((field_len),(bit_offset))) \
              | (((field_value) & SW_BIT_MASK_U32(field_len)) << (bit_offset)));\
    } while (0)

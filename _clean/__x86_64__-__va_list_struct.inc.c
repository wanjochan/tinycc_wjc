typedef struct {
	unsigned int gp_offset;
	unsigned int fp_offset;
	union {
		unsigned int overflow_offset;
		char *overflow_arg_area;
	};
	char *reg_save_area;
} __va_list_struct;


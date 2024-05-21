#pragma once
#include <stdint.h>
#include <stdlib.h>

#define OP_LOAD 0x03
#define OP_STORE 0x23
#define OP_BRANCH 0x63
#define OP_JAL 0x6F
#define OP_JALR 0x67
#define OP_MISC_MEM 0x0F
#define OP_OP 0x33
#define OP_OPI 0x13
#define OP_OP32 0x3B
#define OP_OPI32 0x1B
#define OP_SYSTEM 0x73
#define OP_LUI 0x37
#define OP_AUIPC 0x17

#define RV64I_SIZE 4
#define RV64M_SIZE 4
#define RV64A_SIZE 4
#define RV64F_SIZE 4
#define RV64D_SIZE 4
#define RV64C_SIZE 2
#define RV64Z_SIZE 4

enum argtype_e {
	arg_none,
	arg_immediate,
	arg_register,
	arg_symbol,
};

struct args_t {
	struct arg_t {
		enum argtype_e type;
		size_t arg;
	} a[3];
};

struct bytecode_t {
	size_t size;
	unsigned char *data;
};

struct formation_t;
typedef struct bytecode_t(form_handler)(struct formation_t, struct args_t,
					size_t);

struct formation_t {
	const char *name;
	size_t isize;
	form_handler *handler;
	uint8_t opcode;
	uint8_t funct3;
	uint16_t funct7;
};

extern const struct bytecode_t error_bytecode;

/* form handler sets */
extern const struct formation_t rv64s[]; /* Shortcuts */
extern const struct formation_t rv64i[];
extern const struct formation_t rv64m[];
extern const struct formation_t rv64a[];
extern const struct formation_t rv64f[];
extern const struct formation_t rv64d[];
extern const struct formation_t rv64c[];
extern const struct formation_t rv64z[]; /* zifencei and zicsr extensions */

struct bytecode_t form_empty_bytecode(void);

/* shortcut instructions bytecode generation */
form_handler form_nop;
form_handler form_load_short;
form_handler form_math;
form_handler form_setif;
form_handler form_single; // implement with float extension
form_handler form_double; // ^^^
form_handler form_branchifz;
form_handler form_branchifr;
form_handler form_jump;
form_handler form_ret;

/* basic integer instruction type bytecode generation */
form_handler form_rtype;
form_handler form_itype;
form_handler form_itype2;
form_handler form_stype;
form_handler form_btype;
form_handler form_utype;
form_handler form_jtype;
form_handler form_syscall;
form_handler form_fence;

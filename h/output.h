#pragma once

#include <stdio.h>

#define SECTION_COUNT 10
enum sections_e {
  section_null,
  section_text,
  section_relatext,
  section_data,
  section_bss,
  section_rodata,
  section_riscvattributes,
  section_symtab,
  section_strtab,
  section_shstrtab,
};

struct sectionpos_t {
  enum sections_e section;
  long offset;
};

struct section_t {
  size_t offset;
  size_t size;
  char *contents;
};

extern enum sections_e outputsection;


void change_output(enum sections_e);

struct sectionpos_t get_outputpos(void);
void inc_outputsize(enum sections_e, long);
void set_outputpos(struct sectionpos_t);

size_t calc_fileoffset(struct sectionpos_t);


int alloc_output(void);

size_t write_sectiondata(const char *, size_t, struct sectionpos_t);

int flush_output(FILE *);

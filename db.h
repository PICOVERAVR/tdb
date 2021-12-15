#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>

#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>

#include <signal.h>
#include <stdbool.h>

#define NUM_BREAKPOINTS 32
#define TRAP_CODE 0xCC

#pragma once

enum {
	DUMP_REGS,
    SINGLE_STEP,
    B_CONTINUE,
    B_BREAK,
    PROG_INFO,
    KILL_QUIT,
 	HELP,
	LIST_BP,
    WATCHP,
	END_CMD // sentinel value
 };

int get_input();
int get_mem_break();
void print_breakpoints(uint64_t *break_list);
void check_clear_bp(pid_t child, uint64_t *list, uint64_t *data, int *next_free);

extern const char *help_text;

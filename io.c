#include "db.h"

typedef struct cmd_string_s {
	int num;
	const char *str; // full command name
	const char *short_str; // short version of command name (single letter usually)
} cmd_string;

const cmd_string list_cmd [END_CMD] = {
	{DUMP_REGS,   "dump", "d"},
	{SINGLE_STEP, "step", "s"},
	{B_CONTINUE,  "continue", "c"},
	{B_BREAK,     "break", "b"},
	{PROG_INFO,   "info", "i"},
	{KILL_QUIT,   "quit", "q"},
	{HELP,        "help", "h"},
	{LIST_BP,	  "list", "l"},
	{WATCHP, 	  "watch", "w"},
};

void print_breakpoints(uint64_t *break_list) {
    for (int i = 0; i < NUM_BREAKPOINTS; i++) {
        if (break_list[i] == 0) {
            return;
        }   
        printf("breakpoint %d at address %#lx\n", i, break_list[i]);
    }   
}

void check_clear_bp(pid_t child, uint64_t *list, uint64_t *data, int *next_free) {
    struct user_regs_struct temp_regs;

    ptrace(PTRACE_GETREGS, child, 0, &temp_regs);
    for (int i = 0; i <= *next_free; i++) {
        if (list[i] == temp_regs.rip-1) {
            printf("Resuming from breakpoint %d\n", i); 
            ptrace(PTRACE_POKETEXT, child, list[i], data[i]);
            temp_regs.rip--;
            ptrace(PTRACE_SETREGS, child, 0, &temp_regs);
            (*next_free)--;
        }   
    }   
}

int get_input() {
	char in[512];
	printf("> ");
	int err = scanf(" %s", in); // remove newline here?
	if (err < 0) {
		perror("scanf");
		return -1;
	} else {
		for (int i = 0; i < END_CMD; i++) {
			if (strcmp(in, list_cmd[i].str) == 0 || strcmp(in, list_cmd[i].short_str) == 0) {
				return list_cmd[i].num;
			}
		}
	}
	return -1;
}

int get_mem_break() {
	long long int addr;
	int err = scanf(" %llx", &addr);
	if (err < 0) {
		perror("scanf");
		return -1;
	}
	return addr;
}

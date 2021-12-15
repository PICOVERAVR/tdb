CC = gcc
DFLAGS = -Wall -std=gnu11
SRC := $(filter-out $(exclude), $(wildcard *.c)) # grab anything with a .c ending

USER_FLAGS := $(vars)
UNAME := $(shell uname -sm)

debug: pre
	@$(CC) -g $(SRC) $(DFLAGS) -Og -o 'db.out'
	@echo "Debug build completed."

small: pre
	@$(CC) $(SRC) $(DFLAGS) -s -Os -Wl,--gc-sections -o 'small.out'
	@strip --strip-all --remove-section=.comment --remove-section=.note small.out
	@echo "Small build completed."

pre:
	@echo "Building on $(UNAME), user params: $(USER_FLAGS)"

clean:
	@rm -f *.out
	@rm -f *.o
	

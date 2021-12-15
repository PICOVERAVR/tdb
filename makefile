CC = clang
CFLAGS = -Wall -Wextra -std=gnu11
SRC := $(filter-out $(exclude), $(wildcard *.c)) # grab anything with a .c ending

debug:
	@$(CC) -g $(SRC) $(CFLAGS) -Og -o tdb.debug
	@echo "Debug build completed."

opt:
	@$(CC) $(SRC) $(CFLAGS) -Ofast -flto -o tdb.opt
	@echo "Optimized build completed."

small:
	@$(CC) $(SRC) $(CFLAGS) -s -Os -Wl,--gc-sections -o tdb.small
	@strip --strip-all --remove-section=.comment --remove-section=.note tdb
	@echo "Small build completed."

clean:
	@rm -f tdb.*
	@rm -f *.o


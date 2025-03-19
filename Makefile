OUTPUT=ps2
CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wconversion
LDLIBS=-lm
SOURCES=main.c k.c ui.c hof.c
CPPCHECK=cppcheck --enable=performance,unusedFunction --error-exitcode=1
FORMAT_CODE=uncrustify --no-backup --replace -q -c ../uncrustify.cfg


all: $(OUTPUT)

$(OUTPUT):  $(SOURCES)
	@echo "building all"
	@$(CC) $(CFLAGS) $^ $(LDLIBS) -o $(OUTPUT)

%.o: %.c
	@printf"Building $@ module\n"
	@$(FORMAT_CODE)$^
	@$(CPPCHECK)$^
	@$(CC)$(CFLAGS) -c $^ -o $^

tests: k.c tests_k.c
	@$(CC) $(CFLAGS) $^ $(LDLIBS) -o tests

clean:
	@echo"Cleanup"
	rm -rf $(OUTPUT) tests *.o

push:
	git commit -a
	git push




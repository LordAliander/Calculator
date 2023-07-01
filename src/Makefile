COMPILER = clang
MESSAGE = "PROGRAM: \n"
FILENAME = main
LIB = stack

all:
	@$(COMPILER) -c $(LIB).c -o $(LIB).o
	@$(COMPILER) $(FILENAME).c $(LIB).o -o $(FILENAME).out
	@echo $(MESSAGE)
	@./$(FILENAME).out
	@echo "\n"
	make clean
	
clean:
	rm *.out
	rm *.o


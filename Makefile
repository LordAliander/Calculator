COMPILER = clang
MESSAGE = "PROGRAM: \n"
FILENAME = main_calculator

all:
	@$(COMPILER) $(FILENAME).c -o $(FILENAME).out; 
	@echo $(MESSAGE)
	@./$(FILENAME).out
	@echo "\n"
	make clean
	
clean:
	rm *.out


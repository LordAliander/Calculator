COMPILER = clang
MESSAGE = "PROGRAM: \n"
FILENAME = main
LIB = stack
BUILDDIR = build

all:
	@$(COMPILER) -c $(LIB).c -o $(BUILDDIR)/$(LIB).o
	@$(COMPILER) $(FILENAME).c $(BUILDDIR)/$(LIB).o -o $(BUILDDIR)/$(FILENAME).out
	@echo $(MESSAGE)
	@./$(FILENAME).out
	@echo "\n"
	make clean
	
clean:
	rm *.out
	rm *.o
	rm $(BUILDDIR)/*.out
	rm $(BUILDDIR)/*.o



COMPILER = clang
MESSAGE = "PROGRAM: \n"
FILENAME = main
LIB1 = stack
BUILDDIR = build

all:
	@$(COMPILER) -c $(LIB1).c -o $(BUILDDIR)/$(LIB1).o
	@$(COMPILER) $(FILENAME).c $(BUILDDIR)/$(LIB1).o -o $(BUILDDIR)/$(FILENAME).out
	@echo $(MESSAGE)
	@./$(BUILDDIR)/$(FILENAME).out
	@echo "\n"
	@echo "Cleaning build directory..."
	@make clean
	
clean:
	@rm $(BUILDDIR)/*.out
	@rm $(BUILDDIR)/*.o
	@echo "done"

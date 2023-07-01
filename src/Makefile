COMPILER = clang
MESSAGE = "PROGRAM: \n"
FILENAME = main
LIB = stack
BUILDDIR = build

all:
	@$(COMPILER) -c $(LIB).c -o $(BUILDDIR)/$(LIB).o
	@$(COMPILER) $(FILENAME).c $(BUILDDIR)/$(LIB).o -o $(BUILDDIR)/$(FILENAME).out
	@echo $(MESSAGE)
	@./$(BUILDDIR)/$(FILENAME).out
	@echo "\n"
	@echo "Cleaning build directory..."
	@make clean
	
clean:
	@rm $(BUILDDIR)/*.out
	@rm $(BUILDDIR)/*.o
	@echo "done"

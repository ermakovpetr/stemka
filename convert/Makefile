EXE=../isp2stem
OBJ=flexrule.o genmorph.o

all: $(EXE) $(OBJ)

clean:
	@rm -f $(OBJ)

clean_all: clean
	@rm -f $(EXE)

flexrule.o: flexrule.cpp flexrule.h flexTree.h regexapi.h Makefile
	@$(CC) -c flexrule.cpp

genmorph.o: genmorph.cpp flexrule.h flexTree.h regexapi.h Makefile
	@$(CC) -c genmorph.cpp

$(EXE): $(OBJ) Makefile
	@echo Linking $(EXE)
	@$(CC) -o $(EXE) $(OBJ)

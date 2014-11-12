EXE=../checkrus
OBJ=checkrus.o

all: $(EXE) $(OBJ)

clean:
	@rm -f $(OBJ)

clean_all: clean
	@rm -f $(EXE)

checkrus.o: checkrus.cpp
	@$(CC) -c checkrus.cpp

$(EXE): $(OBJ)
	@echo Linking $(EXE)
	@$(CC) -o $(EXE) $(OBJ) ../libstemka.a


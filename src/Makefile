CFLAGS = -O
CC = g++
SRC = util.cpp PascalTypesLibrary.cpp DBOField.cpp DBObject.cpp DBOTable.cpp main.cpp 
OBJ = $(SRC:.cpp = .o)
codegen: $(OBJ)
	$(CC) $(CFLAGS) -o codegen $(OBJ)
clean:
	rm -f core *.o

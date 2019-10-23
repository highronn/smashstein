LDFLAGS = -lglut -lGL -lglui -lm
CFLAGS = -Wall

CMP = bin/
SRC = source/
HDR = include/

EXE = $(CMP)OBJ
OBJ = $(CMP)main.o $(CMP)Mesh.o $(CMP)Vertex.o

CXX = g++

all: $(EXE)

${EXE}: $(OBJ)
	@echo linking $(EXE) 
	$(CXX) $(LDFLAGS) $(OBJ) -o $(EXE)
	
run: $(EXE)
	./$(EXE)

clean:
	rm -f $(CMP)*.o $(EXE)
	
$(CMP)%.o: $(SRC)%.cpp $(HDR)%.hpp $(HDR)variables.hpp
	@echo compiling $@ 
	$(CXX) $(CFLAGS) -c $< -o $@

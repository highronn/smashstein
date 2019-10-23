CC = g++
CFLAGS = -Wall -I./include -I/home/aherubel/lib/include/librt -D REENTRANT
LDFLAGS += -L./lib

#-- LINUX
LDFLAGS += -lglut -lGLEW -lGLU -lGL

DIR_OBJ = ./
DIR_SRC = ./
DIR_INC = ./


SRC =  MD2Model.cpp main.cpp Fonctions.cpp

OBJ = $(SRC:.cpp=.o)
OBJS = $(addprefix $(DIR_OBJ), $(OBJ))
DEPEND = $(addprefix $(DIR_SRC), $(SRC))
RM = rm -rf
EXEC = md2load

DATE= $$(date '+%d%b%Y_%Hh%M' | tr '[A-Z]' '[a-z]')
FILENAME = $(DATE).tar.gz


all: $(EXEC)
	@echo "--------------------------------------------------------------"
	@echo "            Pour executer, taper : make exec "
	@echo "--------------------------------------------------------------"

$(EXEC): $(OBJS)
	@echo "--------------------------------------------------------------"
	@echo "            LINKING... "
	@echo "--------------------------------------------------------------"
	$(CC) -o $@ $^ $(LDFLAGS)
	@echo "---- Done..."
	@echo "--------------------------------------------------------------"



obj/%.o: $(DIR_SRC)%.cpp $(DIR_INC)%.hpp
	@echo "---- Compiling $* "
	$(CC) -o $@ -c $< $(CFLAGS)
	@echo "---- Done..."
	@echo "--------------------------------------------------------------"

.PHONY: clean ultraclean save supersave exec

clean:
	@echo "--------------------------------------------------------------"
	@echo "           CLEAN"
	@echo "--------------------------------------------------------------"
	rm -Rf *.o 

ultraclean : clean
	@echo "           & ULTRACLEAN"
	@echo "--------------------------------------------------------------"
	@rm -f $(EXEC)
	
save :
	@echo "--------------------------------------------------------------"
	@echo "           SAVE "
	@echo "--------------------------------------------------------------"
	tar -cvzf $(FILENAME) include/* lib/* src/* obj/* bin/* data/* Makefile
	
exec:all
	./$(EXEC)


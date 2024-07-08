# make dynamics

# main program's name
MAIN_PROGRAM_NAME := dynamics


# the header files that main program includes
MAIN_PROGRAM_HEADER := .\screen\screen.h


# sub directory
SCREEN_DIR := .\screen

VPATH := $(SCREEN_DIR)


# object file in the sub directory
SCREEN_OBJ_FILE := graph.o setting.o show.o vector.o draw.o


# compiler
CC := gcc
CPPC := g++





### all
all: $(MAIN_PROGRAM_NAME).exe


###################################### compile program ######################################

# exe file
$(MAIN_PROGRAM_NAME).exe: $(MAIN_PROGRAM_NAME).o $(SCREEN_OBJ_FILE)
	$(CPPC) $^ -o $@


# compile main program
$(MAIN_PROGRAM_NAME).o: $(MAIN_PROGRAM_NAME).cpp $(MAIN_PROGRAM_HEADER)
	$(CPPC) -c $<

############################################################################################





###################################### compile screen ######################################

graph.o: graph.c screen_object.h vector.h PI.h graph.h
	$(CC) -c $<

setting.o: setting.cpp screen_object.h draw.h panel_constant.h
	$(CPPC) -c $<

show.o: show.c screen_object.h draw.h
	$(CC) -c $<

vector.o: vector.c vector.h
	$(CC) -c $<

draw.o: draw.c screen_object.h vector.h graph.h
	$(CC) -c $<

############################################################################################






### delete obj file
clean_obj:
	-@del *.o


### delete obj file and exe file
clean:
	-@$(MAKE) clean_obj
	-@del $(MAIN_PROGRAM_NAME).exe


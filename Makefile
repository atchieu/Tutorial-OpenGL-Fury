# COMPILER
CC=/Users/atchieu/Work/Compilers/gcc/4.8.0/bin/gcc 

# FLAGS
CPPFLAGSOPT += -fstrict-aliasing -fdiagnostics-show-option
CPPFLAGSOPT += -msse3
CPPFLAGSOPT += -O3 
CPPFLAGSOPT += -g
CPPFLAGSOPT += -std=c++0x
CPPFLAGSOPT += \
	-Wall \
	-Wno-missing-braces \
	-Wno-sign-compare \
	-Wno-parentheses

OPENMP_FLAG = -fopenmp
TBB_INC_DIR = /usr/local/tbb
TBB_LIB_DIR = /usr/local/lib
VTK_INC_DIR = /usr/local/include/vtk-5.10
VTK_LIB_DIR = /usr/local/lib/vtk-5.10
OPENGL_LIB = -framework OpenGL -framework GLUT /usr/local/lib/libGLEW.a

CPPFLAGS += 
CPPFLAGS += -I$(TBB_INC_DIR) 
CPPFLAGS += -I$(VTK_INC_DIR) 
CPPFLAGS += $(OPENMP_FLAG)

LIBS += \
	-L$(TBB_LIB_DIR) \
	-L$(VTK_LIB_DIR) \
	$(OPENGL_LIB) \
	$(OPENMP_FLAG)

LIBS += -lstdc++

ifeq "$(config)" "production"
CPPFLAGS += -DNDEBUG
endif

# OBJECTS

EX1_OBJS = \
	example1.o

EX2_OBJS = \
	example2.o

EX3_OBJS = \
	example3.o

EX4_OBJS = \
	example4.o

EX5_OBJS = \
	example5.o \
	texture.o

EX6_OBJS = \
	example6.o

EX7_OBJS = \
	example7.o

EX8_OBJS = \
	example8.o
	
EX9_OBJS = \
	example9.o
	
EX10_OBJS = \
	example10.o

# RULES

.DEFAULT_GOAL := ex1

ex1: $(EX1_OBJS)
	$(CC) $(LIBS) $^ -o $@
	@echo 
	@echo DONE
	@echo 

ex2: $(EX2_OBJS)
	$(CC) $(LIBS) $^ -o $@
	@echo 
	@echo DONE
	@echo 

ex3: $(EX3_OBJS)
	$(CC) $(LIBS) $^ -o $@
	@echo 
	@echo DONE
	@echo 

ex4: $(EX4_OBJS)
	$(CC) $(LIBS) $^ -o $@
	@echo 
	@echo DONE
	@echo 

ex5: $(EX5_OBJS)
	$(CC) $(LIBS) $^ -o $@
	@echo 
	@echo DONE
	@echo

ex6: $(EX6_OBJS)
	$(CC) $(LIBS) $^ -o $@
	@echo 
	@echo DONE
	@echo
	
ex7: $(EX7_OBJS)
	$(CC) $(LIBS) $^ -o $@
	@echo 
	@echo DONE
	@echo
	
ex8: $(EX8_OBJS)
	$(CC) $(LIBS) $^ -o $@
	@echo 
	@echo DONE
	@echo
	
ex9: $(EX9_OBJS)
	$(CC) $(LIBS) $^ -o $@
	@echo 
	@echo DONE
	@echo
	
ex10: $(EX10_OBJS)
	$(CC) $(LIBS) $^ -o $@
	@echo 
	@echo DONE
	@echo

all: ex1 ex2 ex3 ex4 ex5 ex6 ex7 ex8 ex9 ex10

%.o: %.cpp
	$(CC) $(CPPFLAGS) $(CPPFLAGSOPT) -c $^ -o $@

clean:
	rm -f *.o
	rm -f ex1 ex2 ex3 ex4 ex5 ex6 ex7 ex8 ex9 ex10






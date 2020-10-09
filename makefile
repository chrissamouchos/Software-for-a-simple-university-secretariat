# paths
INCLUDE_PATH = ./include
SRC_PATH = ./src
OBJS_PATH = ./bin
INPUT = ./input

#Define the compiler
CC = gcc

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
CFLAGS = -I$(INCLUDE_PATH)

#Define text inputs1 and 2
INPUT1 = input1.txt
INPUT2 = input2.txt

#Define the dependencies
DEP = 	main.c \
		ADTHashtable.c \
		Student.c \
		Utils.c

#Create the .o file with the needed functions
OBJS = $(patsubst %.c,$(OBJS_PATH)/%.o,$(DEP))

#UNLEASH THE FUll POWER OF VALGRIND!!!
FULLVAL = --leak-check=full -v

# The executable programm
EXEC = mngstd

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(CFLAGS)

$(OBJS_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) -c $^ -o $@ $(CFLAGS)

#Run the programm with args1
run1: $(EXEC)
	./$(EXEC) $(INPUT)/$(INPUT1)

#Run the programm with args2
run2: $(EXEC)
	./$(EXEC) $(INPUT)/$(INPUT2)

#Determine full valgrind
fvalgrind:
	valgrind $(FULLVAL) ./$(EXEC)

#Determine simple valgrind
svalgrind:
	valgrind ./$(EXEC)

#Clean workspace
clean:
	rm -f $(OBJS) $(EXEC)
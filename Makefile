C = g++
C_FLAGS = -w -lraylib -lopengl32 -lgdi32 -lwinmm -O2

make:
	$(C) Source/*.cpp -o Build/game $(C_FLAGS)
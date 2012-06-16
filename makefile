MACHINE= $(shell uname -s)

ifeq ($(MACHINE),Darwin)
	OPENGL_INC= -FOpenGL
	OPENGL_LIB= -framework OpenGL
else
	OPENGL_INC= 
	OPENGL_LIB= -lGL -lGLU
endif

SFML_INC= -I/usr/include/SFML
CEGUI_INC= -I/usr/local/include/CEGUI

LIB_DIRS= -L/usr/local/lib/
SFML_LIB= -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio
OTHER_LIB= -lXxf86vm -lX11 -lz

CXX=g++
COMPILER_FLAGS= -O0 -g -Wall
INCLUDE= $(SFML_INC)
LIBS= $(LIB_DIRS) $(SFML_LIB) $(OPENGL_LIB) $(OTHER_LIB)

Test: Test.o SFML_TextureManager.o SFML_WindowEventManager.o IMGuiManager.o IMButton.o IMInstantButton.o IMCursorManager.o
	$(CXX) -o"Test" ./Test.o ./SFML_TextureManager.o ./SFML_WindowEventManager.o ./IMGuiManager.o ./IMCursorManager.o ./IMInstantButton.o ./IMButton.o $(LIBS) 

Test.o: Test.cpp
	$(CXX) $(COMPILER_FLAGS) -c -o"Test.o" ./Test.cpp $(INCLUDE)

SFML_TextureManager.o: SFML_TextureManager.cpp SFML_TextureManager.hpp
	$(CXX) $(COMPILER_FLAGS) -c -o"SFML_TextureManager.o" ./SFML_TextureManager.cpp $(INCLUDE)

SFML_WindowEventManager.o: SFML_WindowEventManager.cpp SFML_WindowEventManager.hpp SFML_Listeners.hpp
	$(CXX) $(COMPILER_FLAGS) -c -o"SFML_WindowEventManager.o" ./SFML_WindowEventManager.cpp $(INCLUDE)

IMGuiManager.o: IMGuiManager.cpp IMGuiManager.hpp IMGuiWidget.hpp SFML_WindowEventManager.hpp IMCursorManager.hpp
	$(CXX) $(COMPILER_FLAGS) -c -o"IMGuiManager.o" ./IMGuiManager.cpp $(INCLUDE)

IMCursorManager.o: IMCursorManager.cpp IMCursorManager.hpp SFML_GlobalRenderWindow.hpp
	$(CXX) $(COMPILER_FLAGS) -c -o"IMCursorManager.o" ./IMCursorManager.cpp $(INCLUDE)

IMButton.o: IMButton.cpp IMButton.hpp IMGuiWidget.hpp
	$(CXX) $(COMPILER_FLAGS) -c -o"IMButton.o" ./IMButton.cpp $(INCLUDE)

IMInstantButton.o: IMInstantButton.cpp IMInstantButton.hpp IMButton.hpp IMButton.cpp IMGuiWidget.hpp
	$(CXX) $(COMPILER_FLAGS) -c -o"IMInstantButton.o" ./IMInstantButton.cpp $(INCLUDE)

clean:
	rm -rf *.o

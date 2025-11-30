# Carpetas
SRC = src
INC = include
OBJDIR = build
DOC = doc
DATOS = datos

# Archivos fuente
CPP = $(SRC)/main.cpp $(SRC)/evento.cpp $(SRC)/agendaeventos.cpp
OBJ = $(patsubst $(SRC)/%.cpp,$(OBJDIR)/%.o,$(CPP))

# Compilador y opciones
CXX = g++
CXXFLAGS = -Wall -std=c++11 -I$(INC)

# Ejecutable
TARGET = programa

# Regla principal
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

$(OBJDIR)/%.o: $(SRC)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(TARGET)

doc:
	doxygen $(DOC)/Doxyfile
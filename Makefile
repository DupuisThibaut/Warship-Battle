# Variables
CXX = g++
CXXFLAGS = -std=c++11
SOURCES = warship.cpp
EXECUTABLE = out/warship

# Règle par défaut
all: $(EXECUTABLE)

# Règle pour créer le dossier out si inexistant
out:
	mkdir -p out

# Règle pour construire l'exécutable
$(EXECUTABLE): out $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXECUTABLE)

# Règle pour nettoyer les fichiers générés
clean:
	rm -f $(EXECUTABLE) *.o

# Règle pour afficher les fichiers objets (en option)
objects:
	@echo $(SOURCES:.cpp=.o)

# Règle pour afficher des informations sur le makefile
info:
	@echo "CXX: $(CXX)"
	@echo "CXXFLAGS: $(CXXFLAGS)"
	@echo "SOURCES: $(SOURCES)"
	@echo "EXECUTABLE: $(EXECUTABLE)"

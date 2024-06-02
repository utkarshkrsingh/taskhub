CXX = g++
CXXFLAGS = -std=c++20 -Wall
LDFLAGS = -lsqlite3

SRCDIR = src
OBJDIR = obj
INCLUDEDIR = include

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))
EXECUTABLE = taskhub

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDEDIR) -c $< -o $@

.PHONY: clean

clean:
	rm -rf $(OBJDIR) $(EXECUTABLE)

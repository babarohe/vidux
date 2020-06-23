

# Makefile
PROGRAM = vidux_capture

CC := g++
CFLAGS := -Wall -Wextra -O3 $(shell pkg-config --cflags --libs opencv gtk+-3.0)
LDFLAGS :=
SOURCES = vidux-capture-main.cpp capture/capture.cpp vidux-capture-gui/capture_gui.cpp


# Build
$(PROGRAM): $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) $(LDFLAGS) -o $(PROGRAM)


# Run
run:
	./$(PROGRAM)

# Clean
clean:
	rm $(PROGRAM)

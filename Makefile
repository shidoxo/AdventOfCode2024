CXX = g++

CXXFLAGS = -std=c++20 -Wall -Wextra

run: clean
	@if [ -z "$(FILE)" ]; then \
		echo "Usage: make run FILE=path/to/your/file.cpp"; \
	else \
		echo "Compiling $(FILE)..."; \
		$(CXX) $(CXXFLAGS) $(FILE) -o runfile && echo "Running $(FILE)..." && ./runfile; \
	fi
	@$(MAKE) -s clean

.PHONY: clean
clean:
	@-rm -f runfile.exe
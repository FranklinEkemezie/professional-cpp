CXX := g++
CXXFLAGS := -std=c++23 -Wall -Wextra -g

BIN_DIR := bin

SOURCES := $(shell find . -type f -name '*.cpp')
PROGRAMS := $(patsubst ./%.cpp,$(BIN_DIR)/%,$(SOURCES))

$(info SOURCES:)
$(foreach source,$(SOURCES),$(info   $(source)))
$(info )

# $(info PROGRAMS:)
# $(foreach program,$(PROGRAMS),$(info   $(program)))
# $(info )

Makefile: ;

.PHONY: all clean

all: $(PROGRAMS)

$(BIN_DIR)/%: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(BIN_DIR)

%:
	@program="$(filter %/$@,$(PROGRAMS))"; \
	$(MAKE) --no-print-directory "$$program" >/dev/null; \
	echo; echo " ------------ Running: $@ [$$program] --------"; echo; \
	"./$$program"
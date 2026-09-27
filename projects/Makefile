CXX 		:= g++
CXXFLAGS 	:= -std=c++23 -Wall -Wextra -g -I src

BIN_DIR 	:= bin
BUILD_DIR	:= build

.PHONY: clean

Makefile: ;

# ------------------------------------------------------------
# Build a project:
#
#     make ProjectName
# ------------------------------------------------------------

%:
	@PROJECT="$@"; \
	if [ ! -d "$$PROJECT" ]; then \
		echo "Error: project '$$PROJECT' does not exist."; \
		exit 1; \
	fi; \
	\
	SOURCES=$$(find "$$PROJECT/src" -type f \( -name '*.cpp' \) | sort); \
	TESTS=$$(find "$$PROJECT/tests/unit" -type f -name '*Test.cpp' | sort); \
	\
	echo; \
	echo "========================================"; \
	echo " Building project: $$PROJECT"; \
	echo "========================================"; \
	echo; \
	\
	echo ">>> Compiling source files"; \
	for source in $$SOURCES; do \
		object="$$PROJECT/$(BIN_DIR)/$${source#$$PROJECT/}"; \
		object="$${object%.*}.o"; \
		mkdir -p "$$(dirname "$$object")"; \
		echo "    $$source"; \
		$(CXX) $(CXXFLAGS) -I"$$PROJECT/src" -c "$$source" -o "$$object" || exit 1; \
	done; \
	\
	echo; \
	echo ">>> Creating static library"; \
	mkdir -p "$$PROJECT/$(BUILD_DIR)"; \
	objects=$$(find "$$PROJECT/$(BIN_DIR)/src" -type f -name '*.o' | sort); \
	ar rcs "$$PROJECT/$(BUILD_DIR)/lib$$PROJECT.a" $$objects; \
	echo "    $$PROJECT/$(BUILD_DIR)/lib$$PROJECT.a"; \
	\
	echo; \
	echo ">>> Compiling tests"; \
	for test in $$TESTS; do \
		test_name=$$(basename "$$test" .cpp); \
		test_binary="$$PROJECT/$(BIN_DIR)/tests/unit/$$test_name"; \
		mkdir -p "$$(dirname "$$test_binary")"; \
		echo "    $$test"; \
		$(CXX) $(CXXFLAGS) -I"$$PROJECT/src" "$$test" "$$PROJECT/$(BUILD_DIR)/lib$$PROJECT.a" -o "$$test_binary" || exit 1; \
	done; \
	\
	echo; \
	echo ">>> Running tests"; \
	./run_tests.sh "$$PROJECT" || exit 1; \
	\
	echo; \
	echo ">>> Tests passed"; \
	echo; \
	\
	echo ">>> Building application"; \
	mkdir -p "$$PROJECT/$(BIN_DIR)/app"; \
	APP_SOURCES=$$(find "$$PROJECT/app" -type f \( -name '*.cpp' \) | sort); \
	for source in $$APP_SOURCES; do\
		object="$$PROJECT/$(BIN_DIR)/$${source#$$PROJECT/}"; \
		object="$${object%.*}.o"; \
		mkdir -p "$$(dirname "$$object")"; \
		echo "    $$source"; \
		$(CXX) $(CXXFLAGS) -I"$$PROJECT/src" -c "$$source" -o "$$object" || exit 1; \
	done; \
	\
	$(CXX) $(CXXFLAGS) -I"$$PROJECT/src" \
		$$(find "$$PROJECT/$(BIN_DIR)/app" -type f -name '*.o') \
		"$$PROJECT/$(BUILD_DIR)/lib$$PROJECT.a" \
		-o "$$PROJECT/$(BIN_DIR)/app/$$PROJECT" \
		|| exit 1; \
	\
	echo; \
	echo "========================================"; \
	echo " Running application: $$PROJECT"; \
	echo "========================================"; \
	echo; \
	"$$PROJECT/$(BIN_DIR)/app/$$PROJECT"

clean:
	@find . -type d -name "$(BIN_DIR)" -prune -exec rm -rf {} +
	@echo "Cleaned build files."
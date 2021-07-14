CXX=g++
CXXFLAGS= -std=c++11 -g -fprofile-arcs -ftest-coverage
LINKFLAGS= -lgtest -lpthread

SRC_DIR = src

TEST_DIR = test

SRC_INCLUDE = include
INCLUDE = -I ${SRC_INCLUDE} -I test

COVERAGE_RESULTS = results.coverage
COVERAGE_DIR = coverage

PROGRAM = inventory
PROGRAM_TEST = inventoryTest

.PHONY: all
all: clean-all $(PROGRAM) $(PROGRAM_TEST) static coverage style docs

# default rule for compiling .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf *~ $(SRC)/*.o $(TEST_SRC)/*.o *.gcov *.gcda *.gcno \
	$(COVERAGE_RESULTS) \
	$(PROGRAM_TEST) $(MEMCHECK_RESULTS) \
	$(COVERAGE_DIR) \
	docs html obj bin \

.PHONY: clean-all
clean-all: clean
	rm -rf $(PROGRAM) $(PROGRAM_TEST)

$(PROGRAM): $(SRC_DIR)/*.cpp $(SRC_DIR)/app/main.cpp
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) -I $(SRC_INCLUDE) $(SRC_DIR)/*.cpp $(SRC_DIR)/app/main.cpp

$(PROGRAM_TEST): $(TEST_DIR) $(SRC_DIR)
	$(CXX) $(CXXFLAGS) -o $(PROGRAM_TEST) $(INCLUDE) \
	$(TEST_DIR)/*.cpp $(SRC_DIR)/*.cpp $(LINKFLAGS)

tests: $(PROGRAM_TEST)
	$(PROGRAM_TEST)

memcheck: $(PROGRAM_TEST)
	valgrind --tool=memcheck --leak-check=yes $(PROGRAM_TEST)

static: ${SRC_DIR}
	cppcheck --verbose --enable=all ${SRC_DIR} ${TEST_DIR} ${SRC_INCLUDE} --suppress=missingInclude

coverage: $(PROGRAM_TEST)
	$(PROGRAM_TEST)
	# Determine code coverage
	lcov --capture --gcov-tool gcov --directory . --output-file $(COVERAGE_RESULTS)
	# Only show code coverage for the source code files (not library files)
	lcov --extract $(COVERAGE_RESULTS) "*/src/*" -o $(COVERAGE_RESULTS)
	#Generate the HTML reports
	genhtml $(COVERAGE_RESULTS) --output-directory $(COVERAGE_DIR)
	#Remove all of the generated files from gcov
	rm -f *.gc* $(COVERAGE_RESULTS)

style: ${SRC_DIR} ${TEST_DIR} ${SRC_INCLUDE}
	cpplint $(SRC_INCLUDE)/* ${SRC_DIR}/* ${TEST_DIR}/*

.PHONY: docs
docs:
	doxygen

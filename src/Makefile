.PHONY : all, build, clean, dist, test, gcov_report, valgrind_test

TARGET = drawBMP
CC = g++
CFLAGS = -g -Wall -Wextra -Werror -std=c++17
LIBRARIES = 
GCOV_FLAGS := -fprofile-arcs -ftest-coverage
VALGRIND_FLAGS := --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log
SOURCES := *.cc
TEST_SOURCES := tests/*.cc 
# GUI := gui/*.cc

DIST_DIR :=archive

ifeq ($(shell uname), Linux)
	TEST_FLAGS := -lcheck -lgtest -lm -lpthread -lrt -lsubunit -lncurses
else
	TEST_FLAGS := -lcheck -lgtest -lm -lpthread -lncurses
endif

OPEN_COMMAND =open
ifeq ($(OS), Linux)
	OPEN_COMMAND=xdg-open
else
	OPEN_COMMAND=open
endif

all: clean build

build:
	$(CC) ${SOURCES} ${CFLAGS} $(LIBRARIES) -o $(TARGET)

clean: clean_static_lib clean_log clean_exec clean_obj clean_gcov clean_lcov clean_lcov_report

dist:
	mkdir -p ${DIST_DIR}
	cp -rf brick_game/ ${DIST_DIR}/brick_game/
	cp -rf gui/ ${DIST_DIR}/gui/
	cp -rf Makefile ${DIST_DIR}/
	tar -czvf ${DIST_DIR}.tar.gz ${DIST_DIR}
	rm -rf ${DIST_DIR}


test:
	$(CC) $(SOURCES) ${TEST_SOURCES} $(TEST_FLAGS) -o ./test
	./test


gcov_report: clean
	@mkdir -p report
	${CC} -g $(SOURCES) ${TEST_SOURCES} $(TEST_FLAGS) $(GCOV_FLAGS) -o ./gcov_report.out
	./gcov_report.out
	lcov --no-external -t "test" -o test.info -c -d .
	genhtml -o report/ test.info
	${OPEN_COMMAND} ./report/index.html
	make clean_gcov


valgrind_test:
	@mkdir -p tests/build
	${CC} -g $(SOURCES) ${TEST_SOURCES} $(TEST_FLAGS) -o ./test
	valgrind ${VALGRIND_FLAGS} ./test


clean_static_lib:
	@find .. -type f -name "*.a" -exec rm {} \;
clean_log:
	@find .. -type f -name "*.log" -exec rm {} \;
clean_exec:
	@find .. -type f -name "*.out" -exec rm {} \;
	@find .. -type f -name "test" -exec rm {} \;
clean_obj:
	@find .. -type f -name "*.o" -exec rm {} \;
clean_gcov:
	@if [ -d "../src/gcov_report.out.dSYM" ]; then rm -rf ../src/gcov_report.out.dSYM; fi
	@find .. -type f -name "*.gcda" -exec rm {} \;
	@find .. -type f -name "*.gcno" -exec rm {} \;
clean_lcov:
	@find .. -type f -name "*.info" -exec rm {} \;
clean_lcov_report:
	@rm -rf report




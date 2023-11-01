CC=g++ -Wall -Werror -Wextra -std=c++17
TEST_FLAGS=-lgtest -pthread -lgtest_main -lstdc++ -lm
NAME = Model
GTEST_FLAG = --gtest_repeat=100 --gtest_shuffle
TEST_FUNC= PolishNotation.cc Arithmetic.cc
PATH_TO_TEST = ./tests

OS := $(shell uname -s)
ifeq ($(OS), Linux)
	TEST_FLAGS += -lsubunit -lrt -lm
	GOALS =  check_cppcheck valgrind
else
	GOALS =  clang check_cppcheck
endif

all: clean library tests
	make $(GOALS)

install:
	mkdir -p Calculator
	cd View; qmake -o ../Calculator/Makefile
	cd Calculator; make

uninstall:
	rm -rf Calculator

open:
	open Calculator/View.app

dvi: clean
	doxygen Doxyfile
	open html/index.html

dist:
	tar -czf SmartCalc.install.tar.gz ./* */*.cc */*.h

ubuntu:
	sudo apt-get update
	sudo apt-get upgrade -y
	sudo apt-get install valgrind -y
	sudo apt-get install libgtest-dev libgmock-dev -y
	sudo apt install g++ -y

dox:
	brew install doxygen

clean: uninstall
	cd tests; ls | find . -type f  ! -name "*.cc" ! -name "*.h" ! -name "*.cpp" | xargs rm -rf
	rm -rf html build-ViewTest-Desktop_x86_darwin_generic_mach_o_64bit-Debug
	rm -rf *.a *.o report gcov_report *.info gcov_report.dSYM SmartCalc.install.tar.gz

library:
	$(CC) -c Model/Model.cc
	ar rc libModel.a *.o
	ranlib libModel.a
	rm *.o

tests:
	cd $(PATH_TO_TEST);rm -f test; $(CC) $(TEST_FUNC) ../libModel.a -o test $(TEST_FLAGS); ./test $(GTEST_FLAG)

clang:
	clang-format -style="{BasedOnStyle: Google}" -n */*.h */*.cc */mainwindow.cpp

goclang:
	clang-format -style="{BasedOnStyle: Google}" -i */*.h */*.cc */mainwindow.cpp

valgrind: tests
	CK_FORK=no valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s ./$(PATH_TO_TEST)/test

push: clean goclang
	git add .
	git commit -m "$(c)"
	git push --set-upstream origin develop

check_cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config */*.h tests/*.cc

gcov_report:
	cd $(PATH_TO_TEST); $(CC)  -g --coverage $(TEST_FUNC) ../libController.a -o ../gcov_report  $(TEST_FLAGS)
	./gcov_report
	lcov -t "report" -o s21_test.info -c -d ./ --no-external --ignore-errors mismatch
	genhtml -o report s21_test.info
	open ./report/index.html

.PHONY: ubuntu clean clang goclang tests valgrind check_cppcheck push gcov_report library doxygen

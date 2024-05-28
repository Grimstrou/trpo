CFLAGS = -Wall -Wextra -Werror -fprofile-arcs -ftest-coverage -g -I.
CC = gcc
CPPFLAGS = -MMD 
LDFLAGS = -lgcov --coverage

TARGET_APP = bin/app
TARGET_TEST = bin/app-test

build: $(TARGET_APP)

test: $(TARGET_TEST)

$(TARGET_APP): obj/src/main.o obj/src/lib.a
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(TARGET_TEST): obj/test/main-test.o obj/src/lib.a 
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

obj/test/main-test.o: src/test/main.c
	@mkdir -p obj/test
	$(CC) -c $(CFLAGS) -I thirdparty $(CPPFLAGS) $< -o $@

obj/src/main.o: src/main/main.c
	@mkdir -p obj/src
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

obj/src/lib.a: obj/src/lib.o
	@mkdir -p obj/src
	ar -rcs $@ $<

obj/src/lib.o: src/lib/lib.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

run_tests: test
	./$(TARGET_TEST)

coverage: run_tests
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory out

clean:
	rm -f obj/src/*.a obj/src/*.d obj/src/*.o obj/test/*.d obj/test/*.o
	rm -f $(TARGET_APP) $(TARGET_TEST) *.gcda *.gcno *.gcov coverage.info
	rm -rf out

-include obj/src/main.d obj/src/lib.d
-include obj/test/main-test.d

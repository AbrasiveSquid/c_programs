# variables
CC = gcc
CFLAGS = -g -Wall -Wextra -std=c99 -fsanitize=address,undefined
TARGETS = my_cat 
OBJECTS = my_cat.o

#build all programs
all: $(TARGETS)

my_cat: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

my_cat.o: my_cat.c
	$(CC) $(CFLAGS) $< -c

.PHONY:

clean:
	rm -f $(TARGETS) *.o a.out 

# mem leak test
cat_leak:
	$(CC) $(CFLAGS) -fsanitize=address my_cat.c -o my_cat
	./my_cat ./cat_test_files/cat_test.txt -n

cat_tests: cat_combined_flags cat_without_newline cat_e_flag cat_number_and_blank cat_no_eof cat_escape_char cat_squeeze_test

cat_combined_flags: my_cat
	./my_cat -ns ./cat_test_files/line_num.txt >my_out 
	cat -ns ./cat_test_files/line_num.txt > sys_out
	diff my_out sys_out
	rm -f my_out sys_out


cat_without_newline: my_cat
	./my_cat ./cat_test_files/eof_after_3newline.txt > my_out
	cat ./cat_test_files/eof_after_3newline.txt > sys_out
	diff my_out sys_out
	rm -f my_out sys_out
	./my_cat -s ./cat_test_files/eof_after_3newline.txt > my_out 
	cat -s ./cat_test_files/eof_after_3newline.txt > sys_out
	diff my_out sys_out
	rm -f my_out sys_out

cat_e_flag: my_cat
	./my_cat -e ./cat_test_files/eof_no_newline.txt > my_out
	cat -e ./cat_test_files/eof_no_newline.txt > sys_out
	diff my_out sys_out
	rm -f my_out sys_out

cat_number_and_blank: my_cat
	./my_cat -n -b ./cat_test_files/line_num.txt > my_out
	cat -n -b ./cat_test_files/line_num.txt > sys_out
	diff my_out sys_out
	rm -f my_out sys_out
	./my_cat -b -n ./cat_test_files/line_num.txt > my_outa
	./my_cat -n -b ./cat_test_files/line_num.txt > my_outb
	diff my_outa my_outb 
	rm -f my_outa my_outb

cat_no_eof: my_cat
	./my_cat -vet ./cat_test_files/no_eof.txt > my_out
	cat -vet ./cat_test_files/no_eof.txt > sys_out
	diff my_out sys_out 
	rm -f my_out sys_out

cat_escape_char: my_cat
	./my_cat -vet ./cat_test_files/cat_test.txt > my_out
	cat -vet ./cat_test_files/cat_test.txt > sys_out
	diff my_out sys_out
	rm -f my_out sys_out

cat_squeeze_test: my_cat
	./my_cat -s ./cat_test_files/squeeze.txt > my_out
	cat -s ./cat_test_files/squeeze.txt > sys_out
	diff my_out sys_out
	rm -f my_out sys_out




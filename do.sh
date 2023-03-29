#!/bin/bash

mkdir outcome

c++ -Wall -Wextra -Werror -std=c++98 -D NAMESPACE=ft -c tester/test.cpp -o tester/test.o
c++ -Wall -Wextra -Werror -std=c++98 -D NAMESPACE=ft -c tester/test_utils.cpp -o tester/test_utils.o
c++ -Wall -Wextra -Werror -std=c++98 -D NAMESPACE=ft -c tester/vector_test.cpp -o tester/vector_test.o
c++ -Wall -Wextra -Werror -std=c++98 -D NAMESPACE=ft -c tester/Foo.cpp -o tester/Foo.o
c++ -Wall -Wextra -Werror -std=c++98 -D NAMESPACE=ft -c tester/stack_test.cpp -o tester/stack_test.o
c++ -Wall -Wextra -Werror -std=c++98 -D NAMESPACE=ft -c tester/map_test.cpp -o tester/map_test.o
c++ -Wall -Wextra -Werror -std=c++98 -D NAMESPACE=ft -c tester/set_test.cpp -o tester/set_test.o
c++ -Wall -Wextra -Werror -std=c++98 -D NAMESPACE=ft -c tester/test_leaks.cpp -o tester/test_leaks.o
c++ -Wall -Wextra -Werror -std=c++98 -D NAMESPACE=ft -c tester/test_time_ft.cpp -o tester/test_time_ft.o

c++ -Wall -Wextra -Werror -std=c++98 -D NAMESPACE=ft tester/test.o tester/test_utils.o tester/vector_test.o tester/Foo.o tester/stack_test.o tester/map_test.o tester/set_test.o -o test
c++ -Wall -Wextra -Werror -std=c++98 -D NAMESPACE=ft tester/test_leaks.o tester/test_utils.o tester/vector_test.o tester/Foo.o tester/stack_test.o tester/map_test.o tester/set_test.o -o test_leaks
c++ -Wall -Wextra -Werror -std=c++98 -D NAMESPACE=ft tester/test_time_ft.o tester/test_utils.o tester/vector_test.o tester/Foo.o tester/stack_test.o tester/map_test.o tester/set_test.o -o test_time

./test > outcome/ft.log
./test_leaks | tail -n19 > outcome/leaks.log
./test_time | grep time_ft: > outcome/time_ft.log


rm -rf test
rm -rf tester/test.o tester/vector_test.o tester/Foo.o tester/test_utils.o tester/stack_test.o tester/map_test.o tester/set_test.o tester/test_leaks.o tester/test_time_ft.o

c++ -Wall -Wextra -Werror -std=c++98 -D NAMESPACE=std -c tester/test.cpp -o tester/test.o
c++ -Wall -Wextra -Werror -std=c++98 -D NAMESPACE=ft -c tester/test_utils.cpp -o tester/test_utils.o
c++ -Wall -Wextra -Werror -std=c++98 -D NAMESPACE=std -c tester/vector_test.cpp -o tester/vector_test.o
c++ -Wall -Wextra -Werror -std=c++98 -D NAMESPACE=std -c tester/Foo.cpp -o tester/Foo.o
c++ -Wall -Wextra -Werror -std=c++98 -D NAMESPACE=std -c tester/stack_test.cpp -o tester/stack_test.o
c++ -Wall -Wextra -Werror -std=c++98 -D NAMESPACE=std -c tester/map_test.cpp -o tester/map_test.o
c++ -Wall -Wextra -Werror -std=c++98 -D NAMESPACE=std -c tester/set_test.cpp -o tester/set_test.o
c++ -Wall -Wextra -Werror -std=c++98 -D NAMESPACE=ft -c tester/test_time_std.cpp -o tester/test_time_std.o

c++ -Wall -Wextra -Werror -std=c++98 -D NAMESPACE=std tester/test.o tester/test_utils.o tester/vector_test.o tester/Foo.o tester/stack_test.o tester/map_test.o tester/set_test.o -o test
c++ -Wall -Wextra -Werror -std=c++98 -D NAMESPACE=std tester/test_time_std.o tester/test_utils.o tester/vector_test.o tester/Foo.o tester/stack_test.o tester/map_test.o tester/set_test.o -o test_time

./test > outcome/std.log
./test_time | grep time_std: > outcome/time_std.log

rm -rf test test_time test_leaks
rm -rf tester/test.o tester/vector_test.o tester/Foo.o tester/test_utils.o tester/stack_test.o tester/map_test.o tester/set_test.o tester/test_time_std.o

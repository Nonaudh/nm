#!/bin/bash

nm $1 $2 > test_result_nm.txt
./ft_nm $1 $2 > test_result_ft_nm.txt

diff test_result_nm.txt test_result_ft_nm.txt

rm test_result_nm.txt test_result_ft_nm.txt
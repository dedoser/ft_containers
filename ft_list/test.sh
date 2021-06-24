clang++ -g test_std_list.cpp -o std
clang++ -g test_ft_list.cpp -o ft
./ft > ft_res &
./std > std_res &
diff ft_res std_res
leaks ft | grep leaks > ft_leaks
leaks std | grep leaks > std_leaks

clang++ -g test_std_stack.cpp -o logs/std
clang++ -g test_ft_stack.cpp -o logs/ft
./logs/ft > logs/ft_res &
./logs/std > logs/std_res &
sleep 1
leaks ft | grep "0 leaks" > logs/ft_leaks
leaks std | grep "0 leaks" > logs/std_leaks
sleep 1;
diff logs/ft_res logs/std_res
echo "Leaks:"
echo -n "ft_stack  " ; cat logs/ft_leaks
echo -n "std_stack " ; cat logs/std_leaks

clang++ -g test_std_queue.cpp -o logs/std
clang++ -g test_ft_queue.cpp -o logs/ft
./logs/ft > logs/ft_res &
./logs/std > logs/std_res &
sleep 1
leaks ft | grep "0 leaks" > logs/ft_leaks
leaks std | grep "0 leaks" > logs/std_leaks
sleep 1;
diff logs/ft_res logs/std_res

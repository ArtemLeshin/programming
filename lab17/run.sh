gcc -O3 4_c.c -o prog -lpthread
rm -f data.txt
for n in 500 1000 1500 2000 2500
do
    for t in 1 2 4 8 16 32 64 128
    do
        echo "Запуск: N=$n, Потоков=$t"
        ./prog $n $t
    done
done


for cores in 1 2 4 8 16; do
    echo "core=$cores"
    OMP_NUM_THREADS=$cores ./build/pi
done

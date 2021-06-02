echo "#####################"
echo "Running CPU emulator ..."
printf "\n"
g++ emuTest.cpp CPU.cpp -lunicorn -lpthread
./a.out
echo "#####################"

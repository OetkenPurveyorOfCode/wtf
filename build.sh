mkdir ./build/
pushd build
gcc -Wall -Wextra ../main.c -o main
./main ../assets/words_nouns.txt
gcc -Wall -Wextra ../wtf.c -o wtf
popd

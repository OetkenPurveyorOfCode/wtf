mkdir build
pushd build
call gcc -Wall -Wextra ..\main.c -o main.exe
call main.exe ..\assets\words_nouns.txt
call gcc -Wall -Wextra ..\wtf.c -o wtf.exe
popd

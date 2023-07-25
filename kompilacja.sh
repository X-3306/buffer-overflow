echo '\033[33;1mCompiling...\033[0m'
nasm -f elf64 -o $1.o $1.asm
ld -o $1 $1.o
echo 'ok'
echo
echo '\033[33;1mAssembly code:\033[0m'
objdump -M intel -d $1
echo
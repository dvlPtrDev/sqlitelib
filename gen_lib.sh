mkdir -p out/obj

for file in $(find . -name "*.c"); do
	name=$(basename "${file%.c}")
	if [ "$name" = "main" ]; then
		continue
	fi
	gcc -c $file -o out/obj/"$name".o -Iinclude
done

ar rcs ./out/libsqlite.a ./out/obj/*.o

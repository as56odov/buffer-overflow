all:
	gcc 6.c -o vuln -fno-stack-protector -m32 -z execstack

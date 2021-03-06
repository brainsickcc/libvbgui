all:
	i686-w64-mingw32-gcc -c -o lib.o lib.c -std=c11
	i686-w64-mingw32-ar rcs libvbgui.a lib.o
	clang -O0 -I/usr/i686-w64-mingw32/sys-root/mingw/include/ --target=i686-w64-mingw32 -c -S -emit-llvm form-user.c -o form-user.ll
	clang -O0 -I/usr/i686-w64-mingw32/sys-root/mingw/include/ --target=i686-w64-mingw32 -c -S -emit-llvm lib.c -o lib.ll
	clang -O0 -I/usr/i686-w64-mingw32/sys-root/mingw/include/ --target=i686-w64-mingw32 -c -S -emit-llvm usesvariant.c -o usesvariant.ll
	clang -O0 -I/usr/i686-w64-mingw32/sys-root/mingw/include/ --target=i686-w64-mingw32 usesvariant.c -loleaut32 -o usesvariant.exe
	# i686-w64-mingw32-gcc demo.c form-user.c lib.c -o demo.exe -lgdi32

install:
	mkdir -p ~/.local/i686-w64-mingw32/sys-root/mingw/lib/
	cp libvbgui.a ~/.local/i686-w64-mingw32/sys-root/mingw/lib/

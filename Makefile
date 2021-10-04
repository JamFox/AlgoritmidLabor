# ----------------------------------------------------------------------------
# "THE BEER-WARE LICENSE" (Revision 42):
# <rebane@alkohol.ee> wrote this file.  As long as you retain this notice you
# can do whatever you want with this stuff. If we meet some day, and you think
# this stuff is worth it, you can buy me a beer in return.        Veiko Rütter
# ----------------------------------------------------------------------------

.PHONY: all run install

all:
	wine ~/.wine/drive_c/Program\ Files\ \(x86\)/Microsoft\ Visual\ Studio/2019/Community/VC/Tools/MSVC/14.29.30133/bin/Hostx86/x86/cl.exe \
	"-IC:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\TOOLS\\MSVC\\14.29.30133\\INCLUDE" \
	"-IC:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\atlmfc\include" \
	"-IC:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\include" \
	"-IC:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.19041.0\\ucrt" \
	"-IC:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.19041.0\\shared" \
	"-IC:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.19041.0\\um" \
	"-IC:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.19041.0\\winrt" \
	"-IC:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.19041.0\\cppwinrt" \
	"-Ilib" \
	main.cpp \
	"/link" \
	"/LIBPATH:C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\atlmfc\\lib\\x86" \
	"/LIBPATH:C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\lib\\x86" \
	"/LIBPATH:C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\lib\\x86\\store\\references" \
	"/LIBPATH:C:\\Program Files (x86)\\Windows Kits\\10\\UnionMetadata\\10.0.19041.0" \
	"/LIBPATH:C:\\Program Files (x86)\\Windows Kits\\10\\References\\10.0.19041.0" \
	"/LIBPATH:C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.19041.0\\um\\x86" \
	"/LIBPATH:C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.19041.0\\ucrt\\x86" \
	"/LIBPATH:C:\\windows\\Microsoft.NET\Framework\v4.0.30319" \
	"/NODEFAULTLIB:libcmt" \
	"/ignore:4075" \
	"lib\\DateTime.obj" \
	"lib\\Objects.obj" \
	"lib\\Structs.obj" \
	2>/dev/null
	rm *.obj

run: install

install:
	@./a.out


grep -r "^\s*#\s*include\s*<" *.h *.c include lib > list_include.txt
echo --------- >> list_include.txt
grep -r "^\s*#\s*include\s*<" win32 >> list_include.txt
cat list_include.txt

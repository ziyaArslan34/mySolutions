import ctypes
# gcc -fPIC -shared -o test.so main.c

start = ctypes.CDLL("/data/data/com.termux/files/home/mySolutions/Login/src.so")

start.main()

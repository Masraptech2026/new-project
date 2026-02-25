Python 3.8.0 (tags/v3.8.0:fa919fd, Oct 14 2019, 19:37:50) [MSC v.1916 64 bit (AMD64)] on win32
Type "help", "copyright", "credits" or "license()" for more information.
>>> from tkinter import
SyntaxError: invalid syntax
>>> from tkinter import *

window = Tk()

window.title("Welcome to LikeGeeks app")

lbl = Label(window, text="Hello")

lbl.grid(column=0, row=0)

window.mainloop()
SyntaxError: multiple statements found while compiling a single statement
>>> import platform

>>> import platform
import datetime
SyntaxError: multiple statements found while compiling a single statement
>>> import datetime
>>> 


def show_system_info():
    print(f"System: {platform.system()}")
    print(f"Node Name: {platform.node()}")
    print(f"Release: {platform.release()}")
    print(f"Processor: {platform.processor()}")
    print(f"Current Time: {datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")

if __name__ == "__main__":
    show_system_info()
    
SyntaxError: invalid syntax
>>> 
def show_system_info():
    print(f"System: {platform.system()}")
    print(f"Node Name: {platform.node()}")
    print(f"Release: {platform.release()}")
    print(f"Processor: {platform.processor()}")
    print(f"Current Time: {datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')}"

if __name__ == "__main__":
    show_system_info()
	  
SyntaxError: invalid syntax
>>> 
def show_system_info():
    print(f"System: {platform.system()}")
    print(f"Node Name: {platform.node()}")
    print(f"Release: {platform.release()}")
    print(f"Processor: {platform.processor()}")
    print(f"Current Time: {datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")

if __name__ == "__main__"
    show_system_info()
    
SyntaxError: invalid syntax
>>> 
def show_system_info():
    print(f"System: {platform.system()}")
    print(f"Node Name: {platform.node()}")
    print(f"Release: {platform.release()}")
    print(f"Processor: {platform.processor()}")
    print(f"Current Time: {datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")


>>> if __name__ == "__main__":
    show_system_info()

    
System: Windows
Node Name: Masraptech
Release: 10
Processor: Intel64 Family 6 Model 156 Stepping 0, GenuineIntel
Current Time: 2026-02-25 09:15:50
>>> 

# **Instruction to install opencv for visual studio 2022**

## Instructions (As Of 19.7.24):

## For Windows:

1. Download opencv 4.10 (Latest as of 19.7.24) using URL below;
    - https://opencv.org/blog/opencv-4-10-0/

2. Extract out all folders and files from downloaded opencv 4.10.0 to a directory 
    - once extracted, you will see a folder structre, eg;
        - Path/to/opencv
            - /build
            - /sources
            - LICENSE.txt
            - LICENSE_FFMPEG.txt
            - README.md.txt

3. Download cmake 3.30.0 using URL below;
    - https://cmake.org/download/ -> under Binary distributions:
        - cmake-3.30.0-windows-x86_64.msi

4. Install cmake
    - make sure to select option 
	- "Add PATH to system environment variable"

5. Go to "Environment variable" 
	- Under system variables 
	- "Path" 
    - edit -> include the path of the opencv folder, eg;
    - C:\Software\OpenCv_4.10.0\opencv\build\x64\vc16\bin
    - and hit apply and ok

6. Under project
	- Properties
	- Configuration Properties
		- VC++ Directories
			- Include Directories -> Add Path: C:\Software\OpenCv_4.10.0\opencv\build\include -> Hit apply
			- Library Directories -> Add Path: C:\Software\OpenCv_4.10.0\opencv\build\x64\vc16\lib -> Hit apply
		- C/C++
			- General -> Additional Include Directories -> Add Path: C:\Software\OpenCv_4.10.0\opencv\build\include , hit apply
		- Linker
			-> General  Additional Include Directories -> Add Path: C:\Software\OpenCv_4.10.0\opencv\build\x64\vc16\lib , hit apply
			-> Input -> Additional Dependencies -> Add Path: C:\Software\OpenCv_4.10.0\opencv\build\x64\vc16\lib\opencv_world4100d.lib
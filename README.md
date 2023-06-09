OpenGI library
------------

The OpenGI library's original source is at http://opengi.sourceforge.net.

OpenGI is an Open Source library written in C for parameterizing triangular 
meshes and creating Geometry Images from this parameterization.  Its API is 
heavily based on OpenGL and the latter is tightly integrated into OpenGI for 
easy and efficient integration into existing graphics software.

The library is released under the terms of the GNU LPGL.  For further 
information on this license consult the COPYING and COPYING.LESSER files.

<br />

Requirements
------------

OpenGI does not require any additional libraries or programs except the OpenGL 
of at least version 1.1.  A recent enough glext.h, that is needed for 
compilation comes with the source code distribution.  To profit from 
multithreading on UNIX platforms the pthreads library is needed when building. 
On Windows platforms multithreading is allways supported.  Note that 
multitreading is only used in a few functions, namely during parameterization 
and sampling.

The gim example requires the GLUT library. It also requires your hardware to 
support floating point textures.

<br />


Building
--------

Windows (MS Visual Studio):

   A solution for VS 2005 can found in projects/vs2005 and can be built as is. 
   After compiling Debug and Release the OpenGI[d].lib files can be found in 
   the lib directory and the OpenGI[d].dll files can be found in the bin 
   directory.  The executables of the examples can also be found in bin.
   
   But before compilation you should run config_win32.exe.  This application 
   analyses your system and creates the file config.h that defines some 
   preprocessor symbols.  You can change these if you want.
   
   By default config_win32.exe will automatically define the maximum number of 
   threads to the number of logical processor cores (including virtual HT 
   cores).  You can override this behaviour by changing the value of 
   OPENGI_MAX_THREADS in config.h.
   
   Additionally the variable OPENGI_SSE is defined to the maximum supported 
   version of the SSE instruction set (0, 1, 2, or 3, higher versions don't 
   matter).  You can disable SSE support by defining it to 0, but you won't 
   gain the performance boosts in parameterization and sampling.
   
   You can also define OPENGI_DEBUG_OUTPUT to let OpenGI print messages 
   informing you about its progress during its operation.  By default this is 
   undefined, but it is automatically defined in the Debug build.

UNIX (configure/make):

   On UNIX just enter the console and type
   
      ./configure
      make
   
   By default configure will automatically define the maximum number threads 
   to the number of processor cores (including virtual HT cores) by evaluating 
   /proc/cpuinfo.  If it cannot figure out this number, which should not 
   happen on a normal UNIX system, it uses 4 as the default.  You can disable 
   this behaviour by calling configure with the option --enable-max-threads=X, 
   with X being the maximum number of threads to use.

   Additionally configure will automatically find the maximum version of the 
   SSE intstruction set supported by your processor by evaluating 
   /proc/cpuinfo.  You can override this too, by calling configure with the 
   option --enable-sse=X, with X being the maximum supported SSE version 
   (0, 1, 2 or 3, higher versions don't matter), but you should only do this 
   if you know about the features of you processor.
   
   You can also compile OpenGI to print out informative messages during its 
   operation which is disabled by default.  Just configure it with the option 
   --enable-verbose.

   For more information see the INSTALL file or type ./configure --help.

<br />

#### Build with CMake

```bash
cmake -DFREEGLUT_ROOT=<freeglut_dir> -S <src_dir> -B <build_dir> --install-prefix <install_dir>
```

`<src_dir>` is the root directory where you have stored this project, such as **`C:/Downloads/OpenGI-main`**.

`<build_dir>` is the directory where you can build this project with Visual Studio, Makefile or Xcode, etc. For instance: **`C:/Downloads/OpenGI-main/build`**.

`<install_dir>` is the directory where the project will generate the final executable, headers and the lib files. For instance: **`C:/Downloads/OpenGI-main/install`**.

Here is a complete example:
```bash
cmake -DFREEGLUT_ROOT=C:/freeglut-3.2.2  -S C:/Downloads/OpenGI-main  -B C:/Downloads/OpenGI-main/build  --install-prefix C:/Downloads/OpenGI-main/install
```

On macOS, there's no need to install FreeGLUT library because the macOS SDK inside the Xcode has already contained GLUT.framework. This project will use the intrinsic GLUT.framework by default. So It is recommended that an Xcode project is generated.

On Windows and macOS platforms, it is recommended to use CMake GUI. It'll be easy to setup the IDE environment.

<br />

Installation
------------

Windows:

   Just copy the GI/gi.h from the include directory into the include directory 
   of your compiler and the OpenGI[d].lib files into the library directory of 
   your compiler.  The OpenGI[d].dll files need to be copied into your system 
   directory or any other directory that is part of your PATH.
   
UNIX:

   Having root access, just type:
   
      make install
      
   which will by default install the libraries into /usr/local/lib, the gi.h 
   into /usr/local/include/GI and some documentation files into 
   /usr/local/share/doc/opengi.  For more information consult the INSTALL file.

<br />

Documentation
-------------

The doc directory contains the most recent OpenGI Programming Guide, which 
can also be found at http://opengi.sourceforge.net.  This site also has a 
Doxygen generated documentation for users (not documenting the internals). 
The source distribution also contains a Doxyfile which will generate the 
complete developer documentation into the doc directory with all internal 
structures and functions documented.



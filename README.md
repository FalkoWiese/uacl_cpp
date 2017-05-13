Unified Architecture Convenience Layer (UACL)
================================================================================

Project websites?
---------------------------
 - **Code repositories: 
    - **C++**: https://gitlab.com/falko.wiese/uacl_cpp/
    - **.NET**: https://gitlab.com/falko.wiese/uacl_cs/
    - **Java**: https://gitlab.com/falko.wiese/uacl_java/

 - Git Branches:
     - `master`: tested and production-ready, has the latest API and the latest 
        tested features.
     - `*`: development branches, only.

What?
-------------------------------------------------------------------------------

 - The Unified Architecture Convenience Layer (UACL) is a closed source software framework to simplify the 
   development of **OPC UA** applications on **Linux** (in **C++/Java**) and **Microsoft Windows **(in **C++/C#/Java**), 
   for Client (for **C++** under usage of **uaf**) and Server Applications!
   
 - OPC UA (OPC Unified Architecture) is the current standard for secure, reliable
   and scalable industrial communication.
   
 - In short, the UACL is **OPC UA made easy**!


Why?
-------------------------------------------------------------------------------
   
 - The intent of UACL is to give fast access to the OPC UA technology.

 - In practice, the UACL is a framework (or "toolkit") that helps you to create advanced OPC UA 
   applications with minimal effort. Essentially, it takes care of some *technical* aspects so 
   that you can concentrate on the *working* aspects of your software application.
   
 - Some very concise and easy to understand examples come along with the UACL, itself.
 
**Intuitive platform driven API:**
All code from the Software Developers Kit is wrapped into some convenient namespaces and 
classes, and for sure, shared libraries. You can write your business code as usual, the
only thing you've to do is to mark your business classes as so called **Remote Objects** via
an annotation and to register it on the supplied **UA Server** object at runtime. Furthermore
you've to mark variables, and methods as **Remote Variables**, and **Remote Methods**, 
respectively. The UACL will generate an UA Server interface for you. I think, it's a really
magic behavior, isn't it?

What ever, if you don't want to dive deep inside of **OPC UA**, you can let UACL do the 
annoying things for you.


How?
-------------------------------------------------------------------------------
Technically we used the language features from .NET and Java - "Attributations" and
"Annotations", respectively. For the C++ platform we have been integrated the Qt
framework. It comes with a bunch of well implemented stuff - e. g. a complete 
"Reflection API". Annotations are implemented via macros, there. It's very simple 
and functional!


Dependencies?
-------------------------------------------------------------------------------
The UACL is for all platforms (C++, C#, Java) based on the commercial C++ OPC UA Software Developers Kit 
from Unified Automation. A demo version for every SDK can be downloaded from their website for free: 
http://www.unified-automation.com. And for the C++ platform - as I mentioned before - I've made heavy 
usage of the Qt 5 framework from http://www.qt.io/.


Examples?
-------------------------------------------------------------------------------
You will find full featured client and server application examples at the gitlab repos
for every platform.


Documentation?
-------------------------------------------------------------------------------
Hmm ... Please read the code of the examples. ;)


Status?
-------------------------------------------------------------------------------
I would say, the implementations for all platforms we are in a **BETA State**.


Installation?
-------------------------------------------------------------------------------
You've to install the external libraries, build the project, and that's it. For
.NET you don't have to install any additional stuff. We install external 
libraries with the NuGet package manager, if necessary. For the C++ UACL please
follow the instructions below.


**Linux (Ubuntu, Linux Mint, Debian)**

Download the UA SDK for Linux 64 bit from ...
> [UA SDK 1.5.2](https://www.unified-automation.com/downloads/opc-ua-development/file/download/details/c-based-opc-ua-clientserver-sdk-bundle-v150.html)

The Libraries are already compiled, the only thing you have to do is to extract
the given tar.gz to a location on your hard disk, maybe anywhere in your home
folder ...
> tar -xzvf uasdkcppbundle-bin-EVAL-debian7-x64-gcc4.7.2-v1.5.2-336.tar.gz $WORKSPACE_FOLDER


Download the Qt Libraries 5.7.0 for Linux 64 bit, as well from ...
> [Qt 5.7.0](https://www.qt.io/download-open-source)

It's a *.run file. Here you have to make this file executable with maybe ...
> chmod 755 qt-opensource-linux-x64-5.7.0.run

And execute it with ...
> ./qt-opensource-linux-x64-5.7.0.run
    

Install external libraries with ...
> sudo apt-get install python-dev

> sudo apt-get install libxml2-dev

> sudo apt-get install libssl-dev

Clone the GoogleTest library to a location of your choice ...
> git clone https://github.com/google/googletest.git

Clone the repository to a location of your choice ...
> git clone git@gitlab.com:falko.wiese/uacl_cpp.git

Create a new file named UaclVars.cmake in the same folder as the root CMakeLists.txt and add the following variables to this file...
- *UASDK_INSTALLATION_DIR* contains the path to the OPC UA Libraries (e.g. set(QT_INSTALLATION_DIR C:/Users/spielmann/Documents/projects/sim/lib/qt-5.4.1))
- *QT_INSTALLATION_DIR* contains the path the to the Qt Framework (e.g. set(UASDK_INSTALLATION_DIR C:/Program\ Files\ \(x86\)/UnifiedAutomation/UaSdkCppBundleEval))
- *CMAKE_PREFIX_PATH* this variable should point to the directory where the cmake-files for Qt can be found (set(CMAKE_PREFIX_PATH ${QT_INSTALLATION_DIR}/lib32/cmake))

Create a symbolic link for ...
- Unit Testing Library *GoogleTest* at $UACL_REPO_FOLDER/test/lib  
> cd $UACL_REPO_FOLDER/test/lib

> ln -s $ googletest


And compile it with ...
> mkdir $UACL_INSTALLATION_FOLDER

> cd $UACL_INSTALLATION_FOLDER

> cmake $UACL_FOLDER && make

That's it.



**Windows**

Download the UA SDK for Windows (tested with version 1.5.5) from the Unified Automation website (https://www.unified-automation.com). 
Unified Automation only provides 32bit-precompiled binaries for Windows if you need the 64-bit variant you have to build the SDK yourself!

Download and install the Qt-framework (tested with Qt-5.4.1 but theoretically every Qt-5.x version should work).

Clone the repository to a location of your choice ...
> git clone git@gitlab.com:falko.wiese/uacl_cpp.git

Create a new file named UaclVars.cmake in the same folder as the root CMakeLists.txt and add the following variables to this file...
- *UASDK_INSTALLATION_DIR* contains the path to the OPC UA Libraries (e.g. set(QT_INSTALLATION_DIR C:/Users/spielmann/Documents/projects/sim/lib/qt-5.4.1))
- *QT_INSTALLATION_DIR* contains the path the to the Qt Framework (e.g. set(UASDK_INSTALLATION_DIR C:/Program\ Files\ \(x86\)/UnifiedAutomation/UaSdkCppBundleEval))
- *CMAKE_PREFIX_PATH* this variable should point to the directory where the cmake-files for Qt can be found (set(CMAKE_PREFIX_PATH ${QT_INSTALLATION_DIR}/lib32/cmake))

The current version should build using the Microsoft MSVC-compiler (tested with MSVC 2010-compiler) other compilers (like the Intel compiler or MINGW) have *NOT* been tested!

And compile it with ...
> mkdir $UACL_INSTALLATION_FOLDER

> cd $UACL_INSTALLATION_FOLDER

> cmake (or cmake-gui) $UACL_FOLDER && nmake (or jom)

Current limitations:

- SEH-exceptionhandling is currently deactivated.
- unit-tests are currently deactivated
- RPC is not working


Who?
-------------------------------------------------------------------------------
 - **Author**: Falko Wiese
 - **Contact**: `f****.w****@mail.de` (replace the asterisks)
 - **Organization**: wieSE Software Engineering (Germany)
 - **Project websites**:
    - https://gitlab.com/falko.wiese/uacl_cpp
    - https://gitlab.com/falko.wiese/uacl_cs
    - https://gitlab.com/falko.wiese/uacl_java


License?
-------------------------------------------------------------------------------
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.



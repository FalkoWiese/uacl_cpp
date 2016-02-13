UACL - the Unified Architecture Convenience Layer
===============================================================================


Project website?
-------------------------------------------------------------------------------

 - **Main code repository for **C++**: https://gitlab.com/falko.wiese/uacl_cpp/**

 - Git Branches:
 
     - `master`: tested and production-ready, has the latest API and the latest tested features.
     - `*`: development branches, only.

What?
-------------------------------------------------------------------------------

 - The Unified Architecture Convenience Layer (UACL) is a closed source software framework to simplify the 
   development of **OPC UA** applications on **Linux** and **Microsoft Windows**, in **C++/C#/Java** for 
   Client and Server Applications!
   
 - OPC UA (OPC Unified Architecture) is the next generation standard for secure, reliable
   and scalable industrial communication.
   
 - In short, the UACL is **OPC UA made easy!**


Why?
-------------------------------------------------------------------------------
   
 - The intent of UACL is to give fast access to the OPC UA technology.

 - In practice, the UACL is a framework (or "toolkit") that helps you to create advanced OPC UA 
   applications with minimal effort. Essentially, it takes care of some *technical* aspects so 
   that you can concentrate on the *functional* aspects of your software application.
   
 - Some very concise and easy to understand examples come along with the UACL, itself.
 
 - **Intuitive platfrom driven API:**

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
framework. It comes with a bunch of well implemented stuff - e. g. complete 
"Reflection API". Annotations are implemented via macros. It's very simple and functional!


Dependencies?
-------------------------------------------------------------------------------

 - The UACL is for all platforms (C++, C#, Java) based on the commercial C++ OPC UA Software Developers Kit 
   from Unified Automation. A demo version for every SDK can be downloaded from their website for free: 
   http://www.unified-automation.com
   

Examples?
-------------------------------------------------------------------------------

You will find full featured client and server application examples at the gitlab repos
for every platform.


Documentation?
-------------------------------------------------------------------------------

Hmm ... Please read the code of the examples. ;)


Status?
-------------------------------------------------------------------------------

I would say, the implementations for all platforms are in a **BETA State**.


Installation?
-------------------------------------------------------------------------------

 - **Linux installation guide**: see [install_linux.rst.txt](http://github.com/uaf/uaf/blob/master/install_linux.rst.txt)
  
 - **Windows installation guide**: see [install_windows.rst.txt](http://github.com/uaf/uaf/blob/master/install_windows.rst.txt)


Who?
-------------------------------------------------------------------------------

 - **Author**: Wim Pessemier

 - **Contact**: `W**.P********@ster.kuleuven.be` (replace the asterisks)

 - **Organization**: Institute of Astronomy, KU Leuven (Belgium)

 - **Project website**: http://github.com/uaf
 

License?
-------------------------------------------------------------------------------

 - This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.



# Heimdall
![Build Status](https://travis-ci.org/adamleighfish/heimdall.svg?branch=master)

A physically based ray tracer that is currently in progress. Intended to be a 
more complete and extensible version of my previous projects. Planned features 
include subsurface scattering, bidirectional path tracing, motion blur, and many,
many more.

I'm using [pbrt-v3](https://github.com/mmp/pbrt-v3) and its accompanying book as reference 
throughout the project and cannot recommend the book enough if you are interested 
in physically based rendering.

## Building

Heimdall uses [cmake](http://www.cmake.org/) for its build system.  On Linux
and OS X, cmake is available via most package management systems.

Once you have cmake installed and the repo cloned, create a new directory for the build, 
change to that directory, and run `cmake /path/to/heimdall`. A Makefile will be created 
in that current directory.  Run `make -j8`, to build heimdall and heimdall_test.
  
## Testing

Running `heimdall_test` will run the [gtest](https://github.com/google/googletest) unit 
tests for heimdall and report any errors. If any issues occur that you can't figure out, 
please raise an issue on github and I'll look into it.

## Running

Running `heimdall` will start up the renderer and display the classic `Hello, world!` text
for now. Instructions will be updated once enough features are implemented to display images.

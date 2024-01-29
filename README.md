## C++ Wt Framework https://www.webtoolkit.eu/wt/doc/reference/html/index.html

## Install Wt on Windows
https://redmine.emweb.be/projects/wt/wiki/Installing_Wt_on_MS_Windows

## Install Wt on linux 
Just folow the Dockerfile instructions and you are golden with one exception, the Wt libraries may not link after the install and there are two fixes for that

run the next command to dynamicly link to those binaries
~~~
export LD_LIBRARY_PATH=/usr/local/lib/
~~~
run the next command to copy the wt library files from /usr/local/lib/ to /usr/lib/
~~~
cp /usr/local/lib/libwt*.so.* /usr/lib/
~~~

## Build / Run
You can build and run this via makefile with commands:
~~~
make
make run
~~~

### Dockerfile 
In case you want to run this in a container, there is a Dockerfile ready to go

### Jenkins
Jenkins file ready to go, working with script files from folder /scripts for building, testing and deploying the app

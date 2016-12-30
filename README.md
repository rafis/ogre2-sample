ogre2-sample
============

Ogre3D project template is ~~ready to be used~~ (please make fork and pull requests to make it usable)
in your experimental projects or to learn Ogre3D. orge2-sample is featuring:

* Oriented to Ogre3D 2.1
* OIS Mouse and Keyboard
* Basic camera controller
* Basic game state controller

![Screenshot](/share/ogrehead.png?raw=true "Screenshot")

Installation on Windows
-----------------------

Copy project, rename folder, rename project name in CMakeLists.txt, then use `cmake-gui`.

Installation on Linux/macOS
--------------------------

Use command line terminal to prepare template for your experimental project. Replace `ogre2-myapp1`
with your experimental project name:

    git clone https://github.com/rafis/ogre2-sample.git
    cp -ar ogre2-sample ogre2-myapp1
    cd ogre2-myapp1
    sed -i 's/Sample/MyApp1/g' CMakeLists.txt
    cd ..
    mkdir ogre2-myapp1-bin
    cd ogre2-myapp1-bin
    cmake ../ogre2-myapp1 -DCMAKE_BUILD_TYPE="Debug"
    make
    cd ogre2-myapp1/bin
    ./ogre2-myapp1

Other templates
---------------

I haven't found any for Ogre3D 2.x, that's why I have created this template.

ogre2-sample
============

Ogre3D project template is ~~ready to be used~~ (make fork and pull requests to make it usable)
in experimental projects to learn Ogre3D, featuring:

* Oriented to Ogre3D 2.1
* OIS Mouse and Keyboard
* Basic camera controller
* Basic game state controller

Installation on Windows
-----------------------

Change project name in CMakeLists.txt and use `cmake-gui`.

Installation on Linux/OS X
--------------------------

For example you want to create `ogre2-myapp1`, rough steps are following:

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

None as I know for Ogre3d 2.x.

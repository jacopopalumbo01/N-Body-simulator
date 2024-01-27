# OpenFrameworks graphic library
We chose this external library to produce more stylish visualizations for our simulations. OpenFrameworks is a cross platform toolkit for creative coding in C++. It is actually a wrapper built on top of OpenGL, a well-known platform for rendering 2D and 3D vector graphics. We added OpenFrameworks to our repository as a submodule, so that its linking with our project is immediate. The process of installing and compiling the library is quite tedious, but it's definitely worth it.
If you wish to do this, head over the [OpenFrameworks website](https://openframeworks.cc/download/) and download a suitable version of the library. The installation and compilation process depends on your operating system. 
You also need to install the OfxBloom addon, which can be found [here](https://github.com/P-A-N/ofxBloom).
Bear in mind that this code can't be actually run inside this project, it just serves as an example of the process used to produce the graphic rendering of the simulation. In order to execute this code, you need to create a new project with OpenFrameworks project installer, which automatically produces all the files necessary for compilation and library linking. The new folder should be created in /pathToOpenFrameworks/apps/myApps. Remember to include the ofxBloom addon! 
If you feel discouraged by this process, we can still give you a taste of what the result may look like. Enjoy this simulation of 1024 particles evolving over 86400 time steps! (We sampled one every 36, otherwise the simulation would have been to heavy)

https://github.com/jacopopalumbo01/N-Body-simulator/assets/118806991/73c7f7d6-0014-4688-ba73-cd3a62f74d61



# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.asteroids.Debug:
PostBuild.glfw.Debug: /Users/Sam/Desktop/intro-graphics/graphics-final/build/Debug/asteroids.app/Contents/MacOS/asteroids
PostBuild.glad.Debug: /Users/Sam/Desktop/intro-graphics/graphics-final/build/Debug/asteroids.app/Contents/MacOS/asteroids
PostBuild.glfw.Debug: /Users/Sam/Desktop/intro-graphics/graphics-final/build/Debug/asteroids.app/Contents/MacOS/asteroids
/Users/Sam/Desktop/intro-graphics/graphics-final/build/Debug/asteroids.app/Contents/MacOS/asteroids:\
	/Users/Sam/Desktop/intro-graphics/graphics-final/build/glfw-3.2/src/Debug/libglfw3.a\
	/Users/Sam/Desktop/intro-graphics/graphics-final/build/Debug/libglad.a\
	/Users/Sam/Desktop/intro-graphics/graphics-final/build/glfw-3.2/src/Debug/libglfw3.a
	/bin/rm -f /Users/Sam/Desktop/intro-graphics/graphics-final/build/Debug/asteroids.app/Contents/MacOS/asteroids


PostBuild.glad.Debug:
/Users/Sam/Desktop/intro-graphics/graphics-final/build/Debug/libglad.a:
	/bin/rm -f /Users/Sam/Desktop/intro-graphics/graphics-final/build/Debug/libglad.a


PostBuild.glfw.Debug:
/Users/Sam/Desktop/intro-graphics/graphics-final/build/glfw-3.2/src/Debug/libglfw3.a:
	/bin/rm -f /Users/Sam/Desktop/intro-graphics/graphics-final/build/glfw-3.2/src/Debug/libglfw3.a


PostBuild.asteroids.Release:
PostBuild.glfw.Release: /Users/Sam/Desktop/intro-graphics/graphics-final/build/Release/asteroids.app/Contents/MacOS/asteroids
PostBuild.glad.Release: /Users/Sam/Desktop/intro-graphics/graphics-final/build/Release/asteroids.app/Contents/MacOS/asteroids
PostBuild.glfw.Release: /Users/Sam/Desktop/intro-graphics/graphics-final/build/Release/asteroids.app/Contents/MacOS/asteroids
/Users/Sam/Desktop/intro-graphics/graphics-final/build/Release/asteroids.app/Contents/MacOS/asteroids:\
	/Users/Sam/Desktop/intro-graphics/graphics-final/build/glfw-3.2/src/Release/libglfw3.a\
	/Users/Sam/Desktop/intro-graphics/graphics-final/build/Release/libglad.a\
	/Users/Sam/Desktop/intro-graphics/graphics-final/build/glfw-3.2/src/Release/libglfw3.a
	/bin/rm -f /Users/Sam/Desktop/intro-graphics/graphics-final/build/Release/asteroids.app/Contents/MacOS/asteroids


PostBuild.glad.Release:
/Users/Sam/Desktop/intro-graphics/graphics-final/build/Release/libglad.a:
	/bin/rm -f /Users/Sam/Desktop/intro-graphics/graphics-final/build/Release/libglad.a


PostBuild.glfw.Release:
/Users/Sam/Desktop/intro-graphics/graphics-final/build/glfw-3.2/src/Release/libglfw3.a:
	/bin/rm -f /Users/Sam/Desktop/intro-graphics/graphics-final/build/glfw-3.2/src/Release/libglfw3.a


PostBuild.asteroids.MinSizeRel:
PostBuild.glfw.MinSizeRel: /Users/Sam/Desktop/intro-graphics/graphics-final/build/MinSizeRel/asteroids.app/Contents/MacOS/asteroids
PostBuild.glad.MinSizeRel: /Users/Sam/Desktop/intro-graphics/graphics-final/build/MinSizeRel/asteroids.app/Contents/MacOS/asteroids
PostBuild.glfw.MinSizeRel: /Users/Sam/Desktop/intro-graphics/graphics-final/build/MinSizeRel/asteroids.app/Contents/MacOS/asteroids
/Users/Sam/Desktop/intro-graphics/graphics-final/build/MinSizeRel/asteroids.app/Contents/MacOS/asteroids:\
	/Users/Sam/Desktop/intro-graphics/graphics-final/build/glfw-3.2/src/MinSizeRel/libglfw3.a\
	/Users/Sam/Desktop/intro-graphics/graphics-final/build/MinSizeRel/libglad.a\
	/Users/Sam/Desktop/intro-graphics/graphics-final/build/glfw-3.2/src/MinSizeRel/libglfw3.a
	/bin/rm -f /Users/Sam/Desktop/intro-graphics/graphics-final/build/MinSizeRel/asteroids.app/Contents/MacOS/asteroids


PostBuild.glad.MinSizeRel:
/Users/Sam/Desktop/intro-graphics/graphics-final/build/MinSizeRel/libglad.a:
	/bin/rm -f /Users/Sam/Desktop/intro-graphics/graphics-final/build/MinSizeRel/libglad.a


PostBuild.glfw.MinSizeRel:
/Users/Sam/Desktop/intro-graphics/graphics-final/build/glfw-3.2/src/MinSizeRel/libglfw3.a:
	/bin/rm -f /Users/Sam/Desktop/intro-graphics/graphics-final/build/glfw-3.2/src/MinSizeRel/libglfw3.a


PostBuild.asteroids.RelWithDebInfo:
PostBuild.glfw.RelWithDebInfo: /Users/Sam/Desktop/intro-graphics/graphics-final/build/RelWithDebInfo/asteroids.app/Contents/MacOS/asteroids
PostBuild.glad.RelWithDebInfo: /Users/Sam/Desktop/intro-graphics/graphics-final/build/RelWithDebInfo/asteroids.app/Contents/MacOS/asteroids
PostBuild.glfw.RelWithDebInfo: /Users/Sam/Desktop/intro-graphics/graphics-final/build/RelWithDebInfo/asteroids.app/Contents/MacOS/asteroids
/Users/Sam/Desktop/intro-graphics/graphics-final/build/RelWithDebInfo/asteroids.app/Contents/MacOS/asteroids:\
	/Users/Sam/Desktop/intro-graphics/graphics-final/build/glfw-3.2/src/RelWithDebInfo/libglfw3.a\
	/Users/Sam/Desktop/intro-graphics/graphics-final/build/RelWithDebInfo/libglad.a\
	/Users/Sam/Desktop/intro-graphics/graphics-final/build/glfw-3.2/src/RelWithDebInfo/libglfw3.a
	/bin/rm -f /Users/Sam/Desktop/intro-graphics/graphics-final/build/RelWithDebInfo/asteroids.app/Contents/MacOS/asteroids


PostBuild.glad.RelWithDebInfo:
/Users/Sam/Desktop/intro-graphics/graphics-final/build/RelWithDebInfo/libglad.a:
	/bin/rm -f /Users/Sam/Desktop/intro-graphics/graphics-final/build/RelWithDebInfo/libglad.a


PostBuild.glfw.RelWithDebInfo:
/Users/Sam/Desktop/intro-graphics/graphics-final/build/glfw-3.2/src/RelWithDebInfo/libglfw3.a:
	/bin/rm -f /Users/Sam/Desktop/intro-graphics/graphics-final/build/glfw-3.2/src/RelWithDebInfo/libglfw3.a




# For each target create a dummy ruleso the target does not have to exist
/Users/Sam/Desktop/intro-graphics/graphics-final/build/Debug/libglad.a:
/Users/Sam/Desktop/intro-graphics/graphics-final/build/MinSizeRel/libglad.a:
/Users/Sam/Desktop/intro-graphics/graphics-final/build/RelWithDebInfo/libglad.a:
/Users/Sam/Desktop/intro-graphics/graphics-final/build/Release/libglad.a:
/Users/Sam/Desktop/intro-graphics/graphics-final/build/glfw-3.2/src/Debug/libglfw3.a:
/Users/Sam/Desktop/intro-graphics/graphics-final/build/glfw-3.2/src/MinSizeRel/libglfw3.a:
/Users/Sam/Desktop/intro-graphics/graphics-final/build/glfw-3.2/src/RelWithDebInfo/libglfw3.a:
/Users/Sam/Desktop/intro-graphics/graphics-final/build/glfw-3.2/src/Release/libglfw3.a:

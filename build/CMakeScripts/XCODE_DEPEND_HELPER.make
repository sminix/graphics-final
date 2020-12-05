# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.glad.Debug:
/Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/Debug/libglad.a:
	/bin/rm -f /Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/Debug/libglad.a


PostBuild.glfw.Debug:
/Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/glfw-3.2/src/Debug/libglfw3.a:
	/bin/rm -f /Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/glfw-3.2/src/Debug/libglfw3.a


PostBuild.soccer.Debug:
PostBuild.glfw.Debug: /Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/Debug/soccer.app/Contents/MacOS/soccer
PostBuild.glad.Debug: /Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/Debug/soccer.app/Contents/MacOS/soccer
PostBuild.glfw.Debug: /Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/Debug/soccer.app/Contents/MacOS/soccer
/Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/Debug/soccer.app/Contents/MacOS/soccer:\
	/Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/glfw-3.2/src/Debug/libglfw3.a\
	/Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/Debug/libglad.a\
	/Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/glfw-3.2/src/Debug/libglfw3.a
	/bin/rm -f /Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/Debug/soccer.app/Contents/MacOS/soccer


PostBuild.glad.Release:
/Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/Release/libglad.a:
	/bin/rm -f /Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/Release/libglad.a


PostBuild.glfw.Release:
/Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/glfw-3.2/src/Release/libglfw3.a:
	/bin/rm -f /Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/glfw-3.2/src/Release/libglfw3.a


PostBuild.soccer.Release:
PostBuild.glfw.Release: /Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/Release/soccer.app/Contents/MacOS/soccer
PostBuild.glad.Release: /Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/Release/soccer.app/Contents/MacOS/soccer
PostBuild.glfw.Release: /Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/Release/soccer.app/Contents/MacOS/soccer
/Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/Release/soccer.app/Contents/MacOS/soccer:\
	/Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/glfw-3.2/src/Release/libglfw3.a\
	/Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/Release/libglad.a\
	/Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/glfw-3.2/src/Release/libglfw3.a
	/bin/rm -f /Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/Release/soccer.app/Contents/MacOS/soccer


PostBuild.glad.MinSizeRel:
/Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/MinSizeRel/libglad.a:
	/bin/rm -f /Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/MinSizeRel/libglad.a


PostBuild.glfw.MinSizeRel:
/Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/glfw-3.2/src/MinSizeRel/libglfw3.a:
	/bin/rm -f /Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/glfw-3.2/src/MinSizeRel/libglfw3.a


PostBuild.soccer.MinSizeRel:
PostBuild.glfw.MinSizeRel: /Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/MinSizeRel/soccer.app/Contents/MacOS/soccer
PostBuild.glad.MinSizeRel: /Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/MinSizeRel/soccer.app/Contents/MacOS/soccer
PostBuild.glfw.MinSizeRel: /Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/MinSizeRel/soccer.app/Contents/MacOS/soccer
/Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/MinSizeRel/soccer.app/Contents/MacOS/soccer:\
	/Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/glfw-3.2/src/MinSizeRel/libglfw3.a\
	/Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/MinSizeRel/libglad.a\
	/Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/glfw-3.2/src/MinSizeRel/libglfw3.a
	/bin/rm -f /Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/MinSizeRel/soccer.app/Contents/MacOS/soccer


PostBuild.glad.RelWithDebInfo:
/Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/RelWithDebInfo/libglad.a:
	/bin/rm -f /Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/RelWithDebInfo/libglad.a


PostBuild.glfw.RelWithDebInfo:
/Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/glfw-3.2/src/RelWithDebInfo/libglfw3.a:
	/bin/rm -f /Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/glfw-3.2/src/RelWithDebInfo/libglfw3.a


PostBuild.soccer.RelWithDebInfo:
PostBuild.glfw.RelWithDebInfo: /Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/RelWithDebInfo/soccer.app/Contents/MacOS/soccer
PostBuild.glad.RelWithDebInfo: /Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/RelWithDebInfo/soccer.app/Contents/MacOS/soccer
PostBuild.glfw.RelWithDebInfo: /Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/RelWithDebInfo/soccer.app/Contents/MacOS/soccer
/Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/RelWithDebInfo/soccer.app/Contents/MacOS/soccer:\
	/Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/glfw-3.2/src/RelWithDebInfo/libglfw3.a\
	/Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/RelWithDebInfo/libglad.a\
	/Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/glfw-3.2/src/RelWithDebInfo/libglfw3.a
	/bin/rm -f /Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/RelWithDebInfo/soccer.app/Contents/MacOS/soccer




# For each target create a dummy ruleso the target does not have to exist
/Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/Debug/libglad.a:
/Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/MinSizeRel/libglad.a:
/Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/RelWithDebInfo/libglad.a:
/Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/Release/libglad.a:
/Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/glfw-3.2/src/Debug/libglfw3.a:
/Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/glfw-3.2/src/MinSizeRel/libglfw3.a:
/Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/glfw-3.2/src/RelWithDebInfo/libglfw3.a:
/Users/Sam/Desktop/intro-graphics/final-copy/graphics-final/build/glfw-3.2/src/Release/libglfw3.a:

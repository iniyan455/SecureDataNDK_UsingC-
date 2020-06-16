# SecureDataNDK_UsingC-

Store Your API Keys More Securely Using CMake & Kotlin

Keep your API keys private and secure using Native C/C++ code

"A good defense is the best offense." 

Well, that's partly true in Android when it comes to storing API keys and protecting them against hackers.

You need to keep your API keys private and secure for multiple reasons. If a hacker gains access to your API key, they could:

make API calls and which could tremendously increase your billing costs, and/or
use it to disrupt your users' data.
Before we dive into enhancing the security of your API keys, let's talk about how most developers are currently storing API keys.

The traditional way of storing API keys


Storing API keys in strings.xml: This is a big no-no. It's definitely not secure, and with a little reverse engineering, hackers can easily decrypt the API key if you store it in any XML file in your Android project. Also, on a more obvious note, if your repo is public, your strings.xml file would be too. This means that your API key would also be public.

Storing API keys in gradle.properties: This seems to be the most popular choice. You might have been adding this file to .gitignore, declaring your API key inside, referring to it in the app-level build.gradle file, and using it in your app via the generated BuildConfig class. While this is more secure than storing it in XML files, your API key can still be decoded by someone via reverse engineering. Hence, this isn't a very secure way to store your API keys.

The better way: Bringing in the power of CMake to Android
CMake is a software tool that manages the build processes of other software.

In this article, I will share how to write a short C++ code to store your API key securely, and access your API key from your C++ file.

Native C/C++ code is harder to decompile and hence, hackers will have a harder time gaining access to your API keys. This has been proven to be more secure than storing it in your gradle.properties file, and is definitely something I'd recommend implementing in your app if you're looking to enhance security around your API key storage system.


Step 1: Install the required tools
You'll need to install 3 tools in Android Studio via the SDK Manager:

NDK (Native Development Kit): This is a tool that is used to work with C/C++ code in Android. It also lets you access certain device components, such as sensors, touch input, etc.
LLDB (Low Level Debugger): This is a debugger for native code.
CMake: This is the tool that builds your native C/C++ library.


Step 2: Create a native-lib.cpp file
Create a new folder, cpp, inside app/src/main.

Once you've created it, right-click on the cpp folder, click on New → C/C++ Source File, and name your file native-lib.cpp.



Step 3: Store your API key inside the native-lib.cpp file
Inside your native-lib.cpp, add the following code:

#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring

JNICALL
Java_com_package_name_Keys_apiKey(JNIEnv *env, jobject object) {
    std::string api_key = "your_api_key_goes_here";
    return env->NewStringUTF(api_key.c_str());
}



Let's take a closer look at the name of the C++ function Java_com_package_name_Keys_apiKey(...) declared above from right to left:

apiKey: This directly refers to the method name that you'll be using in Kotlin later on.
Keys: This refers to the Kotlin object in which you want to use your API key, where you'll interact with the C++ coded, and get a reference to your API key (which you can use throughout your app).
com_package_name: This refers to the package name corresponding to the Keys Kotlin object here. This should always point to the package of the class where you intend to use it. So, if the package name is com.package.name, the . (periods) are replaced with _ (underscores), and it becomes com_package_name.
Store your API key in the api_key variable in the above C++ function , and return it as shown in the code snippet above.



Note: Don't forget to add your native-lib.cpp to your .gitignore.



know what version control is, check out this tutorial here.

Step 4: Create a CMakeLists.txt file
Under the app/ folder, create a new text file and name it CMakeLists.txt. Add the following code in the file:

# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/cpp/native-lib.cpp )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-lib

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )
                       
                       
Step 5: Configure Gradle for CMake
Add the following lines to the android block in your app-level build.gradle file:

android {
  ...
  externalNativeBuild {
    cmake {
        path "CMakeLists.txt"
    }
  }
}

Rebuild your project after you've modified your Gradle file.

Step 6: Creating the Keys.kt file
Create a Kotlin object, Keys.kt, and obtain your API key as followed:

object Keys {

    init {
        System.loadLibrary("native-lib")
    }

    external fun apiKey(): String
}
Now, you need to call the System.loadLibrary("native-lib") method in the init block to load the C++ code that you've written in the native-lib.cpp file.

Once you've done this, you can then get a reference to your method by declaring an external Kotlin function under the same name as the one mentioned above in Step 3. In this example, it's apiKey().

Now, to get your API key from any part of your app, just call:

Keys.apiKey()


It's never a good idea to leave your API keys lying around your codebase in a way that's easily decodable.

Understanding links - https://blog.mindorks.com/getting-started-with-android-ndk-android-tutorial , https://www.codementor.io/blog/kotlin-apikeys-7o0g54qk5b

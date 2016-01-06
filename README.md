s3eWwise
========

This is the official Maramalade extension for [AudioKinetic Wwise](https://www.audiokinetic.com/home/).
Wwise is an audio middleware which can be used to play music and sound.

Supported Platforms
-------------------

* iOS
* Mac OSX
* Windows
* Android

Getting Started
===============

In order to use this extension, you must build it yourself. Unfortunately we cannot redistribute
AudioKinetic's binaries in this repository. Begin by downloading the different Wwise SDKs you will need
and placing them in the empty `s3eWwise/Wwise/SDK` directory.

To get the Wwise SDK:

* Go to the [AudioKinetic Download Page](https://www.audiokinetic.com/downloads/) and download the latest SDK for each platform.
* It is recommended you use the Windows web installer (first download listed).
* iOS and Mac SDKs must be downloaded separately.
* When running the Windows web installer, make sure to install:
    * Authoring Binaries 32-bit / 64-bit (required for the example to work)
    * Android SDK
    * Windows SDK
    * Common SDK
* Begin with the Mac installation, since copying from the Mac to Windows tends to remove some of the Windows files
* iOS and Mac SDKs come as zipped packages. These need to be installed on a Mac.
* Once both are installed, copy the folders from `/Users/$USER/Wwise/<WWISE_VERSION>/SDK` into the `s3eWwise/Wwise/SDK` directory.
* Copy the contents of the Android and Windows SDKs from `C:\Program Files (x86)\Audiokinetic\Wwise <build #>\SDK` into the `s3eWwise/Wwise/SDK` directory.

Building s3eWwise
=================

Once the Wwise SDK is setup, each platform must be build

As you build the library for each platform, make sure to follow the [EDK Guide](http://docs.madewithmarmalade.com/native/extensions/edkguides.html).
The EDK Guide provides helpful instructions, i.e. mounting a the Windows directory
on your Mac so the iOS and Mac versions can be built through SSH. It also contains other helpful tips for troubleshooting

**Note**: Do not rebuild the extension using the s3eWwise.s4e file. This will re-generate some of the extension source code
and cause compile errors.

Windows
-------

On Windows, the debug and release versions are in separate MKB project files. The debug and release
versions must use different libraries and Marmalade doesn't support this well, so the projects were split.

To build Debug:

* Double-Click the s3eWwise_windows_debug.mkb file
* Set the solution configuration to "**x86 Debug**"
* Build the solution

To build Release:

* Double-Click the s3eWwise_windows_release.mkb file
* Set the solution configuration to "**x86 Release**"
* Build the solution

Android
-------

On Android, make sure you have the Android SDK and NDK installed. These can be extracted anywhere on the drive.
Make sure you have an environment variable called NDK_ROOT which points to the NDK installation folder.

**Note**: As of 2013.1, Wwise is only compatible with the r8d version of the NDK. See the Wwise release notes for more details.

**Note**: 

Double-click the s3eWwise_android_release.mkb file to launch the build.

iOS
---

The iOS extension must be built on a Mac. The easiest way to do this is to share the Marmalade/<version>/extensions
folder and mount it on your Mac. Instructions to do this can be found in the [iOS EDK Guide](http://docs.madewithmarmalade.com/native/extensions/edkguides/iosedkguide.html)

Make sure you have the Marmalade SDK installed on your Mac, along with all its dependencies.

Build the extension in the terminal by navigating to the s3eWwise folder and running `mkb --arm --iphone s3eWwise_iphone.mkb`.
The Wwise libraries will be copied to the appropriate locations and the build will run for debug and release.

**NOTE:** If encountering weird linker errors related to AK::SoundEngine - AudioKinetic changed the type of certain functions and it may be necessary to change the type of AkUIntPtr from "unsigned int" to "unsigned long" in order for these functions to link correctly

Mac OSX
-------

The Mac OSX extension must also be built on a Mac. In this case you must run the build in Xcode since some build settings must be manually changed.
Marmalade doesn't have an mkb command for including frameworks into the build, so you must open the s3eWwise_osx.mkb file, which will launch Xcode.
Once Xcode is running:

* Click on the s3eWwise_osx project in the Project Navigator
* Click the "Build Phases" tab
* Expand the header marked "Link Binary with Libraries"
* Click the little "+" icon in bottom left of the window
* Add each of these frameworks one by one:
	* AudioUnit.framework
	* CoreAudio.framework
	* AudioToolbox.framework
	
After the frameworks have been manually set up, build the project for debug and release.

**Note**: You will have to repeat the above steps to include the framework every time you rebuild the extension. The xcode settings will not be saved in the MKB.

**NOTE:** If encountering weird linker errors related to AK::SoundEngine - AudioKinetic changed the type of certain functions and it may be necessary to change the type of AkUIntPtr from "unsigned int" to "unsigned long" in order for these functions to link correctly

Windows Phone 8
---------------

To build the WP8 extension, you need to download the [Windows Phone 8 SDK](http://www.microsoft.com/en-us/download/details.aspx?id=35471) from Microsoft.


Implementation Example
======================

An example of how to use s3eWwise is provided in the `s3eWwise/example` directory. This is a standard Marmalade application
and is configured exactly the way your project should be when using s3eWwise.

Building the Example
--------------------

To build the example, begin by double-clicking the `example/s3eWwiseExample.mkb` file. The example will copy the appropriate Wwise
sound banks from the `s3eWwise/Wwise/SDK/samples` directory and open your IDE. Once this is complete you can run the example in the
simulator to hear audio playing.

**Note**: The example MKB must be executed at least once on Windows, since Wwise can only generate soundbanks on a Windows machine.
The Wwise Authoring application must also be installed.

Clicking on the screen should trigger the "Play Hello" event and you will hear a voice. Holding and moving the mouse and up down will rev
the car engine sound.

Deploying the Example
---------------------

To test the different platform versions of the extension, you must deploy the example to a device. To do this use the Marmalade Deploy Tool.
You can follow instructions on how to deploy to each device in the [Marmalade Documentation](http://docs.madewithmarmalade.com/native/deployment/usingthedeploymenttool.html).

Building the extension with Plugins
===================================

Coming soon: How to use Wwise plugins with the extension.

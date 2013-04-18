s3eWwise
========

This is the Maramalade extension for AudioKinetic Wwise.

Supported Platforms
-------------------

* iOS

Installation
============

A license for Wwise and access to the Wwise SDK is needed before you can install s3eWwise.
Binaries are not included because the final library will contain AudioKinetic code.

To begin, copy the Wwise SDK directory into the Wwise folder.

Build the extension by running `mkb --arm --iphone s3eWwise_iphone.mkb` in the console on OSX.
A Mac is needed to build the extension.

Finally, use the extension in your code by including it as a subproject.

All AudioKinetic APIs are implemented as s3eWwise functions.

See the example directory for a working example which can be deployed to the phone.

## Installation / Setup

bashrc:
```
export ANDROID_HOME=$HOME/Android/Sdk
export ANDROID_NDK_HOME=$ANDROID_HOME/ndk/21.4.7075529
```

 * `sudo apt-get install default-jdk` # To install java
 * `~/Android/Sdk/cmdline-tools/latest/bin/sdkmanager --install "ndk;21.4.7075529"`
    * Bazel supports NDK only up to 21 :-(
    * See also: https://github.com/google/mediapipe/issues/1281

## Build

```
$ bazel build hello_open_cl
```

## Run

```
$ adb push bazel-bin/hello_open_cl/hello_open_cl /data/local/tmp/hello_open_cl && adb shell /data/local/tmp/hello_open_cl 

```


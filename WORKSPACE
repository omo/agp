android_sdk_repository(name = "androidsdk")

# https://bazel.build/docs/android-ndk
# You need the explicit api_level.
# https://github.com/google/mediapipe/issues/1281
android_ndk_repository(name = "androidndk", api_level=21)
register_toolchains("@androidndk//:all")

load("//third_party/opencl_headers:workspace.bzl", opencl_headers = "repo")
opencl_headers()

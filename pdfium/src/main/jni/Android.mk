LOCAL_PATH := $(call my-dir)

#Prebuilt libraries
include $(CLEAR_VARS)
LOCAL_MODULE := aospPdfium

ARCH_PATH = $(TARGET_ARCH_ABI)

LOCAL_SRC_FILES := $(LOCAL_PATH)/lib/$(ARCH_PATH)/libpdfium.so

include $(PREBUILT_SHARED_LIBRARY)

#c++_shared
include $(CLEAR_VARS)
LOCAL_MODULE := libmodc++_shared

LOCAL_SRC_FILES := $(LOCAL_PATH)/lib/$(ARCH_PATH)/libc++_shared.so

include $(PREBUILT_SHARED_LIBRARY)

#libmodft2
include $(CLEAR_VARS)
LOCAL_MODULE := libmodft2

LOCAL_SRC_FILES := $(LOCAL_PATH)/lib/$(ARCH_PATH)/libmodft2.so

include $(PREBUILT_SHARED_LIBRARY)

#libmodpng
include $(CLEAR_VARS)
LOCAL_MODULE := libmodpng

LOCAL_SRC_FILES := $(LOCAL_PATH)/lib/$(ARCH_PATH)/libmodpng.so

include $(PREBUILT_SHARED_LIBRARY)

#Main JNI library
include $(CLEAR_VARS)
LOCAL_MODULE := jniPdfium

LOCAL_CFLAGS += -DHAVE_PTHREADS
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include
LOCAL_SHARED_LIBRARIES := aospPdfium libmodc++_shared libmodft2 libmodpng
LOCAL_LDLIBS += -llog -landroid -ljnigraphics

LOCAL_SRC_FILES :=  $(LOCAL_PATH)/src/mainJNILib.cpp
LOCAL_LDFLAGS += "-Wl,-z,max-page-size=16384"

include $(BUILD_SHARED_LIBRARY)

ifeq ($(TARGET_BUILD_VARIANT),debug)
# Google Test libraries (GTest and GMock)
# GTest
include $(CLEAR_VARS)
LOCAL_MODULE := gtest
LOCAL_SRC_FILES := $(LOCAL_PATH)/gtest/googletest/src
LOCAL_C_INCLUDES := $(LOCAL_PATH)/gtest/googletest/include
include $(BUILD_SHARED_LIBRARY)

# GMock
include $(CLEAR_VARS)
LOCAL_MODULE := gmock
LOCAL_SRC_FILES := $(LOCAL_PATH)/gtest/googlemock/src
LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/gtest/googlemock/include \
    $(LOCAL_PATH)/gtest/googletest/include
include $(BUILD_SHARED_LIBRARY)

# Unit Test Target
include $(CLEAR_VARS)
LOCAL_MODULE := test_jniPdfium

LOCAL_CFLAGS += -DHAVE_PTHREADS -DUNIT_TESTING
LOCAL_LDLIBS += -llog -landroid -ljnigraphics -lz

LOCAL_SRC_FILES := \
    $(LOCAL_PATH)/test/test_mainJNILib.cpp\
  gtest/googlemock/src/gmock-all.cc \
  gtest/googletest/src/gtest-all.cc

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/include \
    $(LOCAL_PATH)/gtest/googletest/include \
    $(LOCAL_PATH)/gtest/googlemock/include

LOCAL_SHARED_LIBRARIES := \
    gtest \
    gmock \
    aospPdfium \
    libmodc++_shared \
    libmodft2 \
    libmodpng

LOCAL_STATIC_LIBRARIES := libmodc++_shared


include $(BUILD_EXECUTABLE)
endif
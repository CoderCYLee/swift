cmake_minimum_required(VERSION 3.4.3)
include("../../../../cmake/modules/StandaloneOverlay.cmake")

add_swift_library(swiftCoreData ${SWIFT_SDK_OVERLAY_LIBRARY_BUILD_TYPES} IS_SDK_OVERLAY
  CocoaError.swift
  NSManagedObjectContext.swift
  CoreData.mm

  SWIFT_COMPILE_FLAGS "${SWIFT_RUNTIME_SWIFT_COMPILE_FLAGS}"
  LINK_FLAGS "${SWIFT_RUNTIME_SWIFT_LINK_FLAGS}"
  SWIFT_MODULE_DEPENDS_OSX Darwin CoreGraphics Dispatch Foundation IOKit ObjectiveC # auto-updated
  SWIFT_MODULE_DEPENDS_IOS Darwin CoreGraphics Dispatch Foundation ObjectiveC XPC # auto-updated
  SWIFT_MODULE_DEPENDS_TVOS Darwin CoreGraphics Dispatch Foundation ObjectiveC XPC # auto-updated
  SWIFT_MODULE_DEPENDS_WATCHOS Darwin CoreGraphics Dispatch Foundation ObjectiveC XPC # auto-updated
  FRAMEWORK_DEPENDS CoreData

  DEPLOYMENT_VERSION_OSX ${SWIFTLIB_DEPLOYMENT_VERSION_COREDATA_OSX}
  DEPLOYMENT_VERSION_IOS ${SWIFTLIB_DEPLOYMENT_VERSION_COREDATA_IOS}
  DEPLOYMENT_VERSION_TVOS ${SWIFTLIB_DEPLOYMENT_VERSION_COREDATA_TVOS}
  DEPLOYMENT_VERSION_WATCHOS ${SWIFTLIB_DEPLOYMENT_VERSION_COREDATA_WATCHOS}
)

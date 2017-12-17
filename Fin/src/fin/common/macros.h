#pragma once

#define REQUIRE_POINTER(CLASS_NAME) \
  CLASS_NAME(const CLASS_NAME &) = delete; \
  CLASS_NAME & operator=( const CLASS_NAME & ) = delete; \
  CLASS_NAME( CLASS_NAME && ) = delete; \
  CLASS_NAME & operator=( CLASS_NAME && ) = delete;

#define PREVENT_POINTER(CLASS_NAME) \
  static void *operator new    ( size_t ) = delete; \
  static void *operator new[]  ( size_t ) = delete; \
  static void  operator delete  ( void* ) = delete; \
  static void  operator delete[]( void* ) = delete;

#define STATIC_CLASS(CLASS_NAME) \
  REQUIRE_POINTER(CLASS_NAME) \
  PREVENT_POINTER(CLASS_NAME)
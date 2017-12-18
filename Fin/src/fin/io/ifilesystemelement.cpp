#include "stdafx.h"

#include "directory.h"
#include "ifilesystemelement.h"

namespace fin::io {
  Directory IFilesystemElement::parent() const {
    return Directory(path.parent_path().string());
  }
}
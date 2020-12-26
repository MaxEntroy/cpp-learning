#include "utils.h"

#include "proto/outer/docinfo.pb.h"

namespace utils {

bool IsValidDocInfo(const DocInfo& docinfo) {
  if (!docinfo.has_doc_type()) {
    return false;
  }

  const std::string& type = docinfo.doc_type();
  if (type == "Art" && !docinfo.has_art()) {
    return false;
  }

  if (type == "Vid" && !docinfo.has_vid()) {
    return false;
  }

  return true;
}

}  // namespace utils

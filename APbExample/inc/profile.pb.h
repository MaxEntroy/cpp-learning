// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: profile.proto

#ifndef PROTOBUF_INCLUDED_profile_2eproto
#define PROTOBUF_INCLUDED_profile_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_profile_2eproto 

namespace protobuf_profile_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[2];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_profile_2eproto
namespace qqnews {
class CatProfile;
class CatProfileDefaultTypeInternal;
extern CatProfileDefaultTypeInternal _CatProfile_default_instance_;
class KBUserInfo;
class KBUserInfoDefaultTypeInternal;
extern KBUserInfoDefaultTypeInternal _KBUserInfo_default_instance_;
}  // namespace qqnews
namespace google {
namespace protobuf {
template<> ::qqnews::CatProfile* Arena::CreateMaybeMessage<::qqnews::CatProfile>(Arena*);
template<> ::qqnews::KBUserInfo* Arena::CreateMaybeMessage<::qqnews::KBUserInfo>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace qqnews {

// ===================================================================

class CatProfile : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:qqnews.CatProfile) */ {
 public:
  CatProfile();
  virtual ~CatProfile();

  CatProfile(const CatProfile& from);

  inline CatProfile& operator=(const CatProfile& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  CatProfile(CatProfile&& from) noexcept
    : CatProfile() {
    *this = ::std::move(from);
  }

  inline CatProfile& operator=(CatProfile&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const CatProfile& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const CatProfile* internal_default_instance() {
    return reinterpret_cast<const CatProfile*>(
               &_CatProfile_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(CatProfile* other);
  friend void swap(CatProfile& a, CatProfile& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline CatProfile* New() const final {
    return CreateMaybeMessage<CatProfile>(NULL);
  }

  CatProfile* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<CatProfile>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const CatProfile& from);
  void MergeFrom(const CatProfile& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(CatProfile* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional string type = 1;
  bool has_type() const;
  void clear_type();
  static const int kTypeFieldNumber = 1;
  const ::std::string& type() const;
  void set_type(const ::std::string& value);
  #if LANG_CXX11
  void set_type(::std::string&& value);
  #endif
  void set_type(const char* value);
  void set_type(const char* value, size_t size);
  ::std::string* mutable_type();
  ::std::string* release_type();
  void set_allocated_type(::std::string* type);

  // optional string weight = 2;
  bool has_weight() const;
  void clear_weight();
  static const int kWeightFieldNumber = 2;
  const ::std::string& weight() const;
  void set_weight(const ::std::string& value);
  #if LANG_CXX11
  void set_weight(::std::string&& value);
  #endif
  void set_weight(const char* value);
  void set_weight(const char* value, size_t size);
  ::std::string* mutable_weight();
  ::std::string* release_weight();
  void set_allocated_weight(::std::string* weight);

  // optional string lv1 = 3;
  bool has_lv1() const;
  void clear_lv1();
  static const int kLv1FieldNumber = 3;
  const ::std::string& lv1() const;
  void set_lv1(const ::std::string& value);
  #if LANG_CXX11
  void set_lv1(::std::string&& value);
  #endif
  void set_lv1(const char* value);
  void set_lv1(const char* value, size_t size);
  ::std::string* mutable_lv1();
  ::std::string* release_lv1();
  void set_allocated_lv1(::std::string* lv1);

  // optional string lv2 = 4;
  bool has_lv2() const;
  void clear_lv2();
  static const int kLv2FieldNumber = 4;
  const ::std::string& lv2() const;
  void set_lv2(const ::std::string& value);
  #if LANG_CXX11
  void set_lv2(::std::string&& value);
  #endif
  void set_lv2(const char* value);
  void set_lv2(const char* value, size_t size);
  ::std::string* mutable_lv2();
  ::std::string* release_lv2();
  void set_allocated_lv2(::std::string* lv2);

  // optional string lv3 = 5;
  bool has_lv3() const;
  void clear_lv3();
  static const int kLv3FieldNumber = 5;
  const ::std::string& lv3() const;
  void set_lv3(const ::std::string& value);
  #if LANG_CXX11
  void set_lv3(::std::string&& value);
  #endif
  void set_lv3(const char* value);
  void set_lv3(const char* value, size_t size);
  ::std::string* mutable_lv3();
  ::std::string* release_lv3();
  void set_allocated_lv3(::std::string* lv3);

  // optional string lv4 = 6;
  bool has_lv4() const;
  void clear_lv4();
  static const int kLv4FieldNumber = 6;
  const ::std::string& lv4() const;
  void set_lv4(const ::std::string& value);
  #if LANG_CXX11
  void set_lv4(::std::string&& value);
  #endif
  void set_lv4(const char* value);
  void set_lv4(const char* value, size_t size);
  ::std::string* mutable_lv4();
  ::std::string* release_lv4();
  void set_allocated_lv4(::std::string* lv4);

  // @@protoc_insertion_point(class_scope:qqnews.CatProfile)
 private:
  void set_has_type();
  void clear_has_type();
  void set_has_weight();
  void clear_has_weight();
  void set_has_lv1();
  void clear_has_lv1();
  void set_has_lv2();
  void clear_has_lv2();
  void set_has_lv3();
  void clear_has_lv3();
  void set_has_lv4();
  void clear_has_lv4();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr type_;
  ::google::protobuf::internal::ArenaStringPtr weight_;
  ::google::protobuf::internal::ArenaStringPtr lv1_;
  ::google::protobuf::internal::ArenaStringPtr lv2_;
  ::google::protobuf::internal::ArenaStringPtr lv3_;
  ::google::protobuf::internal::ArenaStringPtr lv4_;
  friend struct ::protobuf_profile_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class KBUserInfo : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:qqnews.KBUserInfo) */ {
 public:
  KBUserInfo();
  virtual ~KBUserInfo();

  KBUserInfo(const KBUserInfo& from);

  inline KBUserInfo& operator=(const KBUserInfo& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  KBUserInfo(KBUserInfo&& from) noexcept
    : KBUserInfo() {
    *this = ::std::move(from);
  }

  inline KBUserInfo& operator=(KBUserInfo&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const KBUserInfo& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const KBUserInfo* internal_default_instance() {
    return reinterpret_cast<const KBUserInfo*>(
               &_KBUserInfo_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(KBUserInfo* other);
  friend void swap(KBUserInfo& a, KBUserInfo& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline KBUserInfo* New() const final {
    return CreateMaybeMessage<KBUserInfo>(NULL);
  }

  KBUserInfo* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<KBUserInfo>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const KBUserInfo& from);
  void MergeFrom(const KBUserInfo& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(KBUserInfo* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .qqnews.CatProfile cat_profile = 1;
  int cat_profile_size() const;
  void clear_cat_profile();
  static const int kCatProfileFieldNumber = 1;
  ::qqnews::CatProfile* mutable_cat_profile(int index);
  ::google::protobuf::RepeatedPtrField< ::qqnews::CatProfile >*
      mutable_cat_profile();
  const ::qqnews::CatProfile& cat_profile(int index) const;
  ::qqnews::CatProfile* add_cat_profile();
  const ::google::protobuf::RepeatedPtrField< ::qqnews::CatProfile >&
      cat_profile() const;

  // @@protoc_insertion_point(class_scope:qqnews.KBUserInfo)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::qqnews::CatProfile > cat_profile_;
  friend struct ::protobuf_profile_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// CatProfile

// optional string type = 1;
inline bool CatProfile::has_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void CatProfile::set_has_type() {
  _has_bits_[0] |= 0x00000001u;
}
inline void CatProfile::clear_has_type() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void CatProfile::clear_type() {
  type_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_type();
}
inline const ::std::string& CatProfile::type() const {
  // @@protoc_insertion_point(field_get:qqnews.CatProfile.type)
  return type_.GetNoArena();
}
inline void CatProfile::set_type(const ::std::string& value) {
  set_has_type();
  type_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:qqnews.CatProfile.type)
}
#if LANG_CXX11
inline void CatProfile::set_type(::std::string&& value) {
  set_has_type();
  type_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:qqnews.CatProfile.type)
}
#endif
inline void CatProfile::set_type(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  set_has_type();
  type_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:qqnews.CatProfile.type)
}
inline void CatProfile::set_type(const char* value, size_t size) {
  set_has_type();
  type_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:qqnews.CatProfile.type)
}
inline ::std::string* CatProfile::mutable_type() {
  set_has_type();
  // @@protoc_insertion_point(field_mutable:qqnews.CatProfile.type)
  return type_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* CatProfile::release_type() {
  // @@protoc_insertion_point(field_release:qqnews.CatProfile.type)
  if (!has_type()) {
    return NULL;
  }
  clear_has_type();
  return type_.ReleaseNonDefaultNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void CatProfile::set_allocated_type(::std::string* type) {
  if (type != NULL) {
    set_has_type();
  } else {
    clear_has_type();
  }
  type_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), type);
  // @@protoc_insertion_point(field_set_allocated:qqnews.CatProfile.type)
}

// optional string weight = 2;
inline bool CatProfile::has_weight() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void CatProfile::set_has_weight() {
  _has_bits_[0] |= 0x00000002u;
}
inline void CatProfile::clear_has_weight() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void CatProfile::clear_weight() {
  weight_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_weight();
}
inline const ::std::string& CatProfile::weight() const {
  // @@protoc_insertion_point(field_get:qqnews.CatProfile.weight)
  return weight_.GetNoArena();
}
inline void CatProfile::set_weight(const ::std::string& value) {
  set_has_weight();
  weight_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:qqnews.CatProfile.weight)
}
#if LANG_CXX11
inline void CatProfile::set_weight(::std::string&& value) {
  set_has_weight();
  weight_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:qqnews.CatProfile.weight)
}
#endif
inline void CatProfile::set_weight(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  set_has_weight();
  weight_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:qqnews.CatProfile.weight)
}
inline void CatProfile::set_weight(const char* value, size_t size) {
  set_has_weight();
  weight_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:qqnews.CatProfile.weight)
}
inline ::std::string* CatProfile::mutable_weight() {
  set_has_weight();
  // @@protoc_insertion_point(field_mutable:qqnews.CatProfile.weight)
  return weight_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* CatProfile::release_weight() {
  // @@protoc_insertion_point(field_release:qqnews.CatProfile.weight)
  if (!has_weight()) {
    return NULL;
  }
  clear_has_weight();
  return weight_.ReleaseNonDefaultNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void CatProfile::set_allocated_weight(::std::string* weight) {
  if (weight != NULL) {
    set_has_weight();
  } else {
    clear_has_weight();
  }
  weight_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), weight);
  // @@protoc_insertion_point(field_set_allocated:qqnews.CatProfile.weight)
}

// optional string lv1 = 3;
inline bool CatProfile::has_lv1() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void CatProfile::set_has_lv1() {
  _has_bits_[0] |= 0x00000004u;
}
inline void CatProfile::clear_has_lv1() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void CatProfile::clear_lv1() {
  lv1_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_lv1();
}
inline const ::std::string& CatProfile::lv1() const {
  // @@protoc_insertion_point(field_get:qqnews.CatProfile.lv1)
  return lv1_.GetNoArena();
}
inline void CatProfile::set_lv1(const ::std::string& value) {
  set_has_lv1();
  lv1_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:qqnews.CatProfile.lv1)
}
#if LANG_CXX11
inline void CatProfile::set_lv1(::std::string&& value) {
  set_has_lv1();
  lv1_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:qqnews.CatProfile.lv1)
}
#endif
inline void CatProfile::set_lv1(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  set_has_lv1();
  lv1_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:qqnews.CatProfile.lv1)
}
inline void CatProfile::set_lv1(const char* value, size_t size) {
  set_has_lv1();
  lv1_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:qqnews.CatProfile.lv1)
}
inline ::std::string* CatProfile::mutable_lv1() {
  set_has_lv1();
  // @@protoc_insertion_point(field_mutable:qqnews.CatProfile.lv1)
  return lv1_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* CatProfile::release_lv1() {
  // @@protoc_insertion_point(field_release:qqnews.CatProfile.lv1)
  if (!has_lv1()) {
    return NULL;
  }
  clear_has_lv1();
  return lv1_.ReleaseNonDefaultNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void CatProfile::set_allocated_lv1(::std::string* lv1) {
  if (lv1 != NULL) {
    set_has_lv1();
  } else {
    clear_has_lv1();
  }
  lv1_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), lv1);
  // @@protoc_insertion_point(field_set_allocated:qqnews.CatProfile.lv1)
}

// optional string lv2 = 4;
inline bool CatProfile::has_lv2() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void CatProfile::set_has_lv2() {
  _has_bits_[0] |= 0x00000008u;
}
inline void CatProfile::clear_has_lv2() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void CatProfile::clear_lv2() {
  lv2_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_lv2();
}
inline const ::std::string& CatProfile::lv2() const {
  // @@protoc_insertion_point(field_get:qqnews.CatProfile.lv2)
  return lv2_.GetNoArena();
}
inline void CatProfile::set_lv2(const ::std::string& value) {
  set_has_lv2();
  lv2_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:qqnews.CatProfile.lv2)
}
#if LANG_CXX11
inline void CatProfile::set_lv2(::std::string&& value) {
  set_has_lv2();
  lv2_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:qqnews.CatProfile.lv2)
}
#endif
inline void CatProfile::set_lv2(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  set_has_lv2();
  lv2_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:qqnews.CatProfile.lv2)
}
inline void CatProfile::set_lv2(const char* value, size_t size) {
  set_has_lv2();
  lv2_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:qqnews.CatProfile.lv2)
}
inline ::std::string* CatProfile::mutable_lv2() {
  set_has_lv2();
  // @@protoc_insertion_point(field_mutable:qqnews.CatProfile.lv2)
  return lv2_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* CatProfile::release_lv2() {
  // @@protoc_insertion_point(field_release:qqnews.CatProfile.lv2)
  if (!has_lv2()) {
    return NULL;
  }
  clear_has_lv2();
  return lv2_.ReleaseNonDefaultNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void CatProfile::set_allocated_lv2(::std::string* lv2) {
  if (lv2 != NULL) {
    set_has_lv2();
  } else {
    clear_has_lv2();
  }
  lv2_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), lv2);
  // @@protoc_insertion_point(field_set_allocated:qqnews.CatProfile.lv2)
}

// optional string lv3 = 5;
inline bool CatProfile::has_lv3() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void CatProfile::set_has_lv3() {
  _has_bits_[0] |= 0x00000010u;
}
inline void CatProfile::clear_has_lv3() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void CatProfile::clear_lv3() {
  lv3_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_lv3();
}
inline const ::std::string& CatProfile::lv3() const {
  // @@protoc_insertion_point(field_get:qqnews.CatProfile.lv3)
  return lv3_.GetNoArena();
}
inline void CatProfile::set_lv3(const ::std::string& value) {
  set_has_lv3();
  lv3_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:qqnews.CatProfile.lv3)
}
#if LANG_CXX11
inline void CatProfile::set_lv3(::std::string&& value) {
  set_has_lv3();
  lv3_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:qqnews.CatProfile.lv3)
}
#endif
inline void CatProfile::set_lv3(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  set_has_lv3();
  lv3_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:qqnews.CatProfile.lv3)
}
inline void CatProfile::set_lv3(const char* value, size_t size) {
  set_has_lv3();
  lv3_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:qqnews.CatProfile.lv3)
}
inline ::std::string* CatProfile::mutable_lv3() {
  set_has_lv3();
  // @@protoc_insertion_point(field_mutable:qqnews.CatProfile.lv3)
  return lv3_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* CatProfile::release_lv3() {
  // @@protoc_insertion_point(field_release:qqnews.CatProfile.lv3)
  if (!has_lv3()) {
    return NULL;
  }
  clear_has_lv3();
  return lv3_.ReleaseNonDefaultNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void CatProfile::set_allocated_lv3(::std::string* lv3) {
  if (lv3 != NULL) {
    set_has_lv3();
  } else {
    clear_has_lv3();
  }
  lv3_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), lv3);
  // @@protoc_insertion_point(field_set_allocated:qqnews.CatProfile.lv3)
}

// optional string lv4 = 6;
inline bool CatProfile::has_lv4() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void CatProfile::set_has_lv4() {
  _has_bits_[0] |= 0x00000020u;
}
inline void CatProfile::clear_has_lv4() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void CatProfile::clear_lv4() {
  lv4_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_lv4();
}
inline const ::std::string& CatProfile::lv4() const {
  // @@protoc_insertion_point(field_get:qqnews.CatProfile.lv4)
  return lv4_.GetNoArena();
}
inline void CatProfile::set_lv4(const ::std::string& value) {
  set_has_lv4();
  lv4_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:qqnews.CatProfile.lv4)
}
#if LANG_CXX11
inline void CatProfile::set_lv4(::std::string&& value) {
  set_has_lv4();
  lv4_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:qqnews.CatProfile.lv4)
}
#endif
inline void CatProfile::set_lv4(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  set_has_lv4();
  lv4_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:qqnews.CatProfile.lv4)
}
inline void CatProfile::set_lv4(const char* value, size_t size) {
  set_has_lv4();
  lv4_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:qqnews.CatProfile.lv4)
}
inline ::std::string* CatProfile::mutable_lv4() {
  set_has_lv4();
  // @@protoc_insertion_point(field_mutable:qqnews.CatProfile.lv4)
  return lv4_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* CatProfile::release_lv4() {
  // @@protoc_insertion_point(field_release:qqnews.CatProfile.lv4)
  if (!has_lv4()) {
    return NULL;
  }
  clear_has_lv4();
  return lv4_.ReleaseNonDefaultNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void CatProfile::set_allocated_lv4(::std::string* lv4) {
  if (lv4 != NULL) {
    set_has_lv4();
  } else {
    clear_has_lv4();
  }
  lv4_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), lv4);
  // @@protoc_insertion_point(field_set_allocated:qqnews.CatProfile.lv4)
}

// -------------------------------------------------------------------

// KBUserInfo

// repeated .qqnews.CatProfile cat_profile = 1;
inline int KBUserInfo::cat_profile_size() const {
  return cat_profile_.size();
}
inline void KBUserInfo::clear_cat_profile() {
  cat_profile_.Clear();
}
inline ::qqnews::CatProfile* KBUserInfo::mutable_cat_profile(int index) {
  // @@protoc_insertion_point(field_mutable:qqnews.KBUserInfo.cat_profile)
  return cat_profile_.Mutable(index);
}
inline ::google::protobuf::RepeatedPtrField< ::qqnews::CatProfile >*
KBUserInfo::mutable_cat_profile() {
  // @@protoc_insertion_point(field_mutable_list:qqnews.KBUserInfo.cat_profile)
  return &cat_profile_;
}
inline const ::qqnews::CatProfile& KBUserInfo::cat_profile(int index) const {
  // @@protoc_insertion_point(field_get:qqnews.KBUserInfo.cat_profile)
  return cat_profile_.Get(index);
}
inline ::qqnews::CatProfile* KBUserInfo::add_cat_profile() {
  // @@protoc_insertion_point(field_add:qqnews.KBUserInfo.cat_profile)
  return cat_profile_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::qqnews::CatProfile >&
KBUserInfo::cat_profile() const {
  // @@protoc_insertion_point(field_list:qqnews.KBUserInfo.cat_profile)
  return cat_profile_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace qqnews

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_profile_2eproto
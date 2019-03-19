// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: luacall.proto

#ifndef PROTOBUF_INCLUDED_luacall_2eproto
#define PROTOBUF_INCLUDED_luacall_2eproto

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
#include "profile.pb.h"
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_luacall_2eproto 

namespace protobuf_luacall_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[1];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_luacall_2eproto
namespace qqnews {
class LuaNewsInfo;
class LuaNewsInfoDefaultTypeInternal;
extern LuaNewsInfoDefaultTypeInternal _LuaNewsInfo_default_instance_;
}  // namespace qqnews
namespace google {
namespace protobuf {
template<> ::qqnews::LuaNewsInfo* Arena::CreateMaybeMessage<::qqnews::LuaNewsInfo>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace qqnews {

// ===================================================================

class LuaNewsInfo : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:qqnews.LuaNewsInfo) */ {
 public:
  LuaNewsInfo();
  virtual ~LuaNewsInfo();

  LuaNewsInfo(const LuaNewsInfo& from);

  inline LuaNewsInfo& operator=(const LuaNewsInfo& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  LuaNewsInfo(LuaNewsInfo&& from) noexcept
    : LuaNewsInfo() {
    *this = ::std::move(from);
  }

  inline LuaNewsInfo& operator=(LuaNewsInfo&& from) noexcept {
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
  static const LuaNewsInfo& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const LuaNewsInfo* internal_default_instance() {
    return reinterpret_cast<const LuaNewsInfo*>(
               &_LuaNewsInfo_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(LuaNewsInfo* other);
  friend void swap(LuaNewsInfo& a, LuaNewsInfo& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline LuaNewsInfo* New() const final {
    return CreateMaybeMessage<LuaNewsInfo>(NULL);
  }

  LuaNewsInfo* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<LuaNewsInfo>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const LuaNewsInfo& from);
  void MergeFrom(const LuaNewsInfo& from);
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
  void InternalSwap(LuaNewsInfo* other);
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

  // optional .qqnews.KBUserInfo user_info = 2;
  bool has_user_info() const;
  void clear_user_info();
  static const int kUserInfoFieldNumber = 2;
  private:
  const ::qqnews::KBUserInfo& _internal_user_info() const;
  public:
  const ::qqnews::KBUserInfo& user_info() const;
  ::qqnews::KBUserInfo* release_user_info();
  ::qqnews::KBUserInfo* mutable_user_info();
  void set_allocated_user_info(::qqnews::KBUserInfo* user_info);

  // required uint32 lua_id = 1;
  bool has_lua_id() const;
  void clear_lua_id();
  static const int kLuaIdFieldNumber = 1;
  ::google::protobuf::uint32 lua_id() const;
  void set_lua_id(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:qqnews.LuaNewsInfo)
 private:
  void set_has_lua_id();
  void clear_has_lua_id();
  void set_has_user_info();
  void clear_has_user_info();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::qqnews::KBUserInfo* user_info_;
  ::google::protobuf::uint32 lua_id_;
  friend struct ::protobuf_luacall_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// LuaNewsInfo

// required uint32 lua_id = 1;
inline bool LuaNewsInfo::has_lua_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void LuaNewsInfo::set_has_lua_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void LuaNewsInfo::clear_has_lua_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void LuaNewsInfo::clear_lua_id() {
  lua_id_ = 0u;
  clear_has_lua_id();
}
inline ::google::protobuf::uint32 LuaNewsInfo::lua_id() const {
  // @@protoc_insertion_point(field_get:qqnews.LuaNewsInfo.lua_id)
  return lua_id_;
}
inline void LuaNewsInfo::set_lua_id(::google::protobuf::uint32 value) {
  set_has_lua_id();
  lua_id_ = value;
  // @@protoc_insertion_point(field_set:qqnews.LuaNewsInfo.lua_id)
}

// optional .qqnews.KBUserInfo user_info = 2;
inline bool LuaNewsInfo::has_user_info() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void LuaNewsInfo::set_has_user_info() {
  _has_bits_[0] |= 0x00000001u;
}
inline void LuaNewsInfo::clear_has_user_info() {
  _has_bits_[0] &= ~0x00000001u;
}
inline const ::qqnews::KBUserInfo& LuaNewsInfo::_internal_user_info() const {
  return *user_info_;
}
inline const ::qqnews::KBUserInfo& LuaNewsInfo::user_info() const {
  const ::qqnews::KBUserInfo* p = user_info_;
  // @@protoc_insertion_point(field_get:qqnews.LuaNewsInfo.user_info)
  return p != NULL ? *p : *reinterpret_cast<const ::qqnews::KBUserInfo*>(
      &::qqnews::_KBUserInfo_default_instance_);
}
inline ::qqnews::KBUserInfo* LuaNewsInfo::release_user_info() {
  // @@protoc_insertion_point(field_release:qqnews.LuaNewsInfo.user_info)
  clear_has_user_info();
  ::qqnews::KBUserInfo* temp = user_info_;
  user_info_ = NULL;
  return temp;
}
inline ::qqnews::KBUserInfo* LuaNewsInfo::mutable_user_info() {
  set_has_user_info();
  if (user_info_ == NULL) {
    auto* p = CreateMaybeMessage<::qqnews::KBUserInfo>(GetArenaNoVirtual());
    user_info_ = p;
  }
  // @@protoc_insertion_point(field_mutable:qqnews.LuaNewsInfo.user_info)
  return user_info_;
}
inline void LuaNewsInfo::set_allocated_user_info(::qqnews::KBUserInfo* user_info) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete reinterpret_cast< ::google::protobuf::MessageLite*>(user_info_);
  }
  if (user_info) {
    ::google::protobuf::Arena* submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      user_info = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, user_info, submessage_arena);
    }
    set_has_user_info();
  } else {
    clear_has_user_info();
  }
  user_info_ = user_info;
  // @@protoc_insertion_point(field_set_allocated:qqnews.LuaNewsInfo.user_info)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace qqnews

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_luacall_2eproto

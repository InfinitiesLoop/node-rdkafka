/*
 * node-rdkafka - Node.js wrapper for RdKafka C/C++ library
 *
 * Copyright (c) 2016 Blizzard Entertainment
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE.txt file for details.
 */

#ifndef SRC_COMMON_H_
#define SRC_COMMON_H_

#include <nan.h>

#include <iostream>
#include <string>
#include <vector>

#include "deps/librdkafka/src-cpp/rdkafkacpp.h"

typedef std::vector<const RdKafka::BrokerMetadata*> BrokerMetadataList;
typedef std::vector<const RdKafka::PartitionMetadata*> PartitionMetadataList;
typedef std::vector<const RdKafka::TopicMetadata *> TopicMetadataList;

namespace NodeKafka {

void Log(std::string);

template<typename T> T GetParameter(v8::Local<v8::Object>, std::string, T);
template<> std::string GetParameter<std::string>(
  v8::Local<v8::Object>, std::string, std::string);
template<> std::vector<std::string> GetParameter<std::vector<std::string> >(
  v8::Local<v8::Object>, std::string, std::vector<std::string>);
// template int GetParameter<int>(v8::Local<v8::Object, std::string, int);
std::vector<std::string> v8ArrayToStringVector(v8::Local<v8::Array>);

class scoped_mutex_lock {
 public:
  explicit scoped_mutex_lock(uv_mutex_t& lock_) :  // NOLINT
    async_lock(lock_) {
      uv_mutex_lock(&async_lock);
  }

  ~scoped_mutex_lock() {
    uv_mutex_unlock(&async_lock);
  }

 private:
  uv_mutex_t &async_lock;
};

namespace TopicPartition {

v8::Local<v8::Array> ToV8Array(std::vector<RdKafka::TopicPartition*>);

}

namespace Metadata {

v8::Local<v8::Object> ToV8Object(RdKafka::Metadata*);

}  // namespace Metadata

}  // namespace NodeKafka

#endif  // SRC_COMMON_H_

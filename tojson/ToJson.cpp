//
// Created by LC on 2022/4/21.
//

#include "ToJson.h"

const ToJsonConf ToJson::defToJsonConf(256U);

ToJsonConf::ToJsonConf(size_t maxStrSize) : maxStrSize(maxStrSize) {}

size_t ToJsonConf::getMaxStrSize() const {
    return maxStrSize;
}

void ToJson::toPb(std::stringstream &ss, const ::google::protobuf::Message &val, const ToJsonConf &conf) {
    auto desc = val.GetDescriptor();
    auto ref = val.GetReflection();

    ss << "{";
    std::string sep;

    const auto sz = desc->field_count();
    for (int i = 0; i < sz; ++i) {
        auto field = desc->field(i);
        if (!ref->HasField(val, field)) {
            continue;
        }

        ss << sep;
        toStream(ss, field->name(), conf);
        ss << ":";
        pbToJson(ss, val, ref, field, conf);
        sep = ",";
    }

    ss << "}";
}

void ToJson::pbToJson(std::stringstream &ss, const google::protobuf::Message &val, const google::protobuf::Reflection *ref, const google::protobuf::FieldDescriptor *field, const ToJsonConf &conf) {
    if (field->is_repeated()) {
        int size = ref->FieldSize(val, field);
        if (size <= 0) {
            ss << "null";
            return;
        }

        ss << "[";
        std::string sep;
        for (int i = 0; i < size; ++i) {
            ss << sep;
            sep = ", ";
            switch (field->cpp_type()) {
                case google::protobuf::FieldDescriptor::CPPTYPE_INT32:
                    toStream(ss, ref->GetRepeatedInt32(val, field, i), conf);
                    break;
                case google::protobuf::FieldDescriptor::CPPTYPE_INT64:
                    toStream(ss, ref->GetRepeatedInt64(val, field, i), conf);
                    break;
                case google::protobuf::FieldDescriptor::CPPTYPE_UINT32:
                    toStream(ss, ref->GetRepeatedUInt32(val, field, i), conf);
                    break;
                case google::protobuf::FieldDescriptor::CPPTYPE_UINT64:
                    toStream(ss, ref->GetRepeatedUInt64(val, field, i), conf);
                    break;
                case google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE:
                    toStream(ss, ref->GetRepeatedDouble(val, field, i), conf);
                    break;
                case google::protobuf::FieldDescriptor::CPPTYPE_FLOAT:
                    toStream(ss, ref->GetRepeatedFloat(val, field, i), conf);
                    break;
                case google::protobuf::FieldDescriptor::CPPTYPE_BOOL:
                    toStream(ss, ref->GetRepeatedBool(val, field, i), conf);
                    break;
                case google::protobuf::FieldDescriptor::CPPTYPE_ENUM:
                    toStream(ss, ref->GetRepeatedEnum(val, field, i)->name(), conf);
                    break;
                case google::protobuf::FieldDescriptor::CPPTYPE_STRING:
                    toStream(ss, ref->GetRepeatedString(val, field, i), conf);
                    break;
                case google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE:
                    toStream(ss, ref->GetRepeatedMessage(val, field, i), conf);
                    break;
            }
        }
        ss << "]";
        return;
    }

    if (!ref->HasField(val, field)) {
        ss << "null";
        return;
    }

    switch (field->cpp_type()) {
        case google::protobuf::FieldDescriptor::CPPTYPE_INT32:
            toStream(ss, ref->GetInt32(val, field), conf);
            break;
        case google::protobuf::FieldDescriptor::CPPTYPE_INT64:
            toStream(ss, ref->GetInt64(val, field), conf);
            break;
        case google::protobuf::FieldDescriptor::CPPTYPE_UINT32:
            toStream(ss, ref->GetUInt32(val, field), conf);
            break;
        case google::protobuf::FieldDescriptor::CPPTYPE_UINT64:
            toStream(ss, ref->GetUInt64(val, field), conf);
            break;
        case google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE:
            toStream(ss, ref->GetDouble(val, field), conf);
            break;
        case google::protobuf::FieldDescriptor::CPPTYPE_FLOAT:
            toStream(ss, ref->GetFloat(val, field), conf);
            break;
        case google::protobuf::FieldDescriptor::CPPTYPE_BOOL:
            toStream(ss, ref->GetBool(val, field), conf);
            break;
        case google::protobuf::FieldDescriptor::CPPTYPE_ENUM:
            toStream(ss, ref->GetEnum(val, field)->name(), conf);
            break;
        case google::protobuf::FieldDescriptor::CPPTYPE_STRING:
            toStream(ss, ref->GetString(val, field), conf);
            break;
        case google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE:
            toStream(ss, ref->GetMessage(val, field), conf);
            break;
        default:
            ss << "null";
            break;
    }
}


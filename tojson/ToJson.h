//
// Created by LC on 2022/4/21.
//

#ifndef ONEPUNCHMAN_TOJSON_H
#define ONEPUNCHMAN_TOJSON_H

#include <string>
#include <sstream>
#include <map>
#include <vector>
#include "message.h"

class ToJsonConf {
private:
    size_t maxStrSize{0U};
public:
    ToJsonConf() = default;

    explicit ToJsonConf(size_t maxStrSize);

    size_t getMaxStrSize() const;
};

class ToJson {
    static const ToJsonConf defToJsonConf;

public:
    template<class T>
    static std::string format(const T &val, const ToJsonConf &conf = defToJsonConf) {
        std::stringstream ss;
        toStream(ss, val, conf);
        return ss.str();
    }

private:
    template<class T>
    static std::stringstream &toStream(std::stringstream &ss, const T &val, const ToJsonConf &conf) {
        return TypeDispatcher<T>::tos(ss, val, conf);
    }

    template<class T>
    class TypeDispatcher {
    public:
        static std::stringstream &tos(std::stringstream &ss, const T &val, const ToJsonConf &conf) {
            return ToCustom<T,
                    std::is_base_of<::google::protobuf::Message, T>::value,
                    std::is_fundamental<T>::value || std::is_enum<T>::value>
            ::tos(ss, val, conf);
        }
    };

    template<class CharT, class Traits, class Allocator>
    class TypeDispatcher<std::basic_string<CharT, Traits, Allocator>> {
    public:
        static std::stringstream &tos(std::stringstream &ss, const std::basic_string<CharT, Traits, Allocator> &val, const ToJsonConf &conf) {
            ss << "'" << ((conf.getMaxStrSize() > 0U && val.size() > conf.getMaxStrSize()) ? val.substr(0U, conf.getMaxStrSize()) : val) << "'";
            return ss;
        }
    };

    template<class Key, class Tp, class Compare, class Allocator>
    class TypeDispatcher<std::map<Key, Tp, Compare, Allocator>> {
    public:
        static std::stringstream &tos(std::stringstream &ss, const std::map<Key, Tp, Compare, Allocator> &val, const ToJsonConf &conf) {
            std::string sep;
            ss << "{";
            for (const auto &item: val) {
                ss << sep << toStream<Key>(ss, item.first, conf) << ss << ":" << toStream<Tp>(ss, item.second, conf);
                sep = ",";
            }
            ss << "}";
            return ss;
        }
    };

    template<class T1, class T2>
    class TypeDispatcher<std::pair<T1, T2>> {
    public:
        static std::stringstream &tos(std::stringstream &ss, const std::pair<T1, T2> &val, const ToJsonConf &conf) {
            ss << "{" << toStream<T1>(ss, val.first, conf) << ":" << toStream<T2>(ss, val.second, conf) << "}";
            return ss;
        }
    };

    template<class Tp, class Allocator>
    class TypeDispatcher<std::vector<Tp, Allocator>> {
    public:
        static std::stringstream &tos(std::stringstream &ss, const std::vector<Tp, Allocator> &val, const ToJsonConf &conf) {
            std::string sep;
            ss << "[";
            for (const auto &item: val) {
                ss << sep << tojson(item, conf);
                sep = ",";
            }
            ss << "]";
            return ss;
        }
    };

    template<class T, bool IS_MESSAGE, bool IS_FUNDAMENTAL>
    class ToCustom;

    template<class T, bool IS_FUNDAMENTAL>
    class ToCustom<T, true, IS_FUNDAMENTAL> {
    public:
        static std::stringstream &tos(std::stringstream &ss, const T &val, const ToJsonConf &conf) {
            toPb(ss, val, conf);
            return ss;
        }
    };

    template<class T>
    class ToCustom<T, false, true> {
    public:
        static std::stringstream &tos(std::stringstream &ss, const T &val, const ToJsonConf &conf) {
            ss << val;
            return ss;
        }
    };

private:
    static void toPb(std::stringstream &ss, const ::google::protobuf::Message &val, const ToJsonConf &conf);

    static void pbToJson(std::stringstream &ss, const ::google::protobuf::Message &val, const google::protobuf::Reflection *ref, const google::protobuf::FieldDescriptor *field, const ToJsonConf &conf);
};


#endif //ONEPUNCHMAN_TOJSON_H

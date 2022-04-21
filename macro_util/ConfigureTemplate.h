//
// Created by LC on 2021/12/2.
//

#ifndef ONEPUNCHMAN_CONFIGURETEMPLATE_H
#define ONEPUNCHMAN_CONFIGURETEMPLATE_H

#include <map>
#include <iostream>
#include "macro_util.h"

#define CONFIGURE_MEMBERS(sep, a, b, c) a _##b {c};
#define CONFIGURE_REF(sep, a, b, c) a & b##Ref() { return this->_##b; }
#define CONFIGURE_GETTER(sep, a, b, c) const a & b() const { return this->_##b; }
#define CONFIGURE_SETTER(sep, a, b, c) void b(a&& val)  { this->_##b = val; }
#define CONFIGURE_TOSTRINGS(sep, a, b, c) << #b":" << this->_##b << sep
#define CONFIGURE_SETVALS(sep, a, b, c) if (key == #b) { this->str2##b(val); return; }
#define CONFIGURE_SET_STR(sep, a, b, c) void str2##b(const string &val) { if (!val.empty()) { this->_##b = Common::strto<a>(val); }}

#define CONFIGURE_TEMPLATE(args...) public: \
REPEAT(CONFIGURE_REF,,##args)               \
REPEAT(CONFIGURE_GETTER,,##args)            \
REPEAT(CONFIGURE_SETTER,,##args)            \
REPEAT(CONFIGURE_SET_STR,,##args)           \
string toString() const {                   \
stringstream ss;                            \
ss << "{"                                   \
REPEAT(CONFIGURE_TOSTRINGS, ",", ##args)    \
"}";                                        \
return ss.str();                            \
}                                           \
void setVal(const string &key, const string &val) { \
REPEAT(CONFIGURE_SETVALS, else if, ##args)  \
}                                           \
void onTblUpdate();                         \
private:                                    \
REPEAT(CONFIGURE_MEMBERS, "", ##args)

template<class U, class V>
class MapType {
public:
    typedef std::map<U, V> type;

    std::ostream &toStream(std::ostream &os) const {
        return os;
    }

    const type &map() const { return _map; }

    type &map() { return _map; }

private:
    type _map;
};

template<class U, class V>
std::ostream &operator<<(std::ostream &os, const MapType<U, V> &m) {
    if (!os.good()) { return os; }
    return m.toStream(os);
}

template<class V>
class MapTypeInt : public MapType<int, V> {
public:

};

#endif //ONEPUNCHMAN_CONFIGURETEMPLATE_H

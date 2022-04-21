//
// Created by LC on 2022/4/18.
// 安全的uint计算辅助类
//

#ifndef ONEPUNCHMAN_SAFEUINT_H
#define ONEPUNCHMAN_SAFEUINT_H

#include "TypeDef.h"

/**
 * 调试日志
 */
class SafeUIntLogger {
public:
    static void log(const char *func, uint64_t a, uint64_t b, uint64_t result, uint64_t operatorResult);
};

/**
 * 安全加减法实现
 */
class SafeUIntFunction {
public:
    /**
     * safe return (a + b)
     * @param a
     * @param b
     * @param max
     * @return [a, max]
     */
    template<class Unsigned, class LOGGER>
    static Unsigned addU(Unsigned a, Unsigned b, Unsigned max, bool debug) {
        Unsigned result;
        if (a >= max || b >= max) {
            result = max;
        } else {
            result = a >= max - b ? max : a + b;
        }

        if (debug) {
            LOGGER::log("add", a, b, result, a + b);
        }

        return result;
    }

    /**
     * safe return (a - b)
     * @param a
     * @param b
     * @param min
     * @return [min, a]
     */
    template<class Unsigned, class LOGGER>
    static Unsigned subU(Unsigned a, Unsigned b, Unsigned min, bool debug) {
        Unsigned result;
        if (a <= min) {
            result = min;
        } else {
            result = max(min, a > b ? a - b : 0U);
        }

        if (debug) {
            LOGGER::log("sub", a, b, result, a - b);
        }

        return result;
    }
};

/**
 * 编译期错误提示
 * @tparam EXPR
 * @tparam TYPE
 */
template<bool EXPR, int TYPE>
class SafeUIntError;

template<int TYPE>
class SafeUIntError<true, TYPE> {

};

/**
 * SafeUInt 类型匹配失败
 * @tparam A
 * @tparam B
 * @tparam MAX_VAL
 * @tparam MIN_VAL
 * @tparam DEBUG
 * @tparam LOGGER
 * @tparam MATCH
 * @tparam TYPE
 */
template<class A, class B, A MAX_VAL, A MIN_VAL, bool DEBUG, class LOGGER, bool MATCH, int TYPE>
class SafeUInt {
private:
    SafeUIntError<MATCH, TYPE> Type_Not_Match;
};

/**
 * SafeUInt 匹配(unsigned + signed)
 * @tparam A
 * @tparam B
 * @tparam MAX_VAL
 * @tparam MIN_VAL
 * @tparam DEBUG
 * @tparam LOGGER
 * @tparam TYPE
 */
template<class A, class B, A MAX_VAL, A MIN_VAL, bool DEBUG, class LOGGER, int TYPE>
class SafeUInt<A, B, MAX_VAL, MIN_VAL, DEBUG, LOGGER, true, TYPE> {
private:
    const A a;
    const B b;

public:
    explicit SafeUInt(A a, B b) : a(a), b(b) {}

    /**
     * safe return (a + b)
     * @param a
     * @param b
     * @param max
     * @param min
     * @return [min, max]
     */
    A addOrSub(A max = MAX_VAL, A min = MIN_VAL, bool debug = DEBUG) const {
        if (this->b < 0) {
            return SafeUIntFunction::subU<A, LOGGER>(this->a, -this->b, min, debug);
        }

        return SafeUIntFunction::addU<A, LOGGER>(a, b, max, debug);
    }
};

/**
 * SafeUInt 匹配(unsigned +/- unsigned)
 * @tparam A
 * @tparam MAX_VAL
 * @tparam MIN_VAL
 * @tparam DEBUG
 * @tparam LOGGER
 * @tparam TYPE
 */
template<class A, A MAX_VAL, A MIN_VAL, bool DEBUG, class LOGGER, int TYPE>
class SafeUInt<A, A, MAX_VAL, MIN_VAL, DEBUG, LOGGER, true, TYPE> {
private:
    const A a;
    const A b;

public:
    explicit SafeUInt(A a, A b) : a(a), b(b) {}

    /**
   * safe return (a + b)
   * @param a
   * @param b
   * @param max
   * @return [a, max]
   */
    A add(A max = MAX_VAL, bool debug = DEBUG) const {
        return SafeUIntFunction::addU<A, LOGGER>(a, b, max, debug);
    }

    /**
     * safe return (a - b)
     * @param a
     * @param b
     * @param min
     * @return [min, a]
     */
    A sub(A min = MIN_VAL, bool debug = DEBUG) const {
        return SafeUIntFunction::subU<A, LOGGER>(a, b, min, debug);
    }
};

/**
 * 参数匹配器
 * @tparam A
 * @tparam B
 */
template<class A, class B>
class SafeUIntTypeChecker {
public:
    static constexpr int type = -1;
};

template<>
class SafeUIntTypeChecker<uint32_t, uint32_t> {
public:
    static constexpr int type = 32;
};

template<>
class SafeUIntTypeChecker<uint32_t, int32_t> {
public:
    static constexpr int type = 32;
};

template<>
class SafeUIntTypeChecker<uint64_t, uint64_t> {
public:
    static constexpr int type = 64;
};

template<>
class SafeUIntTypeChecker<uint64_t, int64_t> {
public:
    static constexpr int type = 64;
};

/**
 * 构造器封装
 */
class SafeUIntHelper {
private:
    template<class A, class B, A MAX_VAL, A MIN_VAL, bool DEBUG, class LOGGER = SafeUIntLogger>
    class TypeGetter {
    public:
        typedef SafeUInt<A, B, MAX_VAL, MIN_VAL, DEBUG, LOGGER, SafeUIntTypeChecker<A, B>::type == 32, 32> type32;
        typedef SafeUInt<A, B, MAX_VAL, MIN_VAL, DEBUG, LOGGER, SafeUIntTypeChecker<A, B>::type == 64, 64> type64;
    };

public:
    template<class A, class B, A MAX_VAL, A MIN_VAL = 0U, bool DEBUG = true, class LOGGER = SafeUIntLogger>
    static typename TypeGetter<A, B, MAX_VAL, MIN_VAL, DEBUG, LOGGER>::type32 create32(A a, B b) {
        return typename TypeGetter<A, B, MAX_VAL, MIN_VAL, DEBUG, LOGGER>::type32(a, b);
    }

    template<class A, class B, A MAX_VAL, A MIN_VAL = 0U, bool DEBUG = true, class LOGGER = SafeUIntLogger>
    static typename TypeGetter<A, B, MAX_VAL, MIN_VAL, DEBUG, LOGGER>::type64 create64(A a, B b) {
        return typename TypeGetter<A, B, MAX_VAL, MIN_VAL, DEBUG, LOGGER>::type64(a, b);
    }
};

#endif //ONEPUNCHMAN_SAFEUINT_H

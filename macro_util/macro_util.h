//
// Created by LC on 2021/12/2.
//

#ifndef ONEPUNCHMAN_MACRO_UTIL_H
#define ONEPUNCHMAN_MACRO_UTIL_H

// 输出宏展开结果
#define MACRO_TOSTR(...) #__VA_ARGS__
#define MACRO_PRINT(...) MACRO_TOSTR(#__VA_ARGS__) " = " MACRO_TOSTR(__VA_ARGS__)
#define MACRO_STREAM(...) MACRO_TOSTR(#__VA_ARGS__) << ":" << MACRO_TOSTR(__VA_ARGS__)

// 参数个数
#define MACRO_SELECT_NUM(_87, _86, _85, _84, _83, _82, _81, _80, _79, _78, _77, _76, _75, _74, _73, _72, _71, _70, _69, _68, _67, _66, _65, _64, _63, _62, _61, _60, _59, _58, _57, _56, _55, _54, _53, _52, _51, _50, _49, _48, _47, _46, _45, _44, _43, _42, _41, _40, _39, _38, _37, _36, _35, _34, _33, _32, _31, _30, _29, _28, _27, _26, _25, _24, _23, _22, _21, _20, _19, _18, _17, _16, _15, _14, _13, _12, _11, _10, _9, _8, _7, _6, _5, _4, _3, _2, _1, num, args...) num
#define MACRO_ARGS_NUM(args...) MACRO_SELECT_NUM(args,\
29,29,29,                                             \
28,28,28,                                             \
27,27,27,                                             \
26,26,26,                                             \
25,25,25,                                             \
24,24,24,                                             \
23,23,23,                                             \
22,22,22,                                             \
21,21,21,                                             \
20,20,20,                                             \
19,19,19,                                             \
18,18,18,                                             \
17,17,17,                                             \
16,16,16,                                             \
15,15,15,                                             \
14,14,14,                                             \
13,13,13,                                             \
12,12,12,                                             \
11,11,11,                                             \
10,10,10,                                             \
9,9,9,                                                \
8,8,8,                                                \
7,7,7,                                                \
6,6,6,                                                \
5,5,5,                                                \
4,4,4,                                                \
3,3,3,                                                \
2,2,2,                                                \
1,1,1,                                                \
0,0,0                                                 \
)

// 3元扩展
#define MACRO_EXPAND3(macro, sep, a, b, c) macro(sep, a,b,c)
#define REPEAT(macro, sep, args ...) MACRO_REPEATx(MACRO_ARGS_NUM(args), macro, sep, ##args)
#define MACRO_REPEATx(n, args ...) MACRO_REPEATn(n, ##args)
#define MACRO_REPEATn(n, args ...) MACRO_REPEAT##n(args)
#define MACRO_REPEAT1(macro, sep, a, b, c, args ...) MACRO_EXPAND3(macro,,a,b,c)
#define MACRO_REPEAT2(macro, sep, a, b, c, args ...) MACRO_EXPAND3(macro,sep,a,b,c) MACRO_REPEAT1(macro, sep, ##args)
#define MACRO_REPEAT3(macro, sep, a, b, c, args ...) MACRO_EXPAND3(macro,sep,a,b,c) MACRO_REPEAT2(macro, sep, ##args)
#define MACRO_REPEAT4(macro, sep, a, b, c, args ...) MACRO_EXPAND3(macro,sep,a,b,c) MACRO_REPEAT3(macro, sep, ##args)
#define MACRO_REPEAT5(macro, sep, a, b, c, args ...) MACRO_EXPAND3(macro,sep,a,b,c) MACRO_REPEAT4(macro, sep, ##args)
#define MACRO_REPEAT6(macro, sep, a, b, c, args ...) MACRO_EXPAND3(macro,sep,a,b,c) MACRO_REPEAT5(macro, sep, ##args)
#define MACRO_REPEAT7(macro, sep, a, b, c, args ...) MACRO_EXPAND3(macro,sep,a,b,c) MACRO_REPEAT6(macro, sep, ##args)
#define MACRO_REPEAT8(macro, sep, a, b, c, args ...) MACRO_EXPAND3(macro,sep,a,b,c) MACRO_REPEAT7(macro, sep, ##args)
#define MACRO_REPEAT9(macro, sep, a, b, c, args ...) MACRO_EXPAND3(macro,sep,a,b,c) MACRO_REPEAT8(macro, sep, ##args)


#endif //ONEPUNCHMAN_MACRO_UTIL_H

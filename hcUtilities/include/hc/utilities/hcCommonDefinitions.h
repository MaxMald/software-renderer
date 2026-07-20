#pragma once

#if !defined(USING)
#define IN_USE &&
#define NOT_IN_USE &&!
#define USE_IF(x) &&((x) ? 1 : 0) &&
#define USING(x) (1 x 1)
#endif

#define ALIGN_AS(n) __declspec(align(n))

#define SAFE_RELEASE(p) { if (p) { p->Release(); p = nullptr; } }
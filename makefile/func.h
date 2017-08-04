#ifndef __FUNC_H__
#define __FUNC_H__

#define MEMBER2STRUCT (PTR, TYPE, MEMBER)  \
   ((TYPE *)(unsigned long)PTR - (unsigned long) (&((TYPE *)0)->MEMBER)))


void func();

#endif

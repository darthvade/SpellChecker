/**
 *	不可复制基类
 * 	注：任何继承它的子类都不可被复制
 */

#ifndef __NONCOPYABLE_H__
#define __NONCOPYABLE_H__

/*
 *
 */

class Noncopyable {
protected:
	Noncopyable() {};
	~Noncopyable() {};
private:
	Noncopyable(const Noncopyable&);
	Noncopyable& operator=(const Noncopyable&);
};

#endif

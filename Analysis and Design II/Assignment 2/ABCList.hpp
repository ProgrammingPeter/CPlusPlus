#ifndef _BRIZAN_ABCLIST_H_
#define _BRIZAN_ABCLIST_H_



template <class T>
class ABCList {
public:
	virtual bool isEmpty () = 0;
	virtual int  getLength () = 0;
	virtual void insert (int pos, T item) = 0;
	virtual T    remove (int pos) = 0;
	virtual T    retrieve (int pos) = 0;
};

#endif

#ifndef MEMORY_H
#define MEMORY_H

#include <QList>
#include <QObject>

class Memory
{
public:
    Memory() { }
    int addVal(QObject *val)
    {
        if (val)
        {
            _store.append(val);
            _size++;
            return _size - 1;
        }

        return -1;
    }

    void assign(int dir, QObject *val)
    {
        if (0 <= dir && dir < _size)
            _store[dir] = val;
    }

    QObject* getVal(int dir)
    {
        if (0 <= dir && dir < _size)
            return _store[dir];

        return new QObject();
    }

    int getSize() {  return _size;  }

protected:
    int _size;
    QList<QObject*> _store;
};

#endif // MEMORY_H

#ifndef DATA_H
#define DATA_H
#include <QList>
class Data
{
  public:
    Data( QString r , QList<Data * > * h)
    {
      root = r;
      hijos = h;
    }
    inline QString getRoot(){return root;}
    inline void setRoot(QString r){root = r;}
    inline QList<Data * > *  getHijos(){return hijos;}
    inline void setHijos(QList<Data * > * h){ hijos = h;}
    inline bool Eshoja(){return hijos->size()== 0 ;}
    inline int canthijos(){ return hijos->size();}
  private :
    QList<Data * > * hijos;
    QString root;

};

#endif // DATA_H

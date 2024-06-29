
#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include <QList>

template <class TypeKey, class TypeValue>
class DictionaryEntry;

template <class TypeKey, class TypeValue>
class Dictionary
{
    protected:
        QList<DictionaryEntry<TypeKey, TypeValue>*> *valList;

        int FindKey(TypeKey key);
        int FindValue(TypeValue value);

    public:
        Dictionary();
        int AddEntry(TypeKey key, TypeValue value);
        bool TryGetValue( TypeKey key, TypeValue &value );
        ~Dictionary();
};


template <class TypeKey, class TypeValue>
class DictionaryEntry
{
    protected:
        TypeKey key;
        TypeValue value;
    public:
        DictionaryEntry(TypeKey key, TypeValue value)
        {
            this->key = key;
            this->value = value;
        }

        TypeKey GetKey()
        {
            return key;
        }

        TypeValue GetValue()
        {
            return value;
        }
};


template <class TypeKey, class TypeValue>
int Dictionary<TypeKey, TypeValue>::FindKey(TypeKey key)
{
    int i = 0;
    int l_List = valList->size();
    while( i < l_List && key  != valList->value(i)->GetKey() )
    {
         i++;
    }
    if( i != l_List )
      return i;
    return -1;
}

template <class TypeKey, class TypeValue>
int Dictionary<TypeKey, TypeValue>::FindValue(TypeValue value)
{
    int i = 0;
    int l_List = valList->size();
    while( i < l_List && value  != valList->value(i)->GetValue() )
    {
         i++;
    }
    if( i != l_List )
      return i;
    return -1;
}

template <class TypeKey, class TypeValue>
Dictionary<TypeKey, TypeValue>::Dictionary()
{
    valList = new QList<DictionaryEntry<TypeKey, TypeValue>*>();
}

template <class TypeKey, class TypeValue>
int Dictionary<TypeKey, TypeValue>::AddEntry(TypeKey key, TypeValue value)
{
    DictionaryEntry<TypeKey, TypeValue> *entry = new DictionaryEntry<TypeKey, TypeValue>(key, value);
    if( FindKey(key) == -1 )
        valList->append(entry);
    return valList->size() - 1;
}

template <class TypeKey, class TypeValue>
bool Dictionary<TypeKey, TypeValue>::TryGetValue( TypeKey key, TypeValue &value)
{
   int posKey = FindKey(key);
   if(posKey != -1)
   {
     value = valList->value(posKey)->GetValue();
     return true;
   }
   return false;
}

template <class TypeKey, class TypeValue>
Dictionary<TypeKey, TypeValue>::~Dictionary()
{
    delete valList;
}

#endif /* DICTIONARY_H_ */

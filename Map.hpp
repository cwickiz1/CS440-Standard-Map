#ifndef CWICKIZ_MAP_HPP
#define CWICKIZ_MAP_HPP

#include <utility>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace cs540 {
  template<typename Key_T, typename Mapped_T>
  class Map{
    public:
  //Constructors and Assignment Operator
      typedef std::pair<const Key_T, Mapped_T> ValueType;

      //Change node to deal with vector
      class Node{
        public:
          std::vector<Node*> forward_links;
          Node* prev;
          Node(size_t lev){
            for(size_t i = 0; i<=lev;i++){
              forward_links.push_back(NULL);
            }
            prev = NULL;
          };
          //virtual ~Node(){};
      };

      class DataNode: public Node{
        public:
          ValueType value;
          DataNode(size_t level, const ValueType& data) : Node(level), value(data){};
          //virtual ~DataNode(){};
      };

      class Iterator{
        public:
          Node* current;
          //Node* current const{return current;}
          Iterator(Node* n) : current(n) {};
          Iterator(const Iterator & iter) : current(iter.current) {};	//Your class must have a copy constructor, but you do not need to define this if the implicit one works for your implementation. (Which is what I expect in most cases.)
          ~Iterator(){};	//Destructor (implicit definition is likely good enough).
          Iterator& operator=(const Iterator & iter){
            current = iter.current;
            return *this;
          };	//Your class must have an assignment operator, but you do not need to define this if the implicit one works for your implementation. (Which is what I expect in most cases.)
          Iterator &operator++(){
            current = current->forward_links[0];
            return *this;
          };	//Increments the iterator one element, and returns a reference to the incremented iterator (preincrement). If the iterator is pointing to the end of the list, the behavior is undefined.
          Iterator operator++(int){
            Map<Key_T, Mapped_T>::Iterator temp = *this;
            current = current->forward_links[0];
            return temp;
          };	//Increments the iterator one element, and returns an iterator pointing to the element prior to incrementing the iterator (postincrement). If the iterator is pointing to the end of the list, the behavior is undefined.
          Iterator &operator--(){
            current = current->prev;
            return *this;
          };	//Decrements the iterator one element, and returns a reference to the decremented iterator (predecrement). If the iterator is pointing to the beginning of the list, the behavior is undefined. If the iterator has the special value returned by the end() function, then the iterator must point to the last element after this function.
          Iterator operator--(int){
            Map<Key_T, Mapped_T>::Iterator temp = *this;
            current = current->prev;
            return temp;
          };	//Decrements the iterator one element, and returns an iterator pointing to the element prior to decrementing (postdecrement). If the iterator is pointing to the beginning of the list, the behavior is undefined. If the iterator has the special value returned by the end() function, then the iterator must point to the last element after this function.
          ValueType &operator*() const {
            return static_cast<DataNode *>(current)->value;
          };	//Returns a reference to the ValueType object contained in this element of the list. If the iterator is pointing to the end of the list, the behavior is undefined. This can be used to change the Mapped_T member of the element.
          ValueType *operator->() const {
            return &static_cast<DataNode *>(current)->value;
          };	//Special member access operator for the element. If the iterator is pointing to the end of the list, the behavior is undefined. This can be used to change the Mapped_T member of the element.
      };
      class ConstIterator{
        public:
          Node* current;
          //Node* current {return current;}
          ConstIterator(Node* n) : current(n) {};
          ConstIterator(const ConstIterator & citer) : current(citer.current){};	//Your class must have a copy constructor, but you do not need to define this if the implicit one works for your implementation. (Which is what I expect in most cases.)
          ConstIterator(const Iterator & iter) : current(iter.current){};	//This is a conversion operator.
          ~ConstIterator(){};	//Destructor (implicit definition is likely good enough).
          ConstIterator& operator=(const ConstIterator & iter){
            current = iter.current;
            return *this;
          };	//Your class must have an assignment operator, but you do not need to define this if the implicit one works for your implementation. (Which is what I expect in most cases.)
          ConstIterator &operator++(){
            current = current->forward_links[0];
            return *this;
          };	//Increments the iterator one element, and returns a reference to the incremented iterator (preincrement). If the iterator is pointing to the end of the list, the behavior is undefined.
          ConstIterator operator++(int){
            Map<Key_T, Mapped_T>::ConstIterator temp = *this;
            current = current->forward_links[0];
            return temp;
          };	//Increments the iterator one element, and returns an iterator pointing to the element prior to incrementing the iterator (postincrement). If the iterator is pointing to the end of the list, the behavior is undefined.
          ConstIterator &operator--(){
            current = current->prev;
            return *this;
          };	//Decrements the iterator one element, and returns a reference to the decremented iterator (predecrement). If the iterator is pointing to the beginning of the list, the behavior is undefined. if the iterator has the special value returned by the end() function, then the iterator must point to the last element after this function.
          ConstIterator operator--(int){
            Map<Key_T, Mapped_T>::ConstIterator temp = *this;
            current = current->prev;
            return temp;
          };	//Decrements the iterator one element, and returns an iterator pointing to the element prior to decrementing (postdecrement). If the iterator is pointing to the beginning of the list, the behavior is undefined. if the iterator has the special value returned by the end() function, then the iterator must point to the last element after this function.
          const ValueType &operator*() const{
            return static_cast<DataNode *>(current)->value;
          };	//Returns a reference to the current element of the iterator. If the iterator is pointing to the end of the list, the behavior is undefined.
          const ValueType *operator->() const{
            return &static_cast<DataNode *>(current)->value;
          };	//Special member access operator for the element. If the iterator is pointing to the end of the list, the behavior is undefined.
      };
      class ReverseIterator{
        public:
          Node* current;
          //Node* current const{return current;}
          ReverseIterator(Node* n) : current(n) {};
          ReverseIterator(const ReverseIterator & riter): current(riter.current){};	//Your class must have a copy constructor, but you do not need to define this if the implicit one works for your implementation. (Which is what I expect in most cases.)
          ~ReverseIterator(){};	//Destructor (implicit definition is likely good enough).
          ReverseIterator& operator=(const ReverseIterator & riter){
            current = riter.current;
            return *this;
          }	//Your class must have an assignment operator, but you do not need to define this if the implicit one works for your implementation. (Which is what I expect in most cases.)
          ReverseIterator &operator++(){
            current = current->prev;
            return *this;
          }	//Increments the iterator one element, and returns a reference to the incremented iterator (preincrement). If the iterator is pointing to the end of the list, the behavior is undefined.
          ReverseIterator operator++(int){
            Map<Key_T, Mapped_T>::ReverseIterator temp = *this;
            current = current->prev;
            return temp;
          }	//Increments the iterator one element, and returns an iterator pointing to the element prior to incrementing the iterator (postincrement). If the iterator is pointing to the end of the list, the behavior is undefined.
          ReverseIterator &operator--(){
            current = current->forward_links[0];
            return *this;
          }	//Decrements the iterator one element, and returns a reference to the decremented iterator (predecrement). If the iterator is pointing to the beginning of the list, the behavior is undefined. If the iterator has the special value returned by the end() function, then the iterator must point to the last element after this function.
          ReverseIterator operator--(int){
            Map<Key_T, Mapped_T>::ReverseIterator temp = *this;
            current = current->forward_links[0];
            return temp;
          }	//Decrements the iterator one element, and returns an iterator pointing to the element prior to decrementing (postdecrement). If the iterator is pointing to the beginning of the list, the behavior is undefined. If the iterator has the special value returned by the end() function, then the iterator must point to the last element after this function.
          ValueType &operator*() const{
            return static_cast<DataNode *>(current)->value;
          };	//Returns a reference to the ValueType object contained in this element of the list. If the iterator is pointing to the end of the list, the behavior is undefined. This can be used to change the Mapped_T member of the element.
          ValueType *operator->() const{
            return &static_cast<DataNode *>(current)->value;
          };	//Special member access operator for the element. If the iterator is pointing to the end of the list, the behavior is undefined. This can be used to change the Mapped_T member of the element.
      };
      Map(){
        map_default();
      };	//This constructor creates an empty map.
      Map(const Map & cmap){
        map_default();
        Node* temp = cmap.sentinel->prev;
        while(temp != cmap.sentinel){
          insert(static_cast<DataNode*>(temp)->value);
          temp = temp->prev;
        }
      }	//Copy constructor. Must have O(N) performance, where N is the number of elements.
      Map &operator=(const Map & cmap){
        if(this == &cmap){
          return *this;
        }
        //Delete old map
        Node *temp_head = sentinel->forward_links[0];
        Node *temp;
        while(temp_head != sentinel){
          temp = temp_head->forward_links[0];
          delete temp_head;
          temp_head = temp;
        }
        delete sentinel;
        //Default
        map_default();
        //Assign
        temp = cmap.sentinel->prev;
        while(temp != cmap.sentinel){
          insert(static_cast<DataNode*>(temp)->value);
          temp = temp->prev;
        }
        return *this;
      }	//Copy assignment operator. Value semantics must be used. You must be able to handle self-assignment. Must have O(N) performance, where N is the number of elements.
      Map(std::initializer_list<std::pair<const Key_T, Mapped_T>> list){
        map_default();
        for(auto it = list.begin(); it != list.end();++it){
          insert(*it);
        }
      }	//Initializer list constructor. Support for creation of Map with initial values, such as Map<string,int> m{{"key1", 1}, {"key2", 2}};.
      ~Map(){
  				Node *temp_head = sentinel->forward_links[0];
  				Node *temp;
  				while(temp_head != sentinel){
  					temp = temp_head->forward_links[0];
  					delete temp_head;
  					temp_head = temp;
          }
          delete sentinel;
  		};	//Destructor, release any acquired resources.
  //Size
      size_t size() const {return _size;};	//Returns the number of elements in the map.
      bool empty() const {return _size==0;};	//Returns true if the Map has no entries in it, false otherwise.
  //Iterators
      Iterator begin(){
        return Map<Key_T, Mapped_T>::Iterator(sentinel->forward_links[0]);
      };	//Returns an Iterator pointing to the first element, in order.
      Iterator end(){
        return Map<Key_T, Mapped_T>::Iterator(sentinel);
      };	//Returns an Iterator pointing one past the last element, in order.
      ConstIterator begin() const{
        return Map<Key_T, Mapped_T>::ConstIterator(sentinel->forward_links[0]);
      };	//Returns a ConstIterator pointing to the first element, in order.
      ConstIterator end() const{
        return Map<Key_T, Mapped_T>::ConstIterator(sentinel);
      };	//Returns a ConstIterator pointing one past the last element, in order.
      ReverseIterator rbegin(){
        return Map<Key_T, Mapped_T>::ReverseIterator(sentinel->prev);
      };	//Returns an ReverseIterator to the first element in reverse order, which is the last element in normal order.
      ReverseIterator rend(){
        return Map<Key_T, Mapped_T>::ReverseIterator(sentinel);
      };  //Returns an ReverseIterator pointing to one past the last element in reverse order, which is one before the first element in normal order.

      friend bool operator==(const Iterator& iter1, const Iterator& iter2){
  			return (iter1.current == iter2.current)? true : false;
  		}

      friend bool operator==(const ConstIterator & iter1, const ConstIterator & iter2){
        return (iter1.current == iter2.current)? true : false;
      }

      friend bool operator==(const Iterator & iter1, const ConstIterator & iter2){
        return (iter1.current == iter2.current)? true : false;
      }

      friend bool operator==(const ConstIterator & iter1, const Iterator & iter2){
        return (iter1.current == iter2.current)? true : false;
      }

      friend bool operator==(const ReverseIterator& iter1, const ReverseIterator& iter2){
  			return (iter1.current == iter2.current)? true : false;
  		}

  		friend bool operator!=(const Iterator& iter1, const Iterator& iter2){
  			return (iter1.current != iter2.current)? true : false;
  		}

      friend bool operator!=(const ConstIterator & iter1, const ConstIterator & iter2){
        return (iter1.current != iter2.current)? true : false;
      }

      friend bool operator!=(const Iterator & iter1, const ConstIterator & iter2){
        return (iter1.current != iter2.current)? true : false;
      }

      friend bool operator!=(const ConstIterator & iter1, const Iterator & iter2){
        return (iter1.current != iter2.current)? true : false;
      }

  		friend bool operator!=(const ReverseIterator& iter1, const ReverseIterator& iter2){
  			return (iter1.current != iter2.current)? true : false;
  		}

  //Element Access
      Iterator find(const Key_T &);
      ConstIterator find(const Key_T &) const;	//Returns an iterator to the given key. If the key is not found, these functions return the end() iterator.
      Mapped_T& at(const Key_T &);	//Returns a reference to the mapped object at the specified key. If the key is not in the Map, throws std::out_of_range.
      const Mapped_T &at(const Key_T &) const;	//Returns a const reference to the mapped object at the specified key. If the key is not in the map, throws std::out_of_range.
      Mapped_T& operator[](const Key_T &);	//If key is in the map, return a reference to the corresponding mapped object. If it is not, value initialize a mapped object for that key and returns a reference to it (after insert). This operator may not be used for a Mapped_T class type that does not support default construction.
    //Modifiers
      std::pair<Iterator, bool> insert(const ValueType &);
      template <typename IT_T>
      void insert(IT_T range_beg, IT_T range_end){
        for(auto it = range_beg; it < range_end; ++it){
          insert(*it);
        }
      }

  //The first version inserts the given pair into the map.
  //If the key does not already exist in the map, it returns an iterator pointing to the new element, and true.
  //If the key already exists, no insertion is performed nor is the mapped object changed, and it returns an iterator pointing to the element with the same key, and false.

  //The second version inserts the given object or range of objects into the map.
  //In the second version, the range of objects inserted includes the object range_beg points to, but not the object that range_end points to.
  //In other words, the range is half-open. The iterator returned in the first version points to the newly inserted element.
  //There must be only one constructor invocation per object inserted. Note that the range may be in a different container type, as long as the iterator is compatible.
  //A compatible iterator would be one from which a ValueType can be constructed. For example, it might be from a std::vector<std::pair<Key_T, Mapped_T>>.
  //There might be any number of compatible iterator types, therefore, the range insert is a member template.

      void erase(Iterator pos);
      void erase(const Key_T &);	//Removes the given object from the map. The object may be indicated by iterator, or by key. If given by key, throws std::out_of_range if the key is not in the Map
      void clear(){
        Node *temp_head = sentinel->forward_links[0];
        Node *temp;
        while(temp_head != sentinel){
          temp = temp_head->forward_links[0];
          delete temp_head;
          temp_head = temp;
        }
        delete sentinel;
        map_default();
      }	//Removes all elements from the map.
  //Comparison
      friend bool operator==(const Map<Key_T,Mapped_T> & map1, const Map<Key_T,Mapped_T> & map2){
        if(map1.size()!=map2.size()) return false;
        ConstIterator it1 = map1.begin();
        for(ConstIterator it2 = map2.begin(); it2 != map2.end(); it2++){
          if(*it1!=*it2){
            return false;
          }
          it1++;
        }
        return true;
      }
      friend bool operator!=(const Map<Key_T,Mapped_T> & map1, const Map<Key_T,Mapped_T> & map2){
        return !(map1==map2);
      }
      friend bool operator<(const Map<Key_T,Mapped_T> & map1, const Map<Key_T,Mapped_T> & map2){
        if(map1.size()<map2.size()) return true;
        if(map1.size()>map2.size()) return false;
        ConstIterator it1 = map1.begin();
        for(ConstIterator it2 = map2.begin(); it2 != map2.end(); it2++){
          if(*it1<*it2){
            return true;
          }
          if(*it1>*it2){
            return false;
          }
          it1++;
        }
        return false;
      }
      //These operators may be implemented as member functions or free functions, though implementing as free functions is recommended. The first operator compares the given maps for equality. Two maps compare equal if they have the same number of elements, and if all elements compare equal. The second operator compares the given maps for inequality. You may implement this simply as the logical complement of the equality operator. For the third operator, you must use lexicographic sorting. Corresponding elements from each maps must be compared one-by-one. A map M1 is less than a map M2 if there is an element in M1 that is less than the corresponding element in the same position in map M2, or if all corresponding elements in both maps are equal and M1 is shorter than M2.

      //Map elements are of type ValueType, so this actually compares the pairs.
    private:
      Node* sentinel;
      size_t _size;
      size_t max;
      void map_default(){
        _size = 0;
        max = 0;
        sentinel = new Node(0);
  			sentinel->prev = sentinel;
  			sentinel->forward_links[0] = sentinel;
      };
      Node* find_key(const Key_T&);
      size_t random_level();
  };

  template <typename Key_T, typename Mapped_T>
  typename Map<Key_T, Mapped_T>::Node* Map<Key_T, Mapped_T>::find_key(const Key_T& key){
      Node* current = sentinel;
  	  for(int i = max; i>=0;--i){
        while(current->forward_links[i] != sentinel && static_cast<DataNode *>(current->forward_links[i])->value.first < key){
          current = current->forward_links[i];
        }
      }
      current = current->forward_links[0];
      if(current != sentinel && ((DataNode*)current)->value.first == key){
        return current;
      } else {
        return NULL;
      }
  }

  template <typename Key_T, typename Mapped_T>
  typename Map<Key_T, Mapped_T>::Iterator Map<Key_T, Mapped_T>::find(const Key_T & key){
      Node* found = find_key(key);
      if(found==NULL){
        return Iterator(sentinel);
      } else {
        return Iterator(found);
      }
  }

  template <typename Key_T, typename Mapped_T>
  typename Map<Key_T, Mapped_T>::ConstIterator Map<Key_T, Mapped_T>::find(const Key_T & key) const{
      Node* found = find_key(key);
      if(found==NULL){
        return ConstIterator(sentinel);
      } else {
        return ConstIterator(found);
      }
  }

  template <typename Key_T, typename Mapped_T>
  Mapped_T &Map<Key_T, Mapped_T>::at(const Key_T & key){
    Node* found = find_key(key);
    if(found==NULL){
      throw std::out_of_range("Key does not exist in map");
    } else {
      return static_cast<DataNode *>(found)->value.second;
    }
  }	//Returns a reference to the mapped object at the specified key. If the key is not in the Map, throws std::out_of_range.

  template <typename Key_T, typename Mapped_T>
  const Mapped_T& Map<Key_T, Mapped_T>::at(const Key_T & key) const{
    Node* found = find_key(key);
    if(found==NULL){
      throw std::out_of_range("Key does not exist in map");
    } else {
      return static_cast<DataNode *>(found)->value.second;
    }
  }

  template <typename Key_T, typename Mapped_T>
  Mapped_T& Map<Key_T, Mapped_T>::operator[](const Key_T & key){
    Node* found = find_key(key);
    if (found==NULL){
        Iterator ins = insert(std::make_pair(key,Mapped_T())).first;
        return static_cast<DataNode*>(ins.current)->value.second;
    } else {
      return static_cast<DataNode*>(found)->value.second;
    }
  }

  template <typename Key_T, typename Mapped_T>
  size_t Map<Key_T, Mapped_T>::random_level(){
  		size_t rlevel = 0;
  		while(rand() < RAND_MAX*0.5){
  			++rlevel;
  		}
  		return rlevel;
  }

  template <typename Key_T, typename Mapped_T>
  std::pair<typename Map<Key_T, Mapped_T>::Iterator, bool> Map<Key_T, Mapped_T>::insert(const std::pair<const Key_T, Mapped_T>& val){
      const Key_T key = val.first; //get key from param val
      Node* current = sentinel; //current pointer
      std::vector<Node*> updated(max+1,NULL); //updated vector
      for(int i = max; i >= 0; --i){
        while (current->forward_links[i] != sentinel && static_cast<DataNode *>(current->forward_links[i])->value.first < key){
          current = current->forward_links[i];
        }
        updated[i] = current;
      }
      current = current->forward_links[0];

      if (current != sentinel && static_cast<DataNode *>(current)->value.first == key)
      {
        return std::make_pair(Map<Key_T, Mapped_T>::Iterator(current), false);
      } else {
          // Generate a random level for node
        size_t level = random_level();
        DataNode *newNode = new DataNode(level,val);

        // insert node by rearranging pointers
        for (int i=0;i<=level;i++)
        {
          if(i > max){
            sentinel->forward_links.push_back(newNode);
            newNode->forward_links[i] = sentinel;
            ++max;
          } else {
            newNode->forward_links[i] = updated[i]->forward_links[i];
            updated[i]->forward_links[i] = newNode;
          }
        }
        newNode->forward_links[0]->prev = newNode;
        newNode->prev = updated[0];

        _size++;

        return std::make_pair(Map<Key_T, Mapped_T>::Iterator(newNode), true);
      }
  }

  template <typename Key_T, typename Mapped_T>
  void Map<Key_T, Mapped_T>::erase(Iterator pos){
    Node* current = sentinel; //current pointer
    std::vector<Node*> updated(max+1,NULL); //updated vector
    for(int i = max; i >= 0; --i){
      while (current->forward_links[i] != sentinel && static_cast<DataNode *>(current->forward_links[i])->value.first < (*pos).first){
        current = current->forward_links[i];
      }
      updated[i] = current;
    }
    current = current->forward_links[0];

    if (current != sentinel && static_cast<DataNode *>(current)->value.first == (*pos).first)
    {
      // insert node by rearranging pointers
      for (int i=0;i<current->forward_links.size();i++)
      {
        updated[i]->forward_links[i] = current->forward_links[i];
      }
      current->forward_links[0]->prev = current->prev;

      delete current;

      while(max>0 && sentinel->forward_links[max] == sentinel){
        sentinel->forward_links.pop_back();
        max--;
      }

      --_size;
    } else {
      throw std::out_of_range("Key not in map cannot erase");
    }
  }

  template <typename Key_T, typename Mapped_T>
  void Map<Key_T, Mapped_T>::erase(const Key_T & key){
    Node* current = sentinel; //current pointer
    std::vector<Node*> updated(max+1,NULL); //updated vector
    for(int i = max; i >= 0; --i){
      while (current->forward_links[i] != sentinel && static_cast<DataNode *>(current->forward_links[i])->value.first < key){
        current = current->forward_links[i];
      }
      updated[i] = current;
    }
    current = current->forward_links[0];

    if (current != sentinel && static_cast<DataNode *>(current)->value.first == key)
    {
      // insert node by rearranging pointers
      for (int i=0;i<current->forward_links.size();i++)
      {
        updated[i]->forward_links[i] = current->forward_links[i];
      }
      current->forward_links[0]->prev = current->prev;

      delete current;

      while(max>0 && sentinel->forward_links[max] == sentinel){
        sentinel->forward_links.pop_back();
        max--;
      }

      --_size;
    } else {
      throw std::out_of_range("Key not in map cannot erase");
    }
  }
}

#endif

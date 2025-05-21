// Sequence.h
//caitlin nguyen 605943983

#ifndef SEQUENCE_INCLUDED
#define SEQUENCE_INCLUDED

template<typename ItemType>
class Sequence
{
  public:
    Sequence();          // Create an empty sequence (i.e., one whose size() is 0).
    bool empty() const;  // Return true if the sequence is empty, otherwise false.
    int size() const;    // Return the number of items in the sequence.

    int insert(int pos, const ItemType& value);
      // Insert value into the sequence so that it becomes the item at
      // position pos.  The original item at position pos and those that
      // follow it end up at positions one greater than they were at before.
      // Return pos if 0 <= pos <= size() and the value could be
      // inserted.  (It might not be, if the sequence has a fixed capacity,
      // e.g., because it's implemented using a fixed-size array.)  Otherwise,
      // leave the sequence unchanged and return -1.  Notice that
      // if pos is equal to size(), the value is inserted at the end.

    int insert(const ItemType& value);
      // Let p be the smallest integer such that value <= the item at
      // position p in the sequence; if no such item exists (i.e.,
      // value > all items in the sequence), let p be size().  Insert
      // value into the sequence so that it becomes the item in position
      // p.  The original item in position p and those that follow it end
      // up at positions one greater than before.  Return p if the value
      // was actually inserted.  Return -1 if the value was not inserted
      // (perhaps because the sequence has a fixed capacity and is full).

    bool erase(int pos);
      // If 0 <= pos < size(), remove the item at position pos from
      // the sequence (so that all items that followed that item end up at
      // positions one lower than they were at before), and return true.
      // Otherwise, leave the sequence unchanged and return false.

    int remove(const ItemType& value);
      // Erase all items from the sequence that == value.  Return the
      // number of items removed (which will be 0 if no item == value).

    bool get(int pos, ItemType& value) const;
      // If 0 <= pos < size(), copy into value the item at position pos
      // of the sequence and return true.  Otherwise, leave value unchanged
      // and return false.

    bool set(int pos, const ItemType& value);
      // If 0 <= pos < size(), replace the item at position pos of the
      // sequence with value and return true.  Otherwise, leave the sequence
      // unchanged and return false.

    int find(const ItemType& value) const;
      // Let p be the smallest integer such that value == the item at
      // position p in the sequence; if no such item exists, let p be -1.
      // Return p.

    void swap(Sequence& other);
      // Exchange the contents of this sequence with the other one.

      // Housekeeping functions
    ~Sequence();
    Sequence(const Sequence& other);
    Sequence& operator=(const Sequence& rhs);

  private:
      // Representation:
      //   a circular doubly-linked list with a dummy node.
      //   m_head points to the dummy node.
      //   m_head->m_prev->m_next == m_head and m_head->m_next->m_prev == m_head
      //   m_size == 0  iff  m_head->m_next == m_head->m_prev == m_head
      //   if m_size > 0
      //       m_head->next points to the node at position 0.
      //       m_head->prev points to the node at position m_size-1.

    struct Node
    {
        ItemType m_value;
        Node*    m_next;
        Node*    m_prev;
    };

    Node* m_head;
    int   m_size;

    void createEmpty();
      // Create an empty list.  (Should be called only by constructors.)

    void insertBefore(Node* p, const ItemType& value);
      // Insert value in a new Node before Node p, incrementing m_size.

    Node* doErase(Node* p);
      // Remove the Node p, decrementing m_size.  Return the Node that
      // followed p.

    Node* nodeAtPos(int pos) const;
      // Return pointer to Node at position pos.  If pos == m_size, return
      // m_head.  (Will be called only when 0 <= pos <= size().)
};

//member functions
template <typename ItemType>
Sequence<ItemType>::Sequence()
{
    createEmpty();
}

template <typename ItemType>
int Sequence<ItemType>::insert(int pos, const ItemType &value)
{
    if(pos < 0 || pos > size()) //viability check
    {
        return -1;
    }
    Node* placehold = nodeAtPos(pos);
    insertBefore(placehold, value); //insert at place
    return pos;
}

template <typename ItemType>
int Sequence<ItemType>::insert(const ItemType &value)
{
    int count = 0; //counter for pos
    Node* placehold = m_head->m_next; //initialize placeholder node
    for(; placehold != m_head && value > placehold->m_value; placehold = placehold->m_next)
    {
        count++; //find viable pos
    }
    //insert value
    insertBefore(placehold, value);
    return count;
}

template <typename ItemType>
bool Sequence<ItemType>::erase(int pos)
{
    //check if allowed
    if(pos < 0 || pos >= size())
    {
        return false;
    }
    //now erase
    Node* placehold = nodeAtPos(pos);
    doErase(placehold);
    return true;
}

template <typename ItemType>
int Sequence<ItemType>::remove(const ItemType &value)
{
    int count = 0;
    Node* placehold = m_head->m_next; //placeholder initialize
    //go through list and erase nodes
    while(placehold != m_head) //originally a for loop
    {
        if(value == placehold->m_value)
        {
            count++;
            placehold = doErase(placehold); //gets next pointer
        }
        else
            placehold = placehold->m_next;
    }
    return count;
}

template <typename ItemType>
bool Sequence<ItemType>::get(int pos, ItemType &value) const
{
    if(pos < 0 || pos >= size()) //viability check
    {
        return false;
    }
    Node* placehold = nodeAtPos(pos); //get node
    value = placehold->m_value; //change value
    return true;
}

template <typename ItemType>
bool Sequence<ItemType>::set(int pos, const ItemType &value)
{
    if(pos < 0 || pos >= size()) //viability check
    {
        return false;
    }
    Node* placehold = nodeAtPos(pos); //get node
    placehold->m_value = value; //change value
    return true;
}

template <typename ItemType>
int Sequence<ItemType>::find(const ItemType &value) const
{
    int count = 0;
    Node* placehold = m_head->m_next;
    for(; placehold != m_head && placehold->m_value != value; placehold = placehold->m_next)
    {
        count++;
    }
    return count;
}

template <typename ItemType>
void Sequence<ItemType>::swap(Sequence<ItemType> &other)
{
    //trade pointers
    Node* placehold = m_head;
    m_head = other.m_head;
    other.m_head = placehold;
    
    //trade sizes
    int sizePlacehold = m_size;
    m_size = other.m_size;
    other.m_size = sizePlacehold;
}

//housekeeping functions
template <typename ItemType>
Sequence<ItemType>::~Sequence()
{
    //THIS IS MY CODE FROM PROJECT 2
    //this is our placeholder
    Node* placeholder = m_head;
    //we want to mark the end of the loop by making the next pointer of the last item to nullptr
    m_head->m_prev->m_next = nullptr;
    while(placeholder != nullptr)
    {
        Node* placeholder2 = placeholder->m_next; //this holds onto the address of the next item
        delete placeholder; //deletes placeholder things
        placeholder = placeholder2; //we get back the address of the next item (from before we deleted it)
    }
}

template <typename ItemType>
Sequence<ItemType>::Sequence(const Sequence& other)
{
    createEmpty(); //make new Seq
    //fill sequence with values of other seq
    for(Node* placehold = other.m_head->m_next; placehold != other.m_head; placehold = placehold->m_next)
    {
        insert(placehold->m_value);
    }
}

template <typename ItemType>
Sequence<ItemType>& Sequence<ItemType>::operator=(const Sequence& rhs)
{
    //copied from lecture
    if (this != &rhs)
     {
         Sequence temp(rhs);
         swap(temp);
     }
     return *this;
}

//private functions in Node
template <typename ItemType>
void Sequence<ItemType>::createEmpty()
{
    //copied from my project 2
    //setting up head node
    m_head = new Node;
    m_head->m_next = m_head;
    m_head->m_prev = m_head;
    m_size = 0;
}

template <typename ItemType>
void Sequence<ItemType>::insertBefore(Node *p, const ItemType &value)
{
    //size increase
    m_size++;
    //new node
    Node* addedVal = new Node;
    //value
    addedVal->m_value = value;
    //move around pointers for addedVal
    addedVal->m_next = p;
    addedVal->m_prev = p->m_prev;
    //change the pointers for the ones around adddedVal
    addedVal->m_prev->m_next = addedVal;
    addedVal->m_next->m_prev = addedVal;
}

template <typename ItemType>
typename Sequence<ItemType>::Node* Sequence<ItemType>::doErase(Node *p)
{
    Node* toReturn = p->m_next;
    //switch around pointers
    p->m_prev->m_next = p->m_next;
    p->m_next->m_prev = p->m_prev;
    //decrease size
    m_size--;
    //delete p
    delete p;
    return toReturn;
}

template <typename ItemType>
typename Sequence<ItemType>::Node* Sequence<ItemType>::nodeAtPos(int pos) const
{
    Node* iterator = m_head->m_next;
    int posCount = 0;
    for(; iterator!= m_head && posCount < pos; iterator = iterator->m_next, posCount++)
    {
        //move until we get to pos
    }
    return iterator;
}

// non-member functions
template <typename ItemType>
int subsequence(const Sequence<ItemType>& seq1, const Sequence<ItemType>& seq2) //COPY PASTED FROM SOLUTIONS
{
    // If seq2 is a contiguous subsequence of seq1, return the position in
    // seq1 where that subsequence starts (the earliest such position if more
    // than one).  If not, or if seq2 is empty, return -1.
    if (seq2.empty())
        return -1;

      // Walk through seq1

    for (int pos = 0; pos <= seq1.size() - seq2.size(); pos++)
    {
          // Assume there's a match starting at pos

        bool allMatched = true;

          // Check if all corresponding positions match

        for (int k = 0; k < seq2.size(); k++)
        {
            ItemType v1;
            ItemType v2;
            seq1.get(pos+k, v1);
            seq2.get(k, v2);
            if (v1 != v2)
            {
                allMatched = false;
                break;
            }
        }

          // If we never found a mismatch, we've found the match.

        if (allMatched)
            return pos;
    }

      // If we never found a match, there is none.

    return -1;
}

template <typename ItemType>
void concatReverse(const Sequence<ItemType>& seq1, const Sequence<ItemType>& seq2, Sequence<ItemType>& result) //COPY PASTED FROM SOLUTIONS
{
    // Set result to the concatenation of the reverses of seq1 and seq2
    Sequence<ItemType> res;

    for (int k = seq1.size() - 1; k >= 0; k--)
    {
        ItemType v;
        seq1.get(k, v);
        res.insert(res.size(), v);
    }

    for (int k = seq2.size() - 1; k >= 0; k--)
    {
        ItemType v;
        seq2.get(k, v);
        res.insert(res.size(), v);
    }

    result.swap(res);
}

// Inline implementations
template <typename ItemType>
inline
int Sequence<ItemType>::size() const
{
    return m_size;
}

template <typename ItemType>
inline
bool Sequence<ItemType>::empty() const
{
    return size() == 0;
}

#endif // SEQUENCE_INCLUDED

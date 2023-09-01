template <typename T>
class LL
{
    // contents of each node
    struct Node
    {
        T data;
        Node *prev;
        Node *next;
    };
    // iterator class to allow access of each node in main
public:
    class Iterator
    {
    public:
        friend class LL;
        // sets current node to null
        Iterator(){current = nullptr;}
        // sets current node to ptr
        Iterator(Node *ptr){current = ptr;}

        // returns the data field of the node
        T operator*() const {return current->data;}

        // moves the iterator object one node to the right
        const Iterator &operator++(int)
        {
            current = current->next; //change current one to the right
            return *this; //returns this node
        };

        // moves the iterator object one node to the left
        const Iterator &operator--(int)
        {
            current = current->prev; //sets current one to the left
            return *this; //returns this node
        };

        bool operator==(const Iterator &rhs) const
        {   //checks to see if current is = to iterator
            if (current == rhs.current) 
            {
                return true; //returns true if it is
            }
            else
            {
                return false; //returns false if it is not
            }
        };

        bool operator!=(const Iterator &rhs) const
        {   //checks to see if current is not = to iterator
            if (current != rhs.current)
            {
                return true; //returns true if not
            }
            else
            {
                return false; //returns false if it is
            }
        };

    private:
        Node *current;
    };
    // constructor, sets had and tail to nullptr
    LL()
    {
        head = nullptr;
        tail = nullptr;
    };

    LL(const LL<T> &copy)
    {
        Node* temp = copy.head; //temp node created set to copy 
        this->tail = nullptr; //sets current head to null
        this->head = nullptr; //sets current tail to null

        while(temp != nullptr) //looping condition for while temp is not null
        {
            Node* newNode = new Node; //creates new Node for copy
            newNode->data = temp->data; //sets newNode to the temp 
            newNode->next = nullptr; //set next to null
            newNode->prev = nullptr; //set prev to null

            if (this->head == nullptr) //checks to see if this head is null
            {
                this->tail = newNode; //sets this tail to newNode
                this->head = newNode; //sets this head to newNode
            }
            else //if this head isn't null
            {
                this->tail->next = newNode; //setting this tail next to newNode
                newNode->prev = tail; //sets newNode prev to tail
                this->tail = newNode; //links this and newNode together
            }
            temp = temp->next; //sets temp to next temp   
        }
    };

    const LL<T> &operator=(const LL<T> &rhs)
    {
        if (this->head != nullptr) //checks if anything is in node
        {
            Node* temp = this->head; // create temp node
            //loop to clear everything up
            while (temp != nullptr)
            {
                this->head = this->head->next; // will set current head to next
                delete temp; //delete temp
                temp = this->head; //this should end up being null 
            }
            
            this->tail = nullptr; //sets tail to null
            this->head = nullptr; //sets head to null
        } //this should clear everything out

        //check rhs first to see if there is stuff in it
        if (rhs.head != nullptr)
        {
            Node* temp = rhs.head;

            while(temp != nullptr) //looping condition for while temp is not null
            {
                Node* newNode = new Node; //creates new Node for copy
                newNode->data = temp->data; //sets newNode to the temp 
                newNode->next = nullptr; //set next to null
                newNode->prev = nullptr; //set prev to null

                if (this->head == nullptr) //checks to see if this head is null
                {
                    this->head = newNode; //sets this head to newNode
                    this->tail = newNode; //sets this tail to newNode
                }
                else //if this head isn't null make it all one
                {
                    this->tail->next = newNode; //setting this tail next to newNode
                    newNode->prev = tail; //sets newNode prev to tail
                    this->tail = newNode; //links this and newNode together
                }
                temp = temp->next; //sets temp to next temp
            }
        }

        return *this;
    };

    ~LL()
    {
        Node* temp = head;
        while (temp != nullptr) //loops utnil temp is null
        {
            head = head->next; // will set head to next
            delete temp; //delete temp
            temp = head; //this should end up being null 
        }
            
            tail = nullptr; //sets tail to null
            head = nullptr; //sets head to null
    };

    void headInsert(const T &item)
    {   //checks to see if head is null
        if (head == nullptr) 
        {
            head = new Node; //creates new node
            head->data = item; //adds item to node
            head->next = nullptr; //make right null
            head->prev = nullptr; //make left null
            tail = head; //combine everything into one node
        }
        else //if head is not null
        {
            Node *temp; //create temp node
            temp = new Node;
            temp->data = item; //add item to temp 
            temp->prev = nullptr; //set up link
            temp->next = head; //set up link
            head->prev = temp; //set up link
            head = temp; //sets the new head
            temp = nullptr; //gets rid of temp
        }
    };

    void tailInsert(const T &item)
    {
        if (tail == nullptr)
        {
            tail = new Node; //creates new node
            tail->data = item; //adds item to tail
            tail->next = nullptr; //set tail right to null
            tail->prev = nullptr; //set tail left to null
            head = tail; //combine everything to one
        }
        else
        {
            Node *temp; //temp node
            temp = new Node;
            temp->data = item; //add value to temp
            temp->next = nullptr; //set up link
            temp->prev = tail; //set up link
            tail->next = temp; //set up link
            tail = temp; //sets the new tail
            temp = nullptr; //gets rid of temp
        }
    };

    Iterator begin() const 
    {
        return Iterator(this->head); //returns the current beginning
    };

    Iterator end() const 
    {
        return Iterator(this->tail); //returns the current end
    };

    void swapNodes(Iterator &it1, Iterator &it2)
    {
        Node* i = it1.current; //will represent the two numbers
        Node* j = it2.current; //will represent the two numbers
        Node* i_left = i->prev;
        Node* j_right = j->next;
        // ^^^ these we just represent temp values

        //what if it1.current is head
        //what if it2.current is tail
        //also swap addresses of it1 and it2 after swap
        //and make sure head and tail are pointing at the proper spots\
        //it1 = head --- it2 != tail
        //it1 != head --- it2 = tail
        //it1 != head --- it2 != tail
        //it1 = head --- it2 = tail

        if (i_left == nullptr && j_right != nullptr) 
        { //case for if i is head but j is not tail
            i->next = j_right;
            j->next = i;
            //set links
            j_right->prev = i;
            //set links
            i->prev = j;
            j->prev = nullptr;
    
            head = j; //must set new head 
        }
        else if (i_left != nullptr && j_right == nullptr)
        { //case for if i is not head but j is tail
            i_left->next = j;
            //set links
            i->prev = j;
            j->prev = i_left;
            //set links
            j->next = i;
            i->next = nullptr;
            tail = i; //must set new tail
        }
        else if (i_left != nullptr && j_right != nullptr)
        { //case for if i and j are not head nor tail
            //set links
            i_left->next = j;
            j_right->prev = i;
            //set links
            i->prev = j;
            j->prev = i_left;
            //set links
            i->next = j_right;
            j->next = i;
        }
        else if (i_left == nullptr && j_right == nullptr)
        { //case for if i and j are head and tail'
            //link i and j together
            i->prev = j;
            j->next =  i;
            //set next values to be null
            i->next = nullptr;
            j->prev = nullptr;

            tail = i; //must set new tail
            head = j; //must set new head
        }

        //just swaps where it1 and it2  are pointing
        Node* temp = it1.current;
        it1.current = it2.current;
        it2.current = temp;
    };

private:
    Node *head;
    Node *tail;
};

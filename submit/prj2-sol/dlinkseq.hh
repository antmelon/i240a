#ifndef DLINK_SEQ_HH_
#define DLINK_SEQ_HH_

#include "seq.hh"

#include <cassert>
#include <cstddef>
#include <memory>
#include <utility>

template <typename E> class DLinkSeqConstIter;

template <typename E>
class DLinkSeq : public Seq<E> {
    friend class DLinkSeqConstIter<E>;

    private:
    class Node {
        public:
        Node* prev = nullptr;
        Node* next = nullptr;
        Node() {};
        virtual ~Node() = default;
    };
   
    class DataNode : public Node {
        public:
        E val;
        DataNode(const E &val) : val(val) {};
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    int m_size = 0;

    void insertAfter(Node* before, Node* after) {
        after->prev = before;
        after->next = before->next;
        before->next->prev = after;
        before->next = after;
        m_size++;
    }

    const E& removeAndReturn(DataNode* node) {
        const E& ret = node->val;
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
        m_size--;
        return ret;
    }
   
    public:

    DLinkSeq() {
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->prev = head;
    }

    void clear() override {
        Node* temp = head->next;
        while (temp != tail) {
            temp = temp->next;
            delete temp->prev;
        }
        head->next = tail;
        tail->prev = head;
    }

    void unshift(const E& item) override {
        insertAfter(head, new DataNode(item));
    }

    E shift() override {
        assert(m_size && "dlink empty");
        return removeAndReturn(dynamic_cast<DataNode*>(head->next));
    }

    void push(const E& item) override {
        insertAfter(tail->prev, new DataNode(item));
    }

    E pop() override {
        assert(m_size && "dlink empty");
        return removeAndReturn(dynamic_cast<DataNode*>(tail->prev));
    }

    int size() const override { return m_size; }

    ConstIterPtr<E> cbegin() const override {
        return std::make_unique<DLinkSeqConstIter<E>>(head->next);
    }

    ConstIterPtr<E> cend() const override {
        return std::make_unique<DLinkSeqConstIter<E>>(tail->prev);
    }

    static SeqPtr<E> make() {
        return std::make_unique<DLinkSeq<E>>();
    }
};


template <typename E>
class DLinkSeqConstIter : public ConstIter<E> {
    using Node = typename DLinkSeq<E>::Node;
    using DataNode = typename DLinkSeq<E>::DataNode;
    Node* curr;
public:
    DLinkSeqConstIter(Node* curr) : curr(curr) {}
    ConstIter<E>& operator++() override {
        curr = curr->next;
        return *this;
    }

    ConstIter<E>& operator--() override {
        curr = curr->prev;
        return *this;
    }

    operator bool() override {
        return curr->next and curr->prev;
    }

    const E& operator*() override {
        return dynamic_cast<DataNode*>(curr)->val;
    }

    const E* operator->() override {
        return &(dynamic_cast<DataNode*>(curr)->val);
    }
};


#endif //ifndef DLink_SEQ_HH_    

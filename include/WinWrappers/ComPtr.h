#pragma once

template<typename T>
class ComPtr {
public:
    explicit ComPtr(T* p = nullptr) :
        m_p(p)
    {}

    ComPtr(const ComPtr& ref) {
        Copy<false>(ref);
    }

    ComPtr(ComPtr&& that) {
        MoveFrom<false>(std::move(that));
    }

    ComPtr(nullptr_t) :
        m_p(nullptr)
    {
    }

    ~ComPtr() {
        Release<false>();
    }

    T* Get() const {
        return m_p;
    }

    template<bool release_prev = true>
    void Set(T* ptr) {
        if constexpr (release_prev) {
            Release<false>();
        }
        m_p = ptr;
    }

    void AddReference() {
        if (m_p) {
            m_p->AddRef();
        }
    }

    template<bool release_prev>
    void Copy(const ComPtr& ref) {
        Set<release_prev>(ref.m_p);
        AddReference();
    }

    template<bool set_to_null>
    void Release() {
        if (m_p != nullptr) {
            m_p->Release();
            if constexpr (set_to_null) {
                m_p = nullptr;
            }
        }
    }

    template<bool release_prev = true>
    void MoveFrom(ComPtr<T>&& that) {
        Set<release_prev>(that.m_p);
        that.m_p = nullptr;
    }

    T* operator->() const {
        return m_p;
    }

    T& operator*() const {
        return *m_p;
    }

    ComPtr& operator=(const ComPtr& ref) {
        Copy(ref);
        return *this;
    }

    ComPtr& operator=(ComPtr&& that) {
        MoveFrom<true>(std::move(that));
        return *this;
    }

    friend bool operator==(const ComPtr& a, const ComPtr& b) {
        return a.m_p == b.m_p;
    }

    friend bool operator!=(const ComPtr& a, const ComPtr& b) {
        return a.m_p != b.m_p;
    }

    T** Receive() {
        Release<true>();
        return &m_p;
    }

private:
    T * m_p;
};
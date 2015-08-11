#ifndef STORAGE_H_INCLUDED
#define STORAGE_H_INCLUDED

namespace libmda
{
namespace storage
{

template<class T, class Alloc = std::allocator<T> >
//template<class T>
class storage
{
   public:
      using size_type = typename Alloc::size_type;
      
      storage(): size_(0), elem_(Alloc().allocate(size_))
      {
      }

      storage(size_type size): size_(size), elem_(Alloc().allocate(size))
      {
      }

      storage(storage<T>&& t): size_(t.size_), elem_(t.elem_) // we can move a storage
      {
         t.size_ = 0;
         t.elem_ = nullptr;
      }

      ~storage()
      {
         if(elem_)
         {
            Alloc().deallocate(elem_,size_);
         }
      }

      T& operator[](size_type i)
      {
         return elem_[i];
      }
      
      const T& operator[](size_type i) const
      {
         return elem_[i];
      }

      T* data()
      {
         return elem_;
      }

      const T* data() const
      {
         return elem_;
      }

      //size_type size() const
      //{
      //   return size_;
      //}

   private:
      // for now we do not allow copies
      storage(const storage<T>&) = delete;
      storage<T>& operator=(const storage<T>&) = delete;

      size_type size_;
      T* elem_;
};

} /* namespace storage */
} /* namespace libmda */

#endif /* STORAGE_H_INCLUDED */

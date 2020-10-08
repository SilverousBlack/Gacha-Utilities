#pragma once
#include "pch.h"

#ifndef GACHACORE_HXX
#define GACHACORE_HXX

namespace gacha_utilities {

	template<typename Type>
	class base_iterator {
	public:

		using InternalType = Type;
		using TypePtr = Type*;
		using TypeRef = Type&;
		using DifferenceType = long long signed int;

		using iterator_category = std::random_access_iterator_tag;
		using value_type = InternalType;
		using difference_type = DifferenceType;
		using pointer = TypePtr;
		using reference = TypeRef;

	public:
		base_iterator<Type>(TypePtr OtherPtr = nullptr) { data = OtherPtr; }
		base_iterator<Type>(TypePtr OtherPtr, DifferenceType Offset) { data = OtherPtr + Offset; }
		explicit base_iterator<Type>(InternalType Literal) { data = &(Literal); }
		base_iterator<Type>(const base_iterator<Type>& OtherIter) { data = OtherIter.data; }
		~base_iterator<Type>() {}

		base_iterator<Type>& operator=(const base_iterator<Type>& OtherIter) { data = OtherIter.data; return (*this); }
		base_iterator<Type>& operator=(TypePtr OtherPtr) { data = OtherPtr; return (*this); }

		operator bool() const { return bool(data); }

		bool operator== (const base_iterator<Type>& OtherIter) const { return (data == OtherIter.GetConstPtr()); }
		bool operator!= (const base_iterator<Type>& OtherIter) const { return (data != OtherIter.GetConstPtr()); }

		base_iterator<Type>& operator+=(const DifferenceType& Offset) { data += Offset; return (*this); }
		base_iterator<Type>& operator-=(const DifferenceType& Offset) { data -= Offset; return (*this); }
		base_iterator<Type>& operator++() { ++data; return (*this); }
		base_iterator<Type>& operator--() { --data; return (*this); }
		base_iterator<Type> operator++(int) { auto temp(*this); ++data; return temp; }
		base_iterator<Type> operator--(int) { auto temp(*this); --data; return temp; }
		base_iterator<Type> operator+(const DifferenceType& Offset) { auto OldPtr = data; data += Offset; auto temp(*this); data = OldPtr; return temp; }
		base_iterator<Type> operator-(const DifferenceType& Offset) { auto OldPtr = data; data -= Offset; auto temp(*this); data = OldPtr; return temp; }

		difference_type operator-(const base_iterator<Type>& rawIterator) { return std::distance(rawIterator.GetPtr(), this->GetPtr()); }

		TypeRef operator*() { return *data; }
		const TypeRef operator*()const { return *data; }
		TypePtr operator->() { return data; }

		TypePtr GetPtr() const { return data; }
		const TypePtr GetConstPtr() const { return data; }
		base_iterator<Type>& SetPtr(TypePtr ptr) { data = ptr; return (*this); }
	protected:
		TypePtr data;
	};

	template<typename Type>
	class base_reverse_iterator : public base_iterator<Type> {
	public:

		using InternalType = Type;
		using TypePtr = Type*;
		using TypeRef = Type&;
		using DifferenceType = long long signed int;

		base_reverse_iterator<Type>(TypePtr ptr = nullptr) : base_iterator<Type>(ptr) {}
		base_reverse_iterator<Type>(const base_iterator<Type>& OtherIter) { this->data = OtherIter.GetPtr(); }
		base_reverse_iterator<Type>(const base_reverse_iterator<Type>& OtherIter) = default;
		~base_reverse_iterator<Type>() {}

		base_reverse_iterator<Type>& operator=(const base_reverse_iterator<Type>& OtherIter) { this->data = OtherIter.GetPtr(); return (*this); }
		base_reverse_iterator<Type>& operator=(const base_iterator<Type>& OtherIter) { this->data = OtherIter.GetPtr(); return (*this); }
		base_reverse_iterator<Type>& operator=(TypePtr ptr) { this->SetPtr(ptr); return (*this); }

		base_reverse_iterator<Type>& operator+=(const DifferenceType& Offset) { this->data -= Offset; return (*this); }
		base_reverse_iterator<Type>& operator-=(const DifferenceType& Offset) { this->data += Offset; return (*this); }
		base_reverse_iterator<Type>& operator++() { --this->data; return (*this); }
		base_reverse_iterator<Type>& operator--() { ++this->data; return (*this); }
		base_reverse_iterator<Type> operator++(int) { auto temp(*this); --this->data; return temp; }
		base_reverse_iterator<Type> operator--(int) { auto temp(*this); ++this->data; return temp; }
		base_reverse_iterator<Type> operator+(const DifferenceType& Offset) { auto OldPtr = this->data; this->data -= Offset; auto temp(*this); this->data = OldPtr; return temp; }
		base_reverse_iterator<Type> operator-(const DifferenceType& Offset) { auto OldPtr = this->data; this->data += Offset; auto temp(*this); this->data = OldPtr; return temp; }

		DifferenceType operator-(const base_reverse_iterator<Type>& OtherIter) { return std::distance(this->GetPtr(), OtherIter.GetPtr()); }

		base_iterator<Type> base() { base_iterator<Type> ForwardIterator(this->data); ++ForwardIterator; return ForwardIterator; }
	};
	namespace gachapoolexceptions {
		class GachaPoolException : public std::exception {
		public:
			GachaPoolException() {}
			~GachaPoolException() {}
		};
		class IllegalZeroSize : public GachaPoolException {
		public:
			IllegalZeroSize() {}
			~IllegalZeroSize() {}
		};
		class SizeBeyondMaximum : public GachaPoolException {
		public:
			SizeBeyondMaximum() {}
			~SizeBeyondMaximum() {}
		};
		class IndexOutOfRange : public GachaPoolException {
		public:
			IndexOutOfRange() {}
			~IndexOutOfRange() {}
		};
		class IteratorOutOfRange : public GachaPoolException {
		public:
			IteratorOutOfRange() {}
			~IteratorOutOfRange() {}
		};
		class UnidentifiedIteratorRange : public GachaPoolException {
		public:
			UnidentifiedIteratorRange() {}
			~UnidentifiedIteratorRange() {}
		};
		class CannotConvertToKnownIterator : public GachaPoolException {
		public:
			CannotConvertToKnownIterator() {}
			~CannotConvertToKnownIterator() {}
		};
		class AssignOffsetOutOfRange : public GachaPoolException {
		public:
			AssignOffsetOutOfRange() {}
			~AssignOffsetOutOfRange() {}
		};
		class AssignSizeOutOfRange : public GachaPoolException {
		public:
			AssignSizeOutOfRange() {}
			~AssignSizeOutOfRange() {}
		};
		class CopySizeMismatch : public GachaPoolException {
		public:
			CopySizeMismatch() {}
			~CopySizeMismatch() {}
		};
		class CopySizeBeyondAllocation : public GachaPoolException {
		public:
			CopySizeBeyondAllocation() {}
			~CopySizeBeyondAllocation() {}
		};
	};

	template<typename type, typename alloc = std::allocator<type> >
	class GachaPool {
	public:

		using InternalType = type;
		using AllocatorType = alloc;
		using AllocatorTraits = std::allocator_traits<alloc>;
		using TypePtr = type*;
		using TypeRef = type&;
		using DifferenceType = long long signed int;
		using SizeType = long long unsigned int;

		template<typename OtherAllocator = AllocatorType>
		using SameType = GachaPool<InternalType, OtherAllocator>;

		using iterator = base_iterator<type>;
		using const_iterator = base_iterator<const type>;
		using reverse_iterator = base_reverse_iterator<type>;
		using const_reverse_iterator = base_reverse_iterator<const type>;

		static SizeType maxsize();
		static SizeType minsize();

		GachaPool(SizeType InitSize = 0, InternalType InitVal = InternalType());
		GachaPool(SizeType InitSize, InternalType InitVal, AllocatorType Alloc = alloc());
		GachaPool(std::initializer_list<type> InitList);
		~GachaPool();

		template<typename OtherAllocator>
		GachaPool(SameType<OtherAllocator>& OtherPool, OtherAllocator Alloc = OtherAllocator());
		template<typename OtherAllocator>
		GachaPool(const SameType<OtherAllocator>& OtherPool);
		template<typename Iterator>
		GachaPool(Iterator BeginIter, Iterator EndIter, AllocatorType Alloc = alloc());

		GachaPool<type, alloc>& operator= (const GachaPool<type, alloc> OtherPool);
		GachaPool<type, alloc>& operator= (std::initializer_list<type> InitList);
		template<typename Container>
		GachaPool<type, alloc>& operator= (Container OtherContainer);

		SizeType size() const;

		GachaPool<type, alloc>& resize(SizeType NewSize, InternalType FillReference = InternalType());

		GachaPool<type, alloc>& pop();
		GachaPool<type, alloc>& pop(DifferenceType index, SizeType range = 0);
		GachaPool<type, alloc>& pop(iterator iter);
		GachaPool<type, alloc>& pop(const_iterator iter);
		GachaPool<type, alloc>& pop(reverse_iterator iter);
		GachaPool<type, alloc>& pop(const_reverse_iterator iter);
		GachaPool<type, alloc>& pop(iterator BeginIter, iterator EndIter);
		GachaPool<type, alloc>& pop(const_iterator BeginIter, const_iterator EndIter);
		GachaPool<type, alloc>& pop(reverse_iterator BeginIter, reverse_iterator EndIter);
		GachaPool<type, alloc>& pop(const_reverse_iterator BeginIter, const_reverse_iterator EndIter);

		GachaPool<type, alloc>& append(InternalType Object, SizeType Count = 1);
		template<typename Iterator>
		GachaPool<type, alloc>& append(Iterator BeginIter, Iterator EndIter);

		InternalType access(DifferenceType index);
		GachaPool<type, alloc> access(DifferenceType index, SizeType range);
		GachaPool<type, alloc> access(iterator BeginIter, iterator EndIter);
		GachaPool<type, alloc> access(const_iterator BeginIter, const_iterator EndIter);
		GachaPool<type, alloc> access(reverse_iterator BeginIter, reverse_iterator EndIter);
		GachaPool<type, alloc> access(const_reverse_iterator BeginIter, const_reverse_iterator EndIter);

		GachaPool<type, alloc>& assign(InternalType obj, DifferenceType offset = 0, SizeType size = 1);
		template<typename Iterator>
		GachaPool<type, alloc>& assign(Iterator BeginIter, Iterator EndIter, DifferenceType offset = 0);
		template<typename... ArgumentType>
		GachaPool<type, alloc>& assign(DifferenceType offset, SizeType range, InternalType(*function)(ArgumentType...), ArgumentType... Args);

		template<typename Container>
		GachaPool<type, alloc>& copy(Container target);
		template<typename Iterator>
		GachaPool<type, alloc>& copy(Iterator BeginIter, Iterator EndIter);
		template<typename Container>
		GachaPool<type, alloc>& apparent_copy(Container target);
		template<typename Iterator>
		GachaPool<type, alloc>& apparent_copy(Iterator BeginIter, Iterator EndIter);
		template<typename Container>
		GachaPool<type, alloc>& hard_copy(Container target);

		template<typename Container>
		bool hard_compare(Container target, bool (*Comparator)(InternalType, InternalType) = [](InternalType left, InternalType right) { return left == right });
		template<typename Iterator>
		bool hard_compare(Iterator BeginIter, Iterator EndIter, bool (*Comparator)(InternalType, InternalType) = [](InternalType left, InternalType right) { return left == right });
		template<typename Iterator>
		bool hard_compare(iterator srcbegin, iterator srcend, Iterator targetbegin, Iterator targetend, bool (*Comparator)(InternalType, InternalType) = [](InternalType left, InternalType right) { return left == right });
		
		template<typename Container>
		bool free_compare(Container target, bool (*Comparator)(InternalType, InternalType) = [](InternalType left, InternalType right) { return left == right });
		template<typename Iterator>
		bool free_compare(Iterator BeginIter, Iterator EndIter, bool (*Comparator)(InternalType, InternalType) = [](InternalType left, InternalType right) { return left == right });
		template<typename Iterator>
		bool free_compare(iterator srcbegin, iterator srcend, Iterator targetbegin, Iterator targerend, bool (*Comparator)(InternalType, InternalType) = [](InternalType left, InternalType right) { return left == right });

		bool verify(DifferenceType index);
		bool verify(iterator iter);
		bool verify(const_iterator iter);
		bool verify(reverse_iterator iter);
		bool verify(const_reverse_iterator iter);
		bool verify(iterator BeginIter, iterator EndIter);
		bool verify(const_iterator BeginIter, const_iterator EndIter);
		bool verify(reverse_iterator BeginIter, reverse_iterator EndIter);
		bool verify(const_reverse_iterator BeginIter, const_reverse_iterator EndIter);
		bool dereferrencible(iterator iter);
		bool dereferrencible(const_iterator iter);
		bool dereferrencible(reverse_iterator iter);
		bool dereferrencible(const_reverse_iterator iter);
		bool dereferrencible(iterator BeginIter, iterator EndIter);
		bool dereferrencible(const_iterator BeginIter, const_iterator EndIter);
		bool dereferrencible(reverse_iterator BeginIter, reverse_iterator EndIter);
		bool dereferrencible(const_reverse_iterator BeginIter, const_reverse_iterator EndIter);

		InternalType operator [](DifferenceType index);

		iterator begin();
		iterator end();
		const_iterator cbegin() const;
		const_iterator cend() const;
		reverse_iterator rbegin();
		reverse_iterator rend();
		const_reverse_iterator crbegin() const;
		const_reverse_iterator crend() const;
	protected:
		void __resize(SizeType NewSize, InternalType FillReference);

		void __append(InternalType Object, SizeType Count = 1);
		template<typename Iterator>
		void __append(Iterator BeginIter, Iterator EndIter);

		void __pop(DifferenceType index, SizeType range = 0);
		void __pop(iterator BeginIter, iterator EndIter);
		void __pop(reverse_iterator BeginIter, reverse_iterator EndIter);

		void __assign(InternalType obj, DifferenceType offset, SizeType range);
		template<typename Iterator>
		void __assign(Iterator BeginIter, Iterator EndIter, DifferenceType offset);
		template<typename... ArgumentType>
		void __assign(DifferenceType offset, SizeType range, InternalType(*function)(ArgumentType...), ArgumentType... arguments);

		template<typename Container>
		void __apparent_copy(Container target);
		template<typename Iterator>
		void __apparent_copy(Iterator BeginIter, Iterator EndIter);

		void __flush();

		template<typename Iterator>
		iterator _convert_iter_type(Iterator type);

		void _test_resize_size(SizeType NewSize);

		void _test_pop_range(DifferenceType index, SizeType range);
		void _test_pop_range(iterator BeginIter, iterator EndIter);
		void _test_pop_range(reverse_iterator BeginIter, reverse_iterator EndIter);

		template<typename Iterator>
		void _test_append_range(Iterator BeginIter, Iterator EndIter);

		void _test_access_range(DifferenceType index);
		void _test_access_range(DifferenceType index, SizeType count);
		void _test_aceess_range(iterator BeginIter, iterator EndIter);

		void _test_assign_range(DifferenceType Offset, SizeType Range);

		void _test_apparent_copy_size(SizeType CopySize);
		void _test_hard_copy_size(SizeType CopySize);
	private:
		InternalType* data;
		SizeType datasize;
		AllocatorType Allocator;
	};

	template<typename type, typename alloc>
	inline long long unsigned int GachaPool<type, alloc>::maxsize(){
		return SizeType(static_cast<SizeType>(std::numeric_limits<DifferenceType>::max()));
	}

	template<typename type, typename alloc>
	inline long long unsigned int GachaPool<type, alloc>::minsize(){
		return SizeType(0);
	}

	template<typename type, typename alloc>
	inline GachaPool<type, alloc>::GachaPool(SizeType InitSize, InternalType InitVal)
		: Allocator(alloc())
		, data(new InternalType[InitSize])
		, datasize(InitSize)
	{
		_test_resize_size(this->datasize);
		for (SizeType i = 0; i < InitSize; i++) {
			this->data[i] = InitVal;
		}
	}

	template<typename type, typename alloc>
	inline GachaPool<type, alloc>::GachaPool(SizeType InitSize, InternalType InitVal, AllocatorType Alloc)
		: Allocator(Alloc)
		, data(new InternalType[InitSize])
		, datasize(InitSize)
	{
		_test_resize_size(this->datasize);
		for (SizeType i = 0; i < InitSize; i++) {
			this->data[i] = InitVal;
		}
	}

	template<typename type, typename alloc>
	inline GachaPool<type, alloc>::GachaPool(std::initializer_list<type> InitList)
		: Allocator(alloc())
		, data(new InternalType[InitList.size()])
		, datasize(InitList.size())
	{
		_test_resize_size(this->datasize);
		auto j = this->begin();
		for (auto i = InitList.begin(); i != InitList.end(); i++, j++) {
			(*j) = (*i);
		}
	}

	template<typename type, typename alloc>
	inline GachaPool<type, alloc>::~GachaPool(){
		delete[] this->data;
	}

	template<typename type, typename alloc>
	template<typename OtherAllocator>
	inline GachaPool<type, alloc>::GachaPool(SameType<OtherAllocator>& OtherPool, OtherAllocator Alloc)
		: Allocator(Alloc)
		, data(new InternalType[OtherPool.size()])
		, datasize(OtherPool.size())
	{
		_test_resize_size(this->datasize);
		auto j = this->begin();
		for (auto i = OtherPool.begin(); i != OtherPool.end(); i++, j++) {
			(*j) = (*i);
		}
	}

	template<typename type, typename alloc>
	template<typename OtherAllocator>
	inline GachaPool<type, alloc>::GachaPool(const SameType<OtherAllocator>& OtherPool)
		: Allocator(alloc())
		, data(new InternalType[OtherPool.size()])
		, datasize(OtherPool.size())
	{
		_test_resize_size(this->datasize);
		for (auto i = OtherPool.begin(), j = this->begin(); i != OtherPool.end(); i++, j++) {
			(*j) = (*i);
		}
	}

	template<typename type, typename alloc>
	template<typename Iterator>
	inline GachaPool<type, alloc>::GachaPool(Iterator BeginIter, Iterator EndIter, AllocatorType Alloc)
		: Allocator(Alloc)
		, data(new InternalType[std::distance(BeginIter, EndIter)])
		, datasize(std::distance(BeginIter, EndIter))
	{
		_test_resize_size(this->datasize);
		using namespace gachapoolexceptions;
		if (!(BeginIter <= EndIter)) throw UnidentifiedIteratorRange();
		auto j = this->begin();
		for (auto i = BeginIter; i != EndIter; i++, j++) {
			(*j) = (*i);
		}
	}

	template<typename type, typename alloc>
	template<typename Container>
	inline GachaPool<type, alloc>& GachaPool<type, alloc>::operator=(Container OtherContainer){
		_test_resize_size(OtherContainer.size());
		if (this->data != nullptr) delete[] this->data;
		this->data = new InternalType[OtherContainer.size()];
		this->datasize = OtherContainer.size();
		this->Allocator = alloc();
		for (DifferenceType i = 0; i < this->datasize; i++) {
			this->data[i] = OtherContainer[i];
		}
		return (*this);
	}

	template<typename type, typename alloc>
	inline GachaPool<type, alloc>& GachaPool<type, alloc>::operator=(const GachaPool<type, alloc> OtherPool){	
		_test_resize_size(OtherPool.size());
		if (this->data != nullptr) delete[] this->data;
		this->Allocator = OtherPool.Allocator;
		this->data = new InternalType[OtherPool.size()];
		this->datasize = OtherPool.size();
		auto j = this->begin();
		for (auto i = OtherPool.begin(); i != OtherPool.end(); i++, j++) {
			(*j) = (*i);
		}
		return (*this);
	}

	template<typename type, typename alloc>
	inline GachaPool<type, alloc>& GachaPool<type, alloc>::operator=(std::initializer_list<type> InitList){
		_test_resize_size(InitList.size());
		if (this->data != nullptr) delete[] this->data;
		this->Allocator = alloc();
		this->data = new InternalType[InitList.size()];
		this->datasize = InitList.size();
		auto j = this->begin();
		for (auto i = InitList.begin(); i != InitList.end(); i++, j++) {
			(*j) = (*i);
		}
		return (*this);
	}

	template<typename type, typename alloc>
	inline unsigned long long GachaPool<type, alloc>::size() const{
		return SizeType(this->datasize);
	}

	template<typename type, typename alloc>
	inline GachaPool<type, alloc>& GachaPool<type, alloc>::resize(SizeType NewSize, InternalType FillReference){
		_test_resize_size(NewSize);
		__resize(NewSize, FillReference);
		return (*this);
	}

	template<typename type, typename alloc>
	inline GachaPool<type, alloc>& GachaPool<type, alloc>::pop(){
		_test_resize_size(this->size() - 1);
		_test_pop_range(this->size() - 1, 0);
		__pop(this->size() - 1);
		return (*this);
	}

	template<typename type, typename alloc>
	inline GachaPool<type, alloc>& GachaPool<type, alloc>::pop(DifferenceType index, SizeType range){
		_test_resize_size(this->size() - (index + range));
		_test_pop_range(index, range);
		__pop(index, range);
		return (*this);
	}

	template<typename type, typename alloc>
	inline GachaPool<type, alloc>& GachaPool<type, alloc>::pop(iterator iter){
		return this->pop(iter, iter);
	}

	template<typename type, typename alloc>
	inline GachaPool<type, alloc>& GachaPool<type, alloc>::pop(const_iterator iter){
		return this->pop(iter, iter);
	}

	template<typename type, typename alloc>
	inline GachaPool<type, alloc>& GachaPool<type, alloc>::pop(reverse_iterator iter){
		return this->pop(iter, iter);
	}

	template<typename type, typename alloc>
	inline GachaPool<type, alloc>& GachaPool<type, alloc>::pop(const_reverse_iterator iter){
		return this->pop(iter, iter);
	}

	template<typename type, typename alloc>
	inline GachaPool<type, alloc>& GachaPool<type, alloc>::pop(iterator BeginIter, iterator EndIter){
		_test_resize_size(this->size() - std::distance(BeginIter, EndIter));
		_test_pop_range(BeginIter, EndIter);
		__pop(BeginIter, EndIter);
		return (*this);
	}

	template<typename type, typename alloc>
	inline GachaPool<type, alloc>& GachaPool<type, alloc>::pop(const_iterator BeginIter, const_iterator EndIter){
		return pop(_convert_iter_type(BeginIter), _convert_iter_type(EndIter));
	}

	template<typename type, typename alloc>
	inline GachaPool<type, alloc>& GachaPool<type, alloc>::pop(reverse_iterator BeginIter, reverse_iterator EndIter){
		_test_resize_size(this->size() - std::distance(BeginIter, EndIter));
		_test_pop_range(BeginIter, EndIter);
		__pop(BeginIter, EndIter);
		return (*this);
	}

	template<typename type, typename alloc>
	inline GachaPool<type, alloc>& GachaPool<type, alloc>::pop(const_reverse_iterator BeginIter, const_reverse_iterator EndIter){
		return pop(reverse_iterator(BeginIter), reverse_iterator(EndIter));
	}

	template<typename type, typename alloc>
	inline GachaPool<type, alloc>& GachaPool<type, alloc>::append(InternalType Object, SizeType Count){
		_test_resize_size(this->size() + Count);
		__append(Object, Count);
		return (*this);
	}

	template<typename type, typename alloc>
	inline type GachaPool<type, alloc>::access(DifferenceType index){
		_test_access_range(index);
		return InternalType(this->data[index]);
	}

	template<typename type, typename alloc>
	inline GachaPool<type, alloc> GachaPool<type, alloc>::access(DifferenceType index, SizeType range){
		_test_access_range(index, range);
		return GachaPool<type, alloc>(&this->data[index], &this->data[index + range]);
	}

	template<typename type, typename alloc>
	inline GachaPool<type, alloc> GachaPool<type, alloc>::access(iterator BeginIter, iterator EndIter){
		_test_access_range(BeginIter, EndIter);
		return GachaPool<type, alloc>(BeginIter, EndIter);
	}

	template<typename type, typename alloc>
	inline GachaPool<type, alloc> GachaPool<type, alloc>::access(const_iterator BeginIter, const_iterator EndIter){
		_test_access_range(_convert_iter_type(BeginIter), _convert_iter_type(EndIter));
		return GachaPool<type, alloc>(BeginIter, EndIter);
	}

	template<typename type, typename alloc>
	inline GachaPool<type, alloc> GachaPool<type, alloc>::access(reverse_iterator BeginIter, reverse_iterator EndIter){
		_test_access_range(_convert_iter_type(EndIter) + 1, _convert_iter_type(BeginIter) + 1);
		return GachaPool<type, alloc>(BeginIter, EndIter);
	}

	template<typename type, typename alloc>
	inline GachaPool<type, alloc> GachaPool<type, alloc>::access(const_reverse_iterator BeginIter, const_reverse_iterator EndIter){
		_test_access_range(_convert_iter_type(EndIter) + 1, _convert_iter_type(BeginIter) + 1);
		return GachaPool<type, alloc>(BeginIter, EndIter);
	}

	template<typename type, typename alloc>
	inline GachaPool<type, alloc>& GachaPool<type, alloc>::assign(InternalType obj, DifferenceType offset, SizeType size){
		_test_assign_range(offset, size);
		__assign(obj, offset, size);
		return (*this);
	}

	template<typename type, typename alloc>
	inline bool GachaPool<type, alloc>::verify(DifferenceType index){
		return index >= 0 && index < this->datasize;
	}

	template<typename type, typename alloc>
	inline bool GachaPool<type, alloc>::verify(iterator iter){
		return (std::distance(this->begin(), iter) >= 0 && std::distance(iter, this->end()) >= 0);
	}

	template<typename type, typename alloc>
	inline bool GachaPool<type, alloc>::verify(const_iterator iter){
		return (std::distance(this->cbegin(), iter) >= 0 && std::distance(iter, this->cend()) >= 0);
	}

	template<typename type, typename alloc>
	inline bool GachaPool<type, alloc>::verify(reverse_iterator iter){
		return (std::distance(this->rbegin(), iter) >= 0 && std::distance(iter, this->rend()) >= 0);
	}

	template<typename type, typename alloc>
	inline bool GachaPool<type, alloc>::verify(const_reverse_iterator iter){
		return (std::distance(this->crbegin(), iter) >= 0 && std::distance(iter, this->crend()) >= 0);
	}

	template<typename type, typename alloc>
	inline bool GachaPool<type, alloc>::verify(iterator BeginIter, iterator EndIter){
		return (std::distance(this->begin(), BeginIter) >= 0 && std::distance(BeginIter, this->end()) >= 0) && (std::distance(this->begin(), EndIter) >= 0 && std::distance(EndIter, this->end()) >= 0);
	}

	template<typename type, typename alloc>
	inline bool GachaPool<type, alloc>::verify(const_iterator BeginIter, const_iterator EndIter){
		return (std::distance(this->cbegin(), BeginIter) >= 0 && std::distance(BeginIter, this->cend()) >= 0) && (std::distance(this->cbegin(), EndIter) >= 0 && std::distance(EndIter, this->cend()) >= 0);
	}

	template<typename type, typename alloc>
	inline bool GachaPool<type, alloc>::verify(reverse_iterator BeginIter, reverse_iterator EndIter){
		return (std::distance(this->rbegin(), BeginIter) >= 0 && std::distance(BeginIter, this->rend()) >= 0) && (std::distance(this->rbegin(), EndIter) >= 0 && std::distance(EndIter, this->rend()) >= 0);
	}

	template<typename type, typename alloc>
	inline bool GachaPool<type, alloc>::verify(const_reverse_iterator BeginIter, const_reverse_iterator EndIter){
		return (std::distance(this->crbegin(), BeginIter) >= 0 && std::distance(BeginIter, this->crend()) >= 0) && (std::distance(this->crbegin(), EndIter) >= 0 && std::distance(EndIter, this->crend()) >= 0);
	}

	template<typename type, typename alloc>
	inline bool GachaPool<type, alloc>::dereferrencible(iterator iter){
		return (std::distance(this->begin(), iter) >= 0 && std::distance(iter, this->end()) > 0);
	}

	template<typename type, typename alloc>
	inline bool GachaPool<type, alloc>::dereferrencible(const_iterator iter){
		return (std::distance(this->cbegin(), iter) >= 0 && std::distance(iter, this->cend()) > 0);
	}

	template<typename type, typename alloc>
	inline bool GachaPool<type, alloc>::dereferrencible(reverse_iterator iter){
		return (std::distance(this->rbegin(), iter) >= 0 && std::distance(iter, this->rend()) > 0);
	}

	template<typename type, typename alloc>
	inline bool GachaPool<type, alloc>::dereferrencible(const_reverse_iterator iter){
		return (std::distance(this->crbegin(), iter) >= 0 && std::distance(iter, this->crend()) > 0);
	}

	template<typename type, typename alloc>
	inline bool GachaPool<type, alloc>::dereferrencible(iterator BeginIter, iterator EndIter){
		return (std::distance(this->begin(), BeginIter) >= 0 && std::distance(BeginIter, this->end()) > 0) && (std::distance(this->begin(), EndIter) >= 0 && std::distance(EndIter, this->end()) > 0);
	}

	template<typename type, typename alloc>
	inline bool GachaPool<type, alloc>::dereferrencible(const_iterator BeginIter, const_iterator EndIter){
		return (std::distance(this->cbegin(), BeginIter) >= 0 && std::distance(BeginIter, this->cend()) > 0) && (std::distance(this->cbegin(), EndIter) >= 0 && std::distance(EndIter, this->cend()) > 0);
	}

	template<typename type, typename alloc>
	inline bool GachaPool<type, alloc>::dereferrencible(reverse_iterator BeginIter, reverse_iterator EndIter){
		return (std::distance(this->rbegin(), BeginIter) >= 0 && std::distance(BeginIter, this->rend()) > 0) && (std::distance(this->rbegin(), EndIter) >= 0 && std::distance(EndIter, this->rend()) > 0);
	}

	template<typename type, typename alloc>
	inline bool GachaPool<type, alloc>::dereferrencible(const_reverse_iterator BeginIter, const_reverse_iterator EndIter){
		return (std::distance(this->crbegin(), BeginIter) >= 0 && std::distance(BeginIter, this->crend()) > 0) && (std::distance(this->crbegin(), EndIter) >= 0 && std::distance(EndIter, this->crend()) > 0);
	}

	template<typename type, typename alloc>
	inline type GachaPool<type, alloc>::operator[](DifferenceType index) {
		_test_access_range(index);
		return InternalType(this->data[index]);
	}

	template<typename type, typename alloc>
	inline base_iterator<type> GachaPool<type, alloc>::begin() {
		return iterator(&this->data[0]);
	}

	template<typename type, typename alloc>
	inline base_iterator<type> GachaPool<type, alloc>::end() {
		auto temp = iterator(&this->data[this->datasize]);
		return iterator(temp);
	}

	template<typename type, typename alloc>
	inline base_iterator<const type> GachaPool<type, alloc>::cbegin() const {
		return const_iterator(&data[0]);
	}

	template<typename type, typename alloc>
	inline base_iterator<const type> GachaPool<type, alloc>::cend() const {
		return const_iterator(&data[datasize]);
	}

	template<typename type, typename alloc>
	inline base_reverse_iterator<type> GachaPool<type, alloc>::rbegin(){
		return reverse_iterator(&this->data[datasize - 1]);
	}

	template<typename type, typename alloc>
	inline base_reverse_iterator<type> GachaPool<type, alloc>::rend(){
		return reverse_iterator(&this->data[-1]);
	}

	template<typename type, typename alloc>
	inline base_reverse_iterator<const type> GachaPool<type, alloc>::crbegin() const{
		return const_reverse_iterator(&this->data[datasize - 1]);
	}

	template<typename type, typename alloc>
	inline base_reverse_iterator<const type> GachaPool<type, alloc>::crend() const{
		return const_reverse_iterator(&this->data[-1]);
	}

	template<typename type, typename alloc>
	inline void GachaPool<type, alloc>::__resize(SizeType NewSize, InternalType FillReference){
		auto maxsize = NewSize < this->datasize ? NewSize : this->datasize;
		auto copy = new InternalType[this->datasize];
		for (DifferenceType i = 0; i < this->datasize; i++) {
			copy[i] = this->data[i];
		}
		delete[] this->data;
		this->data = new InternalType[NewSize];
		for (DifferenceType i = 0; i < maxsize; i++) {
			this->data[i] = copy[i];
		}
		for (DifferenceType i = maxsize; i < NewSize; i++) {
			this->data[i] = FillReference;
		}
		this->datasize = NewSize;
	}

	template<typename type, typename alloc>
	inline void GachaPool<type, alloc>::__append(InternalType Object, SizeType Count){
		auto maxsize = this->datasize + Count;
		auto copy = new InternalType[this->datasize];
		for (DifferenceType i = 0; i < this->datasize; i++) {
			copy[i] = this->data[i];
		}
		delete[] this->data;
		this->data = new InternalType[maxsize];
		for (DifferenceType i = 0; i < this->datasize; i++) {
			this->data[i] = copy[i];
		}
		for (DifferenceType i = this->datasize; i < maxsize; i++) {
			this->data[i] = Object;
		}
		this->datasize += maxsize;
	}

	template<typename type, typename alloc>
	template<typename Iterator>
	inline GachaPool<type, alloc>& GachaPool<type, alloc>::append(Iterator BeginIter, Iterator EndIter){
		_test_resize_size(this->size() + std::distance(BeginIter, EndIter));
		_test_append_range(BeginIter, EndIter);
		__append(BeginIter, EndIter);
		return (*this);
	}

	template<typename type, typename alloc>
	template<typename Iterator>
	inline GachaPool<type, alloc>& GachaPool<type, alloc>::assign(Iterator BeginIter, Iterator EndIter, DifferenceType offset){
		_test_assign_range(offset, SizeType(std::distance(BeginIter, EndIter)));
		__assign(BeginIter, EndIter, offset);
		return (*this);
	}

	template<typename type, typename alloc>
	template<typename ...ArgumentType>
	inline GachaPool<type, alloc>& GachaPool<type, alloc>::assign(DifferenceType offset, SizeType range, InternalType(*function)(ArgumentType...), ArgumentType ...Args){
		_test_assign_range(offset, range);
		__assign(offset, range, function, Args);
		return (*this);
	}

	template<typename type, typename alloc>
	template<typename Container>
	inline GachaPool<type, alloc>& GachaPool<type, alloc>::copy(Container target){
		return this->apparent_copy(target);
	}

	template<typename type, typename alloc>
	template<typename Iterator>
	inline GachaPool<type, alloc>& GachaPool<type, alloc>::copy(Iterator BeginIter, Iterator EndIter){
		return this->apparent_copy(BeginIter, EndIter);
	}

	template<typename type, typename alloc>
	template<typename Container>
	inline GachaPool<type, alloc>& GachaPool<type, alloc>::apparent_copy(Container target){
		_test_apparent_copy_size(target.size());
		__apparent_copy(target);
		return (*this);
	}

	template<typename type, typename alloc>
	template<typename Iterator>
	inline GachaPool<type, alloc>& GachaPool<type, alloc>::apparent_copy(Iterator BeginIter, Iterator EndIter){
		_test_apparent_copy_size(std::distance(BeginIter, EndIter));
		__apparent_copy(BeginIter, EndIter);
		return (*this);
	}

	template<typename type, typename alloc>
	template<typename Iterator>
	inline void GachaPool<type, alloc>::__append(Iterator BeginIter, Iterator EndIter) {
		auto maxsize = this->datasize + SizeType(std::distance(BeginIter, EndIter));
		auto copy = new InternalType[this->datasize];
		for (DifferenceType i = 0; i < this->datasize; i++) {
			copy[i] = this->data[i];
		}
		delete[] this->data;
		this->data = new InternalType[maxsize];
		for (DifferenceType i = 0; i < this->datasize; i++) {
			this->data[i] = copy[i];
		}
		auto j = BeginIter;
		for (DifferenceType i = this->datasize; j != EndIter; i++, j++) {
			this->data[i] = (*j);
		}
		this->datasize = maxsize;
	}

	template<typename type, typename alloc>
	template<typename Iterator>
	inline void GachaPool<type, alloc>::__assign(Iterator BeginIter, Iterator EndIter, DifferenceType offset){
		auto j = BeginIter;
		for (DifferenceType i = offset; j != EndIter; i++, j++) {
			this->data[i] = (*j);
		}
	}

	template<typename type, typename alloc>
	template<typename ...ArgumentType>
	inline void GachaPool<type, alloc>::__assign(DifferenceType offset, SizeType range, InternalType(*function)(ArgumentType...), ArgumentType ...arguments){
		for (DifferenceType i = offset; i < (offset + range); i++) {
			this->data[i] = function(arguments);
		}
	}

	template<typename type, typename alloc>
	template<typename Container>
	inline void GachaPool<type, alloc>::__apparent_copy(Container target){
		for (DifferenceType i = 0; i < target.size(); i++) {
			this->data[i] = target[i];
		}
	}

	template<typename type, typename alloc>
	template<typename Iterator>
	inline void GachaPool<type, alloc>::__apparent_copy(Iterator BeginIter, Iterator EndIter){
		auto range = std::distance(BeginIter, EndIter);
		auto anchor = BeginIter;
		for (DifferenceType i = 0; i < range; i++, anchor++) {
			this->data[i] = (*anchor);
		}
	}

	template<typename type, typename alloc>
	template<typename Iterator>
	inline base_iterator<type> GachaPool<type, alloc>::_convert_iter_type(Iterator type){
		using namespace gachapoolexceptions;
		if (typeid(Iterator) == typeid(const_iterator)) return iterator(type.GetPtr());
		else if (typeid(Iterator) == typeid(reverse_iterator)) return iterator(type.GetPtr());
		else if (typeid(Iterator) == typeid(const_reverse_iterator)) return iterator(type.GetPtr());
		else throw CannotConvertToKnownIterator();
	}

	template<typename type, typename alloc>
	template<typename Iterator>
	inline void GachaPool<type, alloc>::_test_append_range(Iterator BeginIter, Iterator EndIter){
		using namespace gachapoolexceptions;
		if (std::distance(BeginIter, EndIter) < 0) throw UnidentifiedIteratorRange();
	}

	template<typename type, typename alloc>
	inline void GachaPool<type, alloc>::__pop(DifferenceType index, SizeType range){
		auto copy = new InternalType[this->datasize];
		auto NewSize = this->datasize - (range + 1);
		for (DifferenceType i = 0; i < this->datasize; i++) {
			copy[i] = this->data[i];
		}
		delete[] this->data;
		this->data = new InternalType[NewSize];
		for (DifferenceType i = 0; i < index; i++) {
			this->data[i] = copy[i];
		}
		for (DifferenceType i = index, j = index + (range + 1); i < NewSize; i++, j++) {
			this->data[i] = copy[j];
		}
		this->datasize = NewSize;
	}

	template<typename type, typename alloc>
	inline void GachaPool<type, alloc>::__pop(iterator BeginIter, iterator EndIter){
		auto dodgerange = std::distance(BeginIter, EndIter) + 1;
		auto NewSize = this->datasize - dodgerange;
		auto begin = std::distance(this->begin(), BeginIter);
		auto end = begin + dodgerange;
		auto copy = new InternalType[this->datasize];
		for (DifferenceType i = 0; i < this->datasize; i++) {
			copy[i] = this->data[i];
		}
		delete[] this->data;
		this->data = new InternalType[NewSize];
		for (DifferenceType i = 0; i < begin; i++) {
			this->data[i] = copy[i];
		}
		for (DifferenceType i = begin, j = end; i < NewSize; i++, j++) {
			this->data[i] = copy[j];
		}
		this->datasize = NewSize;
	}

	template<typename type, typename alloc>
	inline void GachaPool<type, alloc>::__pop(reverse_iterator BeginIter, reverse_iterator EndIter){
		auto dodgerange = std::distance(BeginIter, EndIter) + 1;
		auto NewSize = this->datasize - dodgerange;
		auto end = std::distance(this->rbegin(), BeginIter);
		auto begin = end + dodgerange - 1;
		auto copy = new InternalType[this->datasize];
		for (DifferenceType i = 0; i < this->datasize; i++) {
			copy[i] = this->data[i];
		}
		delete[] this->data;
		this->data = new InternalType[NewSize];
		for (DifferenceType i = 0; i < begin; i++) {
			this->data[i] = copy[i];
		}
		for (DifferenceType i = begin, j = end; i < NewSize; i++, j++) {
			this->data[i] = copy[j];
		}
		this->datasize = NewSize;
	}

	template<typename type, typename alloc>
	inline void GachaPool<type, alloc>::__assign(InternalType obj, DifferenceType offset, SizeType range){
		for (DifferenceType i = offset; i < (offset + range); i++) {
			this->data[i] = obj;
		}
	}

	template<typename type, typename alloc>
	inline void GachaPool<type, alloc>::__flush(){
		delete[] this->data;
		this->datasize = 0;
	}

	template<typename type, typename alloc>
	inline void GachaPool<type, alloc>::_test_resize_size(SizeType NewSize){
		using namespace gachapoolexceptions;
		if (NewSize < this->minsize()) throw IllegalZeroSize();
		else if (NewSize > this->maxsize()) throw SizeBeyondMaximum();
	}

	template<typename type, typename alloc>
	inline void GachaPool<type, alloc>::_test_pop_range(DifferenceType index, SizeType range){
		using namespace gachapoolexceptions;
		if (index >= this->datasize) throw IndexOutOfRange();
		else if (index + range >= this->datasize) throw IndexOutOfRange();
	}

	template<typename type, typename alloc>
	inline void GachaPool<type, alloc>::_test_pop_range(iterator BeginIter, iterator EndIter){
		using namespace gachapoolexceptions;
		if (std::distance(BeginIter, EndIter) < 0) throw UnidentifiedIteratorRange();
		else if (std::distance(this->begin(), BeginIter) < 0) throw IteratorOutOfRange();
		else if (std::distance(EndIter, this->end()) < 0) throw IteratorOutOfRange();
	}

	template<typename type, typename alloc>
	inline void GachaPool<type, alloc>::_test_pop_range(reverse_iterator BeginIter, reverse_iterator EndIter){
		using namespace gachapoolexceptions;
		if (std::distance(BeginIter, EndIter) < 0) throw UnidentifiedIteratorRange();
		else if (std::distance(this->rbegin(), BeginIter) < 0) throw IteratorOutOfRange();
		else if (std::distance(EndIter, this->rend()) < 0) throw IteratorOutOfRange();
	}

	template<typename type, typename alloc>
	inline void GachaPool<type, alloc>::_test_access_range(DifferenceType index){
		using namespace gachapoolexceptions;
		if (index >= this->datasize) throw IndexOutOfRange();
	}

	template<typename type, typename alloc>
	inline void GachaPool<type, alloc>::_test_access_range(DifferenceType index, SizeType count){
		using namespace gachapoolexceptions;
		if (index >= this->datasize) throw IndexOutOfRange();
		else if (index + count >= this->datasize) throw IndexOutOfRange();
	}

	template<typename type, typename alloc>
	inline void GachaPool<type, alloc>::_test_aceess_range(iterator BeginIter, iterator EndIter){
		using namespace gachapoolexceptions;
		if (std::distance(BeginIter, EndIter) < 0) throw UnidentifiedIteratorRange();
		else if (std::distance(this->begin(), BeginIter) < 0) throw IteratorOutOfRange();
		else if (std::distance(EndIter, this->end()) > this->datasize) throw IteratorOutOfRange();
	}

	template<typename type, typename alloc>
	inline void GachaPool<type, alloc>::_test_assign_range(DifferenceType Offset, SizeType Range){
		using namespace gachapoolexceptions;
		if (Offset < 0 || Offset >= this->datasize) throw AssignOffsetOutOfRange();
		else if ((Offset + Range) < 0 || (Offset + Range) > datasize) throw AssignSizeOutOfRange();
	}

	template<typename type, typename alloc>
	inline void GachaPool<type, alloc>::_test_apparent_copy_size(SizeType CopySize){
		using namespace gachapoolexceptions;
		if (CopySize > this->maxsize()) throw SizeBeyondMaximum();
		else if (CopySize > this->datasize) throw CopySizeBeyondAllocation();
		else if (CopySize != this->datasize) throw CopySizeMismatch();
	}

	template<typename type, typename alloc>
	inline void GachaPool<type, alloc>::_test_hard_copy_size(SizeType CopySize){
		using namespace gachapoolexceptions;
		if (CopySize > this->maxsize()) throw SizeBeyondMaximum();
	}

};
#endif // !GACHACORE_HXX

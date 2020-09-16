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

		SizeType size() const;
		GachaPool<type, alloc>& resize(SizeType NewSize, InternalType FillReference = InternalType());
		GachaPool<type, alloc>& pop(DifferenceType index, SizeType range);
		GachaPool<type, alloc>& pop(iterator BeginIter, iterator EndIter);
		GachaPool<type, alloc>& append(InternalType Object, SizeType Count);
		template<typename Iterator>
		GachaPool<type, alloc>& append(Iterator BeginIter, Iterator EndIter);

		InternalType operator [](DifferenceType index);

		iterator begin();
		iterator end();
	protected:
		void __resize(SizeType NewSize, InternalType FillReference);
		void __append(InternalType Object, SizeType Count = 1);
		template<typename Iterator>
		void __append(Iterator BeginIter, Iterator EndIter);
		void __pop(DifferenceType index, SizeType range = 0);
		void __pop(iterator BeginIter, iterator EndIter);
	private:
		InternalType* data;
		SizeType datasize;
		AllocatorType Allocator;
	};

	template<typename type, typename alloc>
	inline GachaPool<type, alloc>::GachaPool(SizeType InitSize, InternalType InitVal)
		: Allocator(alloc())
		, data(new InternalType[InitSize])
		, datasize(InitSize)
	{
		for (SizeType i = 0; i < InitSize; i++) {
			data[i] = InitVal;
		}
	}

	template<typename type, typename alloc>
	inline GachaPool<type, alloc>::GachaPool(SizeType InitSize, InternalType InitVal, AllocatorType Alloc)
		: Allocator(Alloc)
		, data(new InternalType[InitSize])
		, datasize(InitSize)
	{
		for (SizeType i = 0; i < InitSize; i++) {
			data[i] = InitVal;
		}
	}

	template<typename type, typename alloc>
	inline GachaPool<type, alloc>::GachaPool(std::initializer_list<type> InitList)
		: Allocator(alloc())
		, data(new InternalType[InitList.size()])
		, datasize(InitList.size())
	{
		auto j = this->begin();
		for (auto i = InitList.begin(); i != InitList.end(); i++, j++) {
			(*j) = (*i);
		}
	}

	template<typename type, typename alloc>
	inline GachaPool<type, alloc>::~GachaPool(){
		delete[] data;
	}

	template<typename type, typename alloc>
	template<typename OtherAllocator>
	inline GachaPool<type, alloc>::GachaPool(SameType<OtherAllocator>& OtherPool, OtherAllocator Alloc)
		: Allocator(Alloc)
		, data(new InternalType[OtherPool.size()])
		, datasize(OtherPool.size())
	{
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
		auto j = this->begin();
		for (auto i = BeginIter; i != EndIter; i++, j++) {
			(*j) = (*i);
		}
	}

	template<typename type, typename alloc>
	inline GachaPool<type, alloc>& GachaPool<type, alloc>::operator=(const GachaPool<type, alloc> OtherPool){	
		if (data != nullptr) delete[] data;
		Allocator = OtherPool.Allocator;
		data = new InternalType[OtherPool.size()];
		datasize = OtherPool.size();
		auto j = this->begin();
		for (auto i = OtherPool.begin(); i != OtherPool.end(); i++, j++) {
			(*j) = (*i);
		}
		return (*this);
	}

	template<typename type, typename alloc>
	inline unsigned long long GachaPool<type, alloc>::size() const{
		return SizeType(datasize);
	}

	template<typename type, typename alloc>
	inline GachaPool<type, alloc>& GachaPool<type, alloc>::resize(SizeType NewSize, InternalType FillReference){
		__resize(NewSize, FillReference);
		return (*this);
	}

	template<typename type, typename alloc>
	inline GachaPool<type, alloc>& GachaPool<type, alloc>::pop(DifferenceType index, SizeType range){
		__pop(index, range);
		return (*this);
	}

	template<typename type, typename alloc>
	inline GachaPool<type, alloc>& GachaPool<type, alloc>::pop(iterator BeginIter, iterator EndIter){
		__pop(BeginIter, EndIter);
		return (*this);
	}

	template<typename type, typename alloc>
	inline GachaPool<type, alloc>& GachaPool<type, alloc>::append(InternalType Object, SizeType Count){
		__append(Object, Count);
		return (*this);
	}

	template<typename type, typename alloc>
	inline type GachaPool<type, alloc>::operator[](DifferenceType index) {
		return InternalType(data[index]);
	}

	template<typename type, typename alloc>
	inline base_iterator<type> GachaPool<type, alloc>::begin() {
		return iterator(&data[0]);
	}

	template<typename type, typename alloc>
	inline base_iterator<type> GachaPool<type, alloc>::end() {
		auto temp = iterator(&data[datasize]);
		return iterator(temp);
	}

	template<typename type, typename alloc>
	inline void GachaPool<type, alloc>::__resize(SizeType NewSize, InternalType FillReference){
		auto maxsize = NewSize < datasize ? NewSize : datasize;
		auto copy = new InternalType[datasize];
		for (int i = 0; i < datasize; i++) {
			copy[i] = data[i];
		}
		delete[] data;
		data = new InternalType[NewSize];
		for (int i = 0; i < maxsize; i++) {
			data[i] = copy[i];
		}
		for (int i = maxsize; i < NewSize; i++) {
			data[i] = FillReference;
		}
		datasize = NewSize;
	}

	template<typename type, typename alloc>
	inline void GachaPool<type, alloc>::__append(InternalType Object, SizeType Count){
		auto maxsize = datasize + Count;
		auto copy = new InternalType[datasize];
		for (int i = 0; i < datasize; i++) {
			copy[i] = data[i];
		}
		delete[] data;
		data = new InternalType[maxsize];
		for (int i = 0; i < datasize; i++) {
			data[i] = copy[i];
		}
		for (int i = datasize; i < maxsize; i++) {
			data[i] = Object;
		}
		datasize += maxsize;
	}

	template<typename type, typename alloc>
	template<typename Iterator>
	inline GachaPool<type, alloc>& GachaPool<type, alloc>::append(Iterator BeginIter, Iterator EndIter){
		__append(BeginIter, EndIter);
		return (*this);
	}

	template<typename type, typename alloc>
	template<typename Iterator>
	inline void GachaPool<type, alloc>::__append(Iterator BeginIter, Iterator EndIter) {
		auto maxsize = datasize + SizeType(std::distance(BeginIter, EndIter));
		auto copy = new InternalType[datasize];
		for (int i = 0; i < datasize; i++) {
			copy[i] = data[i];
		}
		delete[] data;
		data = new InternalType[maxsize];
		for (int i = 0; i < datasize; i++) {
			data[i] = copy[i];
		}
		for (int i = 0, j = datasize; j < maxsize; i++, j++) {
			data[j] = (*(BeginIter + i));
		}
		datasize = maxsize;
	}

	template<typename type, typename alloc>
	inline void GachaPool<type, alloc>::__pop(DifferenceType index, SizeType range){
		auto copy = new InternalType[datasize];
		auto NewSize = datasize - range;
		for (int i = 0; i < datasize; i++) {
			copy[i] = data[i];
		}
		delete[] data;
		data = new InternalType[NewSize];
		for (int i = 0; i < index; i++) {
			data[i] = copy[i];
		}
		for (int i = index, j = index + range; i < NewSize; i++, j++) {
			data[i] = copy[j];
		}
		datasize = NewSize;
	}

	template<typename type, typename alloc>
	inline void GachaPool<type, alloc>::__pop(iterator BeginIter, iterator EndIter){
		auto dodgerange = std::distance(BeginIter, EndIter);
		auto NewSize = datasize - dodgerange;
		auto begin = std::distance(this->begin(), BeginIter);
		auto end = begin + dodgerange;
		auto copy = new InternalType[datasize];
		for (int i = 0; i < datasize; i++) {
			copy[i] = data[i];
		}
		delete[] data;
		data = new InternalType[NewSize];
		for (int i = 0; i < begin; i++) {
			data[i] = copy[i];
		}
		for (int i = begin, j = end; i < NewSize; i++, j++) {
			data[i] = copy[j];
		}
		datasize = NewSize;
	}

};
#endif // !GACHACORE_HXX

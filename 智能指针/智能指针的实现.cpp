#include<iostream>
#include<memory>

template<typename T>
class SmartPointer {
public:
	SmartPointer(T* ptr = nullptr) :_ptr(ptr) {
		if (_ptr) {
			_count = new size_t(1);
		}
		else {
			_count = new size_t(0);
		}
	}

	SmartPointer(const SmartPointer& ptr) {
		if (this != &ptr) {
			this->_ptr = ptr._ptr;
			this->_count = ptr._count;
			(*this->_count)++;
		}
	}

	SmartPointer& operator=(const SmartPointer& ptr) {
		if (this->_ptr == ptr._ptr) {
			return *this;
		}

		//等号左值引用减1，等号右边引用加1
		if (this->_ptr) {
			(*this->_count)--; 
			if (this->_count == 0) {
				delete this->_ptr;
				delete this->_count;
			}
		}

		//将右值赋值给左值，引用次数加1
		this->_ptr = ptr._ptr;
		this->_count = ptr._count;
		(*this->_count)++;

		return *this;
	}

	T& operator*() {
		assert(this->_ptr == nullptr);
		return this->_ptr;
	}

	~SmartPointer() {
		(*this->_count)--;
		if(*this->_count == 0){
			delete this->_ptr;
			delete this->_count;
		}
	}
	
	size_t use_count() {
		return *this->_count;
	}

private:
	T* _ptr;
	size_t* _count;
};

int main() {
	{
		SmartPointer<int> sp(new int(10));
		SmartPointer<int> sp2(sp);
		SmartPointer<int> sp3(new int(20));
		std::cout << sp.use_count() << std::endl;   //2
		std::cout << sp2.use_count() << std::endl;  //2
		// 在这之前，sp2的引用计数和sp相同
		sp2 = sp3;
		//在这之后，sp2的引用计数和sp3相同
		std::cout << sp.use_count() << std::endl;   //1
		std::cout << sp2.use_count() << std::endl;  //2
		std::cout << sp3.use_count() << std::endl;  //2
	}
	//释放内存

	int temp;
	std::cin >> temp;

	return 0;
}
#ifndef VTX_ALLOCATOR_H
#define VTX_ALLOCATOR_H

#include <core/vtx_atomic.h>
namespace core
{
	class Allocator
	{
	public:
		virtual void *allocate(core::U32_t size) = 0;
		virtual void deallocate(void *p) = 0;
		virtual core::U32_t allocatedSize() = 0;



		// ----------------
		// Find out how to solve this template idea.
		// I have two issues with the current approach:
		// 1. I dont want to have to create another overload when another number of arguments are to be passed to the constructor.
		// 2. Its not applicable for me to always use const parameters.
		
		template <class T>
		T *newInstance()
		{
			return new (this->allocate(sizeof(T))) T;
		}

		template <class T, class TArg1>
		T *newInstance(const TArg1 &arg1)
		{
			return new (this->allocate(sizeof(T))) T(arg1);
		}
		
		template <class T, class TArg1, class TArg2>
		T *newInstance(TArg1 &arg1, TArg2 &arg2)
		{
			return new (this->allocate(sizeof(T))) T(arg1, arg2);
		}

		// ------------------


		template <class T>
		void deleteInstance(T *instance)
		{
			if(instance)
			{
				instance->~T();
				this->deallocate(instance);
			}
		}

	};
}

#endif
#ifndef VTX_VECTOR2_H
#define VTX_VECTOR2_H

namespace core
{
	template <class T>
	class Vector2
	{
	public:
		Vector2()
		{
		}

		Vector2( T x, T y )
		{
			this->x = x;
			this->y = y;
		}

		void add( Vector2 &other, Vector2 &result )
		{
			result.x = this->x + other.x;
			result.y = this->y + other.y;
		}

		void subtract( Vector2 &other, Vector2 &result )
		{
			result.x = this->x - other.x;
			result.y = this->y - other.y;
		}

		void lerp( Vector2 &other, Vector2 &result, T amount )
		{
			result.x = this->x + ((other.x - this->x) * amount);
			result.y = this->y + ((other.y - this->y) * amount);
		}

		void multiply( Vector2 &other, Vector2 &result )
		{
			result.x = this->x * other.x;
			result.y = this->y * other.y;
		}

		void multiply( T value, Vector2 &result )
		{
			result.x = this->x * value;
			result.y = this->y * value;
		}

		T x;
		T y;
	};
}

#endif
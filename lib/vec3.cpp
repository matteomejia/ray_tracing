#include "vec3.h"

vec3::vec3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

float vec3::prod_punto(vec3 v)
{
	return x * v.x + y * v.y + z * v.z;
}

vec3 vec3::prod_cruz(vec3 v)
{
	return { y * v.z - v.y * z, v.x * z - x * v.z, x * v.y - v.x * y };
}

vec3 vec3::operator+(vec3 v)
{
	return { x + v.x, y + v.y, z + v.z };
}

vec3 vec3::operator-()
{
	return { -x, -y, -z };
}

vec3 vec3::operator-(vec3 v)
{
	return { x - v.x, y - v.y, z - v.z };
}

vec3 vec3::operator*(float s)
{
	return { x * s, y * s, z * s };
}

vec3 vec3::operator*(vec3 v)
{
	return { x * v.x, y * v.y, z * v.z };
}

vec3 vec3::operator/(float s)
{
	return { x / s, y / s, z / s };
}

double vec3::dist() const
{
	return sqrt(x * x + y * y + z * z);
}

void vec3::normalize()
{
	double m = dist();
	x = x / m;
	y = y / m;
	z = z / m;
}

void vec3::max_to_one()
{
	float max_value = std::max(x, std::max(y, z));
	if (max_value > 1.0)
	{
		x = x / max_value;
		y = y / max_value;
		z = z / max_value;
	}
}

vec3 operator*(float f, vec3& v)
{
	return vec3(v.x * f, v.y * f, v.z * f);
}

vec3 operator/(float f, vec3& v)
{
	if (v.x == 0 || v.y == 0 || v.z == 0)
	{
		std::cout << "Hay cero";
	}
	float tx = (v.x == 0) ? f / 0.01 : f / v.x;
	float ty = (v.y == 0) ? f / 0.01 : f / v.y;
	float tz = (v.z == 0) ? f / 0.01 : f / v.z;

	return vec3(tx, ty, tz);
}

vec3 abs(vec3& v)
{
	return vec3(abs(v.x), abs(v.y), abs(v.z));
}

vec3 sign(vec3& v)
{
	return vec3(sgn(v.x), sgn(v.y), abs(v.z));
}

vec3 step(vec3 v1, vec3 v2)
{
	return vec3(v2.x < v1.x ? 0 : 1,
		v2.y < v1.y ? 0 : 1,
		v2.z < v1.z ? 0 : 1);
}

std::ostream& operator<<(std::ostream& os, const vec3& v)
{
	os << v.x << " " << v.y << " " << v.z;
	return os;
}
#ifndef SIMD_FLOAT
#define SIMD_FLOAT

#include <emmintrin.h>

class SIMDFloat {
private:
	__m128 value;
	union accessUnion {
		__m128 simd;
		float values[4];
	};
public:
	__forceinline SIMDFloat() {
		value = _mm_set1_ps(0.0f); 
	}
	__forceinline SIMDFloat(float v) {
		value = _mm_set1_ps(v);
	}
	__forceinline SIMDFloat(__m128 v) {
		value = v;
	}
	__forceinline void set(float v) noexcept {
		value = _mm_set1_ps(v);
	}
	__forceinline void set(float v, size_t index) noexcept {
		accessUnion access{ value };
		access.values[index] = v;
		value = access.simd;
	}
	__forceinline void set(float* v) noexcept {
		value = _mm_set_ps(v[0], v[1], v[2], v[3]);
	}
	__forceinline float get(size_t index) const noexcept {
		accessUnion access{ value };
		return access.values[index];
	}
	__forceinline float* get() const noexcept {
		accessUnion access{ value };
		return access.values;
	}

	static __forceinline __m128 add(__m128 a, __m128 b) noexcept {
		return _mm_add_ps(a, b);
	}
	static __forceinline __m128 add(__m128 a, float b) noexcept {
		return _mm_add_ps(a, _mm_set1_ps(b));
	}
	static __forceinline __m128 sub(__m128 a, __m128 b) noexcept {
		return _mm_sub_ps(a, b);
	}
	static __forceinline __m128 sub(__m128 a, float b) noexcept {
		return _mm_sub_ps(a, _mm_set1_ps(b));
	}
	static __forceinline __m128 mul(__m128 a, __m128 b) noexcept {
		return _mm_mul_ps(a, b);
	}
	static __forceinline __m128 mul(__m128 a, float b) noexcept {
		return _mm_mul_ps(a, _mm_set1_ps(b));
	}
	static __forceinline __m128 div(__m128 a, __m128 b) noexcept {
		return _mm_div_ps(a, b);
	}
	static __forceinline __m128 div(__m128 a, float b) noexcept {
		return _mm_div_ps(a, _mm_set1_ps(b));
	}
	static __forceinline __m128 min(__m128 a, __m128 b) noexcept {
		return _mm_min_ps(a, b);
	}
	static __forceinline __m128 min(__m128 a, float b) noexcept {
		return _mm_min_ps(a, _mm_set1_ps(b));
	}
	static __forceinline __m128 max(__m128 a, __m128 b) noexcept {
		return _mm_max_ps(a, b);
	}
	static __forceinline __m128 max(__m128 a, float b) noexcept {
		return _mm_max_ps(a, _mm_set1_ps(b));
	}

	__forceinline SIMDFloat& operator=(float other) noexcept {
		value = _mm_set1_ps(other);
		return SIMDFloat(other);
	}

	__forceinline SIMDFloat operator+(const SIMDFloat& rhs) {
		return SIMDFloat(add(value, rhs.value));
	}
	__forceinline SIMDFloat operator+(const float& rhs) {
		return SIMDFloat(add(value, rhs));
	}
	__forceinline SIMDFloat& operator+=(const SIMDFloat& rhs) {
		value = add(value, rhs.value);
		return *this;
	}
	__forceinline SIMDFloat& operator+=(const float& rhs) {
		value = add(value, _mm_set1_ps(rhs));
		return *this;
	}

	__forceinline SIMDFloat operator-(const SIMDFloat& rhs) {
		return SIMDFloat(sub(value, rhs.value));
	}
	__forceinline SIMDFloat operator-(const float& rhs) {
		return SIMDFloat(sub(value, rhs));
	}
	__forceinline SIMDFloat& operator-=(const SIMDFloat& rhs) {
		value = sub(value, rhs.value);
		return *this;
	}
	__forceinline SIMDFloat& operator-=(const float& rhs) {
		value = sub(value, _mm_set1_ps(rhs));
		return *this;
	}

	__forceinline SIMDFloat operator*(const SIMDFloat& rhs) {
		return SIMDFloat(mul(value, rhs.value));
	}
	__forceinline SIMDFloat operator*(const float& rhs) {
		return SIMDFloat(mul(value, rhs));
	}
	__forceinline SIMDFloat& operator*=(const SIMDFloat& rhs) {
		value = mul(value, rhs.value);
		return *this;
	}
	__forceinline SIMDFloat& operator*=(const float& rhs) {
		value = mul(value, _mm_set1_ps(rhs));
		return *this;
	}

	__forceinline SIMDFloat operator/(const SIMDFloat& rhs) {
		return SIMDFloat(div(value, rhs.value));
	}
	__forceinline SIMDFloat operator/(const float& rhs) {
		return SIMDFloat(div(value, rhs));
	}
	__forceinline SIMDFloat& operator/=(const SIMDFloat& rhs) {
		value = div(value, rhs.value);
		return *this;
	}
	__forceinline SIMDFloat& operator/=(const float& rhs) {
		value = div(value, _mm_set1_ps(rhs));
		return *this;
	}
};
#endif
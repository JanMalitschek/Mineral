#ifndef SIMD_INT
#define SIMD_INT

#include <emmintrin.h>

class SIMDInt {
private:
	__m128i value;
	union accessUnion {
		__m128i simd;
		int values[4];
	};
public:
	__forceinline SIMDInt() {
		value = _mm_set1_epi32(0);
	}
	__forceinline SIMDInt(int v) {
		value = _mm_set1_epi32(v);
	}
	__forceinline SIMDInt(__m128i v) {
		value = v;
	}
	__forceinline void set(int v) noexcept {
		value = _mm_set1_epi32(v);
	}
	__forceinline void set(int v, size_t index) noexcept {
		accessUnion access{ value };
		access.values[index] = v;
		value = access.simd;
	}
	__forceinline void set(int* v) noexcept {
		value = _mm_set_epi32(v[0], v[1], v[2], v[3]);
	}
	__forceinline float get(size_t index) const noexcept {
		accessUnion access{ value };
		return access.values[index];
	}
	__forceinline int* get() const noexcept {
		accessUnion access{ value };
		return access.values;
	}

	static __forceinline __m128i add(__m128i a, __m128i b) noexcept {
		return _mm_add_epi32(a, b);
	}
	static __forceinline __m128i add(__m128i a, int b) noexcept {
		return _mm_add_epi32(a, _mm_set1_epi32(b));
	}
	static __forceinline __m128i sub(__m128i a, __m128i b) noexcept {
		return _mm_sub_epi32(a, b);
	}
	static __forceinline __m128i sub(__m128i a, int b) noexcept {
		return _mm_sub_epi32(a, _mm_set1_epi32(b));
	}
	static __forceinline __m128i mul(__m128i a, __m128i b) noexcept {
		return _mm_mul_epu32(a, b);
	}
	static __forceinline __m128i mul(__m128i a, int b) noexcept {
		return _mm_mul_epu32(a, _mm_set1_epi32(b));
	}
	static __forceinline __m128i min(__m128i a, __m128i b) noexcept {
		return _mm_min_epi16(a, b);
	}
	static __forceinline __m128i min(__m128i a, int b) noexcept {
		return _mm_min_epi16(a, _mm_set1_epi32(b));
	}
	static __forceinline __m128i max(__m128i a, __m128i b) noexcept {
		return _mm_max_epi16(a, b);
	}
	static __forceinline __m128i max(__m128i a, int b) noexcept {
		return _mm_max_epi16(a, _mm_set1_epi32(b));
	}

	__forceinline SIMDInt& operator=(int other) noexcept {
		value = _mm_set1_epi32(other);
		return SIMDInt(other);
	}

	__forceinline SIMDInt operator+(const SIMDInt& rhs) {
		return SIMDInt(add(value, rhs.value));
	}
	__forceinline SIMDInt operator+(const float& rhs) {
		return SIMDInt(add(value, rhs));
	}
	__forceinline SIMDInt& operator+=(const SIMDInt& rhs) {
		value = add(value, rhs.value);
		return *this;
	}
	__forceinline SIMDInt& operator+=(const float& rhs) {
		value = add(value, _mm_set1_epi32(rhs));
		return *this;
	}

	__forceinline SIMDInt operator-(const SIMDInt& rhs) {
		return SIMDInt(sub(value, rhs.value));
	}
	__forceinline SIMDInt operator-(const float& rhs) {
		return SIMDInt(sub(value, rhs));
	}
	__forceinline SIMDInt& operator-=(const SIMDInt& rhs) {
		value = sub(value, rhs.value);
		return *this;
	}
	__forceinline SIMDInt& operator-=(const float& rhs) {
		value = sub(value, _mm_set1_epi32(rhs));
		return *this;
	}

	__forceinline SIMDInt operator*(const SIMDInt& rhs) {
		return SIMDInt(mul(value, rhs.value));
	}
	__forceinline SIMDInt operator*(const float& rhs) {
		return SIMDInt(mul(value, rhs));
	}
	__forceinline SIMDInt& operator*=(const SIMDInt& rhs) {
		value = mul(value, rhs.value);
		return *this;
	}
	__forceinline SIMDInt& operator*=(const float& rhs) {
		value = mul(value, _mm_set1_epi32(rhs));
		return *this;
	}
};
#endif
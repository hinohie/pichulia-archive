 /**
  * Copyright (c) 2022. Eunki Hong @pichulia
  *
  * CC BY-SA 4.0 License.
  * You are free to:
  *  - Share — copy and redistribute the material in any medium or format
  *  - Adapt — remix, transform, and build upon the material
  *   for any purpose, even commercially.
  * The licensor cannot revoke these freedoms as long as you follow the license terms.
  * Under the following terms:
  *  - Attribution — You must give appropriate credit, provide a link to the license,
  *   and indicate if changes were made. You may do so in any reasonable manner,
  *  but not in any way that suggests the licensor endorses you or your use.
  * - ShareAlike — If you remix, transform, or build upon the material,
  *  you must distribute your contributions under the same license as the original.
  * - No additional restrictions — You may not apply legal terms or technological measures
  *  that legally restrict others from doing anything the license permits.
  *  - Notices — You do not have to comply with the license for elements of the material
  *  in the public domain or where your use is permitted by an applicable exception or limitation.
  *  No warranties are given. The license may not give you all of
  * the permissions necessary for your intended use. For example,
  * other rights such as publicity, privacy, or moral rights may limit how you use the material.
  * You can find the full license text at https://creativecommons.org/licenses/by-sa/4.0/legalcode
  */

#include<algorithm>
#include<math.h>
using namespace std;
using lld = long long int;
using pll = pair<lld, lld>;
using lf = double;
struct vec2 {
	lld x, y;
	vec2() { x = y = 0; }
	vec2(lld x, lld y) :x(x), y(y) {}
	vec2 operator +(const vec2& z) const {
		return vec2(x + z.x, y + z.y);
	}
	vec2 operator -(const vec2& z) const {
		return vec2(x - z.x, y - z.y);
	}
	vec2 operator -() const {
		return vec2(-x, -y);
	}
	lld operator *(const vec2& z)const {
		return x * z.x + y * z.y;
	}
	lld operator %(const vec2& z)const {
		return x * z.y - y * z.x;
	}
	vec2 operator *(const lld z) const{
		return vec2(x * z, y * z);
	}
	bool operator <(const vec2& z)const {
		if (x - z.x)return x < z.x;
		return y < z.y;
	}
	bool operator ==(const vec2 &z)const{
		return (x == z.x && y == z.y);
	}
	lf dist(vec2 p = vec2()) const {
		lld xx = x - p.x;
		lld yy = y - p.y;
		return sqrt(xx * xx + yy * yy);
	}
	lld disteq(vec2 p = vec2()) const {
		lld xx = x - p.x;
		lld yy = y - p.y;
		return xx * xx + yy * yy;
	}
};
struct vec2f {
	lf x, y;
	vec2f() { x = y = 0; }
	vec2f(lf x, lf y) :x(x), y(y) {}
	vec2f(const vec2& z) :x(z.x), y(z.y) {}
	vec2f operator +(const vec2f& z) const {
		return vec2f(x + z.x, y + z.y);
	}
	vec2f operator -(const vec2f& z) const {
		return vec2f(x - z.x, y - z.y);
	}
	vec2f operator -() const {
		return vec2f(-x, -y);
	}
	lf operator *(const vec2f& z)const {
		return x * z.x + y * z.y;
	}
	lf operator %(const vec2f& z)const {
		return x * z.y - y * z.x;
	}
	vec2f operator *(const lf z) const{
		return vec2f(x * z, y * z);
	}
	bool operator <(const vec2f& z)const {
		if (x - z.x)return x < z.x;
		return y < z.y;
	}
	bool operator ==(const vec2f &z)const{
		return (x == z.x && y == z.y);
	}
	lf dist(vec2f p = vec2f()) const {
		lf xx = x - p.x;
		lf yy = y - p.y;
		return sqrt(xx * xx + yy * yy);
	}
	lf disteq(vec2f p = vec2f()) const {
		lf xx = x - p.x;
		lf yy = y - p.y;
		return xx * xx + yy * yy;
	}
	void rotate(lf ang){
		lf xx = x * cos(ang) - y * sin(ang);
		lf yy = x * sin(ang) + y * cos(ang);
		x = xx;
		y = yy;
	}
};

template<bool allow_multi_points_in_line = false>
struct Polygon {
	struct CONVEX_MAKER_WITHOUT_ATAN2 {
		int i;
		long long int dx;
		long long int dy;
		bool friend operator <(const CONVEX_MAKER_WITHOUT_ATAN2 &p, const CONVEX_MAKER_WITHOUT_ATAN2 &q) {
			if (p.dx == 0) {
				if (q.dx == 0) {
					return p.dy < q.dy;
				}
				return false;
			}
			if (q.dx == 0)return true;
			if (p.dx * q.dy == p.dy * q.dx) {
				return p.dx < q.dx;
			}
			return p.dy * q.dx < p.dx * q.dy;
		}
	};
	vector<vec2> v;
	int n;
	void make_convex() {
		sort(v.begin(),v.end());
		v.erase(unique(v.begin(),v.end()),v.end());
		n = v.size();
		if(n<=1)return;
		int i, j, k;
		sort(v.begin(), v.end());
		int si = 0;
		vector<vec2> tv;
		vector<int> stack(n);
		vector<CONVEX_MAKER_WITHOUT_ATAN2> b(n);
		
		for (i = 1; i < n; i++) {
			b[i].i = i;
			b[i].dx = v[i].x - v[0].x;
			b[i].dy = v[i].y - v[0].y;
		}
		sort(b.begin() + 1, b.end());
		b[0].i = 0;
		if constexpr (allow_multi_points_in_line)
		{
			lld lastDx = b[n-1].dx;
			lld lastDy = b[n-1].dy;
			for(i=n-2;i>0;i--)
			{
				if(lastDx * b[i].dy != b[i].dx * lastDy)break;
			}
			reverse(b.begin()+i+1, b.end());
		}

		stack[0] = 0;
		int sp = 1;

		for (i = 1; i < n; i++) {
			int ti = b[i].i;
			while (sp >= 2) {
				const lld ccwRet = (v[stack[sp-1]] - v[stack[sp-2]])%(v[ti] - v[stack[sp-2]]);
				const bool outOfConvex = allow_multi_points_in_line ? ccwRet < 0 : ccwRet <= 0;
				if(outOfConvex)
				{
					sp--;
				}
				else{
					break;
				}
			}
			stack[sp++] = ti;
		}

		n = sp;
		tv.resize(n);
		for (i = 0; i < n; i++) {
			tv[i] = v[stack[i]];
		}
		v = tv;

		/*
		printf("%d : ", v.size());
		for (auto it : v) {
			printf("%lld,%lld ", it.x, it.y);
		}
		*/
	}
	void append_dual(){
		v.resize(2*n);
		for(int i=0;i<n;i++){
			v[i+n] = v[i];
		}
	}
};
lld ccw(vec2 p, vec2 q, vec2 r){
	lld xx = p.x*q.y + q.x*r.y + r.x*p.y;
	lld yy = p.y*q.x + q.y*r.x + r.y*p.x;
	return xx-yy;
}
//
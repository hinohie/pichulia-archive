#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2")

#include <stdio.h>

#ifndef likely
#define likely(x) __builtin_expect((x),1)
#endif
#ifndef unlikely
#define unlikely(x) __builtin_expect((x),0)
#endif

namespace
{
class FastIn {
public:
	constexpr static int BUFFER_MAX = 1048576;
	char buf[BUFFER_MAX + 1];
	int pos;
	FILE* fp;
	int pl;
	int __eof;

	// Customize yourselfs
	static inline bool isEmpty(char x){
		return x<=32;
	}

private:
	FastIn() {
		clear();
	}
	~FastIn() {
		//flush();
	}
	void clear() {
		pos = BUFFER_MAX;
		pl = BUFFER_MAX;
		fp = stdin;
		__eof = 0;
	}
	void read_buffer() {
		if (__eof)return;
		if (feof(fp)) { __eof = 1; return; }
		pl = fread(buf, sizeof(char), BUFFER_MAX, fp);
	}
	char __getchar() {
		if (pos == pl) {
			pos = 0;
			read_buffer();
			if (__eof)return -1;
		}
		return buf[pos++];
	}
	int __nextint() {
		int res = 0;
		char c;
		bool minus = false;
		do {
			c = __getchar();
			if (__eof)return 0;
			if (c == '-')minus = true;
		} while (c < '0' || c > '9');
		res = c - '0';
		while (1) {
			c = __getchar();
			if (__eof)break;
			if (c < '0' || c > '9')break;
			// special case : -2'147'483'648
			if(unlikely(minus && res == 2'147'483'64 && c == '8')) return -2'147'483'648;
			res = (res * 10) + c - '0';
		}
		return minus ? -res : res;
	}
	
	unsigned int __nextuint() {
		unsigned int res = 0;
		char c;
		do {
			c = __getchar();
			if (__eof)return 0;
		} while (c < '0' || c > '9');
		res = c - '0';
		while (1) {
			c = __getchar();
			if (__eof)break;
			if (c < '0' || c > '9')break;
			res = (res * 10) + c - '0';
		}
		return res;
	}
	
	long long int __nextlld() {
		long long int res = 0;
		char c;
		bool minus = false;
		do {
			c = __getchar();
			if (__eof)return 0;
			if (c == '-')minus = true;
		} while (c < '0' || c>'9');
		res = c - '0';
		while (1) {
			c = __getchar();
			if (__eof)break;
			if (c < '0' || c > '9')break;
			// special case : -9'223'372'036'854'775'808
			if(unlikely(minus && res == 9'223'372'036'854'775'80LL && c == '8')) return -9'223'372'036'854'775'808LL;
			res = (res * 10) + c - '0';
		}
		return minus ? -res : res;
	}
	
	unsigned long long int __nextulld() {
		unsigned long long int res = 0;
		char c;
		do {
			c = __getchar();
			if (__eof)return 0;
		} while (c < '0' || c > '9');
		res = c - '0';
		while (1) {
			c = __getchar();
			if (__eof)break;
			if (c < '0' || c > '9')break;
			res = (res * 10) + c - '0';
		}
		return res;
	}
	
	double __nextlf() {
		double res = 0;
		double base = 1;
		bool minus = false;
		char c;
		do {
			c = __getchar();
			if (__eof)return 0;
			if(c == '-'){
				minus = true;
				continue;
			}
		} while ((c < '0' || c>'9') && (c != '.'));
		bool meet_point = false;
		if(c >= '0' && c<='9')
		{
			res = c - '0';
		}
		else{
			meet_point = true;
		}
		while (1) {
			c = __getchar();
			if (__eof)break;
			if(c == '.'){
				meet_point = true;
				continue;
			}
			if(c == 'e' || c == 'E'){
				int sft = __nextint();
				while(sft != 0){
					if(sft > 0) {res *= 10; sft--;}
					if(sft < 0) {res *= 0.1; sft++;}
				}
				break;
			}
			if (c < '0' || c>'9')break;
			if(meet_point){
				base *= 0.1;
				res = res + base * (c - '0');
			}
			else{
				res = (res * 10) + c - '0';
			}
		}
		return minus ? -res : res;
	}

	int __nextstring(char* x) {
		int i = 0;
		char c;
		do {
			c = __getchar();
			if (__eof)return 0;
		} while (isEmpty(c));
		x[i++] = c;
		while (1) {
			c = __getchar();
			if (__eof)break;
			if (isEmpty(c))break;
			x[i++] = c;
		}
		x[i] = 0;
		return i;
	}

public:
	static FastIn& Get() {
		static FastIn instance;
		return instance;
	}
	static void setfp(FILE* _fp) {
		Get().fp = _fp;
	}
	static bool eof() {
		return Get().__eof;
	}
	static char getchar() {
		return Get().__getchar();
	}
	static int nextint() {
		return Get().__nextint();
	}
	static unsigned int nextuint() {
		return Get().__nextuint();
	}
	static long long int nextlld() {
		return Get().__nextlld();
	}
	static unsigned long long int nextulld() {
		return Get().__nextulld();
	}
	static double nextlf() {
		return Get().__nextlf();
	}
	static int nextstring(char* x) {
		return Get().__nextstring(x);
	}
};

class FastOut {
public:
	constexpr static int BUFFER_MAX = 1048576;
	char buf[BUFFER_MAX + 1];
	int pos;
	FILE* fp;
	
	// Customize yourselfs
	static inline bool isEmpty(char x){
		return x<=32;
	}

private:
	FastOut() {
		clear();
	}
	~FastOut() {
		flush();
	}
	void clear() {
		pos = 0;
		fp = stdout;
	}
	void flush() {
		if (pos > 0) {
			fwrite(buf, 1, pos, fp);
			pos = 0;
		}
	}
	void __putchar(char x) {
		if (pos == BUFFER_MAX) {
			flush();
		}
		buf[pos++] = x;
	}
	void __nextint(int x, char eow = ' ') {
		if(unlikely(x == -2'147'483'648)){
			// Special case.
			// print 2,147,483,648
			__putchar('-');
			__putchar('2');
			__putchar('1');__putchar('4');__putchar('7');
			__putchar('4');__putchar('8');__putchar('3');
			__putchar('6');__putchar('4');__putchar('8');
			__putchar(eow);
			return;
		}
		if (x < 0) {
			__putchar('-');
			x = -x;
		}
		if (x == 0) {
			__putchar('0');
		}
		else {
			char xx[20];
			int xl = 0;
			while (x > 0) {
				xx[xl++] = x % 10 + '0';
				x /= 10;
			}
			while (xl--) {
				__putchar(xx[xl]);
			}
		}
		if (eow > 0)
			__putchar(eow);
	}
	void __nextuint(unsigned int x, char eow = ' ') {
		if (x == 0) {
			__putchar('0');
		}
		else {
			char xx[20];
			int xl = 0;
			while (x > 0) {
				xx[xl++] = x % 10 + '0';
				x /= 10;
			}
			while (xl--) {
				__putchar(xx[xl]);
			}
		}
		if (eow > 0)
			__putchar(eow);
	}
	void __nextlld(long long int x, char eow = ' ') {
		if(unlikely(x == -9'223'372'036'854'775'808LL)){
			// Special case.
			// print 9,223,372,036,854,775,808
			__putchar('-');
			__putchar('9');
			__putchar('2');__putchar('2');__putchar('3');
			__putchar('3');__putchar('7');__putchar('2');
			__putchar('0');__putchar('3');__putchar('6');
			__putchar('8');__putchar('5');__putchar('4');
			__putchar('7');__putchar('7');__putchar('5');
			__putchar('8');__putchar('0');__putchar('8');
			__putchar(eow);
			return;
		}
		if (x < 0) {
			__putchar('-');
			x = -x;
		}
		if (x == 0) {
			__putchar('0');
		}
		else {
			char xx[20];
			int xl = 0;
			while (x > 0) {
				xx[xl++] = x % 10 + '0';
				x /= 10;
			}
			while (xl--) {
				__putchar(xx[xl]);
			}
		}
		if (eow > 0)
			__putchar(eow);
	}
	
	void __nextulld(unsigned long long int x, char eow = ' ') {
		if (x == 0) {
			__putchar('0');
		}
		else {
			char xx[20];
			int xl = 0;
			while (x > 0) {
				xx[xl++] = x % 10 + '0';
				x /= 10;
			}
			while (xl--) {
				__putchar(xx[xl]);
			}
		}
		if (eow > 0)
			__putchar(eow);
	}
	void __nextlf(double x, char eow = ' ', int xl = 9)
	{
		// print double value until under xl.
		// xl's point should be round up
		// Since we cannot print directly, store it on temperal list
		char* tmp = new char[xl + 40];
		int i = 0;
		int xcnt = 0;
		int pi = -1;
		bool minus = false;
		bool carry_one = false;
		if(x < 0){
			minus = true;
			x = -x;
		}
		long long int ix = static_cast<long long int>(x);
		while(ix>0&&ix>x)ix--;
		x-=ix;
		if(ix == 0){
			tmp[i++] = '0';
			pi = i;
		}
		else{
			while(ix>0){
				tmp[i++] = (ix%10)+'0';
				ix/=10;
			}
			//reverse
			for(int j=0;j<i-j;j++){
				char tt=tmp[j];
				tmp[j]=tmp[i-j-1];
				tmp[i-j-1]=tt;
			}
			pi = i;
		}
		while(xcnt < xl)
		{
			xcnt++;
			x *= 10;
			int txi = static_cast<int>(x);
			if(txi > 0 && txi > x) txi--;
			tmp[i++] = txi + '0';
			tmp[i] = 0;
			x -= txi;
		}
		// round up
		{
			x *= 10;
			int txi = static_cast<int>(x);
			if(txi > 0 && txi > x) txi--;
			if((!minus && txi >= 5) || (minus && x > 5))
			{
				tmp[i-1]++;
				for(int j=i-1;j>=0;j--){
					if(tmp[j] > '9'){
						if(j==0){carry_one = true;}
						else{
							tmp[j-1] += (tmp[j] - '0')/10;
						}
						tmp[j] -= 10;
					}
				}
			}
		}
		if(minus) __putchar('-');
		if(carry_one) __putchar('1');
		if(pi == i){
			__nextstring(tmp, eow, i);
		}
		else{
			__nextstring(tmp, '.', pi);
			__nextstring(tmp+pi, eow, i-pi);
		}

		// dealloc
		delete[] tmp;
	}
	void __nextstring(char* x, char eow = ' ', int xl = -1)
	{
		for(int i=0; (xl >= 0 && i < xl) || (xl < 0 && !isEmpty(x[i])); i++)
		{
			__putchar(x[i]);
		}
		if (eow > 0)
			__putchar(eow);
	}

public:
	static FastOut& Get(){
		static FastOut instance;
		return instance;
	}
	static void setfp(FILE* _fp) {
		Get().fp = _fp;
	}
	static void putchar(char c)
	{
		Get().__putchar(c);
	}
	static void nextint(int x, char eow = ' ')
	{
		Get().__nextint(x, eow);
	}
	static void nextuint(unsigned int x, char eow = ' ')
	{
		Get().__nextuint(x, eow);
	}
	static void nextlld(long long int x, char eow = ' ')
	{
		Get().__nextlld(x, eow);
	}
	static void nextulld(unsigned long long int x, char eow = ' ')
	{
		Get().__nextulld(x, eow);
	}
	static void nextlf(double x, char eow = ' ', int xl = 9)
	{
		Get().__nextlf(x, eow, xl);
	}
	static void nextstring(char* x, char eow = ' ', int xl = -1)
	{
		Get().__nextstring(x, eow, xl);
	}
};
}